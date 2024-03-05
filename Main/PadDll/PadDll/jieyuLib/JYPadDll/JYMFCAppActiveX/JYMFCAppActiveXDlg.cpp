
// JYMFCAppActiveXDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JYMFCAppActiveX.h"
#include "JYMFCAppActiveXDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CJYMFCAppActiveXDlg 对话框



CJYMFCAppActiveXDlg::CJYMFCAppActiveXDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJYMFCAppActiveXDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJYMFCAppActiveXDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WRITINGPADCTRL1, WritePad);
}

BEGIN_MESSAGE_MAP(CJYMFCAppActiveXDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CJYMFCAppActiveXDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CJYMFCAppActiveXDlg::OnBnClickedButton1)
	// ON_BN_CLICKED(IDCANCEL, &CJYMFCAppActiveXDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CJYMFCAppActiveXDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CJYMFCAppActiveXDlg 消息处理程序

BOOL CJYMFCAppActiveXDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CJYMFCAppActiveXDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CJYMFCAppActiveXDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CJYMFCAppActiveXDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void WriteToFile(const CString& filePath, const CString& data)
{
	CStdioFile file;
	if (file.Open(filePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
	{
		// 写入数据到文件
		file.WriteString(data);
		// 关闭文件
		file.Close();
	}
	else
	{
		// 处理文件打开失败的情况
		AfxMessageBox(_T("Failed to open file for writing."));
	}
}



void CJYMFCAppActiveXDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码

	//// 纯签字
	//WritePad.DoGWQ_StartSign2("", "d:\\1.xml", "0,1,0,50", "", 0);
	//// 纯指纹
	//WritePad.DoGWQ_StartSign2("", "d:\\1.xml", "1,1,0,50", "", 0);
	// 纯签字+指纹
	WritePad.DoGWQ_StartSign2("", "d:\\1.xml", "2,1,0,50", "", 0);

	
	// CDialogEx::OnCancel();
}

//void CJYMFCAppActiveXDlg::OnBnClickedCancel()
//{
//	// TODO:  在此添加控件通知处理程序代码
//	CDialogEx::OnCancel();
//}


BEGIN_EVENTSINK_MAP(CJYMFCAppActiveXDlg, CDialogEx)
	ON_EVENT(CJYMFCAppActiveXDlg, IDC_WRITINGPADCTRL1, 3, CJYMFCAppActiveXDlg::OnAfterGWQ_StartSignEventWritingpadctrl1, VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()

void CJYMFCAppActiveXDlg::OnAfterGWQ_StartSignEventWritingpadctrl1(long ErrorCode, LPCTSTR SignPdfBase64)
{
	// TODO:  在此处添加消息处理程序代码
	CString filePath = _T("SignFile.txt");
	CString dataToWrite = _T(SignPdfBase64);
	WriteToFile(filePath, dataToWrite);

	CDialogEx::OnCancel();

}

void CJYMFCAppActiveXDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CJYMFCAppActiveXDlg::OnBnClickedButton2()
{
	CString restr = WritePad.GWQ_GetSeriesNum();
	GetDlgItem(IDC_BUTTON2)->SetWindowTextA(restr);

	int res = WritePad.GWQ_DeviceOnline();
	CString strValue;
	strValue.Format(_T("%d"), res);
	GetDlgItem(IDC_BUTTON2)->SetWindowTextA(strValue);

	// TODO:  在此添加控件通知处理程序代码  
}
