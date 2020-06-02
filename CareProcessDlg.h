
// CareProcessDlg.h : header file
//

#pragma once


// CCareProcessDlg dialog
class CCareProcessDlg : public CDialogEx
{
// Construction
public:
	CCareProcessDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAREPROCESS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedRun();
	afx_msg void OnBnClickedRefresh();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListBox exeFile;
	CListBox foundFile;
	CString file;
};
