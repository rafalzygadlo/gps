#include "boat.h"
#include "tools.h"

struct SPoint Ship1[SHIP1_SIZE] = {{0.0,-1.0}, {-0.3,-0.5}, {-0.3,1.0}, {0.3,1.0}, {0.3,-0.5}, {0.0,-1.0}};
struct SPoint Ship2[SHIP2_SIZE] = {{0.0,-1.0}, {-0.3,-0.5}, {-0.3,1.0}, {0.3,1.0}, {0.3,-0.5}, {0.0,-1.0}};
struct SPoint Ship3[SHIP3_SIZE] = {{0.0,-1.0}, {-0.3,-0.2}, {-0.3,0.7}, {-0.2,1.0}, {0.2,1.0}, {0.3,0.7}, {0.3,-0.2}, {0.0, -1.0}};

CBoat::CBoat()
{
		
}

CBoat::~CBoat()
{

}
void CBoat::AddPoint(double x, double y)
{
	SPoint pt;
	pt.x = x;
	pt.y = y;
	vPoints.push_back(pt);
}

void CBoat::SetType(size_t type)
{
	Type = type;
}

void CBoat::SetName(wxString val)
{
	Name = val;
}

wxString CBoat::GetName()
{
	return Name;
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
	
	switch(Type)
	{
		case 0:	RenderGeometry(GL_LINE_LOOP,&Ship1,SHIP1_SIZE);	break;
		case 1:	RenderGeometry(GL_LINE_LOOP,&Ship2,SHIP2_SIZE);	break;
		case 2: RenderGeometry(GL_LINE_LOOP,&Ship3,SHIP3_SIZE);	break;

	}
	
}

CBoats::CBoats()
{
	CBoat *Boat1 = new CBoat();
	Boat1->SetName(_("Boat 1"));
    Boat1->AddPoint(0.0,-1.0);	Boat1->AddPoint(-0.3,-0.5); Boat1->AddPoint(-0.3,1.0); 
	Boat1->AddPoint(0.3,1.0);	Boat1->AddPoint(0.3,-0.5);	Boat1->AddPoint(0.0,-1.0);
	
	CBoat *Boat2 = new CBoat();
	Boat2->SetName(_("Boat 2"));
    Boat2->AddPoint(0.0,-1.0);	Boat2->AddPoint(-0.3,-0.5); Boat2->AddPoint(-0.3,1.0);	
	Boat2->AddPoint(0.3,1.0);	Boat2->AddPoint(0.3,-0.5);	Boat2->AddPoint(0.0,-1.0);
	
	CBoat *Boat3 = new CBoat();
	Boat3->SetName(_("Boat 3"));
	Boat3->AddPoint(0.0,-1.0);	Boat3->AddPoint(-0.3,-0.2);	Boat3->AddPoint(-0.3,0.7);	Boat3->AddPoint(-0.2,1.0);	
	Boat3->AddPoint(0.2,1.0);	Boat3->AddPoint(0.3,0.7);	Boat3->AddPoint(0.3,-0.2);	Boat3->AddPoint(0.0,-1.0);	
	
	Append(Boat1);
	Append(Boat2);
	Append(Boat3);

}

CBoats::~CBoats()
{

}

void CBoats::Append(CBoat *boat)
{
	vBoats.push_back(boat);

}

size_t CBoats::GetCount()
{
	return vBoats.size();
}

CBoat *CBoats::GetBoat(size_t id)
{
	return vBoats[id];
}

