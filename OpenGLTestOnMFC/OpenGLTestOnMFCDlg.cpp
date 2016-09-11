
// OpenGLTestOnMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGLTestOnMFC.h"
#include "OpenGLTestOnMFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// COpenGLTestOnMFCDlg dialog




COpenGLTestOnMFCDlg::COpenGLTestOnMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenGLTestOnMFCDlg::IDD, pParent)
	, m_pickModeActivated(false)
	, m_viewModeActivated(true)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//	m_dlgControl->m_controlScaleSlider = &m_scaleSlider;
}

void COpenGLTestOnMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DRAW_BUTTON, m_drawButton);
	DDX_Control(pDX, IDC_COLOR_LIST, m_colorList);
	DDX_Control(pDX, IDC_SCALE_SLIDER, m_scaleSlider);
	DDX_Control(pDX, IDC_ANGLE_SLIDER_X, m_angleXSlider);
	DDX_Control(pDX, IDC_ANGLE_SLIDER_Y, m_angleYSlider);
	DDX_Control(pDX, IDC_ANGLE_SLIDER_Z, m_angleZSlider);
	DDX_Control(pDX, IDC_TRANSLATEZ_SLIDER, m_translateZSlider);
	DDX_Control(pDX, IDC_SCALEX_SLIDER, m_scaleXSlider);
	DDX_Control(pDX, IDC_SCALEY_SLIDER, m_scaleYSlider);
	DDX_Control(pDX, IDC_SCALEZ_SLIDER, m_scaleZSlider);
	DDX_Control(pDX, IDC_SAVE_BUTTON, m_saveButton);
	DDX_Control(pDX, IDC_LOAD_BUTTON, m_loadButton);
}

BEGIN_MESSAGE_MAP(COpenGLTestOnMFCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_DRAW_BUTTON, &COpenGLTestOnMFCDlg::OnBnClickedDrawButton)
	ON_LBN_SELCHANGE(IDC_COLOR_LIST, &COpenGLTestOnMFCDlg::OnLbnSelchangeColorList)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SCALE_SLIDER, &COpenGLTestOnMFCDlg::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ANGLE_SLIDER_X, &COpenGLTestOnMFCDlg::OnNMCustomdrawAngleSliderX)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ANGLE_SLIDER_Y, &COpenGLTestOnMFCDlg::OnNMCustomdrawAngleSliderY)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ANGLE_SLIDER_Z, &COpenGLTestOnMFCDlg::OnNMCustomdrawAngleSliderZ)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_TRANSLATEZ_SLIDER, &COpenGLTestOnMFCDlg::OnNMCustomdrawTranslatezSlider)
	ON_BN_CLICKED(IDC_PICK_RADIO, &COpenGLTestOnMFCDlg::OnBnClickedPickRadio)
	ON_BN_CLICKED(IDC_VIEW_RADIO, &COpenGLTestOnMFCDlg::OnBnClickedViewRadio)
	ON_BN_CLICKED(IDC_DRAW_PYRAMID_BUTTON, &COpenGLTestOnMFCDlg::OnBnClickedDrawPyramidButton)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SCALEX_SLIDER, &COpenGLTestOnMFCDlg::OnNMCustomdrawScaleXSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SCALEY_SLIDER, &COpenGLTestOnMFCDlg::OnNMCustomdrawScaleYSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SCALEZ_SLIDER, &COpenGLTestOnMFCDlg::OnNMCustomdrawScaleZSlider)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &COpenGLTestOnMFCDlg::OnBnClickedSaveButton)
	ON_BN_CLICKED(IDC_LOAD_BUTTON, &COpenGLTestOnMFCDlg::OnBnClickedLoadButton)
END_MESSAGE_MAP()


// COpenGLTestOnMFCDlg message handlers

BOOL COpenGLTestOnMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	CRect rect;

	m_colorList.AddString(_T("Red"));
	m_colorList.AddString(_T("Green"));
	m_colorList.AddString(_T("Blue"));
	m_colorList.AddString(_T("Yellow"));
	m_colorList.AddString(_T("Cyan"));

	m_scaleSlider.SetRange(2, 100, TRUE);
	m_scaleSlider.SetPos(10);

	m_scaleXSlider.SetRange(2, 100, TRUE);
	m_scaleXSlider.SetPos(10);

	m_scaleYSlider.SetRange(2, 100, TRUE);
	m_scaleYSlider.SetPos(10);

	m_scaleZSlider.SetRange(2, 100, TRUE);
	m_scaleZSlider.SetPos(10);


	
	m_angleXSlider.SetRange(0, 100, TRUE);
	m_angleXSlider.SetPos(0);

	m_angleYSlider.SetRange(0, 100, TRUE);
	m_angleYSlider.SetPos(0);

	m_angleZSlider.SetRange(0, 100, TRUE);
	m_angleZSlider.SetPos(0);

	m_translateZSlider.SetRange(-100, 100, TRUE);
	m_translateZSlider.SetPos(0);


	// Get size and position of the template textfield we created before in the dialog editor
	GetDlgItem(IDC_PIC_OPENGL)->GetWindowRect(rect);

	// Convert screen coordinates to client coordinates
	ScreenToClient(rect);

	// Create OpenGL Control window
	m_oglWindow.oglCreate(rect, this);

	// Setup the OpenGL Window's timer to render
	m_oglWindow.m_unpTimer = m_oglWindow.SetTimer(1, 1, 0);

	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COpenGLTestOnMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COpenGLTestOnMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COpenGLTestOnMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void COpenGLTestOnMFCDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	switch (nType)
	{
	case SIZE_RESTORED:
		{
			if (m_oglWindow.m_bIsMaximized)
			{
				m_oglWindow.OnSize(nType, cx, cy);
				m_oglWindow.m_bIsMaximized = false;
			}

			break;
		}

	case SIZE_MAXIMIZED:
		{
			m_oglWindow.OnSize(nType, cx, cy);
			m_oglWindow.m_bIsMaximized = true;

			break;
		}
	}



}

void COpenGLTestOnMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default


	CDialog::OnTimer(nIDEvent);
}


void COpenGLTestOnMFCDlg::OnBnClickedDrawButton()
{
	CString currentColor;
	m_colorList.GetText(m_colorList.GetCurSel(), currentColor);
	vec3 color = m_oglWindow.defineColor(currentColor);
	m_oglWindow.createConus(1, 3, 5, color, 16, vec3(0,0,0), vec3(0,0,0));
}

void COpenGLTestOnMFCDlg::OnBnClickedDrawPyramidButton()
{
	CString currentColor;
	m_colorList.GetText(m_colorList.GetCurSel(), currentColor);
	vec3 color = m_oglWindow.defineColor(currentColor);
	m_oglWindow.createPyramid(7, 7, color, vec3(0,0,0), vec3(0,0,0));
}


void COpenGLTestOnMFCDlg::OnLbnSelchangeColorList()
{
	// TODO: Add your control notification handler code here
	
}


void COpenGLTestOnMFCDlg::OnNMCustomdrawAngleSliderX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	auto value = m_angleXSlider.GetPos();
	m_oglWindow.m_openGLRenderer.incrementRotX = value*0.001;
	*pResult = 0;
}


void COpenGLTestOnMFCDlg::OnNMCustomdrawAngleSliderY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	auto value = m_angleYSlider.GetPos();
	m_oglWindow.m_openGLRenderer.incrementRotY = value*0.001;
	*pResult = 0;
}


void COpenGLTestOnMFCDlg::OnNMCustomdrawAngleSliderZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	auto value = m_angleZSlider.GetPos();
	m_oglWindow.m_openGLRenderer.incrementRotZ = value*0.001;
	*pResult = 0;
}

void COpenGLTestOnMFCDlg::OnNMCustomdrawTranslatezSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	auto value = m_translateZSlider.GetPos();
	m_oglWindow.m_openGLRenderer.m_translationZ = value*0.5;
	*pResult = 0;
}



void COpenGLTestOnMFCDlg::OnBnClickedPickRadio()
{
	m_oglWindow.m_openGLRenderer.pickMode = true;
	m_oglWindow.m_openGLRenderer.viewMode = false;

	// set default camera view to avoid problems with moving objects
	m_oglWindow.m_fPosX = 0.0f;		// X position of model in camera view
	m_oglWindow.m_fPosY = 0.0f;		// Y position of model in camera view
	m_oglWindow.m_fZoom = 45.0f;	// Zoom on model in camera view
	m_oglWindow.m_fRotX = 45.05f;		// Rotation on model in camera view
	m_oglWindow.m_fRotY	= -10.05f;		// Rotation on model in camera view
	m_oglWindow.m_bIsMaximized = false;
}


void COpenGLTestOnMFCDlg::OnBnClickedViewRadio() 
{
	m_oglWindow.m_openGLRenderer.pickMode = false;
	m_oglWindow.m_openGLRenderer.viewMode = true;
}

void COpenGLTestOnMFCDlg::OnMarkRadio() // set default state of radio button 
{
	CheckRadioButton(IDC_PICK_RADIO, IDC_VIEW_RADIO, IDC_VIEW_RADIO);
}

void COpenGLTestOnMFCDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	static float prev = 2;
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	auto value = m_scaleSlider.GetPos();
	float cof = value*0.1;
	for (auto i : m_oglWindow.m_openGLRenderer.shapes) {
		if (i->marked) {
				vec3 simple(1, 1, 1);
				i->currentScale += simple*(float)(cof - prev);
			}
	}

	prev = m_scaleSlider.GetPos()*0.1;



	*pResult = 0;
}


void COpenGLTestOnMFCDlg::OnNMCustomdrawScaleXSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	static float prevX = 2;
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	auto value = m_scaleXSlider.GetPos();
	float cof = value*0.1;
	if (cof > 0) {
		bool a = 1;
	}
	for (auto i : m_oglWindow.m_openGLRenderer.shapes) {
		if (i->marked) {
			i->currentScale.x += cof - prevX;
		}
	}

	prevX = cof;
	*pResult = 0;
}


void COpenGLTestOnMFCDlg::OnNMCustomdrawScaleYSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	auto value = m_scaleYSlider.GetPos();
	static float prevY = 2;
	float cof = value*0.1;
	for (auto i : m_oglWindow.m_openGLRenderer.shapes) {
		if (i->marked) 
			i->currentScale.y += (float)(cof - prevY);
	}

	prevY = cof;
	*pResult = 0;
}


void COpenGLTestOnMFCDlg::OnNMCustomdrawScaleZSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	auto value = m_scaleZSlider.GetPos();
	static float prevZ = 2*0.1;
	float cof = value*0.1;
	for (auto i : m_oglWindow.m_openGLRenderer.shapes) {
		if (i->marked) 
			i->currentScale.z += (float)(cof - prevZ);
	}

	prevZ = cof;
	*pResult = 0;
}


void COpenGLTestOnMFCDlg::OnBnClickedSaveButton()
{
	// TODO: Add your control notification handler code here
	m_oglWindow.m_openGLRenderer.deleteData();
	m_oglWindow.m_openGLRenderer.saveData();
}


void COpenGLTestOnMFCDlg::OnBnClickedLoadButton()
{
	m_oglWindow.m_openGLRenderer.shapes.clear();
	m_oglWindow.m_openGLRenderer.loadData();
}
