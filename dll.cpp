#include "dll.h"
#include "frame.h"
#include "serial.h"
#include "animpos.h"
#include <wx/listctrl.h>
#include "NaviDisplaySignals.h"
#include "tools.h"

wxMutex mutex;
CMapPlugin::CMapPlugin(CNaviBroker *NaviBroker):CNaviMapIOApi(NaviBroker)
{
	GpsX = GpsY = _X = _Y = _UX = _UY = GPS_OUT_OF_COORDS;
	DisplaySignal = new CDisplaySignal(NDS_GPS);
	nmea_zero_INFO(&NmeaInfo);
	IsWorking = true;
	FileConfig = NULL;
    _ShowHint = false;
    IsData = false;
    NeedExit = false;
    _MouseOverIcon = false;
    _LineBufLen = 0;
    memset(_LineBuffer,0,BUFFER_LENGTH);
    Broker = NaviBroker;
    CircleRadius = 0;
    BuildGeometry();
	_Exit = false;
	MySerial = NULL;
	AnimMarkerSize = 5.0f;
	TexturesCreated = false;
	CreateSumbols();
	CreateApiMenu();
	Track = new CTrack();
//	TrackList = new CTrackList();
//	TrackList->AddTrack(Track);
	GetBroker()->StartAnimation(true, GetBroker()->GetParentPtr());

	// MAX function name 32
	AddExecuteFunction("gps_SetExit", SetExit);
	AddExecuteFunction("gps_SetNMEAInfo",SetNMEAInfo);
	AddExecuteFunction("gps_SetLog",SetLog);
	AddExecuteFunction("gps_SetPort",SetPort);
	AddExecuteFunction("gps_SetBaud",SetBaud);
}

CMapPlugin::~CMapPlugin()
{
	delete DisplaySignal;
//	delete Track;
//	delete TrackList;
	MyFrame = NULL;
	MySerial = NULL;
}

bool CMapPlugin::GetIsWorking()
{
	return IsWorking;
}

CTrackList *CMapPlugin::GetTrackList()
{
	return TrackList;
}

void CMapPlugin::WriteConfig()
{
	FileConfig = new wxFileConfig(_("gps"),wxEmptyString,ConfigPath,wxEmptyString);
	FileConfig->Write(_(KEY_PORT_INDEX),MySerial->GetPortIndex());
	FileConfig->Write(_(KEY_BAUD_INDEX),MySerial->GetBaudIndex());
	delete FileConfig;
}

void CMapPlugin::CreateSumbols(void) 
{

	TMemoryBlock AnimMarker;

	AnimMarker.Ptr = animpos;
	AnimMarker.Size = animpos_size;
	TextureAnimMarker = LoadFromMemoryBlockTGA( &AnimMarker );
}

void CMapPlugin::CreateTexture(TTexture *Texture, GLuint *TextureID) 
{

	glGenTextures(1, TextureID );
	glBindTexture(GL_TEXTURE_2D, *TextureID );
	glTexImage2D(GL_TEXTURE_2D, 0, Texture->Bpp / 8, Texture->Width, Texture->Height, 0, Texture->Type, GL_UNSIGNED_BYTE, Texture->Data );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	FreeTexture( Texture );
}

CMySerial *CMapPlugin::GetMySerial()
{
	return MySerial;
}

void CMapPlugin::CreateTextures(void) 
{
	
	CreateTexture( TextureAnimMarker,  &AnimMarkerID );
	TexturesCreated = true;
}


wxFileConfig *CMapPlugin::GetFileConfig()
{
    return FileConfig;
}

CNaviBroker *CMapPlugin::GetBroker()
{
    return Broker;
}

