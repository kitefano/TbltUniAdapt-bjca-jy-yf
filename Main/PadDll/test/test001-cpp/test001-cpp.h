
// test001-cpp.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// Ctest001cppApp: 
// 有关此类的实现，请参阅 test001-cpp.cpp
//

class Ctest001cppApp : public CWinApp
{
public:
	Ctest001cppApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern Ctest001cppApp theApp;