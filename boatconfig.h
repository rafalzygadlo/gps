#ifndef __BOATCONFIG
#define __BOATCONFIG

#include <wx/wx.h>
#include "boat.h"

class CBoatConfig: public wxDialog
{

	CBoatPanel *BoatPanel;
	CBoats *Boats;
	void OnBoat(wxCommandEvent &event);

public:

	CBoatConfig();
	~CBoatConfig();
		
	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_BOAT = 1243
	};
	
};

#endif