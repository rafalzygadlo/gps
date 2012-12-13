#include "dll.h"
#include "frame.h"
#include "serial.h"
#include "animpos.h"
#include <wx/listctrl.h>
#include "NaviDisplaySignals.h"
#include "tools.h"


unsigned char pib[] = 
{
0x28,0x0,0x0,0x0,0x59,0x17,0xc6,0xfc,0x39,0xe9,0xac,0x2b,0x42,0xa7,0x5f,0xb3,0xc2,0xbc,0x90,0xb7,0x15,0x29,0x3a,0x6,0x4d,0x2c,0x98,0x54,0xa0,0x69,0xce,0x16,0xfb,0x4f,
0x91,0x0,0x3f,0xc4,0x56,0x15,0xcd,0x73,0x89,0x28,0xe9,0x54,0xc3,0x1a,0x85,0xd2,0xa8,0x9e,0x5b,0x50,0xe0,0xc0,0x40,0x54,0x73,0x61,0x13,0x58,0x9f,0x4b,0x6,0x4f,0x33,0xa3,
0x12,0x9,0x92,0xf1,0xc1,0xb4,0xa1,0x8,0x11,0x29,0x85,0x8e,0xd,0xe9,0x25,0x54,0xc9,0x75,0xda,0xe9,0xfe,0x66,0xc3,0x8c,0x8f,0x3e,0xce,0xd3,0xbf,0x77,0xd4,0x98,0x19,0x9b,
0xd0,0x4f,0x3,0xb7,0xa4,0x35,0x8a,0xef,0xbf,0xab,0xf8,0x6c,0x2e,0xd4,0x14,0x7e,0xa,0xd9,0xf8,0x1c,0xa4,0x4b,0x92,0xe0,0x9a,0x21,0x69,0x5e,0x23,0x2b,0xec,0x8b,0x14,0x35,
0xb1,0xc6,0x3e,0xcb,0x16,0xfc,0x1,0x1,0x1a,0x9,0xf4,0xc4,0xcc,0x53,0x3f,0x78,0x78,0x2f,0x99,0x4d,0xf3,0x12,0x92,0x7a,0x48,0x1c,0xd0,0xc5,0x1e,0x60,0xef,0x4,0x8e,0x4b,
0x9b,0xc7,0x1,0xbe,0x78,0x66,0x1,0x10,0xe,0x8e,0x23,0x53,0x4e,0x98,0xc8,0x67,0x38,0x74,0x32,0xfe,0xcc,0x58,0xf1,0xf6,0x62,0x39,0x1,0xc0,0xf,0x7b,0x6f,0x65,0xe,0xae,
0x5d,0xac,0x1b,0x19,0x27,0xe4,0x96,0x38,0x87,0x32,0x10,0xa3,0xa9,0xa1,0x73,0x1d,0x23,0x3e,0x34,0x6d,0xfd,0x91,0xe3,0x2f,0x6c,0xe7,0x33,0x87,0xf7,0x26,0xfe,0xb,0x61,0x8f,
0x23,0xa1,0xa6,0x5f,0x29,0x70,0x5,0xaa,0xf3,0x6a,0x4b,0xb3,0xba,0xae,0xf3,0xa5,0x78,0x3,0xbb,0xfe,0xf8,0x33,0x76,0x9f,0xb,0x90,0x71,0x22,0xd7,0x72,0xfc,0x32,0xfb,0xdb,
0x89,0x18,0xc9,0x19,0x10,0x60,0x66,0x3c,0x88,0x4f,0xd9,0x44,0xab,0x48,0xed,0xd0,0xb3,0xf3,0x4b,0xab,0x30,0x87,0x3d,0xb2,0x85,0xa3,0xfe,0x13,0xbe,0xe3,0x7c,0x2f,0x50,0xce,
0x8c,0x11,0xa0,0xa9,0x93,0x9c,0xf6,0xa0,0x34,0xf3,0x3,0xf5,0x23,0x44,0xa7,0x2,0xb6,0xca,0x5a,0x76,0x9e,0x62,0x61,0x49,0x3a,0x61,0xe7,0x76,0xca,0xa1,0x34,0x5f,0xfd,0x91,
0x34,0xd0,0x1d,0xa6,0x73,0xeb,0x20,0x53,0x18,0x8,0x8c,0xa9,0x83,0x3d,0x28,0xbc,0x30,0x4a,0xc7,0x9a,0x31,0x48,0x0,0x17,0x90,0xf2,0x4c,0x21,0x30,0x7c,0x1d,0x16,0x7c,0x52,
0xed,0xcb,0xdd,0xa,0x9f,0x1e,0x82,0x75,0xcd,0xf7,0xba,0xbb,0xdb,0xb,0x6f,0xa6,0xe1,0xfd,0xfa,0x39,0xa1,0x23,0x2f,0x48,0x3c,0xfc,0x44,0xa0,0x80,0x45,0x75,0xe7,0x8a,0xcb,
0x61,0x42,0xce,0x65,0xcc,0x52,0xbc,0xc4,0x5a,0x9b,0x2e,0x93,0xcb,0xc8,0xd3,0x87,0x6,0x73,0x9d,0x38,0x28,0xd8,0x38,0xac,0x66,0x33,0xa8,0x3,0x4e,0x2b,0x34,0x69,0xd9,0xcd,
0xf7,0x3f,0x24,0x7e,0xa9,0x35,0xeb,0xb7,0xf6,0x6a,0x1b,0xac,0x53,0x6c,0x2e,0xff,0x40,0x41,0xc5,0xe,0xb9,0x3,0x8d,0xb0,0xc4,0x62,0xa6,0x62,0x97,0x2e,0x18,0xdb,0x70,0xb3,
0xe2,0x16,0x6d,0xa,0x32,0xcf,0x44,0xcb,0xa6,0x5d,0x26,0xdf,0x16,0x86,0x92,0xf8,0x3c,0x16,0x73,0x94,0x1,0xf1,0xf5,0x71,0xbb,0x90,0x4f,0x30,0x58,0x68,0x20,0xfa,0x7d,0x2e,
0x2f,0x3d,0x61,0xfb,0xc8,0x18
};

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
	TrackList = new CTrackList();
	TrackList->AddTrack(Track);
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
	delete Track;
	delete TrackList;
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
//	FileConfig->Write(_(KEY_PORT_INDEX),MySerial->GetPortIndex());
//	FileConfig->Write(_(KEY_BAUD_INDEX),MySerial->GetBaudIndex());
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
    fprintf(stderr,"Loading GPS plugin.");
    MyFrame = NULL;
    MySerial = new CMySerial(Broker);
	    
    int	baud = MySerial->GetBaudRate();
	ConfigPath = wxString::Format(wxT("%s%s"),GetWorkDir().wc_str(),_(PLUGIN_CONFIG_FILE));
	FileConfig = new wxFileConfig(_("gps"),wxEmptyString,ConfigPath,wxEmptyString);
	
    int port_index;
	FileConfig->Read(_(KEY_PORT_INDEX), &port_index);
	MySerial->SetPort("COM1");

	int baud_index;
	FileConfig->Read(_(KEY_BAUD_INDEX), &baud_index);
	MySerial->SetBaud(4800);

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
	
	GpsX = _X = NmeaInfo.lon;
	GpsY = _Y = NmeaInfo.lat;
   
	_X = DD(_X);
	_Y = DD(_Y);
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

	// third circle
    Radius = 1.0f;
	CircleRadius = Radius;
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
	
	momX = mom[0];
	momY = mom[1];
	
	Broker->Unproject(mom[0],mom[1],&_x,&_y);
	_y = _y *-1;
	
	MouseX = _x;
	MouseY = _y;
	
	
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
	
	if(lmb)
	{
		double xs, ys;
		double _x,_y;
		xs = GpsX; ys = GpsY;					// srodek ko³a
		double r = CircleRadius * (50/Scale);   // promieñ
		_y = MouseY  ; _x = MouseX;

		double left = (((_x-xs)*(_x-xs) + (_y-ys)*(_y-ys)));
		double right = r * r;

		if(left < right)
			_MouseOverIcon = true;
		else
    		_MouseOverIcon = false;
		
	}

}

