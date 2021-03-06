#include "conf.h"
#include "tools.h"
#include <wx/stdpaths.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int GlobalLanguageID;
wxMutex *mutex = new wxMutex;
const wxChar *nvLanguage[2][31] = 
{ 
	/*EN*/
	{
		_("Connect"),
		_("Disconnect"),
		_("Port scanning on demand.\nWe do not check the available ports automatically because for some devices such as bluetooth,\nit takes a long time and it looks as if the program has crashed.\nThat's why we provide manual search for ports."),
		_("Scan for available ports"),
		_("Close"),
		_("Show Log Window"),
		_("Scaning ports. Please wait."),
		_("Gps is not configured. Go to Settings -> GPS."),
		_("Port name"),
		_("Baud speed"),
		_("Show signals"),
		_("Font %s not found in program folder.\nCopy font file to the program folder and start plugin again."),
		_("Distance unit"),
		_("Ok"),
		_("Cancel"),
		_("Alarm configuration"),
		_("Boat Settings"),
		_("Gps"),
		_("Connection Settings"),
		_("Distance Unit Settings"),
		_("Classic Ship"),
		_("Ship"),
		_("Classic Boat"),
		_("Boat"),
		_("Triangle"),
		_("Bad CRC"),
		_("Status"),
		_("Connected"),
		_("Number of NMEA lines"),
		_("Signal Quality"),
		_("Gps RECORD TRACK"),
		
		
	},
	
	/*PL*/
	{
		_("Abc"),

	}

};

const wxChar *nvDistanceN[2][3] = 
{ 
	//en
	{
		_("Nautic Miles"),
		_("Kilometer"),
		_("Meter"),
	},

	//pl
	{
		_("Mile morskie"),
		_("Kilometry"),
		_("Metry"),
	}

};


const wxChar *nvDistanceU[2][3] = 
{ 
	//en
	{
		_("NM"),
		_("km"),
		_("m"),
	},

	//pl
	{
		_("NM"),
		_("km"),
		_("m"),
	}

};

wxMutex *GetMutex()
{
	return mutex;
}

wxString GetProductInfo()
{
	return wxString::Format(_("%s %s\n%s"),_(PRODUCT_NAME),_(PRODUCT_VERSION),_(PRODUCT_COPYRIGHT));
}
wxString GetProductName()
{
	return wxString::Format(_("%s %s"),_(PRODUCT_NAME),_(PRODUCT_VERSION));
}


wxString GetDistanceName(size_t id)
{
	return nvDistanceN[GlobalLanguageID][id];
}

wxString GetDistanceUnit(size_t id)
{
	return nvDistanceU[GlobalLanguageID][id];
}


wxString GetMsg(int id)
{
	return nvLanguage[GlobalLanguageID][id];
}


double DD( float DM ) 
{

	int ddeg = ( int )(DM / 100);
	double min =  ( double )( DM / 100 - ddeg);
	double x = double ( min / 60 ) * 100;
	double a = ( double ) ddeg + x;

	return a;

}

wxString ConvertDegree(float degree) 
{
	int decimal = (int)degree;
    float minutes = (float)(degree - decimal) *100;
    return wxString::Format(_("%02d %02.2f'"),decimal, minutes);

}

wxString FormatLongitude(float x) 
{
      wxString str;

      if (x > 0.0f) {
        if (x <= 180.0f)
			str = wxString::Format(_("%s E"), ConvertDegree(x).wc_str());
        else
			str = wxString::Format(_("%s W"), ConvertDegree(360 - x).wc_str());
      } else {
        if (x >= -180.0f)
			str = wxString::Format(_("%s W"), ConvertDegree(-x).wc_str());
        else
			str = wxString::Format(_("%s E"), ConvertDegree(x+360).wc_str());
            
      }
      return str;
}



wxString FormatLatitude(float y) 
{
	
	wxString str;

    if (y > 0)
		str = wxString::Format(_("%s N"), ConvertDegree(y).wc_str());
    else
		str = wxString::Format(_("%s S"), ConvertDegree(-y).wc_str());

    return str;

}

void PrintInfo(CNaviBroker *Broker,int UID,wchar_t *text)
{
//	if(Broker != NULL)
//		Broker->PrintInfoBlock(Broker->GetParentPtr(), UID , text, 5);

}

char *gen_random(const int len) 
{
	char *s = (char*)malloc(len + 1);

	srand( (unsigned int) time(NULL));

	for (int i = 0; i < len; ++i) {
         int randomChar = rand()%(26+26+10);
         if (randomChar < 26)
             s[i] = 'a' + randomChar;
         else if (randomChar < 26+26)
             s[i] = 'A' + randomChar - 26;
         else
             s[i] = '0' + randomChar - 26 - 26;
     }
	 s[len] = 0;

	 return s;
}

wxString GenerateRandomFileName(wxString dir, wxString ext, int len)
{
	// genarate random name
	static wxString DestinationPath;
	wxString RandomName;
	char *random;
	
	do
	{
		random = gen_random(len);
		wxString RandomUTF8(random, wxConvUTF8);
		RandomName = RandomUTF8;
		RandomUTF8.Clear();
		DestinationPath.Printf(wxT("%s%s%s.%s"),dir.wc_str(),wxT(DIR_SEPARATOR),RandomName.wc_str(),ext.wc_str());
	}
	while(wxFileExists(DestinationPath));

	free( random );
	return DestinationPath;
}

