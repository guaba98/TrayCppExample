
// TrayCppExampleDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "TrayCppExample.h"
#include "TrayCppExampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTrayCppExampleDlg 대화 상자



CTrayCppExampleDlg::CTrayCppExampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TRAYCPPEXAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrayCppExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTrayCppExampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()

	ON_MESSAGE(WM_TRAYICON_MSG, OnTrayNotify)
	ON_COMMAND(ID_MENU_CLOSE, &CTrayCppExampleDlg::OnTrayPopupClose)
	ON_COMMAND(ID_MENU_OPEN, &CTrayCppExampleDlg::OnTrayPopupOpen)

	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CTrayCppExampleDlg 메시지 처리기

BOOL CTrayCppExampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	InitTray();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTrayCppExampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}

	if (nID == SC_CLOSE)
	{
		Shell_NotifyIcon(NIM_ADD, &nid);
		ShowWindow(SW_HIDE);
	}

	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTrayCppExampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTrayCppExampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTrayCppExampleDlg::InitTray()
{
	nid.cbSize = sizeof(nid);
	nid.hWnd = GetSafeHwnd();
	nid.uID = 0;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);	//아이콘 변경 필요시 여기서 변경
	lstrcpy(nid.szTip, TEXT("View DBAgent program"));
	nid.uCallbackMessage = WM_TRAYICON_MSG;
}

void CTrayCppExampleDlg::OnExit()
{
	Shell_NotifyIcon(NIM_DELETE, &nid); //종료시 삭제작업을 해줘야 바로 아이콘이 사라진다.

	DestroyWindow();
}


LRESULT CTrayCppExampleDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	switch (lParam) 
	{
		case WM_LBUTTONDBLCLK:	// 더블클릭했을 때
			{
				ShowWindow(SW_SHOW);					// 창 띄우기
				Shell_NotifyIcon(NIM_DELETE, &nid);		// TRAY 삭제
			}
			break;
		case WM_RBUTTONUP:	// 오른쪽 마우스 클릭했을 때
			{
				SetForegroundWindow();

				CPoint ptMouse;
				::GetCursorPos(&ptMouse);

				CMenu menu;
				menu.LoadMenu(IDR_MENU_TRAY);	// 메뉴 띄우기
				CMenu *pMenu = menu.GetSubMenu(0);
				pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, ptMouse.x, ptMouse.y, AfxGetMainWnd());
			}
			break;
	}
	return TRUE;
}

void CTrayCppExampleDlg::OnTrayPopupClose()
{
	CString strMessage;
	strMessage.Format(_T("정말 프로그램을 종료하시겠습니까?"));
	if (AfxMessageBox(strMessage, MB_YESNO) == IDNO) {
		return;
	}

	if (m_bTray == TRUE) {
		Shell_NotifyIcon(NIM_DELETE, &nid);
		m_bTray = FALSE;
		OnExit();

	}

	//m_bExit = TRUE;
	AfxGetMainWnd()->PostMessage(WM_CLOSE);
}


void CTrayCppExampleDlg::OnTrayPopupOpen()
{
	if (m_bTray == TRUE) {
		m_bTray = FALSE;
		Shell_NotifyIcon(NIM_DELETE, &nid);
	}

	ShowWindow(SW_SHOW);
	::SetWindowPos(AfxGetMainWnd()->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
}