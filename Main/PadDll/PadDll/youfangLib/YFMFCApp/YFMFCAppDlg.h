
// YFMFCAppDlg.h : ͷ�ļ�
//

#pragma once


#include "device10_server_sdk.h"
#pragma comment(lib,"device10_server_sdk.lib")  
#include <map>
#include <string>  // ������õ��� string ����
#include <shlwapi.h>  // ��Ҫ���� shlwapi ͷ�ļ�
#include "base64.h"
#include <iostream>
#include <fstream>

// CYFMFCAppDlg �Ի���
class CYFMFCAppDlg : public CDialogEx
{
// ����
public:
	CYFMFCAppDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_YFMFCAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();

// lxk
private:
	std::map<int, std::string> hanSigFingerMap_2g;
public:
	afx_msg void OnBnClickedButton2();
};


