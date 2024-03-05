
// YFMFCAppDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YFMFCApp.h"
#include "YFMFCAppDlg.h"
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


// CYFMFCAppDlg 对话框



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


// CYFMFCAppDlg 消息处理程序

BOOL CYFMFCAppDlg::OnInitDialog()
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CYFMFCAppDlg::OnPaint()
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
HCURSOR CYFMFCAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CopyFileToFolder(const CString& sourceFolder, const CString& destinationFolder, const CString& fileName)
{
	// lxk： 复制手写签名数据和指纹数据到当前文件
	// 构建完整的源文件和目标文件路径
	CString sourcePath = sourceFolder + "\\" + fileName;
	CString destinationPath = destinationFolder + "\\" + fileName;

	// 进行文件复制
	if (CopyFile(sourcePath, destinationPath, FALSE)) {
		// 复制成功
		//AfxMessageBox(_T("File copied successfully!"));
	}
	else {
		// 复制失败
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
		// 截取字符串
		parentPath = filePath.Left(lastBackslashPos);
	}
	return parentPath;
}

// 读取 PNG 文件的二进制数据， 进行base64编码，存到txt文件中。
void ReadStorePN(CString filePath, std::string filename)
{
	// lxk: 读取 PNG 文件的二进制数据， 进行base64编码，存到txt文件中。
	CFile pngFile;
	if (pngFile.Open(filePath, CFile::modeRead | CFile::typeBinary))
	{
		// 获取文件大小
		ULONGLONG fileSize = pngFile.GetLength();

		// 分配缓冲区
		BYTE* buffer = new BYTE[fileSize];

		// 读取文件数据
		pngFile.Read(buffer, static_cast<UINT>(fileSize));

		// 关闭文件
		pngFile.Close();

		// 现在 buffer 中存储了 PNG 文件的二进制数据

		// 接下来可以进行 Base64 编码到strbase64
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
		// 将 base64Data 存储到文本文件txt中
		std::ofstream outputFile(filename);
		if (outputFile.is_open()) 
		{
			// 将 base64 数据写入文件
			outputFile << strjsondata;
			// 关闭文件
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

	// 复制手写签名数据和指纹数据到当前文件
	CopyFileToFolder(cspath, _T("."), name);
	std::string strName(CW2A(nameBeforeDot.GetString()));       //采用的方法
	strName = strName + ".txt";
	
	// lxk: 读取 PNG 文件的二进制数据， 进行base64编码，存到txt文件中。
	ReadStorePN(name, strName);


	//printf("Receive callback: cmd=%d, msg=%s, len=%d\n", cmd, msg, len);
}



void CYFMFCAppDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	// 获取手写签名数据。

	int res = 0;
	
	callback_str_send* send_cb = NULL;
	callback_str_receive* receive_cb = my_receive_callback;
	set_callback(send_cb, receive_cb);
	res = GWQ_SignNameEx(NULL, NULL, 4, 100);

	// CDialogEx::OnOK();
}


void CYFMFCAppDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	// 获取指纹数据 。

	int res = 0;
	
	callback_str_send* send_cb = NULL;
	callback_str_receive* receive_cb = my_receive_callback;
	set_callback(send_cb, receive_cb);
	res = GWQ_ReadFingerprint(100, 10, NULL);
	
	// CDialogEx::OnCancel();
}


void CYFMFCAppDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	// 已完成采集
	CDialogEx::OnOK();
}


void CYFMFCAppDlg::OnBnClickedButton2()
{
	// TODO:  获取有方平板的设备号。
	char arr[512] = {0};
	int res = GWQ_GetSN(arr);  
	CString csstr(arr);
	GetDlgItem(IDC_BUTTON2)->SetWindowTextW(csstr);

	// 原设备号          ：arr = "3d9b8674f4b94f6"; 
	// 修改后   ：arr = "3d9b8674f4b94f6xjca";
}
