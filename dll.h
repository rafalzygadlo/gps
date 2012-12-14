#ifndef __DLL
#define __DLL

#include "NaviMapIOApi.h"
#include <wx/fileconf.h>
#include <vector>
#include <wx/wx.h>
#include "NaviDisplayApi.h"

#include <wx/fileconf.h>

#include <wx/dir.h>
#include "tgamem.h"

#ifdef _WIN32
	#include <windows.h>
	#include <crtdbg.h>
#endif
#include <GL/glu.h>
#include "track.h"
#include "frame.h"
#include "serial.h"
#include "conf.h"

#ifdef __cplusplus
extern "C" {
#endif

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
class CTrack;
class CTrackList;
class CMyFrame;

class CMapPlugin :public CNaviMapIOApi
{
	bool MapPluginIsOn;
	double GpsX, GpsY;
	double momX, momY;
	double MouseX,MouseY;
	long DisplaySignalType;
	nmeaINFO NmeaInfo;
	CMyFrame *MyFrame;
	CMySerial *MySerial;
	SPoint *SelectedPtr;
	CDisplaySignal *DisplaySignal;
	CNaviBroker *Broker;
	CTrack *Track;
	CTrackList *TrackList;
	bool NeedExit;
	bool IsData;
	bool _Exit;
#if defined(_WIN32) || defined(_WIN64)
		HANDLE threadFrame;
#endif
	GLuint AnimMarkerID;
	float AnimMarkerSize;
	double SmoothScaleFactor;
	float Scale;
	bool AnimationStart;
	float CircleRadius;
	bool TexturesCreated;
	bool _MouseOverIcon;
	TTexture *TextureAnimMarker;
	bool IsWorking;

	int AreaSize;								// area size saved in config (from spin)
	bool _ShowHint;
	wxFileConfig *FileConfig;
	std::vector <SPoint> vCircle1,vCircle2,vCircle3,vLineV, vLineH;
	std::vector <SPoint>::iterator itvVertex;
	wxString ConfigPath;
	double _X,_Y;								// gps pozycje x,y
	double _UX,_UY;								// unprojected gps pozycje x,y dla pozycji gpsa do renderu
	float minX, maxX, minY, maxY;				// gps area stworzona w konfiguracji

	//int _ValidData;							// sparsowany sygna³ prawid³owy z danymi prawid³owymi gotowy do renderu (0-gotowy 3-nie gotowy)

	unsigned char _LineBuffer[BUFFER_LENGTH];	// buffor lini
	int _LineBufLen;							// d³ugoœæ bufora lini


	bool IsPointInsideBox(double px, double py, double bx1, double by1, double bx2, double by2); 
	void FoldLine( unsigned char *Buffer, int BufferLength );
	void Parse(char *Buffer, int Length);
	static void *MenuConfig(void *NaviMapIOApiPtr, void *Input);
	void CreateApiMenu(void);
	void CreateSumbols();
	void CreateTexture(TTexture *Texture, GLuint *TextureID);
	void CreateTextures(void);
	void RenderTracks();
	void RenderSelection();
	void RenderPosition();
	void RenderAnimation();
	void SetNMEAInfoFunc(nmeaINFO *_nmea);
	void SetLogFunc(char *text);
	void SendDisplaySignal(CMapPlugin *MapPlugin);
	void SetPortFunc(char *port);
	//void SetBaudFunc(int baud);
	void RenderMouseXY();
					
public:

	CMapPlugin(CNaviBroker *NaviBroker);
	virtual ~CMapPlugin();

	bool GetNeedExit(void);
	CNaviBroker *GetBroker();

	void RenderGeometry(GLenum Mode,GLvoid* RawData,size_t DataLength);
	void BuildGeometry();
	wxFileConfig *GetFileConfig();
	void WriteConfig();
	void ReadConfig();
	double GetGpsX();
	double GetGpsY();
	void SetShowHint(bool show);
	void AddPoint(double x, double y, nmeaINFO *info);
	void SetExitFunc(bool exit);
	void NewSignalFunc();
	CTrackList *GetTrackList();
	nmeaINFO GetNmeaINFO();
	CMySerial *GetMySerial();
	bool GetIsWorking();


	virtual void Run(void *Params);
	virtual void Kill(void);
	virtual void Render(void);
	virtual void Config();
	virtual void Mouse(int x, int y, bool lmb, bool mmb, bool rmb );
	virtual void MouseDBLClick(int x, int y);
		
	// funkcje dostêpne dla innych pluginów
	//static void *SetExit(void *NaviMapIOApiPtr, void *Params);			// serial port ustawia flagê zakoñczenia dzia³ania
	static void *SetNMEAInfo(void *NaviMapIOApiPtr, void *Params);
	static void *SetLog(void *NaviMapIOApiPtr, void *Params);				// ustawia log w okienku konfiguracyjnym
	static void *NewSignal(void *NaviMapIOApiPtr, void *Params);
	//static void *SetPort(void *NaviMapIOApiPtr, void *Params);			// ustawia port w okienku konfiguracyjnym
	//static void *SetBaud(void *NaviMapIOApiPtr, void *Params);			// ustawia port w okienku konfiguracyjnym
};	

#ifdef __cplusplus
}
#endif

#endif