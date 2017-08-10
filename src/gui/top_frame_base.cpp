///////////////////////////////////////////////////////////////////////////// C++ code generated with wxFormBuilder (version Sep 12 2010)// http://www.wxformbuilder.org///// PLEASE DO "NOT" EDIT THIS FILE!///////////////////////////////////////////////////////////////////////////#include "top_frame_base.h"///////////////////////////////////////////////////////////////////////////top_frame_base::top_frame_base( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style ){	this->SetSizeHints( wxDefaultSize, wxDefaultSize );	this->SetBackgroundColour( wxColour( 35, 145, 254 ) );		wxGridSizer* gSizer2;	gSizer2 = new wxGridSizer( 2, 2, 10, 10 );		wxGridSizer* gSizer3;	gSizer3 = new wxGridSizer( 5, 2, 0, 0 );		m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("dx/dt = "), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText1->Wrap( -1 );	m_staticText1->SetBackgroundColour( wxColour( 84, 255, 59 ) );		gSizer3->Add( m_staticText1, 0, wxALL, 5 );		text_field = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );	gSizer3->Add( text_field, 0, wxALL, 5 );		m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("dy/dt = "), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText2->Wrap( -1 );	gSizer3->Add( m_staticText2, 0, wxALL, 5 );		m_textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );	gSizer3->Add( m_textCtrl1, 0, wxALL, 5 );		m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("dz/dt ="), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText3->Wrap( -1 );	gSizer3->Add( m_staticText3, 0, wxALL, 5 );		m_textCtrl3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );	gSizer3->Add( m_textCtrl3, 0, wxALL, 5 );		m_button1 = new wxButton( this, wxID_ANY, wxT("Render"), wxDefaultPosition, wxDefaultSize, 0 );	gSizer3->Add( m_button1, 0, wxALL, 5 );		gSizer2->Add( gSizer3, 1, wxEXPAND, 5 );		dynamicalPlane = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );	gSizer2->Add( dynamicalPlane, 1, wxEXPAND | wxALL, 5 );		m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );	gSizer2->Add( m_panel2, 1, wxEXPAND|wxALL, 5 );		wxBoxSizer* bSizer3;	bSizer3 = new wxBoxSizer( wxVERTICAL );		gSizer2->Add( bSizer3, 1, wxEXPAND, 5 );		this->SetSizer( gSizer2 );	this->Layout();	m_menubar1 = new wxMenuBar( 0 );	m_menu2 = new wxMenu();	wxMenuItem* m_menuItem2;	m_menuItem2 = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("MyMenuItem") ) , wxEmptyString, wxITEM_NORMAL );	m_menu2->Append( m_menuItem2 );		m_menubar1->Append( m_menu2, wxT("Vector Field") ); 		m_menu1 = new wxMenu();	wxMenuItem* m_menuItem3;	m_menuItem3 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("MyMenuItem") ) , wxEmptyString, wxITEM_NORMAL );	m_menu1->Append( m_menuItem3 );		m_menubar1->Append( m_menu1, wxT("Windows") ); 		m_menu3 = new wxMenu();	wxMenuItem* m_menuItem1;	m_menuItem1 = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("TEST") ) , wxEmptyString, wxITEM_NORMAL );	m_menu3->Append( m_menuItem1 );		m_menubar1->Append( m_menu3, wxT("Solutions") ); 		m_menu8 = new wxMenu();	wxMenuItem* m_menuItem4;	m_menuItem4 = new wxMenuItem( m_menu8, wxID_ANY, wxString( wxT("MyMenuItem") ) , wxEmptyString, wxITEM_NORMAL );	m_menu8->Append( m_menuItem4 );		m_menubar1->Append( m_menu8, wxT("Symmetries") ); 		this->SetMenuBar( m_menubar1 );			this->Centre( wxBOTH );		// Connect Events	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( top_frame_base::render_button_on_button_click ), NULL, this );	dynamicalPlane->Connect( wxEVT_PAINT, wxPaintEventHandler( top_frame_base::dynamical_plane_on_paint ), NULL, this );}top_frame_base::~top_frame_base(){	// Disconnect Events	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( top_frame_base::render_button_on_button_click ), NULL, this );	dynamicalPlane->Disconnect( wxEVT_PAINT, wxPaintEventHandler( top_frame_base::dynamical_plane_on_paint ), NULL, this );	}