#ifndef __BOATCONFIG
#define __BOATCONFIG

#include <wx/wx.h>
#include "boat.h"

class CBoatConfig: public wxDialog
{

	CBoatPanel *BoatPanel;
	CBoats *Boats;
	wxListBox *ListBoat;
	void OnBoat(wxCommandEvent &event);

public:

	CBoatConfig();
	~CBoatConfig();
	size_t GetId();
		
	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_BOAT = 1243
	};
	
};

#endif