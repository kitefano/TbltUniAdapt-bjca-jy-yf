
// YFMFCApp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CYFMFCAppApp: 
// �йش����ʵ�֣������ YFMFCApp.cpp
//

class CYFMFCAppApp : public CWinApp
{
public:
	CYFMFCAppApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CYFMFCAppApp theApp;