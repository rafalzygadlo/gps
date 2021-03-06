#include "serial.h"
#include "frame.h"
#include "dll.h"
#include "tools.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

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

void CMySerial::OnConnect()
{
    wxString port_name(GetPortName(),wxConvUTF8);
    _ValidGPS = false;
	
}

void CMySerial::OnDisconnect()
{
    _ValidGPS = false;
}


void CMySerial::OnNewSignal()
{
	_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_NewSignal",NULL);
}

void CMySerial::OnData(unsigned char *buffer, int length)
{
     
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
	//nmea_zero_INFO(&_info);
	//_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetNMEAInfo",&_info);
	
}

void CMySerial::OnAfterMainLoop()
{
	bool flag = true;
	_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetExit",&flag);
		
}

void CMySerial::OnBeforeMainLoop()
{
}


void CMySerial::OnLine(unsigned char *buffer, int length)
{
	
	if(nmea_parse(&_parser, (char*)buffer, length, &_info))
		_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetNMEAInfo",&_info);
	
	nmea_parser_buff_clear(&_parser);
}

void CMySerial::OnNoSignal()
{
	_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_NoSignal",NULL);
}
