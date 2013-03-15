#include <wx/hyperlink.h>
#include "boatconfig.h"
#include "tools.h"
#include "conf.h"
#include "boat.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

BEGIN_EVENT_TABLE(CBoatConfig,wxDialog)
	EVT_LISTBOX(ID_BOAT,CBoatConfig::OnBoat)
END_EVENT_TABLE()

CBoatConfig::CBoatConfig()
:wxDialog( NULL,wxID_ANY, GetProductName(), wxDefaultPosition, wxDefaultSize )
{
	
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel->SetBackgroundColour(wxColor(255,255,255));
	Panel->SetSizer(PanelSizer);
		
	wxFont font;
	font.SetPointSize(TITLE_FONT_SIZE);
	wxBoxSizer *TopSizer = new wxBoxSizer(wxVERTICAL);
	PanelSizer->Add(TopSizer,0,wxALL,5);
	wxStaticText *LabelDistance = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_BOAT_CONFIG) ,wxDefaultPosition,wxDefaultSize);
	LabelDistance->SetFont(font);
	TopSizer->Add(LabelDistance,0,wxALL,5);
	
	wxBoxSizer *HSizer = new wxBoxSizer(wxHORIZONTAL);
	PanelSizer->Add(HSizer,1,wxALL|wxEXPAND,5);
	BoatPanel = new CBoatPanel(Panel);
	HSizer->Add(BoatPanel,1,wxALL|wxEXPAND,5);
	BoatPanel->SetSize(200,200);
	
	ListBoat = new wxListBox(Panel,ID_BOAT,wxDefaultPosition,wxDefaultSize);
	HSizer->Add(ListBoat,1,wxALL|wxEXPAND,5);
	
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
		ListBoat->Append( Boat->GetName());
	} 
	
	ListBoat->SetSelection(0);
	BoatPanel->SetBoat(Boats->GetBoat(0));
	GetSizer()->SetSizeHints(this);
	
}

CBoatConfig::~CBoatConfig()
{
	delete Boats;
}

size_t CBoatConfig::GetId()
{
	return ListBoat->GetSelection();
}

void CBoatConfig::OnBoat(wxCommandEvent &event)
{
	BoatPanel->SetBoat(Boats->GetBoat(event.GetSelection()));
}

void CBoatConfig::SetId(size_t id)
{
	BoatPanel->SetBoat(Boats->GetBoat(id));
	ListBoat->SetSelection(id);
}