void CMapPlugin::Run(void *Params)
{
    
    MyFrame = NULL;
    MySerial = new CMySerial(Broker);
	    
    int	baud = MySerial->GetBaudRate();
	ConfigPath = wxString::Format(wxT("%s%s"),GetWorkDir().wc_str(),_(PLUGIN_CONFIG_FILE));
	FileConfig = new wxFileConfig(_("gps"),wxEmptyString,ConfigPath,wxEmptyString);
	
    int port_index;
	FileConfig->Read(_(KEY_PORT_INDEX), &port_index);
	MySerial->SetPortIndex(port_index);

	int baud_index;
	FileConfig->Read(_(KEY_BAUD_INDEX), &baud_index);
	MySerial->SetBaudIndex(baud_index);

    MySerial->Start();


}

void CMapPlugin::SetShowHint(bool show)
{
    _ShowHint = show;
}

void CMapPlugin::Kill(void)
{

	IsWorking = false;
	NeedExit = true;
   
    if(MySerial != NULL)
		MySerial->Stop();	// stop the serial port thread
	
	
	while(!_Exit)
	{	
		Sleep(500);
	}
    
    if(FileConfig !=NULL)
        delete FileConfig;
	
	// before myserial delete
	WriteConfig();
	if(MySerial != NULL)
		delete MySerial;
	
	MySerial = NULL;
	SendDisplaySignal(NULL);

}

/*
void CMapPlugin::SetValids(bool valid)
{
	DisplaySignal->SetData((void*)DisplaySignal,sizeof(DisplaySignal));
	GetBroker()->SendDisplaySignal((void*)DisplaySignal);
	    
	bool *Valids = GetBroker()->GetValids();
    Valids[X_VALUE] = valid;
    Valids[Y_VALUE] = valid;
    Valids[AREA_MINX] = valid;
    Valids[AREA_MINY] = valid;
    Valids[AREA_MAXX] = valid;
    Valids[AREA_MAXY] = valid;
}

*/

bool CMapPlugin::GetNeedExit(void)
{
    return NeedExit;
}

void CMapPlugin::CreateApiMenu(void) 
{

	NaviApiMenu = new CNaviApiMenu( L"Settings" );	// nie u¿uwaæ delete - klasa zwalnia obiejt automatycznie
	NaviApiMenu->AddItem( L"GPS",this, MenuConfig );
	
}

void *CMapPlugin::MenuConfig(void *NaviMapIOApiPtr, void *Input) 
{

	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Config();

	return NULL;
}

void CMapPlugin::Config()
{

#if defined(_WIN32) || defined(_WIN64)
	MyFrame = new CMyFrame(this);
    MyFrame->ShowModal();
    MyFrame->Close();
	MyFrame = NULL;
#endif
#if defined (_LINUX32) || defined(_LINUX64)
    MyFrame = new CMyFrame();
    MyFrame->ShowModal();
    MyFrame->Close();
	MyFrame = NULL;
#endif

}

void *CMapPlugin::SetExit(void *NaviMapIOApiPtr, void *Params)
{
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->SetExitFunc((bool)Params);
		
	return NULL;
}

void CMapPlugin::SetExitFunc(bool exit)
{
	_Exit = exit;
}


void *CMapPlugin::SetNMEAInfo(void *NaviMapIOApiPtr, void *Params)
{

	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->SetNMEAInfoFunc((nmeaINFO*)Params);
		
	return NULL;
}

void CMapPlugin::SetNMEAInfoFunc(nmeaINFO *_nmea)
{
	NmeaInfo = *_nmea;
	SendDisplaySignal(this);
	
	if(NmeaInfo.sig == 0)
		return;
	
	_X = NmeaInfo.lon / 100;
	_Y = NmeaInfo.lat / 100;
    _Y = _Y * (-1);
	Broker->Unproject(_X,_Y, &GpsX,&GpsY);
	AddPoint(GpsX,GpsY,_nmea);
	Broker->Refresh(Broker->GetParentPtr());
	
}

void CMapPlugin::SendDisplaySignal(CMapPlugin *MapPlugin)
{
	DisplaySignal->SetData((void*)MapPlugin,sizeof(MapPlugin));
	GetBroker()->SendDisplaySignal((void*)DisplaySignal);
}

