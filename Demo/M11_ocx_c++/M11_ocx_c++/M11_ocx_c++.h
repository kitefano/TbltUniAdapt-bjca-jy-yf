
// M11_ocx_c++.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CM11_ocx_cApp:
// �йش����ʵ�֣������ M11_ocx_c++.cpp
//

class CM11_ocx_cApp : public CWinApp
{
public:
	CM11_ocx_cApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CM11_ocx_cApp theApp;