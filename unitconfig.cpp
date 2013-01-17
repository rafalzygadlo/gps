#include <wx/hyperlink.h>
#include "unitconfig.h"
#include "tools.h"
#include "conf.h"

BEGIN_EVENT_TABLE(CUnitConfig,wxDialog)
	EVT_RADIOBUTTON(wxID_ANY,CUnitConfig::OnRadio)
END_EVENT_TABLE()

CUnitConfig::CUnitConfig()
:wxDialog( NULL,wxID_ANY, GetProductName(), wxDefaultPosition, wxDefaultSize )
{
	Unit = 0;
	
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel->SetBackgroundColour(wxColor(255,255,255));
	Panel->SetSizer(PanelSizer);
	
	wxFont font;
	font.SetPointSize(14);
	
	wxStaticText *LabelDistance = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_DISTANCE_UNITS) ,wxDefaultPosition,wxDefaultSize);
	LabelDistance->SetFont(font);
	PanelSizer->Add(LabelDistance,0,wxALL,5);
		
	for(size_t i = 0; i < nvDistanceSize;i++)
	{ 
		wxRadioButton *Radio = new wxRadioButton(Panel,ID_RADIO + i,wxString::Format(_("%s - %s"), GetDistanceName(i).wc_str(), GetDistanceUnit(i).wc_str() ),wxDefaultPosition,wxDefaultSize);
		Radios.Add(Radio);
		PanelSizer->Add(Radio,0,wxALL,5);
	}
	
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
	
}

CUnitConfig::~CUnitConfig()
{
	Radios.Clear();
}

void CUnitConfig::OnRadio(wxCommandEvent &event)
{
	Unit = event.GetId() - ID_RADIO;
}

size_t CUnitConfig::GetUnit()
{
	return Unit;
}

void CUnitConfig::SetUnit(size_t val)
{
	
	Unit = val;

	for(size_t i = 0; i < Radios.size();i++)
	{
		wxRadioButton *Radio =  (wxRadioButton*)Radios.Item(i);
		if(Unit == i)
			Radio->SetValue(true);
	}
	
}
