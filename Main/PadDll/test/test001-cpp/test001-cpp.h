
// test001-cpp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ctest001cppApp: 
// �йش����ʵ�֣������ test001-cpp.cpp
//

class Ctest001cppApp : public CWinApp
{
public:
	Ctest001cppApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ctest001cppApp theApp;