#include "frame.h"
#include "conf.h"
#include "dll.h"
#include "serial.h"
#include "tools.h"
#include <wx/statline.h>
#include "NaviMapIOApi.h"

DEFINE_EVENT_TYPE(nvEVT_SET_LOG)
DEFINE_EVENT_TYPE(nvEVT_SET_PORT)
DEFINE_EVENT_TYPE(nvEVT_SET_BAUD)

BEGIN_EVENT_TABLE(CMyFrame,wxDialog)
	EVT_BUTTON(ID_START,CMyFrame::OnStartButton)
	EVT_BUTTON(ID_STOP,CMyFrame::OnStopButton)
	EVT_BUTTON(ID_CLOSE,CMyFrame::OnCloseButton)
	EVT_CHECKBOX(ID_CHECK_LOG,CMyFrame::OnCheckLog)
	EVT_COMBOBOX(ID_PORTS,CMyFrame::OnComboBox)
	EVT_CLOSE(CMyFrame::OnClose)
	EVT_COMMAND(ID_SET_LOG,nvEVT_SET_LOG,CMyFrame::OnSetLog)	//my own defined event
	EVT_COMMAND(ID_SET_PORT,nvEVT_SET_PORT,CMyFrame::OnSetPort)	//my own defined event
	EVT_COMMAND(ID_SET_BAUD,nvEVT_SET_BAUD,CMyFrame::OnSetBaud)	//my own defined event
END_EVENT_TABLE()


