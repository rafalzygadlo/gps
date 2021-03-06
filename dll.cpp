#include "dll.h"
#include "frame.h"
#include "serial.h"
#include "animpos.h"
#include <wx/listctrl.h>
#include "NaviDisplaySignals.h"
#include "tools.h"
#include "boat.h"
#include "status.h"
#include "unitconfig.h"
#include "boatconfig.h"
#include "GeometryTools.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

unsigned char PluginInfoBlock[] = {
0x39,0x0,0x0,0x0,0x4c,0x23,0xc8,0xc1,0xb0,0x7d,0x9,0x9b,0x41,0xf3,0x21,0x4d,0x1d,0x24,0x60,0x76,0x4c,0xd0,0x9b,0x5b,0xe6,0xc1,0xda,0xad,0x8c,0x1e,0x4a,0xa5,0xad,0xb7,
0x1e,0x39,0x3e,0x54,0xc5,0x39,0x62,0x97,0x9c,0xd9,0x77,0x6e,0x83,0x8f,0xe,0x4d,0x9a,0xa2,0xc0,0xa8,0x66,0x78,0x10,0xa,0x83,0x65,0x9e,0xce,0x4b,0xef,0x31,0x2e,0xca,0xa2,
0x6,0xd5,0xa4,0xfe,0x3e,0x82,0x8a,0x92,0x11,0xe6,0x2e,0xcf,0xcb,0xa1,0x14,0xa1,0x46,0x62,0xbc,0x20,0xff,0xd3,0x3,0x2a,0xce,0x4b,0x52,0xb6,0xdc,0x0,0xf8,0xe0,0xad,0xd1,
0xb8,0x7a,0xe1,0x17,0xfb,0xaf,0x1d,0xff,0x6f,0x70,0xc8,0xc8,0xc,0x3f,0x26,0xa4,0x9f,0x38,0xab,0x16,0x41,0xca,0x75,0xd1,0xf2,0xf6,0xa6,0x35,0xe6,0x57,0x1c,0xb4,0x3e,0x33,
0x49,0x3d,0x13,0x84,0x4d,0x17,0x74,0x5b,0xcd,0x15,0x19,0x6f,0xb7,0xea,0x7f,0x38,0xf1,0xbe,0xae,0xcf,0x4a,0x11,0x59,0x99,0xad,0x57,0xa7,0x13,0xce,0x8e,0xcb,0xf0,0x56,0x1d,
0x5f,0x4a,0x51,0xdc,0x3d,0x6,0x2c,0xc3,0x34,0x9b,0xde,0x17,0xd9,0x17,0xe9,0xd5,0xa1,0xfd,0x53,0xed,0x18,0xed,0xe2,0x93,0x9a,0x30,0x7,0xfe,0x3e,0x8d,0x5a,0xf6,0xb7,0xc9,
0x59,0x5c,0xb9,0xec,0x9a,0xd,0xa2,0xbb,0xfd,0xe3,0xb5,0xb3,0xa2,0x9,0xf3,0xda,0x92,0xc2,0x1f,0x74,0x3,0x70,0x75,0x61,0x31,0x98,0xee,0x5d,0x9a,0x1b,0xe9,0x60,0xb4,0x45,
0x69,0x84,0x29,0x11,0xe5,0xc5,0x3b,0xa1,0xf4,0xff,0xa2,0x86,0xd3,0x48,0x78,0xec,0x43,0x51,0x8e,0x31,0x93,0x51,0xa8,0xbc,0x9a,0x59,0x36,0xa6,0xcb,0xbc,0x28,0x80,0xec,0x8e,
0xdd,0xd2,0x60,0x2b,0xa5,0x14,0xc4,0xfe,0x39,0xf8,0x67,0xa1,0x5,0x3a,0x63,0xbf,0x4e,0xe6,0xa0,0xf8,0x81,0xfe,0x3f,0x82,0xb7,0x4b,0xdc,0x8c,0xd2,0x9,0x5a,0xdb,0x97,0xbe,
0x7c,0x25,0xf6,0xc9,0xda,0xfc,0xf6,0xa1,0x31,0x6a,0x71,0x9d,0x71,0xbf,0x6,0xdb,0x9c,0xc8,0xf9,0x1a,0xf1,0x3c,0x19,0xb5,0xb3,0x7b,0x66,0x4a,0x3c,0x70,0xa8,0xa3,0xff,0x20,
0xea,0xf0,0x3c,0x13,0xb0,0x67,0xca,0x61,0x9a,0xb8,0x1b,0xee,0xe9,0x44,0x82,0x4b,0xc6,0xa4,0xea,0xdb,0x96,0xb,0xed,0x29,0x5d,0xa1,0x74,0x0,0x79,0x1d,0x57,0x21,0x4f,0x11,
0x2e,0xd9,0x5d,0xa9,0x33,0x99,0xfe,0xcc,0xfb,0xa0,0x30,0x74,0x9b,0x47,0x67,0x84,0xcd,0x2e,0xe1,0xfe,0xe,0xe5,0x6,0xcb,0x4,0x78,0x58,0xef,0x8d,0x78,0x62,0x68,0x91,0x78,
0xe5,0xcb,0xa1,0x6,0x47,0xc9,0x3b,0x3c,0x1b,0x42,0xe3,0x85,0xc2,0x9e,0xc0,0x72,0xe8,0xd8,0x8b,0xd2,0x65,0x56,0x58,0x7c,0x8d,0x9b,0x95,0x4c,0x44,0xb6,0x3e,0x25,0x83,0x8c,
0x2b,0x52,0x49,0x33,0x72,0xf5,0x11,0x3d,0xcc,0xe,0xd8,0x42,0x3,0x92,0xba,0x2b,0x5d,0x2e,0xb6,0x9e,0xc4,0xa7,0x1e,0x2,0xec,0xef,0xce,0x2c,0x40,0x3d,0x50,0x5a,0x8d,0x43,
0x12,0x95,0xd8,0x98,0x39,0xca,0x25,0xb7,0x8,0xdb,0x54,0xf3,0xf8,0xc,0x1,0x42,0x46,0x6f,0xb0,0x6d,0x17,0xbc,0xad,0xba,0xe4,0xe7,0x1f,0x74,0xfa,0x7c,0x4b,0x21,0xec,0x41,
0xe6,0x8c,0x8a,0xe3,0x30,0xb9};



