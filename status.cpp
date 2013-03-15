#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/dirdlg.h>
#include <wx/hyperlink.h>
#include <wx/settings.h>
#include "conf.h"
#include "dll.h"
#include "status.h"
#include "NaviMapIOApi.h"
#include "conf.h"
#include "tools.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


BEGIN_EVENT_TABLE(CStatus,wxDialog)
	EVT_BUTTON(ID_CLOSE,OnCloseButton)
END_EVENT_TABLE()

CStatus::CStatus(CMySerial *serial)
	:wxDialog(NULL,wxID_ANY, GetProductName() , wxDefaultPosition, wxDefaultSize )
{
	
	MainSizer = new wxBoxSizer(wxVERTICAL);
	MainSizer->SetMinSize(300,-1);
	
	wxPanel *Panel1 = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel1->SetBackgroundColour(*wxWHITE);
	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxVERTICAL);
	
	Panel1->SetSizer(Panel1Sizer);


	wxFont font;
	font.SetPointSize(TITLE_FONT_SIZE);
	wxBoxSizer *TopSizer = new wxBoxSizer(wxVERTICAL);
	Panel1Sizer->Add(TopSizer,0,wxALL,5);
	wxStaticText *LabelDistance = new wxStaticText(Panel1,wxID_ANY,GetMsg(MSG_STATUS) ,wxDefaultPosition,wxDefaultSize);
	LabelDistance->SetFont(font);
	TopSizer->Add(LabelDistance,0,wxALL,5);

		
	wxTextCtrl *Status = new wxTextCtrl(Panel1,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(400,200),wxTE_MULTILINE | wxTE_READONLY |wxTE_CAPITALIZE);
	Panel1Sizer->Add(Status,0,wxALL|wxEXPAND,0);

	wxString port(serial->GetPortName(),wxConvUTF8);
	Status->AppendText(wxString::Format(_("%s: %s\n"),GetMsg(MSG_PORT).wc_str(),port.wc_str()));
	Status->AppendText(wxString::Format(_("%s: %d\n"),GetMsg(MSG_BAUD).wc_str(),serial->GetBaudRate()));
	Status->AppendText(wxString::Format(_("%s: %d\n"),GetMsg(MSG_CONNECTED).wc_str(),serial->IsConnected()));
	Status->AppendText(wxString::Format(_("%s: %d\n"),GetMsg(MSG_BAD_CRC).wc_str(),serial->GetBadCRC()));
	Status->AppendText(wxString::Format(_("%s: %d\n"),GetMsg(MSG_NMEA_LINES).wc_str(),serial->GetLinesCount()));
	
	if(serial->GetLinesCount() == 0)
		Status->AppendText(_("N/A"));	
	else
		Status->AppendText(wxString::Format(_("%s: %d%%\n\n"),GetMsg(MSG_SIGNAL_QUALITY).wc_str(),serial->GetSignalQuality()));	

	for(size_t i = 0; i < serial->GetSignalCount();i++)
	{
		wxString name((char*)serial->GetSignal(i)->name,wxConvUTF8);
		wxString nmea((char*)serial->GetSignal(i)->nmea,wxConvUTF8);
		
		Status->AppendText(wxString::Format(_("%s: %d\n"),name.wc_str(),serial->GetSignal(i)->count));
	}
			
	this->SetSizer(MainSizer);
	
	MainSizer->Add(Panel1,1,wxALL|wxEXPAND,0);
	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	MainSizer->Add(ButtonSizer,0,wxALL|wxEXPAND,5);
	
	wxStaticText *LabelProductInfo = new wxStaticText(this,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(LabelProductInfo,0,wxALL|wxEXPAND,5);
	
	ButtonSizer->AddStretchSpacer(1);
	wxButton *ButtonOk = new wxButton(this,wxID_OK,_("Ok"),wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(ButtonOk,0,wxALL|wxALIGN_RIGHT,5);
		
	MainSizer->SetSizeHints(this);
	Center();
		
}	

CStatus::~CStatus(void)
{

}

void CStatus::ShowWindow(bool show)
{
	Show(show);
}

void CStatus::OnCloseButton(wxCommandEvent &event)
{	
	Hide();
}

void CStatus::OnClose(wxCloseEvent &event)
{
	Destroy();
}
