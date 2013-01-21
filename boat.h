#ifndef __BOAT
#define __BOAT

#include <wx/wx.h>
#include <vector>
#include "conf.h"
#include <GL/gl.h>

class CBoat
{
	std::vector <SPoint> vPoint;
	void RenderGeometry(GLenum Mode,GLvoid* RawData,size_t DataLength);	


public:
	CBoat();
	~CBoat();
	std::vector<SPoint> GetPoints();

	void AddPoint(double x, double y);
	void Render();
	
		
};

#endif