nmeaINFO CMapPlugin::GetNmeaINFO()
{
	return NmeaInfo;
}

void *CMapPlugin::SetLog(void *NaviMapIOApiPtr, void *Params)
{

	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->SetLogFunc((char*)Params);
		
	return NULL;
}

void CMapPlugin::SetLogFunc(char *text) 
{
	if(MyFrame == NULL)
		return;
	
	wxString buffer(text,wxConvUTF8,4096);
	MyFrame->SetLogEvent(buffer);
	
}

void *CMapPlugin::SetPort(void *NaviMapIOApiPtr, void *Params)
{

	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->SetPortFunc((char*)Params);
		
	return NULL;
}

void CMapPlugin::SetPortFunc(char *port) 
{
	if(MyFrame == NULL)
		return;
	
	wxString buffer(port,wxConvUTF8);
	MyFrame->SetPortEvent(buffer);
	
}

void *CMapPlugin::SetBaud(void *NaviMapIOApiPtr, void *Params)
{

	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->SetBaudFunc((int)Params);
		
	return NULL;
}

void CMapPlugin::SetBaudFunc(int baud) 
{
	if(MyFrame == NULL)
		return;
	
	MyFrame->SetBaudEvent(wxString::Format(_("%d"),baud));
	
}




void CMapPlugin::BuildGeometry()
{
    // first circle
    SPoint Points;
    float Radius = 0.2f;
    CircleRadius = Radius;
    for(int i=0; i<360; i+=6)
    {
        Points.x = Radius*(float)sin(i*PI/180.0);
        Points.y = Radius*(float)cos(i*PI/180.0);
        vCircle1.push_back(Points);
    }

    // second circle
    Radius = 0.08f;
    for(int i=0; i<360; i+=6)
    {
        Points.x = Radius*(float)sin(i*PI/180.0);
        Points.y = Radius*(float)cos(i*PI/180.0);
        vCircle2.push_back(Points);
    }

	// second circle
    Radius = 1.0f;
    for(int i=0; i<360; i+=6)
    {
        Points.x = Radius*(float)sin(i*PI/180.0);
        Points.y = Radius*(float)cos(i*PI/180.0);
        vCircle3.push_back(Points);
    }


    // line H
    Points.x = -0.3;	Points.y =	0.0;    vLineH.push_back(Points);
    Points.x = 0.3;		Points.y =	0.0;    vLineH.push_back(Points);
    //line V
    Points.x = 0.0;		Points.y =	0.3;	vLineH.push_back(Points);
    Points.x = 0.0;		Points.y =	-1.0;   vLineH.push_back(Points);
	// bok
	Points.x = 0.0;		Points.y = -1.0;	vLineH.push_back(Points);
	Points.x = 0.3;		Points.y = 0.0;		vLineH.push_back(Points);
	// bok
	Points.x = 0.0;		Points.y = -1.0;	vLineH.push_back(Points);
	Points.x = -0.3;	Points.y = 0.0;		vLineH.push_back(Points);
	// end
    Points.x = -0.3;    Points.y =	0.3;    vLineH.push_back(Points);
    Points.x = 0.3;		Points.y =	0.3;    vLineH.push_back(Points);
	// end1
	Points.x = -0.2;    Points.y =	0.5;    vLineH.push_back(Points);
    Points.x = 0.2;		Points.y =	0.5;    vLineH.push_back(Points);


}

void CMapPlugin::RenderGeometry(GLenum Mode,GLvoid* RawData,size_t DataLength)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_DOUBLE, 0, RawData);
    glDrawArrays(Mode, 0, DataLength);
    glDisableClientState(GL_VERTEX_ARRAY);
}

bool CMapPlugin::IsPointInsideBox(double px, double py, double bx1, double by1, double bx2, double by2) 
{
	if( ((px > bx1) && (px < bx2)) && ((py > by1) && (py < by2)) )
		return true;
	else
		return false;

}


