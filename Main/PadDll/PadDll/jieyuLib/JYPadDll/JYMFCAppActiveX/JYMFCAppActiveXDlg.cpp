
// JYMFCAppActiveXDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JYMFCAppActiveX.h"
#include "JYMFCAppActiveXDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CJYMFCAppActiveXDlg �Ի���



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


// CJYMFCAppActiveXDlg ��Ϣ�������

BOOL CJYMFCAppActiveXDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CJYMFCAppActiveXDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CJYMFCAppActiveXDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void WriteToFile(const CString& filePath, const CString& data)
{
	CStdioFile file;
	if (file.Open(filePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
	{
		// д�����ݵ��ļ�
		file.WriteString(data);
		// �ر��ļ�
		file.Close();
	}
	else
	{
		// �����ļ���ʧ�ܵ����
		AfxMessageBox(_T("Failed to open file for writing."));
	}
}



void CJYMFCAppActiveXDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	//// ��ǩ��
	//WritePad.DoGWQ_StartSign2("", "d:\\1.xml", "0,1,0,50", "", 0);
	//// ��ָ��
	//WritePad.DoGWQ_StartSign2("", "d:\\1.xml", "1,1,0,50", "", 0);
	// ��ǩ��+ָ��
	WritePad.DoGWQ_StartSign2("", "d:\\1.xml", "2,1,0,50", "", 0);

	
	// CDialogEx::OnCancel();
}

//void CJYMFCAppActiveXDlg::OnBnClickedCancel()
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	CDialogEx::OnCancel();
//}


BEGIN_EVENTSINK_MAP(CJYMFCAppActiveXDlg, CDialogEx)
	ON_EVENT(CJYMFCAppActiveXDlg, IDC_WRITINGPADCTRL1, 3, CJYMFCAppActiveXDlg::OnAfterGWQ_StartSignEventWritingpadctrl1, VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()

void CJYMFCAppActiveXDlg::OnAfterGWQ_StartSignEventWritingpadctrl1(long ErrorCode, LPCTSTR SignPdfBase64)
{
	// TODO:  �ڴ˴������Ϣ����������
	CString filePath = _T("SignFile.txt");
	CString dataToWrite = _T(SignPdfBase64);
	WriteToFile(filePath, dataToWrite);

	CDialogEx::OnCancel();

}

void CJYMFCAppActiveXDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ���ӿؼ�֪ͨ����������  
}
