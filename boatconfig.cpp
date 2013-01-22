#include <wx/hyperlink.h>
#include "boatconfig.h"
#include "tools.h"
#include "conf.h"
#include "boat.h"

BEGIN_EVENT_TABLE(CBoatConfig,wxDialog)
	EVT_COMBOBOX(ID_BOAT,CBoatConfig::OnBoat)
END_EVENT_TABLE()

CBoatConfig::CBoatConfig()
:wxDialog( NULL,wxID_ANY, GetProductName(), wxDefaultPosition, wxDefaultSize )
{
	
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	//Panel->SetBackgroundColour(wxColor(255,255,255));
	Panel->SetSizer(PanelSizer);
	
	wxComboBox *ComboBoat = new wxComboBox(Panel,ID_BOAT,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,wxCB_READONLY);
	PanelSizer->Add(ComboBoat,0,wxALL,5);

	BoatPanel = new CBoatPanel(Panel);
	PanelSizer->Add(BoatPanel,0,wxALL,5);
				
	MainSizer->Add(Panel,1,wxALL|wxEXPAND,0);
	
	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	MainSizer->Add(ButtonSizer,0,wxALL|wxEXPAND,5);

	wxStaticText *LabelProductInfo = new wxStaticText(this,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(LabelProductInfo,0,wxALL,5);
	
	wxButton *ButtonOk = new wxButton(this,wxID_OK,GetMsg(MSG_OK));
	ButtonSizer->Add(ButtonOk,0,wxALL|wxALIGN_RIGHT,5);
	
	wxButton *ButtonCancel = new wxButton(this,wxID_CANCEL,GetMsg(MSG_CANCEL));
	ButtonSizer->Add(ButtonCancel,0,wxALL|wxALIGN_RIGHT,5);

	this->SetSizer(MainSizer);
	Boats = new CBoats();

	for(size_t i = 0; i < Boats->GetCount(); i++)
	{
		CBoat *Boat = Boats->GetBoat(i);
		ComboBoat->Append( Boat->GetName());
	} 
	
	GetSizer()->SetSizeHints(this);
	
}

CBoatConfig::~CBoatConfig()
{
	delete Boats;
}

void CBoatConfig::OnBoat(wxCommandEvent &event)
{
	BoatPanel->SetBoat(Boats->GetBoat(event.GetSelection()));
}