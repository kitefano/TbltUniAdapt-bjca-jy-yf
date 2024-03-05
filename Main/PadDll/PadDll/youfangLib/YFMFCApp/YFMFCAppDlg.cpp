
// YFMFCAppDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YFMFCApp.h"
#include "YFMFCAppDlg.h"
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


// CYFMFCAppDlg �Ի���



CYFMFCAppDlg::CYFMFCAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CYFMFCAppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CYFMFCAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CYFMFCAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CYFMFCAppDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CYFMFCAppDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CYFMFCAppDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CYFMFCAppDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CYFMFCAppDlg ��Ϣ�������

BOOL CYFMFCAppDlg::OnInitDialog()
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

void CYFMFCAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CYFMFCAppDlg::OnPaint()
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
HCURSOR CYFMFCAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CopyFileToFolder(const CString& sourceFolder, const CString& destinationFolder, const CString& fileName)
{
	// lxk�� ������дǩ�����ݺ�ָ�����ݵ���ǰ�ļ�
	// ����������Դ�ļ���Ŀ���ļ�·��
	CString sourcePath = sourceFolder + "\\" + fileName;
	CString destinationPath = destinationFolder + "\\" + fileName;

	// �����ļ�����
	if (CopyFile(sourcePath, destinationPath, FALSE)) {
		// ���Ƴɹ�
		//AfxMessageBox(_T("File copied successfully!"));
	}
	else {
		// ����ʧ��
		DWORD error = GetLastError();
		CString errorMessage;
		errorMessage.Format(_T("File copy failed with error code: %d"), error);
		AfxMessageBox(errorMessage);
	}
}

CString GetFilePath(const char *array)
{
	CString filePath = CString(array);
	int lastBackslashPos = filePath.ReverseFind(_T('\\'));
	CString parentPath;
	if (lastBackslashPos != -1)
	{
		// ��ȡ�ַ���
		parentPath = filePath.Left(lastBackslashPos);
	}
	return parentPath;
}

// ��ȡ PNG �ļ��Ķ��������ݣ� ����base64���룬�浽txt�ļ��С�
void ReadStorePN(CString filePath, std::string filename)
{
	// lxk: ��ȡ PNG �ļ��Ķ��������ݣ� ����base64���룬�浽txt�ļ��С�
	CFile pngFile;
	if (pngFile.Open(filePath, CFile::modeRead | CFile::typeBinary))
	{
		// ��ȡ�ļ���С
		ULONGLONG fileSize = pngFile.GetLength();

		// ���仺����
		BYTE* buffer = new BYTE[fileSize];

		// ��ȡ�ļ�����
		pngFile.Read(buffer, static_cast<UINT>(fileSize));

		// �ر��ļ�
		pngFile.Close();

		// ���� buffer �д洢�� PNG �ļ��Ķ���������

		// ���������Խ��� Base64 ���뵽strbase64
		std::string strbuffer(reinterpret_cast<char*>(buffer), fileSize);
		delete[] buffer;
		std::string strbase64 = base64_encode(strbuffer);
		std::string strjsondata;
		std::string subString = "sign";
		size_t found = filename.find(subString);
		if (found != std::string::npos)
		{
			strjsondata = "{\"signImage\":\"" + strbase64 + "\"";
			strjsondata = strjsondata + ", \"fingerImage\":\"\"}";
		}
		else
		{
			strjsondata = "{ \"signImage\":\"\",";
			strjsondata = strjsondata + "\"fingerImage\":\"" + strbase64 + "\"}";
		}
		// �� base64Data �洢���ı��ļ�txt��
		std::ofstream outputFile(filename);
		if (outputFile.is_open()) 
		{
			// �� base64 ����д���ļ�
			outputFile << strjsondata;
			// �ر��ļ�
			outputFile.close();
			std::cout << "Base64 data has been written to " << filename << std::endl;
		}
		else 
		{
			std::cerr << "Unable to open file for writing." << std::endl;
		}

	}
}

void my_receive_callback(int cmd, const char* msg, const char* array[], int len) 
{
	// lxk
	// array = C:\Users\86166\AppData\Local\Temp\device10-demo-dir\sign.xml
	const char *strtmp = array[0];
	CString cspath = GetFilePath(strtmp);
	CString filename = PathFindFileName(CString(strtmp));
	int dotIndex = filename.Find(_T("."));
	CString nameBeforeDot = filename.Left(dotIndex);
	CString name = filename.Left(dotIndex) + ".png";

	// ������дǩ�����ݺ�ָ�����ݵ���ǰ�ļ�
	CopyFileToFolder(cspath, _T("."), name);
	std::string strName(CW2A(nameBeforeDot.GetString()));       //���õķ���
	strName = strName + ".txt";
	
	// lxk: ��ȡ PNG �ļ��Ķ��������ݣ� ����base64���룬�浽txt�ļ��С�
	ReadStorePN(name, strName);


	//printf("Receive callback: cmd=%d, msg=%s, len=%d\n", cmd, msg, len);
}



void CYFMFCAppDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ��дǩ�����ݡ�

	int res = 0;
	
	callback_str_send* send_cb = NULL;
	callback_str_receive* receive_cb = my_receive_callback;
	set_callback(send_cb, receive_cb);
	res = GWQ_SignNameEx(NULL, NULL, 4, 100);

	// CDialogEx::OnOK();
}


void CYFMFCAppDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ��ȡָ������ ��

	int res = 0;
	
	callback_str_send* send_cb = NULL;
	callback_str_receive* receive_cb = my_receive_callback;
	set_callback(send_cb, receive_cb);
	res = GWQ_ReadFingerprint(100, 10, NULL);
	
	// CDialogEx::OnCancel();
}


void CYFMFCAppDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ����ɲɼ�
	CDialogEx::OnOK();
}


void CYFMFCAppDlg::OnBnClickedButton2()
{
	// TODO:  ��ȡ�з�ƽ����豸�š�
	char arr[512] = {0};
	int res = GWQ_GetSN(arr);  
	CString csstr(arr);
	GetDlgItem(IDC_BUTTON2)->SetWindowTextW(csstr);

	// ԭ�豸��          ��arr = "3d9b8674f4b94f6"; 
	// �޸ĺ�   ��arr = "3d9b8674f4b94f6xjca";
}