void CMapPlugin::Mouse(int x, int y, bool lmb, bool mmb, bool rmb)
{

	double mom[2];
	double _x,_y;
	
	Broker->GetMouseOM(mom);
	Broker->Unproject(mom[0],mom[1],&_x,&_y);
	_y = _y *-1;
	
	double MapX = _x;
	double MapY = _y;
	
	if(rmb)
		return;

	std::vector<SPoint>::iterator pt;
	std::vector<SPoint>::iterator it;

	
	//CTrack *trk = TrackList->GetList()[0];
	//pt = trk->GetTrackPoints().end();
	//it = trk->GetTrackPoints().begin();
	/*
	while(it != pt)
	{
		//if(IsPointInsideBox(_x, _y, it->x - Translation, it->y - Translation, it->x + RectWidth-Translation , it->y + RectHeight-Translation))
		if(IsPointInsideBox(_x, _y, it->x , it->y , it->x , it->y))
		{
			if(SelectedPtr == &*it)
				SelectedPtr = NULL;
			else
				SelectedPtr =  &*it;
			return;
		}
		
			it++;
	}
	*/
	
//	double mom[4];
//  float xs, ys;
//  double _x, _y;
//  float scale = Broker->GetMapScale();
//  xs = _X; ys = _Y;						// srodek ko³a
//  float r = CircleRadius;                 // promieñ
//   GetBroker()->GetMouseOM(mom);
//   _y = mom[1] ; _x = mom[0];

//  float left = (((_x-xs)*(_x-xs) + (_y-ys)*(_y-ys)));
//  float right = (r*r);

//  if(left <= right)
//  {
//    	_MouseOverIcon = true;
//  }else{
//    	_MouseOverIcon = false;
//    }

}

void CMapPlugin::AddPoint(double x, double y, nmeaINFO *info)
{

#ifdef BUILD_GPS_POINTS_VECTOR
	Track->AddPoint(x,y);
	Track->AddPointInfo(x,y,info);
#endif

}
double CMapPlugin::GetGpsX()
{
	return _X;
}

double CMapPlugin::GetGpsY()
{
	return _Y;
}

void CMapPlugin::RenderTracks()
{
	glEnable(GL_POINT_SMOOTH);
	
	std::vector<CTrack*> Tracks = TrackList->GetList();
	
	for(int i = 0; i < Tracks.size() ;i++)
	{
		glColor4f(1.0f,0.0f,0.0f,0.5f);
		glPointSize(15.0f);
		
		std::vector<SPoint> pts = Tracks[i]->GetTrackPoints();
		if(pts.size() > 0)
			RenderGeometry(GL_LINE_LOOP,&pts[0], pts.size());			// punkty z gpsa
    }
	
	glDisable(GL_POINT_SMOOTH);

}

void CMapPlugin::RenderSelection()
{
	/*
	// render selection on basemap
    // wtedy kiedy okno konfiguracji jest widoczne
    double *val = GetBroker()->GetValues();
    minX = val[6];
    minY = val[7];
    maxX = val[8];
    maxY = val[9];

	if(MyFrame != NULL && _nmeaINFO.fix > 0 && _ShowHint)
    {
        glColor4f(0.0f,0.0f,1.0f,0.4f);
        glBegin(GL_QUADS);
        glColor4f(0.0f,0.0f,1.0f,0.4f);
        glVertex2d(minX,minY*-1);
        glVertex2d(minX,maxY*-1);
        glVertex2d(maxX,maxY*-1);
        glVertex2d(maxX,minY*-1);
        glEnd();
    }

	*/
}