CMapPlugin::CMapPlugin(CNaviBroker *NaviBroker):CNaviMapIOApi(NaviBroker)
{
	ConfigPath = wxString::Format(wxT("%s%s"),GetWorkDir().wc_str(),_(PLUGIN_CONFIG_FILE));
	
	GpsX = GpsY = _X = _Y = _UX = _UY = GPS_OUT_OF_COORDS;
	DisplaySignal = new CDisplaySignal(NDS_GPS);
	nmea_zero_INFO(&NmeaInfo);
	IsWorking = true;
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
	SelectedTrack = NULL;
	DistanceUnit = 0;
	_NoSignal = true;
	
	CreateSumbols();
	CreateApiMenu();
	ReadConfig();
		
	//Track = new CTrack();
	//TrackList = new CTrackList();
	//TrackList->AddTrack(Track);
	Boats = new CBoats();
	Boat = Boats->GetBoat(BoatType);
	
	// MAX function name 32

	AddExecuteFunction("gps_SetNMEAInfo",SetNMEAInfo);
	AddExecuteFunction("gps_SetLog",SetLog);
	AddExecuteFunction("gps_NewSignal",NewSignal);
	AddExecuteFunction("gps_NoSignal",NoSignal);
	AddExecuteFunction("gps_GetThisPtr",GetThisPtr);
	
}

CMapPlugin::~CMapPlugin()
{
	delete DisplaySignal;
	//delete Track;
	//delete TrackList;
	delete MyFrame;
	delete Boats;
	MyFrame = NULL;
	MySerial = NULL;
}

