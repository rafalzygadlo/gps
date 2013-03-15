#include <wx/statline.h>
#include "NaviMapIOApi.h"
#include "frame.h"
#include "conf.h"
#include "dll.h"
#include "serial.h"
#include "tools.h"
#include "info.h"
#include "status.h"
#include "unitconfig.h"
#include "boatconfig.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

DEFINE_EVENT_TYPE(nvEVT_SET_LOG)
DEFINE_EVENT_TYPE(nvEVT_SET_PORT)
DEFINE_EVENT_TYPE(nvEVT_SET_BAUD)

BEGIN_EVENT_TABLE(CMyFrame,wxDialog)
	EVT_BUTTON(ID_START,CMyFrame::OnStartButton)
	EVT_BUTTON(ID_STOP,CMyFrame::OnStopButton)
	EVT_CHECKBOX(ID_CHECK_LOG,CMyFrame::OnCheckLog)
	EVT_COMBOBOX(ID_PORTS,CMyFrame::OnComboBox)
	EVT_HYPERLINK(ID_SCAN,CMyFrame::OnScan)
	EVT_HYPERLINK(ID_INFO,CMyFrame::OnInfo)
	EVT_HYPERLINK(ID_UNIT,CMyFrame::OnUnit)
	EVT_HYPERLINK(ID_BOAT,CMyFrame::OnBoat)
	EVT_COMMAND(ID_SET_LOG,nvEVT_SET_LOG,CMyFrame::OnSetLog)	//my own defined event
//	EVT_COMMAND(ID_SET_PORT,nvEVT_SET_PORT,CMyFrame::OnSetPort)	//my own defined event
	EVT_COMMAND(ID_SET_BAUD,nvEVT_SET_BAUD,CMyFrame::OnSetBaud)	//my own defined event
END_EVENT_TABLE()


