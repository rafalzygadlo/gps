#include <wx/hyperlink.h>
#include "trackconfig.h"
#include "tools.h"
#include "conf.h"

BEGIN_EVENT_TABLE(CTrackConfig,wxDialog)
END_EVENT_TABLE()

CTrackConfig::CTrackConfig()
:wxDialog( NULL,wxID_ANY, GetProductName(), wxDefaultPosition, wxDefaultSize )
{
		
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel->SetBackgroundColour(wxColor(255,255,255));
	Panel->SetSizer(PanelSizer);
	
	wxFont font;
	font.SetPointSize(TITLE_FONT_SIZE);
	
	wxStaticText *LabelDistance = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_NEW_TRACK_RECORD) ,wxDefaultPosition,wxDefaultSize);
	LabelDistance->SetFont(font);
	PanelSizer->Add(LabelDistance,0,wxALL,5);
		
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

	GetSizer()->SetSizeHints(this);
	Center();
	
}

CTrackConfig::~CTrackConfig()
{
	Radios.Clear();
}

void CTrackConfig::OnRadio(wxCommandEvent &event)
{
	Unit = event.GetId() - ID_RADIO;
}

size_t CTrackConfig::GetUnit()
{
	return Unit;
}

void CTrackConfig::SetUnit(size_t val)
{
	
	Unit = val;

	for(size_t i = 0; i < Radios.size();i++)
	{
		wxRadioButton *Radio =  (wxRadioButton*)Radios.Item(i);
		if(Unit == i)
			Radio->SetValue(true);
	}
	
}
