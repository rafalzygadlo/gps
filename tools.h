#ifndef __TOOLS
#define __TOOLS

#include <wx/wx.h>
#include "NaviBroker.h"

char *gen_random(const int len) ;
wxString GenerateRandomFileName(wxString dir, wxString ext, int len);
wxString GetWorkDir(void);
void PrintInfo(CNaviBroker *Broker,int UID,wchar_t *text);
wxString ConvertDegree(float degree) ;
wxString FormatLongitude(float x);
wxString FormatLatitude(float y);

#endif