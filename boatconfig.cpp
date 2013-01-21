#include <wx/hyperlink.h>
#include "boatconfig.h"
#include "tools.h"
#include "conf.h"
#include "boat.h"

BEGIN_EVENT_TABLE(CBoatConfig,wxDialog)
END_EVENT_TABLE()

CBoatConfig::CBoatConfig()
:wxDialog( NULL,wxID_ANY, GetProductName(), wxDefaultPosition, wxDefaultSize )
{
	
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel->SetBackgroundColour(wxColor(255,255,255));
	Panel->SetSizer(PanelSizer);
	
	wxComboBox *b = new wxComboBox(Panel,wxID_ANY);
	PanelSizer->Add(b,0,wxALL,0);

			
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
	CBoats *Boats = new CBoats();

	for(size_t i = 0; i < Boats->GetCount(); i++)
	{
		CBoat *Boat = Boats->GetBoat(i);
		b->Append( Boat->GetName());
		
	} 


	GetSizer()->SetSizeHints(this);
	
}

CBoatConfig::~CBoatConfig()
{

}


//CBoatPanel::CBoatPanel()
//{

//}