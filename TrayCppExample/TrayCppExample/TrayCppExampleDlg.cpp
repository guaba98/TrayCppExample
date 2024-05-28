
// TrayCppExampleDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "TrayCppExample.h"
#include "TrayCppExampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CTrayCppExampleDlg ��ȭ ����



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


// CTrayCppExampleDlg �޽��� ó����

BOOL CTrayCppExampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	InitTray();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CTrayCppExampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);	//������ ���� �ʿ�� ���⼭ ����
	lstrcpy(nid.szTip, TEXT("View DBAgent program"));
	nid.uCallbackMessage = WM_TRAYICON_MSG;
}

void CTrayCppExampleDlg::OnExit()
{
	Shell_NotifyIcon(NIM_DELETE, &nid); //����� �����۾��� ����� �ٷ� �������� �������.

	DestroyWindow();
}


LRESULT CTrayCppExampleDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	switch (lParam) 
	{
		case WM_LBUTTONDBLCLK:	// ����Ŭ������ ��
			{
				ShowWindow(SW_SHOW);					// â ����
				Shell_NotifyIcon(NIM_DELETE, &nid);		// TRAY ����
			}
			break;
		case WM_RBUTTONUP:	// ������ ���콺 Ŭ������ ��
			{
				SetForegroundWindow();

				CPoint ptMouse;
				::GetCursorPos(&ptMouse);

				CMenu menu;
				menu.LoadMenu(IDR_MENU_TRAY);	// �޴� ����
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
	strMessage.Format(_T("���� ���α׷��� �����Ͻðڽ��ϱ�?"));
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