void CMapPlugin::MouseDBLClick(int x, int y)
{
	if(_MouseOverIcon)
		Config();
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
		{
			RenderGeometry(GL_POINTS,&pts[0], pts.size());			// punkty z gpsa
			RenderGeometry(GL_LINE_LOOP,&pts[0], pts.size());			// linie
		}
    }
	
	glDisable(GL_POINT_SMOOTH);

}


void CMapPlugin::RenderSelection()
{

	glPushMatrix();
		glTranslated(GpsX,GpsY,0.0);
		glScalef(50.0/Scale,50.0/Scale,0.0f);
		glRotatef(NmeaInfo.direction,0.0f,0.0f,1.0f);
		glBegin(GL_QUADS);
			glVertex2f(vCircle3[ 0].x,vCircle3[ 0].y);
			glVertex2f(vCircle3[15].x,vCircle3[15].y);
			glVertex2f(vCircle3[30].x,vCircle3[30].y);
			glVertex2f(vCircle3[45].x,vCircle3[45].y);
		glEnd();
    glPopMatrix();

}

void CMapPlugin::RenderPosition()
{
		
	double x,y;
    x = _UX;
    y = _UY;
	
	if(GpsX == GPS_OUT_OF_COORDS || GpsY == GPS_OUT_OF_COORDS)
		return;
		
		
	glColor4f(0.0f,0.0f,1.0f,0.5f);
	glPushMatrix();
		glLineWidth(2);
		glTranslated(GpsX,GpsY,0.0);
		glScalef(50.0/Scale,50.0/Scale,0.0f);
		glRotatef(NmeaInfo.direction,0.0f,0.0f,1.0f);
		RenderGeometry(GL_LINE_LOOP,&vCircle1[0],vCircle1.size());	// circle 0
		RenderGeometry(GL_LINE_LOOP,&vCircle2[0],vCircle2.size());  // circle 1
		RenderGeometry(GL_LINE_LOOP,&vCircle3[0],vCircle3.size());  // circle 1
		RenderGeometry(GL_LINES,&vLineH[0],vLineH.size());			// line H
		glLineWidth(1);
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
void CMapPlugin::RenderMouseXY()
{
	glPointSize(10);
	glColor3f(1.0,0.0,0.0);
	
	glBegin(GL_POINTS);
		glVertex2d(MouseX,MouseY);
	glEnd();
	
	glPointSize(1);
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
    
	if(_MouseOverIcon)
		RenderSelection();
        
	RenderAnimation();	
	RenderMouseXY();
	RenderTracks();
		
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

unsigned char *GetNaviPluginInfoBlock()
{
	return pib;
}

void NAVIMAPAPI FreeNaviClassInstance(void *ptr)
{
	delete (CMapPlugin*)ptr;
	_CrtDumpMemoryLeaks();
}

