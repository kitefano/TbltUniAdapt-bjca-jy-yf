// M11_ocx_c++Dlg.h : ͷ�ļ�
//

#pragma once
#include "writingpadctrl1.h"
#include "afxwin.h"


// CM11_ocx_cDlg �Ի���
class CM11_ocx_cDlg : public CDialogEx
{
// ����
public:
	CM11_ocx_cDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_M11_OCX_C_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
