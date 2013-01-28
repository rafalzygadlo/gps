#include "conf.h"
#include "tools.h"
#include "display.h"
#include <wx/wx.h>


BEGIN_EVENT_TABLE(CDisplayPlugin,CNaviDiaplayApi)
    EVT_CONTEXT_MENU(CDisplayPlugin::OnMenu)
	EVT_MOUSE_EVENTS(CDisplayPlugin::OnMouse)
	EVT_MENU_RANGE(ID_MENU_BEGIN,ID_MENU_END,CDisplayPlugin::OnMenuRange)
	EVT_MOUSEWHEEL(CDisplayPlugin::OnMouseWheel)
	EVT_LISTBOX(ID_TRACK_LIST, CDisplayPlugin::OnListBox)
END_EVENT_TABLE()

const wxChar *nvSpeedDesc[] = { _("kn"),_("km/h"),_("m/s"),_("mph"),_("ft/s") };
const wxChar *nvDirection[] = {_("S"), _("SW"), _("W"), _("NW"), _("N"), _("NE"),_("E"),_("SE") };
const wxChar *nvDegrees[] = {_("180"), _("225"), _("270"), _("315"), _("0"), _("45"),_("90"),_("135") };

CDisplayPlugin::CDisplayPlugin(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
:CNaviDiaplayApi( parent, id, pos, size, style, name )
{
	IsDrawning = false;
	nmea_zero_INFO(&info);
	MapPlugin = NULL;
    Broker = NULL;
	ConfigPath = wxString::Format(wxT("%s%s"),GetWorkDir().wc_str(),_(PLUGIN_CONFIG_FILE));
    wxFileConfig *FileConfig = new wxFileConfig(_("gps"),wxEmptyString,ConfigPath,wxEmptyString);
	_Radius = 0;
	Direction = 0;
	Name = parent->GetLabel();
	int Alpha = 0;
	SetDisplayID(NDS_GPS);
	Parent = parent;
	Panel = NULL;
	
	ArrayOfTypes.Add(_("Speed"));
	ArrayOfTypes.Add(_("Date"));
	ArrayOfTypes.Add(_("Time"));
	ArrayOfTypes.Add(_("Fix"));
	ArrayOfTypes.Add(_("Direction"));
	ArrayOfTypes.Add(_("Longitude"));
	ArrayOfTypes.Add(_("Latitude"));
	ArrayOfTypes.Add(_("PDOP"));
	ArrayOfTypes.Add(_("HDOP"));
	ArrayOfTypes.Add(_("VDOP"));
	ArrayOfTypes.Add(_("Quality"));
	ArrayOfTypes.Add(_("Sattelites"));
	ArrayOfTypes.Add(_("Status"));
	ArrayOfTypes.Add(_("Tracks"));
	//ArrayOfTypes.Add(_("Status"));
		
	if(!FileConfig->Read(wxString::Format(_("%s/%s"),Name.wc_str(),_(KEY_CONTROL_TYPE)),&ControlType))
		ControlType = DEFAULT_CONTROL_TYPE;
	if(!FileConfig->Read(wxString::Format(_("%s/%s"),Name.wc_str(),_(KEY_CONTROL_PRECISION)),&Precision))
		Precision = DEFAULT_PRECISION;
	if(!FileConfig->Read(wxString::Format(_("%s/%s"),Name.wc_str(),_(KEY_FORMAT_TYPE)),&FormatType))
		FormatType = DEFAULT_FORMAT;

	Caption = GetCaption();

	delete FileConfig;

};

CDisplayPlugin::~CDisplayPlugin()
{

	wxFileConfig *FileConfig = new wxFileConfig(_("gps"),wxEmptyString,ConfigPath,wxEmptyString);
	
	FileConfig->Write(wxString::Format(_("%s/%s"),Name,_(KEY_CONTROL_PRECISION)),Precision);
	FileConfig->Write(wxString::Format(_("%s/%s"),Name,_(KEY_CONTROL_TYPE)),ControlType);
	FileConfig->Write(wxString::Format(_("%s/%s"),Name,_(KEY_FORMAT_TYPE)),FormatType);
	
	delete FileConfig;
}

int CDisplayPlugin::GetControlType()
{
	return ControlType - ID_MENU_BEGIN;
}

wxString CDisplayPlugin::GetCaption()
{
	return ArrayOfTypes[GetControlType()];
}

void CDisplayPlugin::OnMenu(wxContextMenuEvent &event)
{
	
	wxMenu *Menu = new wxMenu();
	for(int i = 0; i < ArrayOfTypes.size(); i++)
		Menu->AppendRadioItem(i + ID_MENU_BEGIN ,ArrayOfTypes[i]);
		
	Menu->Check(ControlType, true);
	
	PopupMenu(Menu);
	delete Menu;
	
}

void CDisplayPlugin::OnMenuRange(wxCommandEvent &event)
{
	ControlType = event.GetId();
	Caption = ArrayOfTypes[GetControlType()];
	if(Panel != NULL)
	{
		delete Panel;
		Panel = NULL;
	}
	Refresh();
}

void CDisplayPlugin::OnMouseWheel(wxMouseEvent &event)
{
	Precision = Precision + (event.GetWheelRotation() / 120);
	_Radius = _Radius + (event.GetWheelRotation() / 120);
	if(Precision < 0)
		Precision = 0;
	
	Direction++;
	
	Refresh();
	event.Skip();
}

void CDisplayPlugin::OnMouse(wxMouseEvent & event)
{
	
	//if(event.ControlDown() && event.LeftDown())
	//{
	//	Precision++;
	//	if(Precision < 0)
	//		Precision = 0;
	
	//	Refresh();
	//}
	
	if(event.ButtonDClick())
	{
		
		FormatType++;
		switch(ControlType)
		{
			case ID_SPEED:
				if(NVSPEED_COUNT <= FormatType)
					FormatType = 0;
			break;
			
			case ID_LON:
			case ID_LAT:
				if(NVLON_COUNT <= FormatType)
					FormatType = 0;
			break;
			case ID_DATE:
				if(NVDATE_COUNT <= FormatType)
					FormatType = 0;
			break;

		}

		Refresh();
	}
	
	event.Skip();
}

//void CDisplayPlugin::OnListCheck(wxCommandEvent &event)
//{	
	//bool checked = TrackList->IsChecked(event.GetSelection());
	//MapPlugin->GetTrackList()->GetList()[event.GetSelection()]->SetVisible(checked);
//}

void CDisplayPlugin::OnListBox(wxCommandEvent &event)
{	
	GetMutex()->Lock();
	OptionsPanel->Show();
	this->Layout();
	
	CTrack *Track = MapPlugin->GetTrack(event.GetSelection());
	LabelName->SetLabel(Track->GetName());
	LabelFileName->SetLabel(Track->GetFileName());
		
	MapPlugin->SetSelectedTrack(event.GetSelection());

	GetMutex()->Unlock();
}

void CDisplayPlugin::DrawStatus(wxGCDC &dc)
{
		
	dc.SetTextForeground(wxColor(0,0,0));
	
	if(MapPlugin != NULL)
	{
			
		CMySerial *MySerial = MapPlugin->GetMySerial();
		if(MySerial == NULL)
			return;
		
		if(MySerial->IsRunning())
		{
			if(MySerial->IsRunning())
			{
				wxString port(MySerial->GetPortName(),wxConvUTF8);
				DrawData(dc,Caption,wxString::Format(_("%s:%d"),port.wc_str(),MySerial->GetBaudRate()));
			}else{
				wxString port(MySerial->GetPortName(),wxConvUTF8);
				DrawData(dc,Caption,wxString::Format(_("Connected %s:%d"),port.wc_str(),MySerial->GetBaudRate()));
			}
		}else{
			DrawData(dc,Caption,_("Connect Serial"));
		}
	}else{
		DrawData(dc,Caption,_("Start Gps"));
	}

}

void CDisplayPlugin::Draw(wxGCDC &dc)
{

	switch(ControlType)
	{
		
		case ID_SPEED:
			DrawSpeed(dc);
		break;
		case ID_DATE:
			DrawDate(dc);
		break;
		case ID_TIME:
			DrawTime(dc);
		break;
		case ID_FIX:
			DrawFix(dc);
		break;
		case ID_DIRECTION:
			DrawDirection(dc);
		break;
		case ID_LON:
			DrawLon(dc);
		break;
		case ID_LAT:
			DrawLat(dc);
		break;
		case ID_PDOP:
			DrawData(dc,ArrayOfTypes[ControlType - ID_MENU_BEGIN],wxString::Format(_("%4.*f"),Precision,info.PDOP));
		break;
		case ID_HDOP:
			DrawData(dc,ArrayOfTypes[ControlType - ID_MENU_BEGIN],wxString::Format(_("%4.*f"),Precision,info.HDOP));
		break;
		case ID_VDOP:
			DrawData(dc,ArrayOfTypes[ControlType - ID_MENU_BEGIN],wxString::Format(_("%4.*f"),Precision,info.VDOP));
		break;
		case ID_QUALITY:
			DrawQuality(dc);
		break;
		case ID_SATELLITES:
			DrawSatellites(dc);
		break;
		case ID_STATUS:
			DrawStatus(dc);
		break;
		case ID_TRACKS:
			DrawTracks(dc);
		break;
		case ID_SIGNALS:
			DrawSignals(dc);
		break;

	}
}

void CDisplayPlugin::DrawData(wxGCDC &dc, wxString caption, wxString text)
{
	if(IsDrawning)
		return;
	
	IsDrawning = true;
	
	Caption = caption;
	int Size;
	
	wxFont Font;
	if(GetWidth() < GetHeight())
		Size = GetWidth() / 2;
	else
		Size = GetHeight() / 2;
	
	wxSize FontSize;

	Font.SetPointSize( GetHeight() / 4 * 2 ) ;
	dc.SetTextForeground(wxColor(0,0,0));  
	dc.SetFont( Font );

	FontSize = dc.GetTextExtent(text);

	if( FontSize.GetWidth() > GetWidth() ) 
	{
		do 
		{
			Font.SetPointSize( Font.GetPointSize() - 1 );
			dc.SetFont( Font );
			if(dc.IsOk())
				FontSize = dc.GetTextExtent(text);
			else
				int a =0;
		
		} while ( FontSize.GetWidth() > GetWidth() );
	}

	dc.DrawText( text, (int)GetWidth()/2 - FontSize.GetWidth()/2, (int)GetHeight() * 0.625 - FontSize.GetHeight() / 2 );
	IsDrawning = false;
	
}

void CDisplayPlugin::DrawSignals(wxGCDC &dc)
{
	
	if(Panel == NULL)
	{
		
		wxBoxSizer *MainSizer = new wxBoxSizer(wxHORIZONTAL);
		Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
		wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
		
		List = new wxListCtrl(Panel,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxLC_REPORT);
		List->InsertColumn(0,_("Signal"));
		List->InsertColumn(0,_("Count"));
		PanelSizer->Add(List,1,wxALL|wxEXPAND,5);

		MainSizer->Add(Panel,1,wxALL|wxEXPAND,0);
		Panel->SetSizer(PanelSizer);

		//wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxVERTICAL);
		//wxPanel *Panel1 = new wxPanel(Panel,wxID_ANY,wxDefaultPosition,wxDefaultSize);
		//PanelSizer->Add(Panel1,0,wxALL|wxEXPAND,5);
			
		this->SetSizer(MainSizer);
		Panel->SetSize(GetWidth(),GetHeight());
	}	
	
	
	if(MapPlugin != NULL)
	{			
		CMySerial *Serial = MapPlugin->GetMySerial();
		if(Serial == NULL)
			return;

		static int counter;

		if(counter == Serial->GetSignalCount())
			return;
				
		counter = Serial->GetSignalCount();
				
		for(size_t i = 0; i < Serial->GetSignalCount(); i++)
		{	
			wxListItem item;
			wxString sig((char*)Serial->GetSignal(i)->name,wxConvUTF8);
			item.SetText(sig);
			item.SetMask(wxLIST_MASK_TEXT);
			item.SetColumn(0);
			List->InsertItem(item);


			wxString nmea((char*)Serial->GetSignal(i)->nmea,wxConvUTF8);
			item.SetText(nmea);
			item.SetMask(wxLIST_MASK_TEXT);
			//item.SetColumn(1);
			List->InsertItem(item);
		
		}
			
	}		
	
}



void CDisplayPlugin::DrawTracks(wxGCDC &dc)
{
	
	if(Panel != NULL)
		return; // nie rysuj kontrolek
	
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
		
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
		
	TrackList = new wxListBox(Panel,ID_TRACK_LIST,wxDefaultPosition,wxDefaultSize);
	PanelSizer->Add(TrackList,1,wxALL|wxEXPAND,0);
	//TrackData = new wxListBox(Panel,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	//PanelSizer->Add(TrackData,1,wxALL|wxEXPAND,5);
	
	//wxListCtrl *List = new wxListCtrl(Panel,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxLC_REPORT);
	//List->InsertColumn(0,_("aaa"));
	//List->InsertColumn(0,_("aaa"));
	//PanelSizer->Add(List,1,wxALL|wxEXPAND,5);

	MainSizer->Add(Panel,1,wxALL|wxEXPAND,0);
	Panel->SetSizer(PanelSizer);

	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *Panel1 = new wxPanel(Panel,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	PanelSizer->Add(Panel1,0,wxALL|wxEXPAND,5);

	OptionsPanel = new wxPanel(Panel,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	PanelSizer->Add(OptionsPanel,0,wxALL|wxEXPAND,0);
	//OptionsPanel->Hide();

	wxBoxSizer *OptionsPanelSizer = new wxBoxSizer(wxVERTICAL);
	OptionsPanel->SetSizer(OptionsPanelSizer);

	wxFont font;
	font.SetPointSize(14);

	LabelName = new wxStaticText(OptionsPanel,wxID_ANY,wxEmptyString);
	LabelName->SetFont(font);
	OptionsPanelSizer->Add(LabelName,0,wxALL|wxEXPAND,2);
	
	LabelFileName = new wxStaticText(OptionsPanel,wxID_ANY,wxEmptyString);
	OptionsPanelSizer->Add(LabelFileName,0,wxALL|wxEXPAND,2);

	LabelSize = new wxStaticText(OptionsPanel,wxID_ANY,wxEmptyString);
	OptionsPanelSizer->Add(LabelSize,0,wxALL|wxEXPAND,2);
		
	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	OptionsPanelSizer->Add(ButtonSizer,0,wxALL|wxEXPAND,2);
	wxButton *Edit = new wxButton(OptionsPanel,ID_EDIT,_("Edit"),wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(Edit,0,wxALL,5);

	wxButton *Delete = new wxButton(OptionsPanel,ID_DELETE,_("Delete"),wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(Delete,0,wxALL,5);

	Panel1->SetSizer(Panel1Sizer);
		
	this->SetSizer(MainSizer);
		
	if(MapPlugin != NULL)
	{			
		std::vector<CTrack*> Tracks = MapPlugin->GetTrackList()->GetList();
		
		for(int i = 0; i< Tracks.size(); i++)
		{	
			TrackList->Append(wxString::Format(_("%s"), Tracks[i]->GetName().wc_str()));
		}
	}
		
	Panel->SetSize(GetWidth(),GetHeight());
	
}

void CDisplayPlugin::DrawDate(wxGCDC &dc)
{
	//if(!CheckGpsFix(dc))
		//return;
	
	switch(FormatType)
	{
		case DATE_YYMMDD:
			DrawData(dc,ArrayOfTypes[ControlType - ID_MENU_BEGIN],wxString::Format(_("%02d-%02d-%02d"),info.utc.year,info.utc.mon,info.utc.day));
		break;
		case DATE_MMDDYY:
			DrawData(dc,ArrayOfTypes[ControlType - ID_MENU_BEGIN],wxString::Format(_("%02d-%02d-%02d"),info.utc.mon,info.utc.day,info.utc.year));
		break;
	}
}

void CDisplayPlugin::DrawTime(wxGCDC &dc)
{
	//if(!CheckGpsFix(dc))
		//return;
	
	DrawData(dc,ArrayOfTypes[ControlType - ID_MENU_BEGIN],wxString::Format(_("%02d:%02d:%02d"),info.utc.hour,info.utc.min,info.utc.sec));
}

void CDisplayPlugin::DrawLon(wxGCDC &dc)
{
	double value;

	switch(FormatType)
	{
		case LON_NORMAL:
			value = info.lon/100;	
		break;
	
	}
		
	if(info.sig	== 0)
	{
		DrawData(dc,ArrayOfTypes[ControlType - ID_MENU_BEGIN],_(NOT_AVAILABLE));
	}else{
		DrawData(dc,ArrayOfTypes[ControlType - ID_MENU_BEGIN],FormatLongitude(value));
	}
}

void CDisplayPlugin::DrawLat(wxGCDC &dc)
{
	
	double value;

	switch(FormatType)
	{
		case LAT_NORMAL:
			value = info.lat/100;	
		break;	
	}
	
	if(info.sig	== 0)
		DrawData(dc,ArrayOfTypes[ControlType - ID_MENU_BEGIN],_(NOT_AVAILABLE));
	else
		DrawData(dc,ArrayOfTypes[ControlType - ID_MENU_BEGIN],FormatLatitude(value));
}

void CDisplayPlugin::DrawQuality(wxGCDC &dc)
{
	wxString buf;
		
	switch(info.sig)
	{
		
		case GPS_QUALITY_INVALID:
			buf = _("Invalid");
		break;
		case GPS_QUALITY_FIX:
			buf = _("Fix");
		break;
		case GPS_QUALITY_DIFFERENTIAL:
			buf = _("Differential");
		break;

		case GPS_QUALITY_SENSITIVE:
			buf = _("Sensitive");
		break;
		
	}

	DrawData(dc,ArrayOfTypes[ControlType - ID_MENU_BEGIN],buf);
}

void CDisplayPlugin::DrawFix(wxGCDC &dc)
{

	wxString buf;
	switch(info.fix)
	{
		case GPS_FIX_NA:
			buf = _(NOT_AVAILABLE);
		break;
		case GPS_FIX_2D:
			buf = _("2D");
		break;
		case GPS_FIX_3D:
			buf = _("3D");
		break;
	}

	DrawData(dc,ArrayOfTypes[ControlType - ID_MENU_BEGIN],buf);
}

void CDisplayPlugin::DrawSpeed(wxGCDC &dc)
{
	double value;
	double speed = info.speed;
	wxString dsc;
		
	switch(FormatType)
	{
		case SPEED_KNOT:
			value = speed; 
		break;
		case SPEED_MS:
			value = MS * speed;
		break;
		case SPEED_KMH:
			value = KMH * speed;
		break;
		case SPEED_MPH:
			value = MPH * speed;
		break;
		case SPEED_FTS:	 
			value = FTS * speed;
		break;
	}
	
	wxString buf = wxString::Format(_("%4.*f %s"),Precision,value,nvSpeedDesc[FormatType]);
	DrawData(dc,ArrayOfTypes[ControlType - ID_MENU_BEGIN],buf);
}

void CDisplayPlugin::DrawBackground(wxGCDC &dc)
{
	
	CenterX = GetWidth() / 2;
	CenterY = GetHeight() / 2;
	
	wxBrush brush;
	brush.SetColour(wxColor(BACKGROUND_BRUSH_COLOR));
	dc.SetBrush(brush);
	
	wxPen pen;
	
	wxFont Font;
	Font.SetPointSize(12);
	dc.SetFont( Font );
	
	dc.SetTextForeground(wxColor(BACKGROUND_TEXT_COLOR));
	dc.DrawRectangle(0,0,GetWidth(),GetHeight());
	
	if(GetWidth() < GetHeight())
		Radius = GetWidth() / 2;
	else
		Radius = GetHeight() / 2;
	
	Radius = Radius - 25 + _Radius;
	
	pen.SetColour(wxColor(200,200,200,100));
	pen.SetWidth(20);
	dc.SetPen(pen);
	dc.DrawCircle(GetWidth()/2, GetHeight()/2, Radius);

	// outer circle
	pen.SetColour(wxColor(OUTER_CIRCLE_COLOR));
	pen.SetWidth(4);
	dc.SetPen(pen);
	dc.DrawCircle(GetWidth()/2, GetHeight()/2, Radius);
		
	//inner circle
	pen.SetColour(wxColor(22,67,112));
	pen.SetWidth(2);
	dc.SetPen(pen);
	dc.DrawCircle(GetWidth()/2, GetHeight()/2, Radius/1.5);
	
	// set color to white
	pen.SetWidth(10);
	pen.SetColour(wxColor(LINE_COLOR));
	dc.SetPen(pen);
	
	
	int x, y;
	
	for(int i = 0; i < WXSIZEOF(nvDirection); i++)
	{
		int nr_elem = WXSIZEOF(nvDirection);
		x = (Radius + 16) * sin(i*(360/nr_elem) * nvPI/180)*-1 + CenterX;
		y = (Radius + 16) * cos(i*(360/nr_elem) * nvPI/180) + CenterY;	
		// set color to white
		pen.SetWidth(10);
		pen.SetColour(wxColor(LINE_COLOR));
		dc.SetPen(pen);
		dc.DrawLine(CenterX,CenterY, x  , y );
		
		
		dc.DrawCircle(x,y,10);	
		wxString text = nvDirection[i];
		wxSize FontSize = dc.GetTextExtent(text);
		dc.DrawText(text,x - FontSize.GetWidth()/2, y - FontSize.GetHeight()/2);
	}
	
	Font.SetPointSize(10);
	dc.SetFont( Font );
	for(int i = 0; i < WXSIZEOF(nvDegrees); i++)
	{
		int nr_elem = WXSIZEOF(nvDegrees);
		x = (Radius - 16) * sin(i*(360/nr_elem) * nvPI/180)*-1 + CenterX;
		y = (Radius - 16) * cos(i*(360/nr_elem) * nvPI/180) + CenterY;	
		// set color to white
		
		wxString text = nvDegrees[i];
		wxSize FontSize = dc.GetTextExtent(text);
		dc.DrawText(text,x - FontSize.GetWidth()/2, y - FontSize.GetHeight()/2);
	
	}
}

bool CDisplayPlugin::CheckGpsValid(wxGCDC &dc)
{
	if(info.sig == 0)
	{
		buf = _(NOT_AVAILABLE);
		DrawData(dc,ArrayOfTypes[ControlType - ID_MENU_BEGIN],buf);
		return false;
	}
	return true;
}

/*
void CDisplayPlugin::DrawSearchSatellites(wxGCDC &dc)
{
	
	CenterX = GetWidth() / 2;
	CenterY = GetHeight() / 2;
	wxBrush brush;
	brush.SetColour(wxColor(BACKGROUND_BRUSH_COLOR));
	dc.SetBrush(brush);
	
	wxPen pen;
	dc.SetTextForeground(wxColor(BACKGROUND_TEXT_COLOR));
	dc.DrawRectangle(0,0,GetWidth(),GetHeight());
	DrawData(dc,_("searching for satellites"),_("searching for satellites"));
	
	
}
*/

void CDisplayPlugin::DrawSatellites(wxGCDC &dc)
{
		
	if(!CheckGpsValid(dc) )
		return;
	
	DrawBackground(dc);	
	wxPen pen;	
	pen.SetWidth(10);
	dc.SetPen(pen);
	int x,y;
	
	wxFont Font;
	Font.SetPointSize(10);
	dc.SetFont( Font );
	dc.SetTextForeground(wxColor(0,0,0));

	for(int i = 0; i < info.satinfo.inview; i++)
	{	

		int id = info.satinfo.sat[i].id;
		int azimuth = info.satinfo.sat[i].azimuth - 180;

		int elv = info.satinfo.sat[i].elv;
		double a = (double)Radius/90;
		x = (Radius - (a*elv))*sin(azimuth * nvPI/180)*-1 + CenterX;
		y = (Radius - (a*elv))*cos(azimuth * nvPI/180) + CenterY;
		
		wxBrush brush;
		
		if(info.satinfo.sat[i].in_use)
		{
			pen.SetColour(wxColor(0,255,0));
			brush.SetColour(wxColor(0,255,0));
		}else{
			brush.SetColour(wxColor(255,0,0));
			pen.SetColour(wxColor(255,0,0));
		}
		
		pen.SetWidth(2);
		dc.SetPen(pen);
		
		
		dc.SetBrush(brush);
		dc.DrawCircle(x,y,SATTELITE_RADIUS);
		dc.DrawText(wxString::Format(_("%2d "),info.satinfo.sat[i].sig),x - SATTELITE_RADIUS,y - SATTELITE_RADIUS);
	}	
	
	
}

void CDisplayPlugin::DrawDirection(wxGCDC &dc)
{
	if(!CheckGpsValid(dc) )
		return;
		
	DrawBackground(dc);	
	int direction = info.direction - 180;
	
	double a = (double)Radius/90;
	int x1 = (Radius  - (a*100)) * sin((direction - 25) * nvPI/180)*-1 + CenterX;
	int y1 = (Radius  - (a*100)) * cos((direction - 25) * nvPI/180) + CenterY;
	
	int x2 = (Radius  - (a*100)) * sin((direction + 25) * nvPI/180)*-1 + CenterX;
	int y2 = (Radius  - (a*100)) * cos((direction + 25) * nvPI/180) + CenterY;

	
	int x3 = (Radius - (a*10)) * sin((direction) * nvPI/180)*-1 + CenterX;
	int y3 = (Radius - (a*10)) * cos((direction) * nvPI/180) + CenterY;

	wxFont Font;
	Font.SetPointSize(12);
	dc.SetFont( Font );
	wxPen pen;
	pen.SetColour(wxColor(255,0,0));
	pen.SetWidth(3);
	dc.SetPen(pen);
	
	wxBrush brush;
	brush.SetColour(wxColor(255,0,0));
	dc.SetBrush(brush);
	
	wxPoint point[3];
	point[0].x = x1;
	point[0].y = y1;
	
	point[1].x = x2;
	point[1].y = y2;
	
	point[2].x = x3;
	point[2].y = y3;
		
	dc.DrawPolygon(3,point);
		
	dc.DrawCircle(CenterX,CenterY,8);	
	wxString text = wxString::Format(_("%4.2f"),info.direction);
	wxSize FontSize = dc.GetTextExtent(text);
	dc.DrawText(text,CenterX - (FontSize.GetWidth()/2) ,CenterY + 10);
	
	
}

bool CDisplayPlugin::IsValidSignal(CDisplaySignal *SignalID) {

	if(SignalID->GetSignalID() == NDS_BROKER_BROADCAST && Broker == NULL)
	{
		Broker = (CNaviBroker*)SignalID->GetData();
		MapPlugin = (CMapPlugin*)Broker->ExecuteFunction(Broker->GetParentPtr(),"gps_GetThisPtr",NULL);
		return false;
	}

	if(SignalID->GetSignalID() == NDS_GPS)
	{
		MapPlugin = (CMapPlugin*)SignalID->GetData();
		return true;
	}
	
	return false;
	//return true;
}

void CDisplayPlugin::OnRender(wxGCDC &dc) 
{

	if(MapPlugin != NULL)
		info = MapPlugin->GetNmeaINFO();
	
	Draw(dc);

}

void CDisplayPlugin::OnWork(CDisplaySignal *Signal) 
{
		
	Refresh();
	wxMilliSleep(300);

}

void CDisplayPlugin::AfterWork(CDisplaySignal *Signal)
{

	
}

void CDisplayPlugin::BeforeWork(CDisplaySignal *Signal)
{
	
}

const wchar_t *NaviDisplayIntroduce(int LanguageID) 
{

	switch( LanguageID ) 
	{

		case 0: 
			return L"GPS";
			break;

		default:
			return L"GPS";
	}

}

const int NaviDisplayID()
{
	return NDS_GPS;
}

CNaviDiaplayApi *CreateDisplayInstance(wxWindow *Parent, wxWindowID WindowID,int LangID) 
{
	CDisplayPlugin *SimplePlugin = new CDisplayPlugin(Parent, WindowID);
	return SimplePlugin;
}