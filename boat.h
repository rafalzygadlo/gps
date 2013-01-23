#ifndef __BOAT
#define __BOAT

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <vector>
#include <GL/gl.h>
#include "conf.h"

class CBoats;
class CBoatPanel;
class CBoatPoints
{
	std::vector <SPoint> vPoints;

public:
	
	CBoatPoints();
	~CBoatPoints();
	void AddPoint(double x, double y);
	SPoint GetPoint(size_t id);
	size_t GetCount();

};

class CBoat
{
	CBoatPanel *BoatPanel;
	size_t Type;
	wxString Name;
	wxArrayPtrVoid GeometryList;
	void RenderGeometry(GLenum Mode,GLvoid* RawData,size_t DataLength);	

public:

	CBoat();
	~CBoat();

	void AddGeometry(CBoatPoints *BoatPoints);
	void *GetGeometry(size_t id);
	size_t GetCount();
	void SetName(wxString val);
	wxString GetName();
	
	//SPoint GetPoint(size_t id);
	wxPanel *GetBoatPanel();
	void SetType(size_t type);
	void Render();
	
};

class CBoatPanel: public wxGLCanvas
{
	
	int ScreenWidth,ScreenHeight;
	wxGLContext *GLContext;	
	CBoat *Boat;
	void UpdateViewPort();
	void OnPaint(wxPaintEvent &event);
	void OnSize(wxSizeEvent& event);
	void OnMouse(wxMouseEvent &event);

public:
	
	CBoatPanel(wxWindow *parent);
	~CBoatPanel();
	void SetBoat(CBoat *boat);
	void Render();
	
	DECLARE_EVENT_TABLE();
		
};

class CBoats
{

	std::vector <CBoat*> vBoats;

public:
	CBoats();
	~CBoats();

	size_t GetCount();
	CBoat *GetBoat(size_t id);
	void Append(CBoat *boat);
	
		
};
#endif