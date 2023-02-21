
// OutlineDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "OutlineApp.h"
#include "OutlineDlg.h"

#include "Outline.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx {
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COutlineDlg dialog



COutlineDlg::COutlineDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OUTLINE_DIALOG, pParent) {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COutlineDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COutlineDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OUTLINE, &COutlineDlg::OnBnClickedOutline)
	ON_BN_CLICKED(IDC_SELECT_FONT, &COutlineDlg::OnBnClickedSelectFont)
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// COutlineDlg message handlers

BOOL COutlineDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr) {
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// Font
	// 초기 Font 설정
	CFont font;
	CString strFontName = _T("Segoe UI");
	font.CreatePointFont(3000, strFontName);
	font.GetLogFont(&m_logfont);
	SetDlgItemText(IDC_TEXT, _T("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"));
	SetDlgItemText(IDC_FONT_NAME, strFontName);
	SetDlgItemInt(IDC_FONT_SIZE, -m_logfont.lfHeight);
	CheckDlgButton(IDC_CHK_OUTLINE, 1);
	CheckDlgButton(IDC_CHK_HORZ_HATCHING, 1);
	SetDlgItemText(IDC_HORZ_HATCHING_STEP, _T("10"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COutlineDlg::OnSysCommand(UINT nID, LPARAM lParam) {
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else {
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COutlineDlg::OnPaint() {
	if (IsIconic()) {
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
	else {
		CDialogEx::OnPaint();
	}
}

HCURSOR COutlineDlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}

void COutlineDlg::OnBnClickedSelectFont() {
	// Get Font Name/Size from user
	CFontDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;
	dlg.GetCurrentFont(&m_logfont);
	SetDlgItemText(IDC_FONT_NAME, m_logfont.lfFaceName);
	SetDlgItemText(IDC_FONT_SIZE, std::to_wstring(-m_logfont.lfHeight).c_str());
	OnBnClickedOutline();
}

void COutlineDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) {
	switch (nIDCtl) {
	case IDC_VIEW:
		if (auto* pWnd = GetDlgItem(nIDCtl)) {
			CDC dcClient;
			dcClient.Attach(lpDrawItemStruct->hDC);
			struct DETACH {
				CDC& dc;
				DETACH(CDC& dc) : dc(dc) {}
				~DETACH() {
					dc.Detach();
				}
			} detacher(dcClient);

			CMemDC dcMem(dcClient, pWnd);
			CDC& dc = dcMem.GetDC();
			CRect rectClient;
			pWnd->GetClientRect(rectClient);

			CBrush brushWhite(RGB(255, 255, 255));
			dc.Rectangle(rectClient);

			double scale = rectClient.Height()* 0.7;

			dc.SelectStockObject(BLACK_PEN);
			for (auto const& line : m_lines) {
				auto pt = line.front();
				pt *= scale;
				dc.MoveTo(pt.x, pt.y);
				for (size_t i{1}; i < line.size(); i++) {
					pt = line[i] * scale;
					dc.LineTo(pt.x, pt.y);
				}
			}

		}
		return;
	}

	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void COutlineDlg::OnBnClickedOutline() {
	CWaitCursor wc;

	auto GetText = [&](int id) -> CString {
		CString str;
		GetDlgItemText(IDC_TEXT, str);
		return str;
	};

	auto text = GetText(IDC_TEXT);
	bool bOutline = IsDlgButtonChecked(IDC_CHK_OUTLINE);
	bool bHorzHatching = IsDlgButtonChecked(IDC_CHK_HORZ_HATCHING);
	int nHatchingStep = GetDlgItemInt(IDC_HORZ_HATCHING_STEP);

	// Outline
	m_lines = Outline(text, m_logfont, bOutline, bHorzHatching, nHatchingStep);

	// display
	if (auto* pWnd = GetDlgItem(IDC_VIEW)) {
		pWnd->Invalidate();
	}
}
