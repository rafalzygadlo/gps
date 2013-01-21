#ifndef __BOAT
#define __BOAT

#include <wx/wx.h>
#include <vector>
#include "conf.h"
#include <GL/gl.h>

class CBoat
{
	size_t Type;
	wxString Name;
	std::vector <SPoint> vPoints;
	void RenderGeometry(GLenum Mode,GLvoid* RawData,size_t DataLength);	
	
public:
	CBoat();
	~CBoat();

	void AddPoint(double x, double y);
	void SetName(wxString val);
	wxString GetName();
	void SetType(size_t type);
	void Render();
		
};

class CBoats
{

	std::vector <CBoat*> vBoats;

public:
	CBoats();
	~CBoats();

	size_t GetCount();
	//wxString GetName();
	CBoat *GetBoat(size_t id);
	void Append(CBoat *boat);
	
		
};
#endif