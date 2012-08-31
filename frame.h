#ifndef __FRAME
#define __FRAME

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/fileconf.h>
#include <wx/spinctrl.h>
#include <vector>
#include <wx/dcbuffer.h>
#include "NaviMapIOApi.h"
#include "dll.h"



typedef struct
{
	int rect_x;
	int rect_y;
	int rect_width;
	int rect_height;
	int min_x;
	int min_y;
	int max_x;
	int max_y;

} SHints;

class CMyPanel;
class CMapPlugin;
class CMyFrame: public wxDialog
{
	int PortSelection;
	CMapPlugin *MapPlugin;
	wxString ConfigPath;
	wxFileConfig *FileConfig;
	wxTextCtrl *LogText;
	wxStaticText *ConfigPathText;
	wxComboBox *PortComboBox,*BaudComboBox;
	wxButton *StartButton;
	wxButton *StopButton;
	wxCheckBox *CheckLogBox,*CheckBoxHint;
	wxSpinCtrl *Spin;
	double minX, maxX, minY, maxY;						// gps area
	double old_data;


	bool _Start,_Stop , _Close;
	void OnStartButton(wxCommandEvent &event);			// start button click
	void OnStopButton(wxCommandEvent &event);			// stop button click
	void OnCloseButton(wxCommandEvent &event);			// close click
	void OnPortComboChange(wxCommandEvent &event);		// combo box changed
	void OnCheckLog(wxCommandEvent &event);				// check box log
	
	void OnClose(wxCloseEvent &event);
	void OnComboBox(wxCommandEvent &event);
	// custom events to send text from thread
	void OnSetLog(wxCommandEvent &event);
	void OnSetPort(wxCommandEvent &event);
	void OnSetBaud(wxCommandEvent &event);
	

public:

	CMyFrame(CMapPlugin *_MapPlugin);
	~CMyFrame();

	void _SetInfoText(wxString text);
	void _SetStatusText(wxString text);
	void _SetConfigPathText(wxString text);
	void _SetPort();
	void _SetGpsFix(int fix);
	wxSpinCtrl *_GetSpin();
	wxComboBox *_GetPortComboBox();
	wxTextCtrl *_GetTextCtrl();
	void RefreshPortsList();
	void RefreshBaudList();
	void SetLogEvent(wxString str);	
	void SetPortEvent(wxString str);
	void SetBaudEvent(wxString str);

	DECLARE_EVENT_TABLE();

	enum
	{
		ID_START = 12345,
		ID_STOP,
		ID_CLOSE,
		ID_PORTS,
		ID_TRANSPARENT,
		ID_CHECK_LOG,
		ID_CHECK_HINT,
		ID_REFRESH,
		ID_SPIN,
	};
};





class CMyPanel: public wxPanel
{

	int _OldX,_OldY;
	int	_X,_Y;									// X,Y myszy
	double _Xd, _Yd;							// X,Y zaznaczenia
	int _DragX, _DragY;
	int CenterX, CenterY;						// centrum okna rysowania
	bool _Drag;
	std::vector <SHints> vHints;				// lista wymiar�w zaznacze�

	int RectWidth, RectHeight;					// wysoko�� szeroko�� zaznaczenia
	int MinRectWidth, MinRectHeight;			// minimalna wysoko�� zaznaczenia
	int RectCenterX, RectCenterY;				// centralne punkty zaznaczenia
	int Selection;								// id zaznaczenia hintu
	int ScreenWidth, ScreenHeight;				// wymiary ekranu rysowania
	float Zoom;									// zoom okna rysowania
	bool Start;									// flaga kreowania kontrolki
	float minX, maxX, minY, maxY;				// gps area
	wxWindow *_Parent;

	void OnPaint(wxPaintEvent &event);
	void OnMouseEvents(wxMouseEvent &event);
	void OnWindowEnter(wxMouseEvent &event);
	void OnWindowLeave(wxMouseEvent &event);
	void OnEraseBackground(wxEraseEvent &event);
	void OnSize(wxSizeEvent &event);

	void DrawHints(wxBufferedPaintDC *dc);		// rysuj podpowied�
	void DrawGps(wxBufferedPaintDC *dc);		// rysuj obrazek gpsa
	void DrawInfo(wxBufferedPaintDC *dc);		// rysuj info
	void BuildHints();							// buduj na podstawie wymiar�w zaznaczenia list� podpowiedzi w postaci prostok�t�w
	void Render(wxBufferedPaintDC *dc);			// rysuj wszystko

public:
	CMyPanel(wxWindow *Parent);
	~CMyPanel();

		DECLARE_EVENT_TABLE();
};

#endif