CMyFrame::CMyFrame(CMapPlugin *_MapPlugin)
:wxDialog(NULL, wxID_ANY, GetProductName(), wxDefaultPosition, wxDefaultSize )
{
	Unit = _MapPlugin->GetUnit();
	PortSelection = 0;
	MapPlugin = _MapPlugin;
	ConfigPath = wxString::Format(wxT("%s%s"),GetWorkDir().wc_str(),_(PLUGIN_CONFIG_FILE));
	FileConfig = new wxFileConfig(_("gps"),wxEmptyString,ConfigPath,wxEmptyString);
	_Start = false;
	_Stop = false;
	_Close = false;
	
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel->SetBackgroundColour(*wxWHITE);
	MainSizer->Add(Panel,1,wxALL|wxEXPAND,0);

	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *TopSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *CenterSizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	CenterSizer->Add(FlexSizer,0,wxALL|wxEXPAND,5);

	wxBoxSizer *BottomSizer = new wxBoxSizer(wxVERTICAL);

	PanelSizer->Add(TopSizer,0,wxEXPAND,0);
	PanelSizer->Add(CenterSizer,0,wxEXPAND,0);
	MainSizer->Add(BottomSizer,0,wxEXPAND,0);

	wxFont font;
	font.SetPointSize(TITLE_FONT_SIZE);
	wxStaticText *LabelTop = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SETTINGS) ,wxDefaultPosition,wxDefaultSize);
	LabelTop->SetFont(font);
	TopSizer->Add(LabelTop,0,wxALL,10);

	wxStaticText *PortLabel = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_PORT));
	FlexSizer->Add(PortLabel,0,wxALL,5);
		
	//font.SetPointSize(8);
	wxBoxSizer *PortSizer = new wxBoxSizer(wxVERTICAL);
	FlexSizer->Add(PortSizer,0,wxALL,0);
	PortComboBox = new wxComboBox(Panel,ID_PORTS,wxEmptyString,wxDefaultPosition,wxDefaultSize,	NULL);
	PortComboBox->Disable();
	PortSizer->Add(PortComboBox,0,wxALL,5);
	wxStaticText *ScanInfo = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_PORT_INFO));
	PortSizer->Add(ScanInfo,0,wxALL|wxEXPAND,5);
	Scan = new wxHyperlinkCtrl(Panel,ID_SCAN,GetMsg(MSG_SCAN),wxEmptyString);
	//Scan->SetFont(font);
	PortSizer->Add(Scan,0,wxALL,2);
		
	wxStaticText *BaudLabel = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_BAUD));
	FlexSizer->Add(BaudLabel,0,wxALL,5);
	BaudComboBox = new wxComboBox(Panel,ID_PORTS,wxEmptyString,wxDefaultPosition,wxDefaultSize,	NULL);
	BaudComboBox->Disable();
	FlexSizer->Add(BaudComboBox,0,wxALL,5);

	//FlexSizer->AddSpacer(1);
	
	
	//button start
		
	//wxStaticLine *line1 = new wxStaticLine(Panel,wxID_ANY);
	//TopSizer->Add(line1,0,wxALL|wxEXPAND,0);
	
	//Info = new wxHyperlinkCtrl(Panel,ID_INFO,GetMsg(MSG_SIGNALS_INFO),wxEmptyString);
	//Info->SetFont(font);
	//TopSizer->Add(Info,0,wxALL,2);

	//wxHyperlinkCtrl *Unit = new wxHyperlinkCtrl(Panel,ID_UNIT,GetMsg(MSG_DISTANCE_UNITS),wxEmptyString);
	//Unit->SetFont(font);
	//TopSizer->Add(Unit,0,wxALL,2);

	//wxHyperlinkCtrl *Alarm = new wxHyperlinkCtrl(Panel,ID_UNIT,GetMsg(MSG_ALARM_CONFIG),wxEmptyString);
	//Alarm->SetFont(font);
	//TopSizer->Add(Alarm,0,wxALL,5);

	//wxHyperlinkCtrl *Boat = new wxHyperlinkCtrl(Panel,ID_BOAT,GetMsg(MSG_BOAT_CONFIG),wxEmptyString);
	//Boat->SetFont(font);
	//TopSizer->Add(Boat,0,wxALL,2);

	//wxStaticLine *line2 = new wxStaticLine(Panel,wxID_ANY);
	//CenterSizer->Add(line2,0,wxALL|wxEXPAND,0);

	//wxBoxSizer *LeftSizer = new wxBoxSizer(wxHORIZONTAL);
	//CenterSizer->Add(LeftSizer,0,wxALL|wxEXPAND,5);
		
	// log window check
	bool chk_log;
	FileConfig->Read(_(KEY_CHECK_LOG),&chk_log,false);
	//CheckLogBox = new wxCheckBox(Panel,ID_CHECK_LOG,GetMsg(MSG_SHOW_LOG),wxDefaultPosition,wxDefaultSize);
	//CheckLogBox->SetValue(chk_log);
	//CenterSizer->Add(CheckLogBox,0,wxALL,5);

	// Log Window on center
	LogText = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE);
	LogText->Show(chk_log);
	LogText->SetMinSize(wxSize(-1,200));
	CenterSizer->Add(LogText,1,wxALL|wxEXPAND,5);
	
	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	ButtonSizer->AddStretchSpacer(1);
	// button start
	StartButton = new wxButton(this,ID_START,GetMsg(MSG_CONNECT),wxDefaultPosition,wxDefaultSize);
	StartButton->Disable();
	ButtonSizer->Add(StartButton,0,wxALL|wxALIGN_RIGHT,10);

	// button stop
	StopButton = new wxButton(this,ID_STOP,GetMsg(MSG_DISCONNECT),wxDefaultPosition,wxDefaultSize);
	StopButton->Disable();
	ButtonSizer->Add(StopButton,0,wxALL|wxALIGN_RIGHT,10);
	BottomSizer->Add(ButtonSizer,0,wxALL|wxALIGN_RIGHT,0);
	
	wxStaticLine *line2 = new wxStaticLine(this,wxID_ANY);
	BottomSizer->Add(line2,0,wxALL|wxEXPAND,0);
	
	// plugin name
	wxBoxSizer *ButtonSizer1 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *LabelProductInfo = new wxStaticText(this,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	ButtonSizer1->Add(LabelProductInfo,0,wxALL|wxEXPAND,10);
		
	// button close
	ButtonSizer1->AddStretchSpacer(1);
	wxButton *ButtonClose = new wxButton(this,wxID_OK,GetMsg(MSG_CLOSE),wxDefaultPosition,wxDefaultSize);
	ButtonSizer1->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,10);
	BottomSizer->Add(ButtonSizer1,0,wxALL|wxEXPAND,0);
	Panel->SetSizer(PanelSizer);
		
	this->SetSizer(MainSizer);

	
	MySerial = MapPlugin->GetMySerial();
	
	if(MapPlugin->GetMySerial() != NULL)
	{
        if(MapPlugin->GetMySerial()->GetWorkingFlag())
		{
            StopButton->Enable();
			PortComboBox->Disable();
			BaudComboBox->Disable();
			Scan->Disable();
		}else{
            StartButton->Enable();
			PortComboBox->Enable();
			BaudComboBox->Enable();
			Scan->Enable();
		}
	}
	
	CMySerial *serial = _MapPlugin->GetMySerial();
	wxString buf(_MapPlugin->GetMySerial()->GetPortName(),wxConvUTF8);
	PortComboBox->SetValue(buf);

	for(size_t i = 0; i < serial->GetBaudInfoLength();i++)
	{
		BaudComboBox->Append(wxString::Format(_("%d"),serial->GetBaudInfo(i)));
	
	}
	
	BaudComboBox->SetValue(wxString::Format(_("%d"),_MapPlugin->GetMySerial()->GetBaudRate()));
		
	PortComboBox->SetDoubleBuffered(true);
	
	if(GetSizer())
		GetSizer()->SetSizeHints(this);

	
	Center();
}

CMyFrame::~CMyFrame(void)
{
	delete FileConfig;
}