CTrack *CMapPlugin::GetTrack(size_t id)
{
	return TrackList->GetTrack(id);
}

bool CMapPlugin::GetIsWorking()
{
	return IsWorking;
}

CTrackList *CMapPlugin::GetTrackList()
{
	return TrackList;
}

void CMapPlugin::ReadConfig()
{
	wxFileConfig *FileConfig = new wxFileConfig(_("gps"),wxEmptyString,ConfigPath,wxEmptyString);
	FileConfig->Read(_(KEY_DISTANCE_UNIT), &DistanceUnit,nvNauticMiles);
	FileConfig->Read(_(KEY_BOAT_TYPE),&BoatType,0);
	delete FileConfig;

}

void CMapPlugin::WriteConfig()
{
	wxFileConfig *FileConfig = new wxFileConfig(_("gps"),wxEmptyString,ConfigPath,wxEmptyString);
	FileConfig->Write(_(KEY_DISTANCE_UNIT), DistanceUnit);
			
	bool running = MySerial->IsRunning();
	wxString port(MySerial->GetPortName(),wxConvUTF8);
	fprintf(stdout,"%s\n",port.char_str());
	int baud = MySerial->GetBaudRate();
	
	FileConfig->Write(_(KEY_PORT),port);
	FileConfig->Write(_(KEY_BAUD),baud);
	FileConfig->Write(_(KEY_RUNNING),running);
	FileConfig->Write(_(KEY_BOAT_TYPE),BoatType);
	
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


//wxFileConfig *CMapPlugin::GetFileConfig()
//{

//}

CNaviBroker *CMapPlugin::GetBroker()
{
    return Broker;
}

void CMapPlugin::Run(void *Params)
{
	//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF );
    
	/*
	wxString fontFile(FONT_NAME,wxConvUTF8);
	if(!wxFileExists(fontFile))
	{
		wxLogError(wxString::Format(GetMsg(MSG_FONT_NOT_EXISTS),FONT_NAME));
		FreeNaviClassInstance(this);
		return;
	}
	*/
	
	//Font = new CNaviPixmapFont(FONT_NAME,FONT_SIZE);
    MyFrame = NULL;
    MySerial = new CMySerial(Broker);
	    
	
	wxFileConfig *FileConfig = new wxFileConfig(_("gps"),wxEmptyString,ConfigPath,wxEmptyString);
	
    wxString port;
			
	bool exists = true;
	if(!FileConfig->Exists(_(KEY_PORT)))
		exists = false;

	if(!FileConfig->Exists(_(KEY_BAUD)))
		exists = false;

	
	if(exists)
	{	
		FileConfig->Read(_(KEY_PORT), &port);
		MySerial->_SetPort(port.char_str());

		int baud;
		FileConfig->Read(_(KEY_BAUD), &baud);
		MySerial->SetBaud(baud);
		MySerial->SetCheckCRC(true);

		bool running;
		FileConfig->Read(_(KEY_RUNNING), &running);
		if(running)
			MySerial->Start();
	}

	delete FileConfig;

}

void CMapPlugin::SetShowHint(bool show)
{
    _ShowHint = show;
}

void CMapPlugin::Kill(void)
{

	IsWorking = false;
	NeedExit = true;
	WriteConfig();
    
	
	if(MySerial != NULL)
		MySerial->Stop();	// stop the serial port thread
		
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

	NaviApiMenu = new CNaviApiMenu( GetMsg(MSG_GPS).wchar_str() );	// nie u�uwa� delete - klasa zwalnia obiejt automatycznie
	NaviApiMenu->AddItem( GetMsg(MSG_SETTINGS).wchar_str(),this, MenuConfig );
	//NaviApiMenu->AddItem( GetMsg(MSG_NEW_TRACK_RECORD).wchar_str(),this, MenuTrack );
	NaviApiMenu->AddItem( GetMsg(MSG_BOAT_CONFIG).wchar_str(),this, MenuBoatConfig );
	NaviApiMenu->AddItem( GetMsg(MSG_DISTANCE_UNIT_CONFIG).wchar_str(),this, MenuDistanceUnitConfig );
	NaviApiMenu->AddItem( GetMsg(MSG_STATUS).wchar_str(),this, MenuStatus );
	
}

void *CMapPlugin::MenuConfig(void *NaviMapIOApiPtr, void *Input) 
{

	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Config();

	return NULL;
}

void CMapPlugin::Config()
{
	if(NeedExit)
		return;

#if defined(_WIN32) || defined(_WIN64)
	if(MyFrame == NULL)
		MyFrame = new CMyFrame(this);
	if(MyFrame->IsModal())
		MyFrame->Show();
	else
		MyFrame->ShowModal();
#endif
#if defined (_LINUX32) || defined(_LINUX64)
    MyFrame = new CMyFrame();
    MyFrame->ShowModal();
    MyFrame = NULL;
#endif

}

void *CMapPlugin::MenuTrack(void *NaviMapIOApiPtr, void *Input) 
{

	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->TrackConfig();

	return NULL;
}

void CMapPlugin::TrackConfig()
{

}

void *CMapPlugin::MenuBoatConfig(void *NaviMapIOApiPtr, void *Input) 
{

	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->BoatConfig();

	return NULL;
}

void CMapPlugin::BoatConfig()
{

	CBoatConfig *BoatConfig = new CBoatConfig();
	BoatConfig->SetId(BoatType);
	
	if(BoatConfig->ShowModal() == wxID_OK)
	{
		BoatType = BoatConfig->GetId();
		Boat = Boats->GetBoat(BoatType);
	}
	
	delete BoatConfig;
}

void *CMapPlugin::MenuDistanceUnitConfig(void *NaviMapIOApiPtr, void *Input) 
{

	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->DistanceUnitConfig();

	return NULL;
}

void CMapPlugin::DistanceUnitConfig()
{
	CUnitConfig *UnitConfig = new CUnitConfig();
	UnitConfig->SetUnit(GetUnit());
		
	if(UnitConfig->ShowModal() == wxID_OK)
	{
		SetUnit(UnitConfig->GetUnit());
	}

	delete UnitConfig;
}

void *CMapPlugin::MenuStatus(void *NaviMapIOApiPtr, void *Input) 
{

	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->Status();

	return NULL;
}

void CMapPlugin::Status()
{
	CStatus *Status = new CStatus(MySerial);
	Status->ShowModal();
	delete Status;

}

//void *CMapPlugin::SetExit(void *NaviMapIOApiPtr, void *Params)
//{
	//CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	//ThisPtr->SetExitFunc((bool)Params);
		
	//return NULL;
//}

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
	_NoSignal = false;

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
	
	GetMutex()->Lock();
	wxString buffer(text,wxConvUTF8,4096);
	MyFrame->SetLogEvent(buffer);
	GetMutex()->Unlock();
	
}

