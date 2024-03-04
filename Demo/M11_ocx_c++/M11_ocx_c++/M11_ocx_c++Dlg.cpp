
// M11_ocx_c++Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M11_ocx_c++.h"
#include "M11_ocx_c++Dlg.h"
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


// CM11_ocx_cDlg �Ի���



CM11_ocx_cDlg::CM11_ocx_cDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CM11_ocx_cDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM11_ocx_cDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WRITINGPADCTRL1, WritePad);
	//DDX_Control(pDX, IDC_EDIT1, SignReturn);
	DDX_Control(pDX, IDC_EDIT1, CEditT);
}

BEGIN_MESSAGE_MAP(CM11_ocx_cDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON1, &CM11_ocx_cDlg::OnBnClickedButton1)
	//ON_BN_CLICKED(IDC_BUTTON3, &CM11_ocx_cDlg::OnBnClickedButton3)
	//ON_BN_CLICKED(IDC_BUTTON2, &CM11_ocx_cDlg::OnBnClickedButton2)
	//ON_BN_CLICKED(IDC_BUTTON4, &CM11_ocx_cDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CM11_ocx_cDlg::OnBnClickedButton5)
	//ON_BN_CLICKED(IDC_BUTTON6, &CM11_ocx_cDlg::OnBnClickedButton6)
	//ON_BN_CLICKED(IDC_BUTTON7, &CM11_ocx_cDlg::OnBnClickedButton7)
	//ON_EN_CHANGE(IDC_EDIT1, &CM11_ocx_cDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CM11_ocx_cDlg ��Ϣ�������

BOOL CM11_ocx_cDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CM11_ocx_cDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CM11_ocx_cDlg::OnPaint()
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
HCURSOR CM11_ocx_cDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CM11_ocx_cDlg::OnBnClickedButton1()
//{
//	int k=WritePad.GWQ_DeviceOnline();
//	CEditT.SetWindowTextA(""+k);
//	
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}
//
//void CM11_ocx_cDlg::OnBnClickedButton2()
//{
//	// ǩ��PDF(���ǩ��)
//	WritePad.TouchSign("d:\\1.pdf", 0);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}
//
//void CM11_ocx_cDlg::OnBnClickedButton3()
//{
//	// ����ǩ�����̶���
//	WritePad.DoGWQ_StartSign2("d:\\1.pdf","d:\\1.xml", "2,1,100,100", "��ǩ��",2);
//	
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}
//
//void CM11_ocx_cDlg::OnBnClickedButton4()
//{
//	// ��Ԥ��
//	WritePad.DoGWQ_StartSign2("d:\\1.pdf","d:\\1.xml", "0,1,0,50|0,1,0,100", "��ǩ��",1);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}


void CM11_ocx_cDlg::OnBnClickedButton5()
{
	// ��ǩ��
	WritePad.DoGWQ_StartSign2("","d:\\1.xml", "0,1,0,50", "",0);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


//void CM11_ocx_cDlg::OnBnClickedButton6()
//{
//	// ��ָ��
//	WritePad.DoGWQ_StartSign2("","d:\\1.xml", "1,1,0,50", "",0);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}


//void CM11_ocx_cDlg::OnBnClickedButton7()
//{
//	// ��ǩ��+ָ��
//	WritePad.DoGWQ_StartSign2("","d:\\1.xml", "2,1,0,50", "",0);
//	
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}


BEGIN_EVENTSINK_MAP(CM11_ocx_cDlg, CDialogEx)
	ON_EVENT(CM11_ocx_cDlg, IDC_WRITINGPADCTRL1, 3, CM11_ocx_cDlg::OnAfterGWQ_StartSignEventWritingpadctrl1, VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()


void CM11_ocx_cDlg::OnAfterGWQ_StartSignEventWritingpadctrl1(long ErrorCode, LPCTSTR SignPdfBase64)
{
	// TODO: �ڴ˴������Ϣ����������
	CEditT.SetWindowTextA(SignPdfBase64);
}
