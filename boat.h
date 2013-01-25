#ifndef __BOAT
#define __BOAT

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <vector>
#include <GL/gl.h>
#include "conf.h"
#include "NaviGeometry.h"

class CBoats;
class CBoatPanel;

class CBoat
{
	CBoatPanel *BoatPanel;
	CNaviGeometryGroup *BoatGeometryGroup;
	size_t Type;
	wxString Name;
	void RenderGeometry(GLenum Mode,GLvoid* RawData,size_t DataLength);	

public:

	CBoat();
	~CBoat();

	void NewGeometry();
	CNaviGeometry *CreateGeometry();
	void AddGeometry(CNaviGeometry *geometry);
	CNaviVertexArray *CreateVertexArray();
	
	void *GetGeometry(size_t id);
	size_t GetCount();
	void SetName(wxString val);
	wxString GetName();
	
	//SPoint GetPoint(size_t id);
	wxPanel *GetBoatPanel();
	void SetType(size_t type);
	void RenderBackground();
	void RenderBoat();
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