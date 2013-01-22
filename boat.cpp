
#include "boat.h"
#include "tools.h"



CBoat::CBoat()
{
	
}

CBoat::~CBoat()
{
	vPoints.clear();
}

void CBoat::AddPoint(double x, double y)
{
	SPoint pt;
	pt.x = x;
	pt.y = y;
	vPoints.push_back(pt);
}

SPoint CBoat::GetPoint(size_t id)
{
	return vPoints[id];
}

size_t CBoat::GetCount()
{
	return vPoints.size();
}

//wxGLContext *CBoat::GetBoatPanel()
//{
	//return BoatPanel;
//}

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
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
	glTranslatef(0.0,0.0,0.0);
	
	glPointSize(5);
	glColor4f(0.0f,0.0f,0.0f,1.0f);
	glBegin(GL_POINTS);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1.0f,1.0f,0.0f);
		glVertex3f(-1.0f,-1.0f,0.0f);
		glVertex3f(1.0f,-1.0f,0.0f);
		glVertex3f(-1.0f,1.0f,0.0f);
	glEnd();
	glPointSize(1);
			
	
	glColor4f(0.0f,0.0f,1.0f,0.5f);
	RenderGeometry(GL_LINE_LOOP,&vPoints[0],vPoints.size());
	
	glColor4f(0.0f,0.0f,1.0f,0.f);
	RenderGeometry(GL_POLYGON,&vPoints[0],vPoints.size());

	glColor4f(1.0f,0.0f,0.0f,0.5f);
	glPointSize(5);
	RenderGeometry(GL_POINTS,&vPoints[0],vPoints.size());
	
	glDisable(GL_BLEND);

}


BEGIN_EVENT_TABLE(CBoatPanel,wxGLCanvas)
	EVT_PAINT(CBoatPanel::OnPaint)
	EVT_SIZE(CBoatPanel::OnSize)
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
	
	}else{
		
		//dc.DrawText(_("Choose boat"),0,0);
	}
	
	SwapBuffers();

}


CBoats::CBoats()
{
	CBoat *Boat1 = new CBoat();
	Boat1->SetName(_("Ship 1"));
    Boat1->AddPoint(0.0,-1.0);	Boat1->AddPoint(-0.3,-0.5); Boat1->AddPoint(-0.3,1.0); Boat1->AddPoint(0.3,1.0); Boat1->AddPoint(0.3,-0.5);	
		
	CBoat *Boat2 = new CBoat();
	Boat2->SetName(_("Ship 2"));
	Boat2->AddPoint(0.0,-1.0); 
	Boat2->AddPoint(-0.25,-0.5);	Boat2->AddPoint(-0.3,-0.3); Boat2->AddPoint(-0.3,0.7); Boat2->AddPoint(-0.2,1.0); 
	Boat2->AddPoint(0.2,1.0); Boat2->AddPoint(0.3,0.7); Boat2->AddPoint(0.3,-0.3); Boat2->AddPoint(0.25,-0.5);	
		
	CBoat *Boat3 = new CBoat();
	Boat3->SetName(_("Boat"));
	Boat3->AddPoint(0.0,-1.0);	Boat3->AddPoint(-0.3,-0.2);	Boat3->AddPoint(-0.3,0.7);	Boat3->AddPoint(-0.2,1.0); Boat3->AddPoint(0.2,1.0); Boat3->AddPoint(0.3,0.7); Boat3->AddPoint(0.3,-0.2);	
	
	
	Append(Boat1);
	Append(Boat2);
	Append(Boat3);

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

