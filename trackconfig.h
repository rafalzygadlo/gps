#ifndef __TRACKCONFIG
#define __TRACKCONFIG

#include <wx/wx.h>

class CTrackConfig: public wxDialog
{
	size_t Unit;
	wxArrayPtrVoid Radios;
	void OnRadio(wxCommandEvent &event);
						
public:

	CTrackConfig();
	~CTrackConfig();
	void SetUnit(size_t val);
	size_t GetUnit();
	
	DECLARE_EVENT_TABLE();
	enum
	{
		ID_RADIO = 2234,
		
	};
	
};

#endif