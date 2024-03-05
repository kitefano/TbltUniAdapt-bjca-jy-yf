#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装器类

// 注意:  不要修改此文件的内容。  如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CWritingpadctrl1 包装器类

class CWritingpadctrl1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CWritingpadctrl1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x675F282B, 0xC42C, 0x4E4E, { 0x81, 0x89, 0xFB, 0x66, 0x24, 0x7B, 0x3, 0xF7 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:


// 操作
public:

// _DWritingPad

// Functions
//

	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL OpenURL(LPCTSTR url)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, url);
		return result;
	}
	long GWQ_TellerInfo(LPCTSTR TellerName, LPCTSTR TellerNo, LPCTSTR TellerPhoto)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, TellerName, TellerNo, TellerPhoto);
		return result;
	}
	long DoGWQ_StartSign(LPCTSTR PDFPath, LPCTSTR TxtPath, LPCTSTR Location, LPCTSTR VoiceStr)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, PDFPath, TxtPath, Location, VoiceStr);
		return result;
	}
	CString OnAfterGWQ_StartSign()
	{
		CString result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long GWQ_CallNumber(LPCTSTR TellerName, LPCTSTR TellerNo, LPCTSTR TellerPhoto, LPCTSTR Number)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, TellerName, TellerNo, TellerPhoto, Number);
		return result;
	}
	long GWQ_PaymentInfo(LPCTSTR QR_Code, LPCTSTR Info)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, QR_Code, Info);
		return result;
	}
	long DoGWQ_StartEvaluator(LPCTSTR TellerName, LPCTSTR TellerNo, LPCTSTR TellerPhoto)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, TellerName, TellerNo, TellerPhoto);
		return result;
	}
	long Pleased(short score)
	{
		long result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, score);
		return result;
	}
	long GWQ_StartInfo(LPCTSTR VoiceStr, LPCTSTR Info)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, parms, VoiceStr, Info);
		return result;
	}
	long InfoExchangeResult(short InfoExchange)
	{
		long result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, InfoExchange);
		return result;
	}
	void WebbrowserExit()
	{
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long DoGWQ_StartSign2(LPCTSTR PDFPath, LPCTSTR XmlPath, LPCTSTR Location, LPCTSTR VoiceStr, short ifpreview)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I2 ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, parms, PDFPath, XmlPath, Location, VoiceStr, ifpreview);
		return result;
	}
	CString OnAfterGWQ_StartSign2()
	{
		CString result;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long GWQ_StartInputCode(BOOL showcode)
	{
		long result;
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms, showcode);
		return result;
	}
	long GWQ_StartTakingphoto(LPCTSTR photopath)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, parms, photopath);
		return result;
	}
	long GWQ_StartRecord(LPCTSTR recordpath)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, parms, recordpath);
		return result;
	}
	long GWQ_StartFaceMatch()
	{
		long result;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SignExit()
	{
		long result;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long TouchSign(LPCTSTR PDFPath, short signmode)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I2 ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, parms, PDFPath, signmode);
		return result;
	}
	long GWQ_DeviceOnline()
	{
		long result;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GWQ_SetPenWidth(short penwidth)
	{
		long result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, parms, penwidth);
		return result;
	}
	CString GWQ_GetSeriesNum()
	{
		CString result;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long GWQ_SetPicHeight(long picheight)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, parms, picheight);
		return result;
	}

// Properties
//



};
