// M11_ocx_c++Dlg.h : 头文件
//

#pragma once
#include "writingpadctrl1.h"
#include "afxwin.h"


// CM11_ocx_cDlg 对话框
class CM11_ocx_cDlg : public CDialogEx
{
// 构造
public:
	CM11_ocx_cDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_M11_OCX_C_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

public:
	CWritingpadctrl1 WritePad;
	//afx_msg void OnBnClickedButton1();
	//afx_msg void OnBnClickedButton3();
	//afx_msg void OnBnClickedButton2();
	//afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	//afx_msg void OnBnClickedButton6();
	//afx_msg void OnBnClickedButton7();
	//CEdit SignReturn; //--lxk
	//afx_msg void OnEnChangeEdit1();
	//DECLARE_EVENTSINK_MAP()
	//void OnAfterGWQ_StartSignEventWritingpadctrl1(long ErrorCode, LPCTSTR SignPdfBase64);
	DECLARE_EVENTSINK_MAP()
	void OnAfterGWQ_StartSignEventWritingpadctrl1(long ErrorCode, LPCTSTR SignPdfBase64);
	CEdit CEditT;
};
