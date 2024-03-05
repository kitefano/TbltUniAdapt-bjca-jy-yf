
// JYMFCAppActiveXGetDevNumDlg.cpp : ʵ���ļ�
//
#include <afx.h> // ���� MFC ����ͷ�ļ�
#include <iostream>
#include "stdafx.h"
#include "JYMFCAppActiveXGetDevNum.h"
#include "JYMFCAppActiveXGetDevNumDlg.h"
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


// CJYMFCAppActiveXGetDevNumDlg �Ի���



CJYMFCAppActiveXGetDevNumDlg::CJYMFCAppActiveXGetDevNumDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJYMFCAppActiveXGetDevNumDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJYMFCAppActiveXGetDevNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WRITINGPADCTRL1, WritePad);
}

BEGIN_MESSAGE_MAP(CJYMFCAppActiveXGetDevNumDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CJYMFCAppActiveXGetDevNumDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CJYMFCAppActiveXGetDevNumDlg ��Ϣ�������

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

BOOL CJYMFCAppActiveXGetDevNumDlg::OnInitDialog()
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
	CString filePath = _T("DevNum.txt");
	// �����DevNum.txt�ļ����ݡ�
	// ʹ�� CStdioFile ���ļ�
	CStdioFile file;
	if (file.Open(filePath, CFile::modeWrite | CFile::modeCreate | CFile::typeText))
	{
		// ����ļ�����
		file.SetLength(0);
		file.Close();
	}
	CString dataToWrite = WritePad.GWQ_GetSeriesNum();
	WriteToFile(filePath, dataToWrite);

	// ���ļ� JYOnline.txt д�� �豸����״̬��
	CString filePath2 = _T("JYOnline.txt");
	CStdioFile file2;
	if (file2.Open(filePath2, CFile::modeWrite | CFile::modeCreate | CFile::typeText))
	{
		// ����ļ�����
		file2.SetLength(0);
		file2.Close();
	}
	int res = WritePad.GWQ_DeviceOnline();
	CString stres;
	stres.Format(_T("%d"), res);
	WriteToFile(filePath2, stres);
		
	// Ϊ�˾��� ����ʾ���棬ִ��������Ĵ�����˳���
	CDialogEx::OnOK();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CJYMFCAppActiveXGetDevNumDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CJYMFCAppActiveXGetDevNumDlg::OnPaint()
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
HCURSOR CJYMFCAppActiveXGetDevNumDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CJYMFCAppActiveXGetDevNumDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CString restr = WritePad.GWQ_GetSeriesNum();
	GetDlgItem(IDC_BUTTON1)->SetWindowTextA(restr);

	CDialogEx::OnOK();
}