void CMyFrame::OnScan(wxHyperlinkEvent &event)
{
	wxWindowDisabler();
	CMyInfo Info(this,GetMsg(MSG_SCANNING_PORTS));
	CMySerial *Serial =  MapPlugin->GetMySerial();
	Serial->ScanPorts();
	wxString value = PortComboBox->GetValue();
	PortComboBox->Clear();
	
	for(size_t i = 0; i < Serial->GetPortInfoLength(); i++)
	{
		wxString port(Serial->GetPortInfo(i).port_name,wxConvUTF8);
		PortComboBox->Append(wxString::Format(_("%s"),port.wc_str()));
	}

	PortComboBox->SetValue(value);

}

void CMyFrame::OnInfo(wxHyperlinkEvent &event)
{
	CStatus *Status = new CStatus(MySerial);
	Status->ShowModal();
	delete Status;

}

void CMyFrame::OnUnit(wxHyperlinkEvent &event)
{
	CUnitConfig *UnitConfig = new CUnitConfig();
	UnitConfig->SetUnit(Unit);
		
	if(UnitConfig->ShowModal() == wxID_OK)
	{
		Unit = UnitConfig->GetUnit();
		MapPlugin->SetUnit(Unit);
	}

	delete UnitConfig;

}

void CMyFrame::OnBoat(wxHyperlinkEvent &event)
{
	CBoatConfig *BoatConfig = new CBoatConfig();
	
	BoatConfig->ShowModal();
	

	delete BoatConfig;

}

void CMyFrame::OnComboBox(wxCommandEvent &event)
{
	PortSelection = event.GetSelection();
//	MapPlugin->GetMySerial()->SetPortIndex(event.GetSelection());
}

//wxSpinCtrl *CMyFrame::_GetSpin()
//{
	//return Spin;

//}

void CMyFrame::OnStartButton(wxCommandEvent &event)
{
	wxString port = PortComboBox->GetValue();
	wxString baud = BaudComboBox->GetValue();
	StartButton->Disable();
	StopButton->Enable();
	Scan->Disable();
	PortComboBox->Disable();
	BaudComboBox->Disable();
	PortComboBox->SetValue(port);
	BaudComboBox->SetValue(baud);
	MapPlugin->GetMySerial()->SetPort(PortComboBox->GetValue().char_str());
	long _baud;
	BaudComboBox->GetValue().ToLong(&_baud);
	MapPlugin->GetMySerial()->SetBaud(_baud);
		
	MapPlugin->GetMySerial()->Start();
}

void CMyFrame::OnStopButton(wxCommandEvent &event)
{
	if(_Stop)
		return;

	wxString value = PortComboBox->GetValue();
	PortComboBox->SetValue(value);
	StopButton->Disable();
	PortComboBox->Enable();
	BaudComboBox->Enable();
	Scan->Enable();
	_Stop = true;
	MapPlugin->GetMySerial()->Stop();
	StartButton->Enable(true);
	_Stop = false;
}

void CMyFrame::OnCheckLog(wxCommandEvent &event)
{
	LogText->Show(event.IsChecked());
	FileConfig->Write(_(KEY_CHECK_LOG),event.IsChecked());
	if(GetSizer())
		GetSizer()->SetSizeHints(this);

}


//void CMyFrame::SetPortEvent(wxString str)
//{
	//wxCommandEvent evt(nvEVT_SET_PORT,ID_SET_PORT);
	//evt.SetString(str);
	//wxPostEvent(this,evt);
//}

//void CMyFrame::SetBaudEvent(wxString str)
//{
	//wxCommandEvent evt(nvEVT_SET_BAUD,ID_SET_BAUD);
	//evt.SetString(str);
	//wxPostEvent(this,evt);
//}

void CMyFrame::SetLogEvent(wxString str)
{
	wxCommandEvent evt(nvEVT_SET_LOG,ID_SET_LOG);
	evt.SetString(str);
	wxPostEvent(this,evt);
}

void CMyFrame::OnSetLog(wxCommandEvent &event)
{
    if(!_Close)
    {
        LogText->AppendText(event.GetString());
    }
}

//void CMyFrame::OnSetPort(wxCommandEvent &event)
//{
	//RefreshPortsList();
	//PortComboBox->SetValue(event.GetString());
//}

void CMyFrame::OnSetBaud(wxCommandEvent &event)
{
	BaudComboBox->SetValue(event.GetString());
}

void CMyFrame::_SetInfoText(wxString text)
{
	if(!_Close)
	{
		if(!text.empty())
			LogText->AppendText(text);
	}
}

//wxComboBox *CMyFrame::_GetPortComboBox()
//{
	//return PortComboBox;
//}


//wxTextCtrl *CMyFrame::_GetTextCtrl()
//{
	//return LogText;
//}
void CMyFrame::_SetGpsFix(int fix)
{
	//if(!_Close)
		//FixText->SetLabel(wxString::Format(_(MSG_4),fix));
}
