
// JYMFCAppActiveXDlg.h : ͷ�ļ�
//

#pragma once
#include <string>
#include "writingpadctrl1.h"
#include <atlstr.h>
#include <afxwin.h>



// CJYMFCAppActiveXDlg �Ի���
class CJYMFCAppActiveXDlg : public CDialogEx
{
// ����
public:
	CJYMFCAppActiveXDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_JYMFCAPPACTIVEX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ��̬����
public:

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