void *CMapPlugin::NewSignal(void *NaviMapIOApiPtr, void *Params)
{

	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->NewSignalFunc();
		
	return NULL;
}

void CMapPlugin::NewSignalFunc() 
{

	SendDisplaySignal(this);
	
}

void *CMapPlugin::GetThisPtr(void *NaviMapIOApiPtr, void *Params)
{
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	return ThisPtr;
}


void *CMapPlugin::NoSignal(void *NaviMapIOApiPtr, void *Params)
{

	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->NoSignalFunc();
		
	return NULL;
}

void CMapPlugin::NoSignalFunc()
{
	_NoSignal = true;
}

void CMapPlugin::SetSelectedTrack(size_t id)
{
	SelectedTrack = TrackList->GetTrack(id);	
	Broker->Refresh(Broker->GetParentPtr());
}

//void *CMapPlugin::SetPort(void *NaviMapIOApiPtr, void *Params)
//{

	//CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	//ThisPtr->SetPortFunc((char*)Params);
		
	//return NULL;
//}

//void CMapPlugin::SetPortFunc(char *port) 
//{
	//if(MyFrame == NULL)
		//return;
	
	//wxString buffer(port,wxConvUTF8);
	//MyFrame->SetPortEvent(buffer);
	
//}

//void *CMapPlugin::SetBaud(void *NaviMapIOApiPtr, void *Params)
//{

	//CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	//ThisPtr->SetBaudFunc((int)Params);
		
	//return NULL;