wxString GetWorkDir(void)
{
	static wxString buffer;
	wxStandardPaths *Paths = new wxStandardPaths();
 	buffer.Printf(wxT("%s%s%s%s"), Paths->GetUserDataDir().wc_str(wxConvUTF8),  wxT(DIR_SEPARATOR), wxT(DIR_WORKDIR), wxT(DIR_SEPARATOR) );
	delete Paths;
	return buffer;
}

void nvMidPoint(double lon1, double lat1,double lon2, double lat2, double *v1, double *v2)
{
	*v1 = (lon1 + lon2) / 2;
	*v2 = (lat1 + lat2) / 2;
}

double nvDistance(double lon1, double lat1, double lon2, double lat2, size_t distanceunit) 
{

	double dLat = _nvToRad( lat2 - lat1 );
	double dLon = _nvToRad( lon2 - lon1 );
	double R = 6371.0;

	double a = ( sin(dLat/2) * sin(dLat/2) )  +  ( cos( _nvToRad(lat1) ) * cos( _nvToRad(lat2) ) * sin(dLon/2) * sin(dLon/2) );
	double c = 2 * atan2( sqrt(a), sqrt( 1 - a ) );

	switch( distanceunit ) {

	case nvKilometer: return R * c;
		case nvNauticMiles: return (R *c) / 1.852;
		case nvMeter : return R * c * 1000;
		default:
			return (R *c) / 1.852;

	}
}

double _nvToRad( double degree ) 
{
	return (NV_PI * degree / 180 );
}

CBoat *CreateBoat1()
{
	CBoat *Boat = new CBoat();
	Boat->SetName(GetMsg(MSG_SHIP1));
	CNaviGeometry *Geometry = Boat->CreateGeometry();
	Boat->AddGeometry(Geometry);
	CNaviVertexArray *VertexArray = Boat->CreateVertexArray();
	Geometry->AddVertexArray(VertexArray);
	
	VertexArray->AddVertex(0.0,-1.0,0.0); 
	VertexArray->AddVertex(-0.3,-0.5,0.0); 
	VertexArray->AddVertex(-0.3,1.0,0.0); 
	VertexArray->AddVertex(0.3,1.0,0.0); 
	VertexArray->AddVertex(0.3,-0.5,0.0);
	
	return Boat;

}

CBoat *CreateBoat2()
{
	CBoat *Boat = new CBoat();
	Boat->SetName(GetMsg(MSG_BOAT1));
	CNaviGeometry *Geometry = Boat->CreateGeometry();
	Boat->AddGeometry(Geometry);
	CNaviVertexArray *VertexArray = Boat->CreateVertexArray();
	Geometry->AddVertexArray(VertexArray);
	
	VertexArray->AddVertex(0.0,-1.0,0.0); 
	VertexArray->AddVertex(-0.3,-0.2,0.0); 
	VertexArray->AddVertex(-0.3,1.0,0.0);	
	VertexArray->AddVertex(0.3,1.0,0.0); 
	VertexArray->AddVertex(0.3,-0.2,0.0); 
		
	return Boat;
	
}


CBoat *CreateBoat3()
{
	CBoat *Boat = new CBoat();
	Boat->SetName(GetMsg(MSG_SHIP2));
	CNaviGeometry *Geometry = Boat->CreateGeometry();
	Boat->AddGeometry(Geometry);
	CNaviVertexArray *VertexArray = Boat->CreateVertexArray();
	Geometry->AddVertexArray(VertexArray);
	
	VertexArray->AddVertex(0.0,-1.0,0.0);
	VertexArray->AddVertex(-0.25,-0.5,0.0);
	VertexArray->AddVertex(-0.3,-0.3,0.0);
	VertexArray->AddVertex(-0.3,0.7,0.0);
	VertexArray->AddVertex(-0.2,1.0,0.0);
	VertexArray->AddVertex(0.2,1.0,0.0);
	VertexArray->AddVertex(0.3,0.7,0.0);
	VertexArray->AddVertex(0.3,-0.3,0.0);
	VertexArray->AddVertex(0.25,-0.5,0.0);

	return Boat;
}

CBoat *CreateBoat4()
{
	CBoat *Boat = new CBoat();
	Boat->SetName(GetMsg(MSG_BOAT2));
	CNaviGeometry *Geometry = Boat->CreateGeometry();
	Boat->AddGeometry(Geometry);
	CNaviVertexArray *VertexArray = Boat->CreateVertexArray();
	Geometry->AddVertexArray(VertexArray);
	
	VertexArray->AddVertex(0.0,-1.0,0.0); 
	VertexArray->AddVertex(-0.3,-0.2,0.0); 
	VertexArray->AddVertex(-0.3,0.7,0.0);	
	VertexArray->AddVertex(-0.2,1.0,0.0); 
	VertexArray->AddVertex(0.2,1.0,0.0); 
	VertexArray->AddVertex(0.3,0.7,0.0); 
	VertexArray->AddVertex(0.3,-0.2,0.0);	
	
	return Boat;
	
}

