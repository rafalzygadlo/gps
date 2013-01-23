
#include "boat.h"
#include "tools.h"


CBoatPoints::CBoatPoints()
{
	
}

CBoatPoints::~CBoatPoints()
{
	vPoints.clear();
}


void CBoatPoints::AddPoint(double x, double y)
{
	SPoint pt;
	pt.x = x;
	pt.y = y;
	vPoints.push_back(pt);
}

SPoint CBoatPoints::GetPoint(size_t id)
{
	return vPoints[id];
}

size_t CBoatPoints::GetCount()
{
	return vPoints.size();
}

// . . . . . . . . . . . . .. . . 


CBoat::CBoat()
{
	
}

CBoat::~CBoat()
{
	
}

void CBoat::AddGeometry(CBoatPoints *BoatPoints)
{
	GeometryList.Add(BoatPoints);		
}

void *CBoat::GetGeometry(size_t id)
{
	return GeometryList.Item(id);
}

size_t CBoat::GetCount()
{
	return GeometryList.size();
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

	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
	glTranslatef(0.0,0.0,0.0);
	glPointSize(10);		
	glColor4f(0.0f,0.0f,0.0f,1.0f);
	glBegin(GL_POINTS);
		glVertex3f(0.0f,0.0f,0.0f);
	glEnd();
	
	glPointSize(5);
	glBegin(GL_POINTS);
		glVertex3f(1.0f,1.0f,0.0f);
		glVertex3f(1.0f,-1.0f,0.0f);
		glVertex3f(-1.0f,-1.0f,0.0f);
		glVertex3f(-1.0f,1.0f,0.0f);
	glEnd();
	glPointSize(1);
	
	glColor4f(0.0f,0.0f,0.0f,0.1f);
	glBegin(GL_QUADS);
		glVertex3f(1.0f,1.0f,0.0f);
		glVertex3f(-1.0f,1.0f,0.0f);
		glVertex3f(-1.0f,-1.0f,0.0f);
		glVertex3f(1.0f,-1.0f,0.0f);
	glEnd();
	
	
	for(size_t i = 0; i < GeometryList.size(); i++)
	{
		CBoatPoints *Points = (CBoatPoints*)GeometryList.Item(i);
		
		glColor4f(0.0f,0.0f,1.0f,0.5f);
		glBegin(GL_LINE_LOOP);
		
		size_t j = 0;
		for(j = 0; j < Points->GetCount(); j++)
			glVertex2f(Points->GetPoint(j).x,Points->GetPoint(j).y);	
		glEnd();
			
		glColor4f(0.0f,0.0f,1.0f,0.2f);
		glBegin(GL_POLYGON);
		for(j = 0; j < Points->GetCount(); j++)
			glVertex2f(Points->GetPoint(j).x,Points->GetPoint(j).y);	
		glEnd();
		
		glColor4f(1.0f,0.0f,0.0f,0.5f);
		glPointSize(5);
		
		glBegin(GL_POINTS);
		for(j = 0; j < Points->GetCount(); j++)
			glVertex2f(Points->GetPoint(j).x,Points->GetPoint(j).y);	
		glEnd();
		
	}

	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_BLEND);

}


BEGIN_EVENT_TABLE(CBoatPanel,wxGLCanvas)
	EVT_PAINT(CBoatPanel::OnPaint)
	EVT_SIZE(CBoatPanel::OnSize)
	EVT_MOUSE_EVENTS(CBoatPanel::OnMouse)
END_EVENT_TABLE()


CBoatPanel::CBoatPanel(wxWindow *parent)
 :wxGLCanvas( parent, (wxGLCanvas*) NULL, wxID_ANY, wxDefaultPosition, wxSize(200,200))
 
{
	GLContext = new wxGLContext(this);
	Boat = NULL;
	
}

CBoatPanel::~CBoatPanel()
{
		
}

void CBoatPanel::SetBoat(CBoat *boat)
{
	Boat = boat;
	Refresh();
}

void CBoatPanel::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	SetCurrent(*GLContext);
	Render();
}

void CBoatPanel::OnSize(wxSizeEvent &event)
{
	int w, h;
	GetClientSize(&w, &h);
	 
	ScreenWidth = w;
	ScreenHeight = h;
}

