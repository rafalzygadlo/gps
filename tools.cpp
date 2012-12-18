#include "conf.h"
#include "tools.h"
#include <wx/stdpaths.h>


int GlobalLanguageID;
const wxChar *nvLanguage[2][20] = 
{ 
	/*EN*/
	{
		_("Connect"),
		_("Disconnect"),
		_("Port scanning on demand.\nWe do not check the available ports automatically because for some devices such as bluetooth,\nit takes a long time and it looks as if the program has crashed.\nThat's why we provide manual search for ports."),
		_("Scan for available ports"),
		_("Ok"),
		_("Show Log Window"),
		_("Scaning ports. Please wait."),
		_("Gps is not configured. Go to Settings -> GPS."),
		_("Port"),
		_("Baud"),
		_("Show signals"),
		
	},
	
	/*PL*/
	{
		_("Abc"),

	}

};

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
	if(Broker != NULL)
		Broker->PrintInfoBlock(Broker->GetParentPtr(), UID , text, 5);

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