CMyFrame::CMyFrame(CMapPlugin *_MapPlugin)
:wxDialog(NULL, wxID_ANY, _(PRODUCT_NAME), wxDefaultPosition, wxDefaultSize )
{
	PortSelection = 0;
	MapPlugin = _MapPlugin;
	ConfigPath = wxString::Format(wxT("%s%s"),GetWorkDir().wc_str(),_(PLUGIN_CONFIG_FILE));
	FileConfig = new wxFileConfig(_("gps"),wxEmptyString,ConfigPath,wxEmptyString);
	_Start = false;
	_Stop = false;
	_Close = false;
	//wxMenu *MenuFile = new wxMenu();
	//MenuFile->Append(wxID_ANY,_("Exit"));
	//wxMenuBar *MenuBar = new wxMenuBar();
	//MenuBar->Append(MenuFile,_("File"));
	//wxMenu *MenuHelp = new wxMenu();
	//MenuHelp->Append(wxID_ANY,_("About"));
	//MenuHelp->Append(wxID_ANY,_("How to use"));
	//MenuBar->Append(MenuHelp,_("Help"));

	//this->SetMenuBar(MenuBar);
	//wxStatusBar *StatusBar = new wxStatusBar(this,wxID_ANY,wxSB_FLAT);
	//static const int widths[1] = {-1};
	//StatusBar->SetFieldsCount(1,widths);
	//StatusBar->SetStatusText(_("GPS plugin"),0);
	//this->SetStatusBar(StatusBar);

	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);

	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *TopSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *CenterSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *BottomSizer = new wxBoxSizer(wxHORIZONTAL);

	PanelSizer->Add(TopSizer,0,wxEXPAND,0);
	PanelSizer->Add(CenterSizer,0,wxEXPAND,0);
	PanelSizer->Add(BottomSizer,0,wxEXPAND,0);

	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	PortComboBox = new wxComboBox(Panel,ID_PORTS,wxEmptyString,wxDefaultPosition,wxDefaultSize,	NULL,wxCB_READONLY);
	PortComboBox->Disable();
	ButtonSizer->Add(PortComboBox,1,wxALL|wxEXPAND,2);
	
	BaudComboBox = new wxComboBox(Panel,ID_PORTS,wxEmptyString,wxDefaultPosition,wxDefaultSize,	NULL,wxCB_READONLY);
	BaudComboBox->Disable();
	ButtonSizer->Add(BaudComboBox,1,wxALL|wxEXPAND,2);

	//button start
	StartButton = new wxButton(Panel,ID_START,_("Connect"),wxDefaultPosition,wxDefaultSize);
	StartButton->Disable();
	ButtonSizer->Add(StartButton,0,wxALL,2);

	// button stop
	StopButton = new wxButton(Panel,ID_STOP,_("Disconnect"),wxDefaultPosition,wxDefaultSize);
	StopButton->Disable();
	ButtonSizer->Add(StopButton,0,wxALL,2);

	TopSizer->Add(ButtonSizer,1,wxALL|wxEXPAND,2);

	wxStaticLine *Line1 = new wxStaticLine(Panel,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxHORIZONTAL);
	CenterSizer->Add(Line1,0,wxALL|wxEXPAND,2);

	wxBoxSizer *LeftSizer = new wxBoxSizer(wxHORIZONTAL);
	CenterSizer->Add(LeftSizer,0,wxALL|wxEXPAND,5);

	//wxBoxSizer *RightSizer = new wxBoxSizer(wxVERTICAL);
	//CenterSizer->Add(RightSizer,0,wxALL|wxEXPAND,5);



	//wxStaticText *Info = new wxStaticText(Panel,wxID_ANY,_("The area around your GPS position will be selected.\n Use Grib Browser to download this grib."),wxDefaultPosition,wxDefaultSize);
	//LeftSizer->Add(Info,0,wxALL|wxEXPAND|wxCENTER,5);
	//FixText = new wxStaticText(Panel,wxID_ANY,_("Gps Fix: 0"),wxDefaultPosition,wxDefaultSize);
	//LeftSizer->Add(FixText,0,wxALL,5);

	// Long
	//wxStaticText *LonText = new wxStaticText(Panel,-1,_("Longtitute:"),wxDefaultPosition,wxDefaultSize);
	//CenterSizer->Add(LonText,0, wxEXPAND | wxALL,5);

	// Lat
	//wxStaticText *LatText = new wxStaticText(Panel,-1,_("Lattitude:"),wxDefaultPosition,wxDefaultSize);
	//CenterSizer->Add(LatText,0, wxEXPAND | wxALL,5);

	//Spin = new wxSpinCtrl(Panel,ID_SPIN,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	//Spin->SetFont(wxFont(12, wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	//wxString size;
	//long _size;
	//bool read = GpsDLL->GetFileConfig()->Read(_(KEY_AREA_SIZE),&size,wxString::Format(_("%d"),DEFAULT_SELECTION_SIZE));
	//size.ToLong(&_size);
	//GpsDLL->SetAreaSize(_size);
	//Spin->SetMin(0);
	//Spin->SetMax(5000);
	//Spin->SetValue(size);
	//CenterSizer->Add(Spin,0,wxALL,5);
	//Spin->Disable();

	//Area box
	//AreaBox = new CMyPanel(Panel);
	//AreaBox->SetBackgroundColour(*wxWHITE);
	//AreaBox->SetSize(wxSize(-1,150));
	//AreaBox->Show(chk_dw);
	//CenterSizer->Add(AreaBox,1,wxALL|wxEXPAND,5);

	// line
	//wxStaticLine *Line2 = new wxStaticLine(Panel,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxHORIZONTAL);
	//CenterSizer->Add(Line2,0,wxALL|wxEXPAND,2);

	// download check
	//bool chk_hint;
	//FileConfig->Read(_(KEY_CHECK_HINT),&chk_hint,false);
	//CheckBoxHint = new wxCheckBox(Panel,ID_CHECK_HINT,_("Show download area hint"));
	//CheckBoxHint->SetValue(chk_hint);
	//GpsDLL->SetShowHint(chk_hint);
	//CenterSizer->Add(CheckBoxHint,0,wxALL,5);

	// log window check
	bool chk_log;
	FileConfig->Read(_(KEY_CHECK_LOG),&chk_log,false);
	CheckLogBox = new wxCheckBox(Panel,ID_CHECK_LOG,_("Show log window"),wxDefaultPosition,wxDefaultSize);
	CheckLogBox->SetValue(chk_log);
	CenterSizer->Add(CheckLogBox,0,wxALL,5);

	// Log Window on center
	LogText = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE);
	LogText->Show(chk_log);
	LogText->SetMinSize(wxSize(-1,200));
	CenterSizer->Add(LogText,1,wxALL|wxEXPAND,5);

	
	if(MapPlugin->GetMySerial() != NULL)
	{
        if(MapPlugin->GetMySerial()->GetWorkingFlag())
		{
            StopButton->Enable();
			PortComboBox->Disable();
			BaudComboBox->Disable();
		}else{
            StartButton->Enable();
			PortComboBox->Enable();
			BaudComboBox->Enable();
		}
	}


	// static horizontal line
	wxStaticLine *Line3 = new wxStaticLine(Panel,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxHORIZONTAL);
	CenterSizer->Add(Line3,0,wxALL|wxEXPAND,2);

	// plugin name
	wxStaticText *PluginName = new wxStaticText(Panel,wxID_ANY,wxString::Format(_("%s \n%s"),_(PRODUCT_NAME),_(PRODUCT_COPYRIGHT)));
	BottomSizer->Add(PluginName,1,wxALL|wxEXPAND,5);

	// button close
	wxButton *ButtonClose = new wxButton(Panel,ID_CLOSE,_("Close"),wxDefaultPosition,wxDefaultSize);
	BottomSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);

	Panel->SetSizer(PanelSizer);

	MainSizer->Add(Panel,1,wxALL|wxEXPAND,0);
	this->SetSizer(MainSizer);

	RefreshPortsList();
	RefreshBaudList();
	
	
	//_SetStatusText(wxString::Format(_(MSG_2),_MapPlugin->GetMySerial()->GetPortNumber(),_MapPlugin->GetMySerial()->GetBaudRate()));
	if(MapPlugin->GetMySerial() != NULL)
	{
		wxString buf(_MapPlugin->GetMySerial()->GetPortName(),wxConvUTF8);
		PortComboBox->SetValue(buf);
		BaudComboBox->SetValue(wxString::Format(_("%d"),_MapPlugin->GetMySerial()->GetBaudRate()));
	}
	
	PortComboBox->SetDoubleBuffered(true);
	
	if(GetSizer())
		GetSizer()->SetSizeHints(this);

	
	Center();
}

