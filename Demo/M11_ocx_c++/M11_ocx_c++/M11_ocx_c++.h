
// M11_ocx_c++.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CM11_ocx_cApp:
// 有关此类的实现，请参阅 M11_ocx_c++.cpp
//

class CM11_ocx_cApp : public CWinApp
{
public:
	CM11_ocx_cApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CM11_ocx_cApp theApp;