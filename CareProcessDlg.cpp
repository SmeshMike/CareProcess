
// CareProcessDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "CareProcess.h"
#include "CareProcessDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define IDC_TIMER 5000

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
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

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCareProcessDlg dialog



CCareProcessDlg::CCareProcessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CAREPROCESS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCareProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXE, exeFile);
	DDX_Control(pDX, IDC_PEXE, foundFile);
	DDX_Text(pDX, IDC_EDIT1, file);
}

BEGIN_MESSAGE_MAP(CCareProcessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEARCH, &CCareProcessDlg::OnBnClickedSearch)
	ON_BN_CLICKED(IDC_RUN, &CCareProcessDlg::OnBnClickedRun)
	ON_BN_CLICKED(IDC_REFRESH, &CCareProcessDlg::OnBnClickedRefresh)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCareProcessDlg message handlers

BOOL CCareProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
		
	SetTimer(IDC_TIMER, 500, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCareProcessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCareProcessDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCareProcessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCareProcessDlg::OnBnClickedSearch()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	exeFile.ResetContent();

	CFileFind Findexe;
	BOOL Work = Findexe.FindFile((LPCTSTR)(file + "\\*.exe"));
	while (Work)
	{
		Work = Findexe.FindNextFileW();
		exeFile.AddString((LPCTSTR)(Findexe.GetFileName()));
	}
	UpdateData(FALSE);
}


void CCareProcessDlg::OnBnClickedRun()
{
	// TODO: Add your control notification handler code here
	STARTUPINFO si{ sizeof(si) };
	PROCESS_INFORMATION info;
	CString StringName;
	exeFile.GetText(exeFile.GetCurSel(), StringName);
	BOOL Work = CreateProcess(
		NULL, (file + "\\" + StringName).GetBuffer(),
		NULL, NULL, FALSE, 0, NULL,
		file.GetBuffer(), &si, &info);
	if (Work != 0)
	{
		::CloseHandle(info.hThread);
		int s = foundFile.AddString(StringName);
		foundFile.SetItemData(s, (DWORD_PTR)info.hProcess);
	}
	if (Work == 0)
	{
		MessageBox(L"Процесс не может быть запущен. Выберете другой", MB_OK);
	}
}


void CCareProcessDlg::OnBnClickedRefresh()
{
	// TODO: Add your control notification handler code here
	if (foundFile.GetCurSel() != -1)
	{
		HANDLE pi = (HANDLE)(foundFile.GetItemData(foundFile.GetCurSel()));
		::TerminateProcess(pi, EXCEPTION_BREAKPOINT);
	}
	else
		MessageBox(L"Выберете процесс, который хотите закрыть", MB_OK);
}


void CCareProcessDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	for (int i = 0; i < foundFile.GetCount(); i++)
	{
		DWORD ExitCode = STILL_ACTIVE;
		HANDLE pi = (HANDLE)(foundFile.GetItemData(i));
		::GetExitCodeProcess(pi, &ExitCode);
		if (ExitCode != STILL_ACTIVE)
		{
			::CloseHandle(pi);
			foundFile.DeleteString(i);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}
