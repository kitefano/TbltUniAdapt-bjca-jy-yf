
// YFMFCAppDlg.h : 头文件
//

#pragma once


#include "device10_server_sdk.h"
#pragma comment(lib,"device10_server_sdk.lib")  
#include <map>
#include <string>  // 如果你用到了 string 类型
#include <shlwapi.h>  // 需要包含 shlwapi 头文件
#include "base64.h"
#include <iostream>
#include <fstream>

// CYFMFCAppDlg 对话框
class CYFMFCAppDlg : public CDialogEx
{
// 构造
public:
	CYFMFCAppDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_YFMFCAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();

// lxk
private:
	std::map<int, std::string> hanSigFingerMap_2g;
public:
	afx_msg void OnBnClickedButton2();
};


