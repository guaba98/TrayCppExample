
// TrayCppExampleDlg.h : 헤더 파일
//

#pragma once
#define WM_TRAYICON_MSG WM_USER + 1 

// CTrayCppExampleDlg 대화 상자
class CTrayCppExampleDlg : public CDialogEx
{
// 생성입니다.
public:
	CTrayCppExampleDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRAYCPPEXAMPLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	// 트레이 관련 변수 선언
	NOTIFYICONDATA  nid;		// 트레이 객체
	BOOL m_bTray = FALSE;		// 트레이 생성 flag

	// 트레이 관련 함수 선언
	void InitTray();			// 트레이 생성
	void OnExit();				// 프로그램 종료
	void OnTrayPopupClose();	// 트레이 Open
	void OnTrayPopupOpen();		// 트레이 Close
	LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);	

};

