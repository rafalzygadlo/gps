#include "serial.h"
#include "frame.h"
#include "dll.h"
#include "tools.h"

CMySerial::CMySerial(CNaviBroker *Broker):CSerial(DEVICE_GPS)
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


void CMySerial::OnData()
{
    FoldLine(GetBuffer(),GetLength());
	_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetLog",(void*)GetBuffer());
    
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
	_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetPort",GetPortName());
	_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetBaud",(void*)GetBaudRate());
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

void CMySerial::Parse(char *buffer, int length)
{
     if(nmea_parse(&_parser, buffer, length, &_info))
		_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetNMEAInfo",&_info);
		 
}


void CMySerial::FoldLine( unsigned char *Buffer, int BufferLength )
{
    unsigned char *ptr_Buffer, *ptr1;
    ptr1 = ptr_Buffer = Buffer;
    
    while ( *ptr_Buffer )
    {
        ptr_Buffer++;
        if ( !*ptr_Buffer )
        {
            _LineBufLen = POS_IN_BUF( ptr1, ptr_Buffer );
            memset( _LineBuffer, 0, BUFFER_LENGTH );
            memcpy( _LineBuffer, ptr1, _LineBufLen );
            return;
        }

        if ( *ptr_Buffer == 13 )
            ptr_Buffer++;
        if ( *ptr_Buffer == 10 )
        {
            ptr_Buffer++;
            memcpy( ( char *)_LineBuffer + _LineBufLen, ( const char *)ptr1, ( ptr_Buffer-ptr1 ) );
            Parse((char*)_LineBuffer, ( ptr_Buffer - ptr1 ) );
            memset( _LineBuffer, 0, BUFFER_LENGTH );
            _LineBufLen = 0;
            ptr1 = ptr_Buffer;
        }
    }

}

