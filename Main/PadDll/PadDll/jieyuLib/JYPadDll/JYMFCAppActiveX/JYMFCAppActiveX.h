
// JYMFCAppActiveX.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CJYMFCAppActiveXApp: 
// �йش����ʵ�֣������ JYMFCAppActiveX.cpp
//

class CJYMFCAppActiveXApp : public CWinApp
{
public:
	CJYMFCAppActiveXApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CJYMFCAppActiveXApp theApp;