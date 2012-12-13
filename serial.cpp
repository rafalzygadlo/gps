#include "serial.h"
#include "frame.h"
#include "dll.h"
#include "tools.h"

CMySerial::CMySerial(CNaviBroker *Broker):CSerial()
{
    _IsRunning = false;
	_Broker = Broker;
	_AreaSize = DEFAULT_AREA_SIZE;
    _ValidGPS = false;
    _Exit = false;
    _LineBufLen = 0;
    _ValidData = false; // valid parsed data
	 nmea_parser_init(&_parser);
	 nmea_zero_INFO(&_info);
	 memset(_LineBuffer,0,BUFFER_LENGTH);
}

CMySerial::~CMySerial()
{
	bool flag = true;
	_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetExit",&flag);
	 nmea_parser_destroy(&_parser);
}

bool CMySerial::IsRunning()
{
	return _IsRunning;
}

nmeaINFO CMySerial::GetNmeaINFO()
{
	return _info;
}

void CMySerial::OnConnect()
{
    wxString port_name(GetPortName(),wxConvUTF8);
    _ValidGPS = false;
	
}

void CMySerial::OnDisconnect()
{
    _ValidGPS = false;
}


void CMySerial::OnData(unsigned char *buffer, int length)
{
    _Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetLog",(void*)buffer);
    
}

void CMySerial::OnValid()
{
     _ValidGPS = true;	
}

void CMySerial::OnInvalid()
{
    _ValidGPS = false;
}

bool CMySerial::IsValidGPS()
{
    return _ValidGPS;
}

void CMySerial::OnExit()
{
    _Exit = true;
}

void CMySerial::OnStart()
{
	_IsRunning = true;
}

void CMySerial::OnStop()
{
	_IsRunning = false;
	nmea_zero_INFO(&_info);
	_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetNMEAInfo",&_info);

}

void CMySerial::OnReconnect()
{
	char str[32];
	sprintf(str,"%s %d\n",GetPortName(),GetBaudRate());
	nmea_zero_INFO(&_info);
	_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetNMEAInfo",&_info);
	//_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetLog",&str);
	//_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetPort",GetPortName());
	//_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetBaud",(void*)GetBaudRate());
}

void CMySerial::OnNewScan()
{
    //SendInfoEvent(_(MSG_5));
}

void CMySerial::OnAfterMainLoop()
{
	bool flag = true;
	_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetExit",&flag);
		
}

void CMySerial::OnBeforeMainLoop()
{
}


void CMySerial::OnLine(unsigned char *line)
{
	if(nmea_parse(&_parser, (char*)line, strlen((char*)line), &_info))
		_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetNMEAInfo",&_info);

}

void CMySerial::OnNoSignal()
{

}