//}

//void CMapPlugin::SetBaudFunc(int baud) 
//{
	//if(MyFrame == NULL)
		//return;
	
	//MyFrame->SetBaudEvent(wxString::Format(_("%d"),baud));
	
//}

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
    Radius = 1.2f;
	CircleRadius = Radius;
    for(int i=0; i<360; i+=10)
    {
        Points.x = Radius*(float)sin(i*PI/180.0);
        Points.y = Radius*(float)cos(i*PI/180.0);
        vCircle3.push_back(Points);
    }
		
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
	
	
	if(_MouseOverIcon)
		Broker->Refresh(Broker->GetParentPtr());

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
		xs = GpsX; ys = GpsY;					// srodek ko�a
		double r = CircleRadius * (50/Scale);   // promie�
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

size_t CMapPlugin::GetUnit()
{
	return DistanceUnit;
}

void CMapPlugin::SetUnit(size_t val)
{
	DistanceUnit = val;
}

void CMapPlugin::AddPoint(double x, double y, nmeaINFO *info)
{

	GetMutex()->Lock();
#ifdef BUILD_GPS_POINTS_VECTOR
	//Track->AddPoint(x,y);
	//Track->AddPointInfo(x,y,info);
#endif
	GetMutex()->Unlock();

}
double CMapPlugin::GetGpsX()
{
	return _X;
}

double CMapPlugin::GetGpsY()
{
	return _Y;
}

void CMapPlugin::SetValues()
{
	double vm[4];
	Broker->GetVisibleMap(vm);


	MapX1 = vm[0];
	MapY1 = vm[1];
	MapX2 = vm[2];
	MapY2 = vm[3];


	Broker->GetMapCircle(Broker->GetParentPtr(),dMapCircle);

	MapCircle.Center.x = dMapCircle[0];
	MapCircle.Center.y = dMapCircle[1];
	MapCircle.Radius = dMapCircle[2];

	GpsCircle.Center.x = GpsX;
	GpsCircle.Center.y = GpsY;
	GpsCircle.Radius = 0.0;

	//Broker->Unproject(vm[0],vm[1], &MapX1, &MapY1);
	//Broker->Unproject(vm[2],vm[3], &MapX2, &MapY2);
	
}
/*
float CMapPlugin::RenderText(double x, double y, wchar_t *text)
{
	//if(MapScale < Factor)
		//return 0;

	float width, height;
	width = (Font->GetWidth(text)/2)/SmoothScaleFactor;
	height = (Font->GetHeight()/2)/SmoothScaleFactor;
	Font->Render(x - width , y - height , text);
	
	return height;
}

float CMapPlugin::RenderText(double x, double y, char *text)
{
	//if(MapScale < Factor)
		//return 0;
	float width, height;
	width = (Font->GetWidth(text)/2)/SmoothScaleFactor;
	height = (Font->GetHeight()/2)/SmoothScaleFactor;
		
	Font->Render(x - width , y - height , text);

	return height;
}
*/
void CMapPlugin::RenderSelectedTrack()
{
	if(SelectedTrack == NULL)
		return;
	
	glEnable(GL_POINT_SMOOTH);
	
	GetMutex()->Lock();
	
	glColor4f(1.0f,0.0f,0.0f,0.2f);
	glPointSize(5.0f);
		
	std::vector<SPoint> pts = SelectedTrack->GetTrackPoints();
	if(pts.size() > 0)
	{
		RenderGeometry(GL_POINTS,&pts[0],pts.size());				// punkty z gpsa
		RenderGeometry(GL_LINE_STRIP,&pts[0], pts.size());			// linie
	}
	    	
	GetMutex()->Unlock();
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
			glVertex2f(vCircle3[9].x,vCircle3[9].y);
			glVertex2f(vCircle3[18].x,vCircle3[18].y);
			glVertex2f(vCircle3[27].x,vCircle3[27].y);
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
	
	if(_NoSignal)
		glColor4f(1.0f,0.0f,0.0f,0.5f);
	else
		glColor4f(0.0f,0.0f,1.0f,0.5f);
	
	glPushMatrix();
		glLineWidth(2);
		glTranslated(GpsX,GpsY,0.0);
		glScalef(40.0/Scale,40.0/Scale,0.0f);
		glRotatef(NmeaInfo.direction,0.0f,0.0f,1.0f);
		RenderGeometry(GL_LINE_LOOP,&vCircle1[0],vCircle1.size());	// circle 1
		RenderGeometry(GL_LINE_LOOP,&vCircle2[0],vCircle2.size());  // circle 2
		RenderGeometry(GL_LINE_LOOP,&vCircle3[0],vCircle3.size());  // circle 3
		//RenderGeometry(GL_POINTS,&vCircle3[0],vCircle3.size());  // circle 3
		Boat->RenderBoat();
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
	if( AnimMarkerSize > 200.0f )
		AnimMarkerSize = 50.0f;

}

