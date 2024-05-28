
// TrayCppExampleDlg.h : ��� ����
//

#pragma once
#define WM_TRAYICON_MSG WM_USER + 1 

// CTrayCppExampleDlg ��ȭ ����
class CTrayCppExampleDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CTrayCppExampleDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRAYCPPEXAMPLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	// Ʈ���� ���� ���� ����
	NOTIFYICONDATA  nid;		// Ʈ���� ��ü
	BOOL m_bTray = FALSE;		// Ʈ���� ���� flag

	// Ʈ���� ���� �Լ� ����
	void InitTray();			// Ʈ���� ����
	void OnExit();				// ���α׷� ����
	void OnTrayPopupClose();	// Ʈ���� Open
	void OnTrayPopupOpen();		// Ʈ���� Close
	LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);	

};

