
// JYMFCAppActiveXDlg.h : 头文件
//

#pragma once
#include <string>
#include "writingpadctrl1.h"
#include <atlstr.h>
#include <afxwin.h>



// CJYMFCAppActiveXDlg 对话框
class CJYMFCAppActiveXDlg : public CDialogEx
{
// 构造
public:
	CJYMFCAppActiveXDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_JYMFCAPPACTIVEX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 静态变量
public:

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
	CWritingpadctrl1 WritePad;
	DECLARE_EVENTSINK_MAP()
	void OnAfterGWQ_StartSignEventWritingpadctrl1(long ErrorCode, LPCTSTR SignPdfBase64);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	// afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();

public:
	int IsJYTbl();
};
