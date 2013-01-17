#ifndef __TOOLS
#define __TOOLS

#include <wx/wx.h>
#include "NaviBroker.h"

char *gen_random(const int len);
wxString GenerateRandomFileName(wxString dir, wxString ext, int len);
wxString GetWorkDir(void);
void PrintInfo(CNaviBroker *Broker,int UID,wchar_t *text);
wxString ConvertDegree(float degree);
double ConvertDegreeDouble(float degree);
wxString FormatLongitude(float x);
wxString FormatLatitude(float y);
double DD(float DM);
wxString GetMsg(int id);
void nvMidPoint(double lon1, double lat1,double lon2, double lat2, double *v1, double *v2);
double nvDistance(double lon1, double lat1, double lon2, double lat2, size_t distanceunit);
double nvToRad( double degree );
wxString GetDistanceUnit(size_t id);
wxString GetDistanceName(size_t id);
wxString GetProductInfo();
wxString GetProductName();
#endif