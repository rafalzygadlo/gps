#include "boat.h"
#include "tools.h"


struct SPoint Ship1[6] = {{0.0,-1.0}, {-0.3,-0.5}, {-0.3,1.0}, {0.3,1.0}, {0.3,-0.5}, {0.0,-1.0}};
//struct SPoint Ship2[] = {{0.0,-1.0}, {-0.3,-0.5}, {-0.3,1.0}, {0.3,1.0}, {0.3,-0.5}, {0.0,-1.0}};
struct SPoint Boat[8] = {{0.0,-1.0}, {-0.3,-0.2}, {-0.3,0.7}, {-0.2,1.0}, {0.2,1.0}, {0.3,0.7},{0.3,-0.2},{0.0, -1.0}};

CBoat::CBoat()
{
	
}

CBoat::~CBoat()
{

}

void CBoat::AddPoint(double x, double y)
{
	
}

std::vector<SPoint> CBoat::GetPoints()
{
	return vPoint;
}

void CBoat::RenderGeometry(GLenum Mode,GLvoid* RawData,size_t DataLength)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_DOUBLE, 0, RawData);
    glDrawArrays(Mode, 0, DataLength);
    glDisableClientState(GL_VERTEX_ARRAY);
}


void CBoat::Render()
{
	glColor4f(0.0f,0.0f,1.0f,0.2f);
	RenderGeometry(GL_LINE_LOOP,&Ship1,6);
	//glColor4f(0.0f,0.0f,1.0f,0.5f);
	//RenderGeometry(GL_POLYGON,&Ship1,sizeof(Ship1));
}