void CBoatPanel::OnMouse(wxMouseEvent &event)
{
	int _X = event.GetX();
    int _Y = event.GetY();
}

void CBoatPanel::UpdateViewPort()
{
    glViewport(0, 0, (GLint) ScreenWidth, (GLint) ScreenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(1.0, -1.0, -1.0, 1.0, 0.0, 0.0);
    //glOrtho(0, ScreenWidth, ScreenHeight, 0, 0.0, 1.0f);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotated( 180.0, 0.0, 0.0, 1.0 );
		
}

void CBoatPanel::Render()
{
	UpdateViewPort();
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if(Boat != NULL)
	{
		//glTranslatef(ScreenWidth/2,ScreenHeight/2,1.0f);
		glPushMatrix();
		glScalef(0.8f,0.8f,1.0f);
		Boat->Render();
		glPopMatrix();
	}
	
	SwapBuffers();

}


CBoats::CBoats()
{
	CBoat *Boat1 = new CBoat();
	Boat1->SetName(GetMsg(MSG_SHIP1));
	CBoatPoints *Boat1Points = new CBoatPoints();
    Boat1Points->AddPoint(0.0,-1.0); 
	Boat1Points->AddPoint(-0.3,-0.5); 
	Boat1Points->AddPoint(-0.3,1.0); 
	Boat1Points->AddPoint(0.3,1.0); 
	Boat1Points->AddPoint(0.3,-0.5);
	Boat1->AddGeometry(Boat1Points);

	CBoat *Boat2 = new CBoat();
	Boat2->SetName(GetMsg(MSG_SHIP2));
	CBoatPoints *Boat2Points = new CBoatPoints();
	Boat2Points->AddPoint(0.0,-1.0); 
	Boat2Points->AddPoint(-0.25,-0.5);	
	Boat2Points->AddPoint(-0.3,-0.3); 
	Boat2Points->AddPoint(-0.3,0.7); 
	Boat2Points->AddPoint(-0.2,1.0); 
	Boat2Points->AddPoint(0.2,1.0); 
	Boat2Points->AddPoint(0.3,0.7); 
	Boat2Points->AddPoint(0.3,-0.3); 
	Boat2Points->AddPoint(0.25,-0.5);	
	Boat2->AddGeometry(Boat2Points);

	CBoat *Boat3 = new CBoat();
	Boat3->SetName(GetMsg(MSG_BOAT1));
	CBoatPoints *Boat3Points = new CBoatPoints();
	Boat3Points->AddPoint(0.0,-1.0); 
	Boat3Points->AddPoint(-0.3,-0.2); 
	Boat3Points->AddPoint(-0.3,0.7);	
	Boat3Points->AddPoint(-0.2,1.0); 
	Boat3Points->AddPoint(0.2,1.0); 
	Boat3Points->AddPoint(0.3,0.7); 
	Boat3Points->AddPoint(0.3,-0.2);	
	Boat3->AddGeometry(Boat3Points);
	
	CBoat *Boat4 = new CBoat();
	Boat4->SetName(GetMsg(MSG_BOAT2));
	CBoatPoints *Boat4Points = new CBoatPoints();
	Boat4Points->AddPoint(0.0,-1.0);	
	Boat4Points->AddPoint(-0.3,-0.2);	
	Boat4Points->AddPoint(-0.3,1.0); 
	Boat4Points->AddPoint(0.3,1.0); 
	Boat4Points->AddPoint(0.3,-0.2);	
	Boat4->AddGeometry(Boat4Points);
	
	CBoat *Boat5 = new CBoat();
	Boat5->SetName(GetMsg(MSG_TRIANGLE));
	CBoatPoints *Boat5Points = new CBoatPoints();
	Boat5Points->AddPoint(0.0,-1.0); 
	Boat5Points->AddPoint(-0.3,1.0); 
	Boat5Points->AddPoint(0.3,1.0);
	Boat5->AddGeometry(Boat5Points);
		
	Append(Boat2);
	Append(Boat1);
	Append(Boat3);
	Append(Boat4);
	Append(Boat5);
	
}

CBoats::~CBoats()
{
	for(size_t i = 0; i < vBoats.size(); i++)
	{
		delete vBoats[i];
	}
	
	vBoats.clear();
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

