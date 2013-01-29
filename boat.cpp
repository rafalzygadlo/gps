#include "boat.h"
#include "tools.h"


CBoat::CBoat()
{
	BoatGeometryGroup = CNaviGeometryGroup::Create(NULL);
		
	CNaviVertexArray *VertexArray = VertexArray = CNaviVertexArray::Create(NULL);
	VertexArray->SetType(EXTERIOR_VERTEX_ARRAY);
	
}

CBoat::~CBoat()
{
	CNaviGeometryGroup::Destroy(BoatGeometryGroup);
}

CNaviGeometry *CBoat::CreateGeometry()
{
	CNaviGeometry *BoatGeometry = CNaviGeometry::Create();
	return BoatGeometry;
}

void CBoat::AddGeometry(CNaviGeometry *geometry)
{
	BoatGeometryGroup->AddGeometry(geometry);
}

CNaviVertexArray *CBoat::CreateVertexArray()
{
	CNaviVertexArray *VertexArray = VertexArray = CNaviVertexArray::Create(NULL);
	VertexArray->SetType(EXTERIOR_VERTEX_ARRAY);
	return VertexArray;
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

void CBoat::RenderBackground()
{
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

}

void CBoat::RenderBoat(bool points)
{
	for(size_t i = 0; i < BoatGeometryGroup->Length(); i++)
	{
		CNaviGeometry *Geometry = BoatGeometryGroup->GetGeometry(i);
			
		Geometry->First();
		while(!Geometry->Eof())
		{
			CNaviVertexArray *VertexArray = Geometry->GetVertexArray();
			VertexArray->First();
			glColor4f(0.0f,0.0f,1.0f,0.5f);
			RenderGeometry(GL_LINE_LOOP,VertexArray->GetRawArray(),VertexArray->Length());

			glColor4f(0.0f,0.0f,1.0f,0.2f);
			RenderGeometry(GL_POLYGON,VertexArray->GetRawArray(),VertexArray->Length());
			
			if(points)
			{			
				glPointSize(8);
				glColor4f(1.0f,0.0f,0.0f,0.2f);
				RenderGeometry(GL_POINTS,VertexArray->GetRawArray(),VertexArray->Length());
				glPointSize(1);
			}
			
			Geometry->Next();
		}
	}
}

void CBoat::Render()
{

	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
	glTranslatef(0.0,0.0,0.0);
	
	RenderBackground();
	RenderBoat(true);
	
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_BLEND);

}


BEGIN_EVENT_TABLE(CBoatPanel,wxGLCanvas)
	EVT_PAINT(CBoatPanel::OnPaint)
	EVT_SIZE(CBoatPanel::OnSize)
	EVT_MOUSE_EVENTS(CBoatPanel::OnMouse)
END_EVENT_TABLE()

CBoatPanel::CBoatPanel(wxWindow *parent)
:wxGLCanvas( parent, (wxGLCanvas*) NULL, wxID_ANY, wxDefaultPosition, wxDefaultSize,wxFULL_REPAINT_ON_RESIZE)
{
	GLContext = new wxGLContext(this);
	Boat = NULL;
	ScreenWidth = 0;
	ScreenHeight = 0;
		
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
	fprintf(stdout,"%d %d\n",ScreenWidth,ScreenHeight);
	ScreenWidth = w;
	ScreenHeight = h;
}

void CBoatPanel::OnMouse(wxMouseEvent &event)
{
	event.Skip();
}

void CBoatPanel::UpdateViewPort()
{
    glViewport(0, 0, (GLint) ScreenWidth, (GLint) ScreenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(1.0, -1.0, -1.0, 1.0, 0.0, 0.0);
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
		glPushMatrix();
		glTranslatef(0.0,0.0,0.0f);
		glScalef(0.8f,0.8f,1.0f);
		Boat->Render();
		glPopMatrix();
	}
	
	SwapBuffers();

}


CBoats::CBoats()
{
	
	CBoat *Boat = CreateBoat1();
	Append(Boat);
	Boat = CreateBoat2();
	Append(Boat);
	Boat = CreateBoat3();
	Append(Boat);
	Boat = CreateBoat4();
	Append(Boat);

	/*
	
	
	CBoat *Boat5 = new CBoat();
	Boat5->SetName(GetMsg(MSG_TRIANGLE));
	CBoatPoints *Boat5Points = new CBoatPoints();
	Boat5Points->AddPoint(0.0,-1.0); 
	Boat5Points->AddPoint(-0.3,1.0); 
	Boat5Points->AddPoint(0.3,1.0);
	Boat5->AddGeometry(Boat5Points);
	*/
	
	//Append(Boat3);
	//Append(Boat4);
	//Append(Boat5);
	//Append(Boat6);
	
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