void CMapPlugin::RenderPosition()
{
		
	double x,y;
    x = _UX;
    y = _UY;
	
	if(GpsX == GPS_OUT_OF_COORDS || GpsY == GPS_OUT_OF_COORDS)
		return;
		
		
	glColor4f(0.0f,0.0f,1.0f,0.8f);

	if(_MouseOverIcon)
        glColor4f(1.0f,1.0f,1.0f,0.8f);

	glPushMatrix();
		glTranslated(GpsX,GpsY,0.0);
		glScalef(50.0/Scale,50.0/Scale,0.0f);
		glRotatef(NmeaInfo.direction,0.0f,0.0f,1.0f);
		RenderGeometry(GL_LINE_LOOP,&vCircle1[0],vCircle1.size());	// circle 0
		RenderGeometry(GL_LINE_LOOP,&vCircle2[0],vCircle2.size());  // circle 1
		RenderGeometry(GL_LINE_LOOP,&vCircle3[0],vCircle3.size());  // circle 1
		RenderGeometry(GL_LINES,&vLineH[0],vLineH.size());			// line H
    glPopMatrix();

}

void CMapPlugin::RenderAnimation()
{
	double Factor = 500.0;
		
	if( GetBroker()->GetMapScale() > Factor )
		SmoothScaleFactor = GetBroker()->GetMapScale();
	else
		SmoothScaleFactor = Factor;
	float MarkerSize = AnimMarkerSize / SmoothScaleFactor * 0.2f;
	
	// animation
	if(NmeaInfo.sig == 0)         
		glColor4ub( 255, 0, 0, 255 - ((AnimMarkerSize / 1000.0f) * 255) );
	else
		glColor4ub( 0, 0, 255, 255 - ((AnimMarkerSize / 1000.0f) * 255) );
		
	
	glEnable(GL_TEXTURE_2D);
		glBindTexture( GL_TEXTURE_2D, AnimMarkerID );
		glPushMatrix();
		glTranslated(GpsX,GpsY,0.0);
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex2f( -(MarkerSize), -(MarkerSize) );
			glTexCoord2f(0.0f, 0.0f); glVertex2f( MarkerSize, -(MarkerSize));
			glTexCoord2f(0.0f, 1.0f); glVertex2f( MarkerSize, MarkerSize );
			glTexCoord2f(1.0f, 1.0f); glVertex2f( -(MarkerSize), MarkerSize );
		glEnd();
		glPopMatrix();
	glDisable(GL_TEXTURE_2D);	
		
	AnimMarkerSize += 10.0f;
	if( AnimMarkerSize > 500.0f )
		AnimMarkerSize = 100.0f;

}

void CMapPlugin::Render(void)
{
	
	if( GetNeedExit())
        return;
	
	
	Scale = Broker->GetMapScale();
		
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
		
	if( !TexturesCreated )
		CreateTextures();
	    
	RenderPosition();
    RenderSelection();
	RenderAnimation();	
		
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);


}



//	 API dla DLL
void NAVIMAPAPI *CreateNaviClassInstance(CNaviBroker *NaviBroker)
{
   CMapPlugin *DLL = new CMapPlugin(NaviBroker);
    return (void*) ( DLL );
}

const NAVIMAPAPI wchar_t *NaviPluginDescription(int LangID)
{
#if defined(_WIN32) || defined(_WIN64)
    return TEXT("GPS plugin automatic port detection.");
#endif
#if defined(_LINUX32) || defined(_LINUX64)
    return L"GPS plugin automatic port detection.";
#endif
}

const NAVIMAPAPI wchar_t *NaviPluginIntroduce(int LangID)
{
#if defined(_WIN32) || defined(_WIN64)
    return TEXT("GPS");
#endif
#if defined(_LINUX32) || defined(_LINUX64)
    return L"GPS";
#endif
}

int NAVIMAPAPI GetNaviPluginType(void)
{
    return MAP_PLUGIN_RUN_ON_DEMAND;
}
#if defined(_WIN32) || defined(_WIN64)
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
    return 1;
}
#endif
void NAVIMAPAPI FreeNaviClassInstance(void *ptr)
{
	delete (CMapPlugin*)ptr;
	_CrtDumpMemoryLeaks();
}

