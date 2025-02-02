#ifndef _SIGNPAD_H_
#define _SIGNPAD_H_

#ifdef SIGNPAD_EXPORTS
#define DECLSPEC_IMPORT __declspec(dllexport) 
#else
#define DECLSPEC_IMPORT 
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define SIGNPAD_OK 0 
#define SIGNPAD_FAILED 1 
#define SIGNPAD_NO_DEVICE 2 

#pragma pack(push) 
#pragma pack(1)	
// 设备信息结构
typedef struct tagDEVICE_INFO {
	char VenderName[56];//厂家名称
	char ProductName[32];
	char DllVersion[12];
	RECT MonitorBounds;//笔迹坐标范围
	int PressureLevel;//压感级别（1、512、1024、2048）
	int DeviceType;//屏幕类型，自行定义
	unsigned short vendorID;
	unsigned short productID;
	char serial[20];
} DEVICE_INFO;

// 手写笔信息结构
typedef struct tagTOUCH_INFO {
	int x; // X坐标
	int y; // Y坐标
	int pressure; // 压感值
	int buttonDown; // 是否按下手写笔按钮（0：未按下；1：按下）
} TOUCH_INFO;

/*/ 手写笔信息结构
typedef struct tagTOUCH_INFO {
	int x; // X坐标
	int y; // Y坐标
	int pressure; // 压感值
	int timestamp;
	int pressstate;
} TOUCH_INFO;*/

#pragma pack(pop)

// 设备状态侦听器回调函数
typedef void	(CALLBACK *DEVICE_STATUS_FUNC)(int status);//设备当前状态：0，可用；其他值，不可用

// 手写笔信息回调函数
typedef int (CALLBACK *TOUCH_INFO_FUNC)(TOUCH_INFO info);

/**
 * 获取设备的状态。
 *
 * 参数：无
 * 返回值：0:设备可用；其他值:设备不可用，可以通过GetErrorMessage得到描述
 */
DECLSPEC_IMPORT 
int WINAPI GetDeviceStatus();

/**
 * 获取设备的信息。
 *
 * 参数 info: 设备信息结构体，内存由调用方分配
 * 返回值：0:成功；其他值:失败，可以通过GetErrorMessage得到描述
 */
DECLSPEC_IMPORT 
int WINAPI GetDeviceInfo(DEVICE_INFO* info);

/**
*	描述：注册设备状态更改的回调函数。
*	返回值：0：成功；其他值：失败。可以通过GetErrorMessage得到描述。
*	输入1：回调函数指针
*/
DECLSPEC_IMPORT int WINAPI RegisterDeviceStatusCallBack(DEVICE_STATUS_FUNC func);

/**
*	描述：注销设备状态更改的回调函数，与RegisterDeviceStatusCallBack配对使用。
*	返回值：0：成功；其他值：失败。可以通过GetErrorMessage得到描述。
*	输入1：回调函数指针。
*/
DECLSPEC_IMPORT int WINAPI UnregisterDeviceStatusCallBack(DEVICE_STATUS_FUNC func);

/**
 * 注册手写笔信息回调函数。
 *
 * 参数 func：回调函数指针
 * 返回值：0:成功；其他值:失败，可以通过GetErrorMessage得到描述
 */
DECLSPEC_IMPORT 
int WINAPI RegisterTouchInfoCallBack(TOUCH_INFO_FUNC func);

/**
 * 注销手写笔信息回调函数。，与RegisterTouchInfoCallBack配对使用
 *
 * 参数 func：回调函数指针
 * 返回值：0:成功；其他值:失败，可以通过GetErrorMessage得到描述
 */
DECLSPEC_IMPORT 
int WINAPI UnregisterTouchInfoCallBack(TOUCH_INFO_FUNC func);

/**
 * 取错误信息, 可显示给用户。
 *
 * 参数 errorCode: 错误号
 * 参数 errorMsg: 错误信息
 * 返回值：无
 */
DECLSPEC_IMPORT 
void WINAPI GetErrorMessage(int errorCode, char* errorMsg);

#ifdef __cplusplus
}
#endif

#endif // _SIGNPAD_H_