void CMapPlugin::RenderMouseXY()
{
	glPointSize(10);
	glColor3f(1.0,0.0,0.0);
	
	glBegin(GL_LINES);
		glVertex2d(MouseX,MouseY);
		glVertex2d(GpsX,GpsY);
	glEnd();
	
	glPointSize(1);
}

void CMapPlugin::RenderDistance()
{

	double v1,v2, _x1,_y1, _x2, _y2;
	wchar_t val[32];
	Broker->Project(GpsX,GpsY,&_x1,&_y1);
	Broker->Project(MouseX,MouseY,&_x2,&_y2);
	swprintf(val,L"%4.4f %s",nvDistance(_x1,_y1,_x2,_y2,DistanceUnit),GetDistanceUnit(DistanceUnit));
	
	nvMidPoint(GpsX,GpsY,MouseX,MouseY,&v1,&v2);
		
	glPushMatrix();
	glTranslatef(v1 ,v2 ,0.0f);
	glScalef(0.6/Scale,0.6/Scale,0.0f);
	glEnable(GL_TEXTURE_2D);
//	Broker->Print(Broker->GetParentPtr(),0.0f,0.0f,val);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void CMapPlugin::Render(void)
{
	
	if( GetNeedExit())
        return;
	
	SetValues();
		
//	if(!nvIsCircleColision(&MapCircle,&GpsCircle))
		
	//	return;
	
	Scale = Broker->GetMapScale();
		
    glEnable(GL_LINE_SMOOTH);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
		
	if( !TexturesCreated )
		CreateTextures();
	
	RenderPosition();
    
	if(_MouseOverIcon)
	{
		RenderSelection();
		RenderMouseXY();
		RenderDistance();
		
	}
        
	//RenderSelectedTrack();
	//RenderAnimation();	
			
    glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);


}

//	 API dla DLL
void NAVIMAPAPI *CreateNaviClassInstance(CNaviBroker *NaviBroker)
{
   CMapPlugin *DLL = new CMapPlugin(NaviBroker);
  return static_cast<void*> ( DLL );
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
    return MAP_PLUGIN_RUN_ON_DEMAND | RENDER_PRIORITY_10;
}

unsigned char *GetNaviPluginInfoBlock()
{
	return PluginInfoBlock;
}

void NAVIMAPAPI FreeNaviClassInstance(void *ptr)
{
	delete (CMapPlugin*)ptr;
}

