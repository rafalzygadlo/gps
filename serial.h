#ifndef __SERIAL
#define __SERIAL

#include "serial_port.h"
#include <wx/wx.h>
#include <nmea/nmea.h>
#include "conf.h"
#include "NaviMapIOApi.h"

class CMySerial :public CSerial
{
		bool _IsRunning;
		CNaviBroker *_Broker;
		nmeaINFO _info;
		nmeaPARSER _parser;
		bool _ValidGPS;								// valid gps ale mo¿e byæ nie zsynchronizowany
		bool _Exit;
		bool _ValidData;							// from parser
		unsigned char _LineBuffer[BUFFER_LENGTH];
		int _LineBufLen;
		double _AreaSize;							// selection area defined in spin ctrl (but changed to minutes)

		void FoldLine( unsigned char *Buffer, int BufferLength );
		//void Parse(char *Buffer, int Length);
		void BuildPortList();						// buduje liste portów
		void SendInfoEvent(wxString info_text);     // wysylaj event do okienka informacyjnego

public:
		CMySerial(CNaviBroker *_Broker);
		~CMySerial();
		nmeaINFO GetNmeaINFO();
		bool IsValidGPS();					// zwraca flagê czy prawid³owy sygna³ gps (mo¿e byæ nie z synchronizowany)
		bool IsRunning();

		virtual void OnValid();
		virtual void OnInvalid();
		virtual void OnConnect();
		virtual void OnDisconnect();
		virtual void OnData(unsigned char *buffer, int length);
		virtual void OnLine(unsigned char* line);
		virtual void OnStart();
		virtual void OnStop();
		virtual void OnAfterMainLoop();
		virtual void OnBeforeMainLoop();
		virtual void OnExit();			// no gps found plugin ends working
		virtual void OnReconnect();
};




#endif