CMyFrame::~CMyFrame(void)
{
	delete FileConfig;
}

void CMyFrame::OnComboBox(wxCommandEvent &event)
{
	PortSelection = event.GetSelection();
	MapPlugin->GetMySerial()->SetPortIndex(event.GetSelection());
}

void CMyFrame::OnCloseButton(wxCommandEvent &event)
{
	_Close = true;
	//FileConfig->Write(_(KEY_PORT),wxString::Format(_("COM%d"),MapPlugin->GetMySerial()->GetPortName()));
	//FileConfig->Write(_(KEY_BAUD),MapPlugin->GetMySerial()->GetBaudRate());
	FileConfig->Flush();
	Close();

}
void CMyFrame::OnClose(wxCloseEvent &event)
{
	Destroy();
}

wxSpinCtrl *CMyFrame::_GetSpin()
{
	return Spin;

}

void CMyFrame::OnStartButton(wxCommandEvent &event)
{
	wxString port = PortComboBox->GetValue();
	wxString baud = BaudComboBox->GetValue();
	StartButton->Disable();
	RefreshPortsList();
	StopButton->Enable();
	PortComboBox->Disable();
	BaudComboBox->Disable();
	PortComboBox->SetValue(port);
	BaudComboBox->SetValue(baud);
	MapPlugin->GetMySerial()->SetPortIndex(PortComboBox->GetSelection());
	MapPlugin->GetMySerial()->SetBaudIndex(BaudComboBox->GetSelection());
		
	MapPlugin->GetMySerial()->Start();
}

void CMyFrame::OnStopButton(wxCommandEvent &event)
{
	if(_Stop)
		return;

	wxString value = PortComboBox->GetValue();
	RefreshPortsList();
	PortComboBox->SetValue(value);
	StopButton->Disable();
	PortComboBox->Enable();
	BaudComboBox->Enable();
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


void CMyFrame::SetPortEvent(wxString str)
{
	wxCommandEvent evt(nvEVT_SET_PORT,ID_SET_PORT);
	evt.SetString(str);
	wxPostEvent(this,evt);
}

void CMyFrame::SetBaudEvent(wxString str)
{
	wxCommandEvent evt(nvEVT_SET_BAUD,ID_SET_BAUD);
	evt.SetString(str);
	wxPostEvent(this,evt);
}

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

void CMyFrame::OnSetPort(wxCommandEvent &event)
{
	RefreshPortsList();
	PortComboBox->SetValue(event.GetString());
}

void CMyFrame::OnSetBaud(wxCommandEvent &event)
{
	BaudComboBox->SetValue(event.GetString());
}


void CMyFrame::RefreshPortsList()
{
	
	size_t len = MapPlugin->GetMySerial()->GetPortInfoLength();
	PortComboBox->Clear();
		
	for(size_t i = 0; i < len; i++)
	{
		wxString str( MapPlugin->GetMySerial()->GetPortInfo(i).port_name,wxConvUTF8);
		PortComboBox->Append(wxString::Format(_("%s"),str.wc_str()));
	}

}

void CMyFrame::RefreshBaudList()
{

	size_t len = MapPlugin->GetMySerial()->GetBaudInfoLength();
	BaudComboBox->Clear();
		
	for(size_t i = 0; i < len; i++)
		BaudComboBox->Append(wxString::Format(_("%d"),MapPlugin->GetMySerial()->GetBaudInfo(i)));


}

void CMyFrame::_SetInfoText(wxString text)
{
	if(!_Close)
	{
		if(!text.empty())
			LogText->AppendText(text);
	}
}

wxComboBox *CMyFrame::_GetPortComboBox()
{
	return PortComboBox;
}


wxTextCtrl *CMyFrame::_GetTextCtrl()
{
	return LogText;
}
void CMyFrame::_SetGpsFix(int fix)
{
	//if(!_Close)
		//FixText->SetLabel(wxString::Format(_(MSG_4),fix));
}
