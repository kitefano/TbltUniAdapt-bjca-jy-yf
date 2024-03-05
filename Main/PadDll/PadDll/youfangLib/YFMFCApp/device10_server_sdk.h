#ifndef DEVICE10_SDK_H
#define DEVICE10_SDK_H

#ifdef _WIN32
      #define DLL_API_EXPORT __declspec(dllexport)
    /* Define calling convention in one place, for convenience. */
      //#define DLL_API_CALL __cdecl  //vc c++ call  // __stdcall //vb call
	#define DLL_API_CALL /**< API call macro */

#else
      #define DLL_API_EXPORT /**< API export macro */
      #define DLL_API_CALL /**< API call macro */
#endif


#ifdef __cplusplus
extern "C" {
#endif


/*********************************
 * 功能:
 *      设置回调函数
 * 参数:
 *      tmp_send_cb     -       发送结果回调
 *      tmp_receive_cb  -       接收回调
 * 返回值:
 *      成功 0
 **********************************/
typedef void (callback_str_send)(int ret);

typedef void (callback_str_receive)(int cmd, const char* msg, const char* array[], int len);

DLL_API_EXPORT int DLL_API_CALL set_callback(callback_str_send* tmp_send_cb, callback_str_receive* tmp_receive_cb);





/*********************************
 * 功能:
 *      设置USB插拔事件回调
 * 参数:
 *      cb      -       USB插拔事件回调
 * 回调:
 *      type    -       1 插入USB 0 拔出USB
 *      usbInfo -       USB路径信息
 * 返回值:
 *      成功 0
 **********************************/
typedef void (*callback_UsbEventCallback)(int type, const char* usbInfo);
DLL_API_EXPORT int DLL_API_CALL set_UsbEventCallback(callback_UsbEventCallback cb);


/*********************************
 *  功能:
 *      设置hid模式还是tcp模式, 默认 hid模式
 *  参数:
 *      isHid   -   true HID false tcp
 *      ip      -   tcp 时需要设置IP(端口内部固定8888)
 *  返回值：
 *      成功 0
 *  建议:
 *      程序启动时调用一次即可, 模式切换也可使用此接口,
 *      切换后建议重新设置一次回调函数
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_SetHidAndTcp(const bool isHid, const char* ip = nullptr);

/*********************************
 *  功能:
 *      是否打印debug信息(服务启动前设置和启动后设置效果相同)
 *  参数:
 *      非零 打开 0关闭
 *  返回值：
 *      成功 0 服务未启动-1
 **********************************/
//DLL_API_EXPORT int DLL_API_CALL set_printDebug(int flag);

/*********************************
 *  功能:
 *      设置连接的设备ip和端口号(需服务启动后设置)(已弃用, 100%返回0)
 *  参数:
 *      ip      -       设备ip
 *      port    -       设备端口号(设备固定端口号为8888)
 *  返回值：
 *      成功 0 服务未启动-1
 **********************************/
//DLL_API_EXPORT int DLL_API_CALL exec_configNetwork(const char *ip, unsigned short port);

/*********************************
 *  功能:
 *      连接设置的ip和端口号(已弃用, 100%返回0)
 * 返回值：
 *      连接成功 1 失败 0 服务未启动-1
 **********************************/
DLL_API_EXPORT int DLL_API_CALL exec_ConnectingDevice();

/*********************************
 *  功能:
 *      断开与设备的连接 (已弃用, 100%返回0)
 **********************************/
DLL_API_EXPORT int DLL_API_CALL exec_breakConnectingDevice();

/*********************************
 *  功能:
 *      启动服务(已弃用, 100%返回0)
 *  参数:
 *      ip      -       设备ip
 *      port    -       设备端口号(设备固定端口号为8888)
 * 返回值:
 *      1 成功(或已经启动服务) -1失败(创建服务线程超时)
 **********************************/
DLL_API_EXPORT int DLL_API_CALL start_device10_server(const char* ip = nullptr, unsigned short port = 0);

/*********************************
 *  功能:
 *      停止服务(与直接使用exec_cmd(CloseService) 效果相同)(已弃用, 100%返回0)
 * 返回值:
 *      0 成功 -1 没有创建服务
 **********************************/
DLL_API_EXPORT int DLL_API_CALL stop_device10_server();

/************************************************************************
*函数名称：GWQ_DeviceOnline
*功能描述：检查设备是否在线
*输入参数：无
*输出参数：无
*返回值：参见：错误代码
*/
DLL_API_EXPORT int DLL_API_CALL GWQ_DeviceOnline();

/*********************************
 *  功能:
 *      手写名字（采集手写图片和轨迹数据）
 *  参数1:
 *      签字图片保存路径(路径错误为空或错误保存在默认目录下)
 *  参数2:
 *      签字xml数据文件保存路径(路径错误为空或错误保存在默认目录下)
 *  参数3:
 *      签字笔线宽(小于或等于0 默认 6)
 *  参数4:
 *      签字超时时间,单位: 秒(小于或等于0 默认 1000秒)
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_SignNameEx(const char *signPath, const char* xmlPath, const int linewidth, const int timeout);

/*********************************
 *  功能:
 *      多字抄录
 *  参数:
 *      Title       -   标题
 *      msg         -   需要抄录的文字
 *      linewidth   -   签字笔线宽(小于或等于0 默认 6)
 *      number      -   多少个文字一行(传入小于或等于0默认3个字一行)
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_SignName2(const char *msg, const int linewidth, const int number);
DLL_API_EXPORT int DLL_API_CALL GWQ_SignName(const char* Title, const char *msg, const int linewidth, const int number);

/****************************************
 *  功能:
 *      拍照
 *  参数1:
 *      文件保存文件夹路径
 *  参数2:
 *      相机指令(0 打开相机,
 *              1 拍照,
 *              2 开始采集视频(第三个参数可传超时时间单位: 分钟),
 *              3 停止采集视频(停止录像, 立即返回录制的视频文件),
 *              4 关闭相机(如果在录像没有调用停止录像返回视频时,自动停止录像返回视频)
 *              5 打开视频传输(通过USBHID_setImageData 回调返回,打开前设置),
 *              6 关闭视频传输,
 *              7 用户手动拍照,
 *              8 手动获取拍照图片,
 *              9 手动获取视频和录音,
 *              10 关闭相机(如果在录像没有调用停止录像返回视频时,自动停止录像不返回视频)
 *              11 拍照自动裁边(2022年11月22日以后的设备软件支持)
 *              12 打开相机并裁边画框
 *              13 暂停录制
 *              14 恢复录制)
 *  参数3:
 *      相机参数(默认打开相机传 {"GWQ_GetFrame":"0","order":3843,"stringarray":["640","480","0"],"type":"1"}, 不是打开相机传空)
 *  参数4:
 *      相机参数长度
 *  设备返回结果:
 *      通过设置 set_callback 回调接收
 *  返回值:
 *      参见: 错误代码
*************************************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_GetFrame(const char* path, const char *msg, const char *str[] = nullptr, const int len_2 = -1);//普通拍照

//设置的文件夹不覆盖保存
DLL_API_EXPORT int DLL_API_CALL GWQ_GetFrame2(const char* path, const char *msg, const char *str[] = nullptr, const int len_2 = -1);//普通拍照


/****************************************
 *  功能: 
 *      打开读取二代证读取界面
 *  参数:
 *      msg     -       设置超时时间格式: {"timeout":"1800"}
 *  设备返回结果:
 *      通过设置 set_callback 回调接收
 *  返回值:
 *      参见: 错误代码
 * lxknote: 不好使？
 *************************************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_ReadID(const char *msg);                              //二代证信息读取


/*********************************
 *  功能:
 *      指纹采集，设置指纹最大采集次数
 *  参数:
 *      timeout     -       超时时间
 *      count       -       指纹采集上限
 *      isFeatures    -     是否要特征 0 不要 1 要
 *      dir         -       文件保存目录(可选)
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 *  返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_ReadFingerprint(const int timeout, const int count, const char* dir = nullptr);  //指纹采集，设置指纹最大采集次数
DLL_API_EXPORT int DLL_API_CALL GWQ_ReadFingerprint2(const int timeout, const int count, const int isFeatures);  //指纹采集，设置指纹最大采集次数



/*********************************
 *  功能:
 *      指纹特征比对(必须是对应指纹采集的特征才可比对)
 *  参数:
 *      pTemplet1     -       指纹特征base64数据1
 *      pTemplet2       -     指纹特征base64数据1
 * 设备返回结果:
 *      通过设置 set_callback 回调接收 (0 不是同一特征  1 是同一特征)
 *  返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_ReadFingerprintFeature(const char* pTemplet1, const char* pTemplet2);

/*********************************
 * 功能:
 *      指纹采集采集不上调用接口,摄像头拍摄指纹
 * 参数:
 *      无
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_SetIsOneByOne();                       //设置数据传输模式（定制接口，为解决指纹采集不上问题，设置采集失败次数，超过次数之后提示可以跳过指纹采集，通过拍照收集证据）


/*********************************
 * 功能:
 *      设置轮播图片或待机界面,并设置切换时间
 * 参数:
 *      time        -       切换时间
 *      array       -       图片路径数组
 *      len         -       图片路径数量
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
typedef void (* GWQ_FileUploadCB)(int ErrorCode);
DLL_API_EXPORT int DLL_API_CALL GWQ_FileUpload(const char *time, const char* array[], const int len, GWQ_FileUploadCB callback);   //广告图片上传
DLL_API_EXPORT int DLL_API_CALL GWQ_FileUpload2(const char *time, const char* array[], const int len);   //广告图片上传
DLL_API_EXPORT int DLL_API_CALL GWQ_SetIMGFileList(int time, const char* path);


/*********************************
 * 功能:
 *      删除单张或多张轮播图片或设置的单张待机图片
 * 参数:
 *      msg         -       要删除的图片名称,如需删除全部设置的图片传入-1即可
 *                          设备中的图片文件名可通过 调用GWQ_FileListTime()接口
 *                          在接受回调中收到当前设备中的图片列表
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/

DLL_API_EXPORT int DLL_API_CALL GWQ_FileDelete(const char *msg);           //广告图片删除

/*********************************
 * 功能:
 *      获取设备中设置的轮播图片和切换时间
 * 参数:
 *      无
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_FileListTime();                        //获取广告图片和切换时间

/*********************************
 * 功能:
 *      获取软件版本号
 * 参数:
 *      ver		-		保存获取到的设备软件版本号
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_GetVer(char ver[512]);                              //获取版本号


/*********************************
 * 功能:
 *      获取设备序列号
 * 参数:
 *      sn		-		保存获取到的设备序列号
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_GetSN(char sn[512]);                               //获取设备序列号

/*********************************
 * 功能:
 *      取消当前设备所有操作,返回轮播界面
 * 参数:
 *      无
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_CancelOperate();                       //取消操作接口


/*********************************
 * 功能:
 *      设备同屏到电脑显示(只支持NET, HID模式不支持)
 * 参数:
 *      index       -       1打开 0关闭
 *      ip          -       设备ip
 *      port        -       接收端口号
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
//DLL_API_EXPORT int DLL_API_CALL GWQ_StartPreview(int index, const char *ip, unsigned short port);         //终端屏幕投射到pc 1打开 非1关闭
/*********************************
 * 功能:
 *      发送html页面到设备显示
 * 参数:
 *      msg       -       设置超时时间格式: {"timeout":"1800"}
 *      path      -       html静态文件路径或URL
 *      isImg     -       true 直接发送html文件到设备显示
 *                        false windows上位机html转图片发送设备显示
 *                        Linux true  false 都是直接发送html文件到设备显示
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_OpenURL(const char *msg, const char* path, bool isImg = false);              //打开URL


/*********************************
 * 功能:
 *      文档确认
 * 参数:
 *      type            -       文件类型 0pdf 1html(此接口只能pdf,如需HTML和pdf都能使用
 *                                                请使用 GwQ_PDFConfirmCB 接口)
 *      timeout         -       超时时间
 *      optionInfo      -       未使用参数传 nullptr 即可
 *      path            -       pdf文件路径
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_PDFConfirm(const int type, const int timeout, const char* optionInfo, const char* path);       //文档确认
DLL_API_EXPORT int DLL_API_CALL GWQ_PDFConfirm2(const int type, const int timeout, const char* optionInfo, const char* array[], const int len); //安卓文档确认


/*********************************
 * 功能:
 *      文档批注(点击签字位置弹出签字和指纹采集界面)
 * GWQ_PDFPostil参数1:
 *      msg         -       设置超时时间格式: {"isSaveSign":"0","topText":"文档批注","timeout":"1800"}
 *      path        -       pdf文件路径
 *      dir         -       设备返回后的保存路径(可选)
 * GWQ_PDFPostil3参数2:
 *      isSaveSign  -       是否保存签字指纹到pdf 0 保存 1 不保存
 *      timeout     -       超时时间
 *      topText     -       设备头部显示文本(传空默认为 “文档批注”)
 *      path        -       pdf文件路径
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_PDFPostil(const char *msg, const char* path, const char* dir = nullptr);       //文档批注
DLL_API_EXPORT int DLL_API_CALL GWQ_PDFPostil3(const int isSaveSign, const int timeout, const char* topText, const char* path);

typedef struct STRU_DeviceInfo{
    char szVendorName[128];//商家名称
    char szProductName[128];//产品名称
}STRU_DeviceInfo;


#ifdef _WIN32

/**************************************
 * 描述:
 *      签名回调函数
 * 回调原型: typedef void(QMPDRIVER_SDK_CALL *PictureSignCallBack)(int nCode,char* szEleJson)
 * 参数: void
 *      返回值:  szEleJson   返回 Json
 *              nCode       返回错误信息  0成功 其他失败
 *  说明: 返回Json 格式示例如下
 *      {
 *       "fingerBase64”:[]
 *       "pdfBase64":
 *       "signBase64":[]
 *      }
 **************************************/
typedef void(__stdcall *PictureSignCallBack)(int nCode, char* szEleJson);

/**************************************
 * 描述:
 *      签名屏设备信息回调函数。
 * 原型:
 *      typedef void(QMPDRIVER_SDK_CALL*DeviceOnlineCallBack)(int nCode, STRU_DeviceInfo *pStruDevicelnfo)
 * 参数:
 *      void
 * 返回值:
 *          pStruDeviceInfo -   当设备连接成功，返回设备信息。(成功返回信息, 失败返回空结构体)
 *          nCode           -   当设备连接未成功，返回错误信息。 0成功 其他失败
 * 说明:设备信息结构体如下
 *  typedef struct STRU_DeviceInfo{
 *       char szVendorName[128] = {0};//商家名称
 *       char szProductName[128] = {0};//产品名称
 *   }STRU_DeviceInfo;
 ****************************************/
typedef void(__stdcall *DeviceOnlineCallBack)(int nCode, STRU_DeviceInfo *pStruDeviceInfo);

#else
typedef void(*PictureSignCallBack)(int nCode, char* szEleJson);

typedef void(*DeviceOnlineCallBack)(int nCode, STRU_DeviceInfo *pStruDeviceInfo);

#endif
DLL_API_EXPORT int DLL_API_CALL GWQ_PDFPostil4(const int isSaveSign, const int timeout, const char* topText, const char* path, PictureSignCallBack cb);


/*********************************
 * 功能:
 *      获取设备信息(设备在线返回传入的字符串结构体, 设备不在线返回错误信息)
 * 参数:
 *      path      -       签字固件 .bin 文件路径
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_GetDevInfo(const char szVendorName[128], const char szProductName[128], DeviceOnlineCallBack cb);

/*********************************
 *  功能:
 *      柜员信息展示
 *  参数1:
 *      姓名
 *  参数2:
 *      工号
 *  参数3:
 *      职位
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_TellerInfo(const char *name, const char* number, const char* post, const char* path, const int save);           //柜员信息展示

/*********************************
 *  功能:
 *      评价器(3,5,7阶)
 *  参数1:
 *      姓名
 *  参数2:
 *      部门
 *  参数3:
 *      工号
 *  参数4:
 *      评级分数(0-100)
 *  参数5:
 *      评价器等级(3,5,7)
 *  参数6:
 *      超时时间
 *  参数7:
 *      员工照片
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码 -3(员工信息有误)
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_StartEvaluator(const char *name, const char *department, const char *jobnumber, const int evaluateorder, const int starlevel,const int time, const char *path);       //满意度评价

/*********************************
 * 功能:
 *      设备软件升级接口(软件名称必须是pdfviewer,否则设备不予处理)
 * 参数:
 *      path      -       pdfviewer文件绝对路径
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_UpdateFile(const char* path);           //设备软件升级

/*********************************
 * 功能:
 *      设备中的签字固件升级
 * 参数:
 *      path      -       签字固件 .bin 文件路径
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_SignUpdateFile(const char* path);

/*********************************
 * 功能:
 *      人证比对(需设备带身份证模块和摄像头)
 * 参数:
 *      msg       -       固定传入"0"
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_StartFace(const char *msg);            //身份核验（活体检测，并和二代证中的照片进行比对，返回相关数据）

/*********************************
 * 功能:
 *      活体检测(需设备带摄像头)
 * 参数:
 *      msg       -       固定传入"0"
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_StartLiveDetection(const char *msg); 	//活体检测

/*********************************
 * 功能:
 *      设置支付码
 * 参数:
 *      msg     -       字符串信息json字符串格式 {"msg":"订单号: 0123456789;费 用: 10元","time":"30","isPlay":0} //isPlay
 *                      msg     -       显示信息
 *                      time    -       超时时间
 *                      isPlay  -       是否播放语音(使用微信支付宝完成支付 0 不播放 1或其他 播放)
 *      path    -       支付码图片绝对路径
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_QRCode(const char *json, const char* path);
DLL_API_EXPORT int DLL_API_CALL GWQ_QRCode2(const char *msg, const int time, const int isPlay, const char* path);

/*********************************
 * 功能:
 *      叫号信息牌
 * 参数:
 *      msg     -       字符串信息json字符串格式 {"name":"测试","number":"10001","call":"A10001"}
 *      path    -       操作员人脸图片绝对路径
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_CallNumberInfo(const char *msg, const char* path);  //叫号信息牌
DLL_API_EXPORT int DLL_API_CALL GWQ_CallNumberInfo2(const char *name, const char *number, const char* call, const char* path);  //叫号信息牌

/*********************************
 * 功能:
 *      键盘输入2
 * 参数:
 *      msg     -       字符串信息json字符串格式 {"ret":"0","time":"30"}
 *      ret参数:
 *          0       -       手机号
 *          1       -       金额
 *          2       -       密码
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_Keyboard2(const char *msg);        //键盘输入（手机号，密码，金额）

/*********************************
 * 功能:
 *      键盘输入
 * 参数:
 *      ret参数:
 *          0       -       手机号
 *          1       -       金额
 *          2       -       密码
 *      time        -       超时时间 (小于或等于 0 不超时)
 *      isPassword  -       显示明文还是密文 1 密文  0 明文
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_Keyboard(int ret, int time, int isPassword);        //键盘输入（手机号，密码，金额）

/*********************************
 * 功能:
 *      亮屏息屏
 * 参数:
 *      msg     -       0 息屏    1 亮屏
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_TheScreenSwitch(const char *msg);        //亮屏息屏

/*********************************
 * 功能:
 *      关机重启
 * 参数:
 *      msg     -       0 关机    1 重启
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_ShutdownRestart(const char *msg);      //0关机 1重启


/*********************************
 * 功能:
 *      设备打开读取身份证信息界面
 * 身份证信息接收回调设置参数 (setCallbackReadID):
 *      id      -       身份证信息回调
 * 回调接收参数demo(CallBackGWQ_ReadID):
 *      ErrorCode：程序执行代码 0：执行成功 非0：执行失败
        JsonData：身份证信息，json结构如下：
        {
            "id_num": "身份证号",
            "FrontImgBase64": "身份证照片字节流（BASE64编码）"
        }
 * 返回值:
 *      0 成功 -1(服务未启动) -2(未连接设备)
 **********************************/
//typedef void (*CallBackGWQ_ReadID)(int ErrorCode, const char * JsonData);
typedef void (*CallBackGWQ_ReadID)(int ErrorCode, void * JsonData);

//DLL_API_EXPORT int DLL_API_CALL setCallbackReadID(CallBackGWQ_ReadID id);
DLL_API_EXPORT int DLL_API_CALL DoGWQ_ReadID(CallBackGWQ_ReadID id);      //读取身份证信息

/*********************************
 *  功能:
 *      摄像头扫码类别设置
 *  参数:
 *      codeType    -   codeType：扫码类别0：二维码 1:一维码(暂无)
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_SetQRCodeType(int codeType);

/*********************************
 * 功能:
 *      打开摄像头扫码(必须先设置扫描类别 GWQ_SetQRCodeType)
 * 参数:
 *      无
 * 摄像头二维码接收回调设置参数 (setCallbackGetQRCode):
 *      QRCode      -       摄像头二维码回调
 *      json        -      参数配置({"type":"0","title":"支付码"})
 *                          type    -    0 二维码 1 一维码(暂无)
 *                          title   -    标题
 * 回调接收参数demo(DoGWQ_GetQRCode):
 *      ErrorCode：程序执行代码 0：执行成功 非0：执行失败
        QRCode：二维码信息
 * 返回值:
 *      参见: 错误代码
 **********************************/
typedef void (*DoGWQ_GetQRCode)(int ErrorCode, const char * QRCode);
DLL_API_EXPORT int DLL_API_CALL GWQ_GetQRCode(DoGWQ_GetQRCode cb, const char* jaon = nullptr);      //扫描二维码

//DLL_API_EXPORT int DLL_API_CALL setCallbackGetQRCode(GWQ_GetQRCode QRCode);

DLL_API_EXPORT int DLL_API_CALL Base64ToFile(const char *SignPdfBase64, const char * filePath);      //将BASE64编码格式字节转换为文件，并保存到所连接的PC上
DLL_API_EXPORT const char* DLL_API_CALL GetFileBase64(const char *filePath);        //将所连接的PC上的文件转换为BASE64编码格式字节流

/*********************************
 * 功能:
 *      打开签字界面(带加密)
 * 参数:
 *      SignerName              -   签名人姓名
 *      SignerIDNumType         -   签名认证件号类型(身份证，军官证、护照、户口本、其他)
 *      SIgnerIDNum             -   签名人证件号
 *      PDFPath                 -   PC端PDF文件路径
 *      SignType                -   签字类别 1：电容笔签字
 *      Location                -   签字位置坐标 格式 上,下,左,右 逗号分隔
 *      showSignAndFingerType   -   签字类型：0：表示接口参数控制签字位置，参数参考Location，1：表示自由位置签名，用户点哪里就签哪里
 *      timeout                 -   超时
 *      promptMessage           -   提示信息
 *      PMmode                  -   是否开启声音提示 0关闭, 其他开启
 *      SignDeclaration         -   签字声明
 *      FPWidth                 -   指纹显示区域宽度
 *      SignWidth               -   签字区域宽度
 *      LineWidth               -   签字线条宽度
 * 加密签字返回信息回调设置参数 (GWQ_StartSignEx4):
 *      sign      -       加密签字回调
 * 回调接收参数demo(GWQ_StartSignEx4):
 *      ErrorCode：程序执行代码 0：执行成功 非0：执行失败
        SignPdfBase64       -   加密pdf base64数据 或 nullptr
        SignNameBase64      -   签字图片 base64数据 或 nullptr
        FingerPrintBase64   -   无指纹数据 一直为 nullptr
        XML                 -   签字轨迹数据 base64数据 或 nullptr
 * 返回值:
 *      参见: 错误代码
 **********************************/
typedef void (*GWQ_StartSignEx4)(int ErrorCode,const char* SignPdfBase64, const char* SignNameBase64, const char *FingerPrintBase64, const char* XML);

//DLL_API_EXPORT int DLL_API_CALL setCallbackStartSignEx4(GWQ_StartSignEx4 sign);
DLL_API_EXPORT int DLL_API_CALL DoGWQ_StartSignEx4( const char *SignerName,         //签名人姓名
                                                    const char *SignerIDNumType,    //签名认证件号类型(身份证，军官证、护照、户口本、其他)
                                                    const char *SIgnerIDNum,        //签名人证件号
                                                    const char *PDFPath,            //PC端PDF文件路径
                                                    const int SignType,             //签字类别 1：电容笔签字
                                                    const char* Location,           //签字位置坐标 格式 上,下,左,右 逗号分隔
                                                    const int showSignAndFingerType,//签字类型：0：表示接口参数控制签字位置，参数参考Location，1：表示自由位置签名，用户点哪里就签哪里
                                                    const int timeout,              //超时
                                                    const char* promptMessage,      //提示信息
                                                    const int PMmode,               //是否开启声音提示 0关闭, 其他开启
                                                    const char* SignDeclaration,    //签字声明
                                                    const int FPWidth,              //指纹显示区域宽度
                                                    const int SignWidth,            //签字区域宽度
                                                    const int LineWidth,            //签字线条宽度
                                                    GWQ_StartSignEx4 sign);         //回调


/*********************************
 * 功能:
 *      打开评价器 0
 * 参数:
 *      AfterAppraise      -       评价器结果回调
 *      json               -       自定义评价信息(nullptr或""为默认参数)
 *      样例:{"\"evaluator\":[{\"evaluatorText\":\"非常满意\",\"evaluatorLevel\":\"5\",\"detail\":[
                                            {\"text\":\"一窗受理一次办结\",\"code\":\"510\"},{\"text\":\"可以先受理后补材料\",\"code\":\"511\"},
                                            {\"text\":\"不用提交证明\",\"code\":\"512\"},{\"text\":\"可以全程网上办理\",\"code\":\"513\"},
                                            {\"text\":\"可以使用手机办理\",\"code\":\"514\"},{\"text\":\"可以就近办理\",\"code\":\"515\"},
                                            {\"text\":\"无需材料直接办理\",\"code\":\"516\"},{\"text\":\"服务热情效率高\",\"code\":\"517\"}]},"
                            "{\"evaluatorText\":\"满意\",\"evaluatorLevel\":\"4\",\"detail\":[
                                            {\"text\":\"填写一张表单就可完成申报\",\"code\":\"406\"},{\"text\":\"在线提交材料窗口核验\",\"code\":\"407\"},
                                            {\"text\":\"一张清单告知全部申报材料\",\"code\":\"408\"},{\"text\":\"用告知承诺减免申报材料\",\"code\":\"409\"},
                                            {\"text\":\"可以在线预约办理\",\"code\":\"410\"},{\"text\":\"跑大厅一次办完\",\"code\":\"411\"},
                                            {\"text\":\"可以使用自助机办理\",\"code\":\"412\"},{\"text\":\"服务态度较好\",\"code\":\"413\"}]},"
                            "{\"evaluatorText\":\"一般\",\"evaluatorLevel\":\"3\",\"detail\":[
                                            {\"text\":\"一次性告知需要补正的材料\",\"code\":\"307\"},{\"text\":\"提供申报材料样本\",\"code\":\"308\"},
                                            {\"text\":\"在承诺的时间内办结\",\"code\":\"309\"},{\"text\":\"办事指南指引准确\",\"code\":\"310\"},
                                            {\"text\":\"按办事指南要求的材料即可办理\",\"code\":\"311\"},{\"text\":\"可以快递送达\",\"code\":\"312\"},
                                            {\"text\":\"跑动次数与承诺的一致\",\"code\":\"313\"},{\"text\":\"服务态度一般\",\"code\":\"314\"}]},"
                            "{\"evaluatorText\":\"不满意\",\"evaluatorLevel\":\"2\",\"detail\":[
                                            {\"text\":\"没有提供材料样本\",\"code\":\"207\"},{\"text\":\"没有提供材料清单\",\"code\":\"208\"},
                                            {\"text\":\"未在承诺时间内办结\",\"code\":\"209\"},{\"text\":\"同样内容的证明材料被要求多次提交\",\"code\":\"210\"},
                                            {\"text\":\"承诺网办但无法在线办理\",\"code\":\"211\"},{\"text\":\"在线预约办理后到实体大厅重复取号排队\",\"code\":\"212\"},
                                            {\"text\":\"窗口人员业务不熟练\",\"code\":\"213\"},{\"text\":\"服务态度生硬\",\"code\":\"214\"}]},"
                            "{\"evaluatorText\":\"非常不满意\",\"evaluatorLevel\":\"1\",\"detail\":[
                                            {\"text\":\"在办事指南之外增加新的审批条件\",\"code\":\"108\"},{\"text\":\"需提供办事指南之外的申报材料\",\"code\":\"109\"},
                                            {\"text\":\"无理由超过法定办理时间\",\"code\":\"110\"},{\"text\":\"办事指南提供样本有错\",\"code\":\"111\"},
                                            {\"text\":\"承诺在线收取申报材料实际无法收取\",\"code\":\"112\"},{\"text\":\"多头跑窗口和部门\",\"code\":\"113\"},
                                            {\"text\":\"跑动次数与承诺的不一致\",\"code\":\"114\"},{\"text\":\"服务态度差效率低\",\"code\":\"115\"}]}"
                       "],
            \"title\":\"xx市xx平台好差评\",
            \"supportInputEvaluation\":\"false\"}
 * 回调接收参数demo(OnAfterAppraise):
 *      ErrorCode：程序执行代码 0：执行成功 非0：执行失败
        AppraiseResult：评价结果信息，Json结构，具体如下：
        {
            "appraiseLevel": "", // 评价等级
            "appraiseContent": "", // 评价内容，为评价内容代码串，以“|”分割
            "otherAppraiseContent": "" // 其他评价内容
        }
 * 返回值:
 *      参见: 错误代码
 **********************************/
typedef void (*OnAfterAppraise)(int ErrorCode, const char * AppraiseResult);

//DLL_API_EXPORT int DLL_API_CALL setOnAfterAppraise(OnAfterAppraise AfterAppraise);
DLL_API_EXPORT int DLL_API_CALL GWQ_StartAppraise(OnAfterAppraise AfterAppraise, const char* json);    //打开定制评价器

/*********************************
 * 功能:
 *      打开人脸识别
 * 参数:
 *      无
 * 加密签字返回信息回调设置参数 (setGWQ_StartFaceCB):
 *      Face      -       人脸识别结果回调
 * 回调接收参数demo(GWQ_StartFaceCB):
 *      ErrorCode：程序执行代码 0：执行成功 非0：执行失败
        JsonData    -   人脸识别结果字符串
 * 返回值:
 *      参见: 错误代码
 **********************************/
//typedef void (*GWQ_StartFaceCB)(int ErrorCode, const char * JsonData);
typedef void (*GWQ_StartFaceCB)(int ErrorCode, void* JsonData);

//DLL_API_EXPORT int DLL_API_CALL setGWQ_StartFaceCB();
DLL_API_EXPORT int DLL_API_CALL DoGWQ_StartFace(GWQ_StartFaceCB Face);  //人脸识别

/*********************************
 * 功能:
 *      评价器3
 * 参数:
 *      msg       -       设置超时时间格式: {"timeout":"1800"}
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL openEvaluate(const char *msg);         //打开多页评价页面

/******************************************
* 功能描述:电子签名
* 输入参数:
*       FilePath       --------------  凭证完整路径
*       Timeout        --------------  超时时t间(秒)
*       ButtonStatus   --------------  0,1,显示文字内容I1,1,显示文字内容l2,1,显示文字内容
                                        第一个数字是按钮,第二个数字0位隐藏，1为显示按钮
*       FileType       --------------  0表示pdf 1表示html 2图片
*       callback       --------------  回调函数
* 输出参数:
*       无
* 返回值:
*       参见: 错误代码
*********************************************************/
typedef void(*DoGWQ_PDFConfirmCB)(int ErrorCode, const char* Buttonstatus);
DLL_API_EXPORT int DLL_API_CALL GWQ_PDFConfirmCB(const char* FilePath, int Timeout, const char* ButtonStatus, int FileType, DoGWQ_PDFConfirmCB callback);
DLL_API_EXPORT int DLL_API_CALL GWQ_PDFConfirmCB2(const char* Title, const char* FilePath, int Timeout, const char* ButtonStatus, int FileType, DoGWQ_PDFConfirmCB callback);

/*********************************
 *  功能:
 *      设置设备SN号
 *  参数1:
 *      sn号
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_SetSN(const char* sn);

/*********************************
 * 功能:
 *      婚姻交互界面
 * 参数:
 *      msg         -   {
 *                       "id":"23",     //固定
 *                       "boy":"0,2",   //男方页码
 *                       "girl":"1,3"   //女方页码
 *                      }
 *      callback    -   回调
 * 回调:
 *      ErrorCode   -   0 成功 其他失败
 *      json        -   成功返回json图片数据
 * 返回值:
 *      参见: 错误代码
 *********************************/
typedef void (*CallBack_MarriageInteraction)(int ErrorCode, const char *json);
DLL_API_EXPORT int DLL_API_CALL MarriageInteraction(const char *msg, const char* path, CallBack_MarriageInteraction callback);       //婚姻交互

/*********************************
 * 功能:
 *      评价器
 * 参数:
 *      msg         -   固定"24"
 *      callback    -   回调
 * 回调:
 *      ErrorCode   -   0 成功 其他失败
 *      json         -   成功返回获取的结果否则为nullptr
 * 返回值:
 *      参见: 错误代码
 *********************************/
typedef void (*CallBack_MarriageInteractionSaff)(int ErrorCode, const char *json);
DLL_API_EXPORT int DLL_API_CALL MarriageInteractionSaff(const char *msg, CallBack_MarriageInteractionSaff callback);                     //婚姻交互评价器

/*********************************
 * 功能:
 *      单功能
 * 参数:
 *      msg         -      25 单签字 27 单指纹 28 单抄录文字
 *      callback    -   回调
 * 回调:
 *      ErrorCode   -   0 成功 其他失败
 *      jaon        -   成功返回获取的结果否则为nullptr
 * 返回值:
 *      参见: 错误代码
 *********************************/
typedef void (*CallBack_MarriageInteractionGreffier)(int ErrorCode, const char* json);
DLL_API_EXPORT int DLL_API_CALL MarriageInteractionGreffier(const char *msg, CallBack_MarriageInteractionGreffier callback);                 //婚姻交互登记员签名

/*********************************
 * 功能:
 *      地区代码获取
 * 参数:
 *      msg         -   固定传"26"
 *      callback    -   回调
 * 回调:
 *      ErrorCode   -   0 成功 其他失败
 *      json        -   成功返回获取的结果否则为nullptr
 * 返回值:
 *      参见: 错误代码
 *********************************/
typedef void (*CallBack_MarriageInteractionRegion)(int ErrorCode, const char* json);
DLL_API_EXPORT int DLL_API_CALL MarriageInteractionRegion(const char *msg, CallBack_MarriageInteractionRegion callback);

//人社
//ID编号 姓名 窗口名称 岗位 图片
DLL_API_EXPORT int DLL_API_CALL showEmpolyeePersion(const char *userId, const char* userName, const char* windowName, const char* postName, const char* userPicturePath);       //婚姻交互登记员签名
DLL_API_EXPORT int DLL_API_CALL getstutes();            //获取当前设备状态 0 无操作 1操作pdf 2操作评价器 3工牌展示
DLL_API_EXPORT int DLL_API_CALL GetgetEvaluateValue();  //获取用户点击的评价器结果 1,2,3,4
DLL_API_EXPORT int DLL_API_CALL showEvaluate();         //打开评价页面
DLL_API_EXPORT int DLL_API_CALL NewStarPdf(char* oldpdfpath,char* newpdfpath, char*  signpath);//打开pdf签字
DLL_API_EXPORT int DLL_API_CALL GetGrbmpData(char* savepath);   //获取设备画面，保存到savepath路径下
DLL_API_EXPORT int DLL_API_CALL CancelAll();//取消所有操作
//DLL_API_EXPORT int DLL_API_CALL conmc();//连接设备
//DLL_API_EXPORT int DLL_API_CALL disconmc();//断开连接
//oneClubGetSNAndSetSN_Value
DLL_API_EXPORT int DLL_API_CALL getOneClubSN(); //人社获取sn
DLL_API_EXPORT int DLL_API_CALL setOneClubSN(const char* sn); //设置人社sn

/*********************************
 * 功能:
 *      PDF关键字查找插入签字
 * 参数:
 *      msg         -       插入信息设置{\"height\":\"53\",\"key\":\"办事人（签字）：\",\"timeout\":\"1800\",\"width\":\"96\"}
 *      path        -       pdf绝对路径
 * msg参数说明:
 *      height      -       签字图片插入PDF后最大高度
 *      width       -       签字图片插入PDF后最大大宽度
 *      key         -       PDF中查询的关键字(没有找到默认插入左下角)
 *      timeout     -       超时时间
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL designatedSpotSignPdf(const char *msg, const char* path);       //pdf指定位置插入

/*********************************
 * 功能:
 *      条形码识别(二维码设备采集)
 * 参数:
 *      无
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_GetQRCodeTwo(DoGWQ_GetQRCode cb = nullptr);

/*********************************
 * 功能:
 *      评价器4
 * 参数:
 *      head        -       页面头部文字
 *      department  -       办事部门信息
 *      time        -       办件时间信息
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL StartAppraiseTwo(const char* head, const char* department, const char* time); //第二套评价器

/*********************************
 * 功能:
 *      评价器配置文件更新(只需设置一次, 调用评价器请调用 StartAppraiseTwo 接口)
 * 参数:
 *      path        -       配置文件路径或nullptr(传空路径恢复设备默认选项列表)
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL StartConfigurationInfo(const char* path);   //第二套评价器配置更新 null 恢复默认值

/*********************************
 *  功能:
 *      使用hid方式连接设备(需先调用启动服务 start_device10_server(), hid直接使用, 不用传参)
 * 返回值:
 *      成功 0  失败 -1(服务未启动) -2(连接失败)
 **********************************/
//DLL_API_EXPORT int DLL_API_CALL USBHID_ConnectingDevice();
/*********************************
 *  功能:
 *      断开与设备的连接
 * 返回值:
 *      成功 0  失败 -1(服务未启动)
 **********************************/
//DLL_API_EXPORT int DLL_API_CALL USBHID_breakConnectingDevice();
/*********************************
 * 功能:
 *      设置视频画面回调
 * 参数:
 *      data        -       HID接收的摄像头画面
 * 回调参数:
 *      data        -       图片数据
 *      len         -       图片数据长度
 * 返回值:
 *      成功 0  失败 -1(服务未启动)
 **********************************/
typedef void (*USBHID_IMAGE_DATA)(const char* data, const int len);
DLL_API_EXPORT int DLL_API_CALL USBHID_setImageData(USBHID_IMAGE_DATA data);

/*********************************
 * 功能:
 *      心跳包
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      成功 0 失败 -1(服务未启动)
 **********************************/
DLL_API_EXPORT int DLL_API_CALL USBHID_Heartbeat();

/************************************
* 功能:
*   电子签名(指定位置合成图片到PDF)
* 输入参数: PDFPath---------凭证完整路径
*          XmlPath---------XML文件生成路径
*          Location--------签名或指纹位置 0,1,400,500|1,1,400,500
*          Retain --------预留项
*          Timeout---------超时时间
* 设备返回结果:
*       通过设置 set_callback 回调接收
* 返回值:
*       成功 0  失败 -1(服务未启动) -2(连接失败) -3(pdf文件路径为空)
**************************************/
DLL_API_EXPORT int DLL_API_CALL DoGWQ_StartSign(const char* PDFPath, const char* XmlPath, const char* Location, const char* Retain, int Timeout);

/*************************************
* 功能:
*       人社评价器2
* 输入参数样例:
*       "{\"evaluator\":[{\"evaluatorText\":\"非常满意\",\"evaluatorLevel\":\"0\",\"detail\":[{\"text\":\"态度很好\",\"code\":\"501\"},{\"text\":\"效率很高\",\"code\":\"502\"}]},
*                       {\"evaluatorText\":\"满意\",\"evaluatorLevel\":\"1\",\"detail\":[{\"text\":\"态度好\",\"code\":\"503\"},{\"text\":\"效率高\",\"code\":\"504\"}]},
*                       {\"evaluatorText\":\"一般\",\"evaluatorLevel\":\"2\",\"detail\":[{\"text\":\"态度一般\",\"code\":\"505\"},{\"text\":\"效率一般\",\"code\":\"506\"}]},
*                       {\"evaluatorText\":\"不满意\",\"evaluatorLevel\":\"3\",\"detail\":[{\"text\":\"态度不好\",\"code\":\"507\"},{\"text\":\"效率不高\",\"code\":\"508\"}]},
*                       {\"evaluatorText\":\"非常不满意\",\"evaluatorLevel\":\"4\",\"detail\":[{\"text\":\"态度非常差\",\"code\":\"509\"},{\"text\":\"效率极低\",\"code\":\"510\"}]}]}"
* 设备返回结果:
*       通过设置 set_callback 回调接收
* 返回值:
*       参见: 错误代码
*************************************/
DLL_API_EXPORT int DLL_API_CALL DoGWQ_StartGoodBadEvaluator(const char* UserJson);

/*************************************
* 功能:
*       获取 DoGWQ_StartGoodBadEvaluator 评价器结果,
*       没有调用 DoGWQ_StartGoodBadEvaluator 时,调用返回 nullptr
* 返回值:
*       评价器返回的json字符串
*************************************/
DLL_API_EXPORT const char* DLL_API_CALL OnAfterGWQ_StartGoodBadEvaluator();

/************************************
* 功能:
*       设置发送接收文件进度回调(可选项, 不设置不触发回调)
* 返回值:
*       成功 0  失败 -1(服务未启动)
**************************************/
typedef void (*callback_schedule)(int min, int max);
DLL_API_EXPORT int DLL_API_CALL set_callback_schedule(callback_schedule tmp_send_cb);

/************************************
* 功能:
*       打开pdf并且可悬浮签字界面
* 参数:
*       path        -       pdf文件绝对路径
*       tmp_cb      -       设备返回操作结果后的回调函数
* 回调函数参数:
*       json        -       设备返回的json字符串信息
*       signPath    -       设备返回的签字图片绝对路径
*       xmlPath     -       设备返回的签字轨迹xml文件绝对路径
* 返回值:
*       成功 0  失败 -1(服务未启动) -2(连接失败) -3(pdf文件路径为空)
**************************************/
typedef void (*callback_suspendSign)(const char* json, const char* signPath, const char* xmlPath, const char* pdfPath);
DLL_API_EXPORT int DLL_API_CALL suspendSign(const char* SignPosition, const char *path, callback_suspendSign tmp_cb);

/*************************
* 功能:
*       公积金评价器
* 参数:
*       UserJson        -       评价器参数Json字符串
* json字符串样例(detail 选项最多八项, 必须每条一样多,否则解析失败!):
*       {\"head\":\"公积金业务办理\","
        "\"completedTime\":\"2021/11/26\","
        "\"doNumber\":\"123456\","
        "\"unit\":\"单位住房公积金\","
        "\"evaluator\":[""{\"evaluatorText\":\"非常满意\",\"evaluatorLevel\":\"0\",\"detail\":[{\"text\":\"态度很好\",\"code\":\"501\"},{\"text\":\"效率很高\",\"code\":\"502\"}]},"
                         "{\"evaluatorText\":\"满意\",\"evaluatorLevel\":\"1\",\"detail\":[{\"text\":\"态度好\",\"code\":\"503\"},{\"text\":\"效率高\",\"code\":\"504\"}]},"
                         "{\"evaluatorText\":\"一般\",\"evaluatorLevel\":\"2\",\"detail\":[{\"text\":\"态度一般\",\"code\":\"505\"},{\"text\":\"效率一般\",\"code\":\"506\"}]},"
                         "{\"evaluatorText\":\"不满意\",\"evaluatorLevel\":\"3\",\"detail\":[{\"text\":\"态度不好\",\"code\":\"507\"},{\"text\":\"效率不高\",\"code\":\"508\"}]},"
                         "{\"evaluatorText\":\"非常不满意\",\"evaluatorLevel\":\"4\",\"detail\":[{\"text\":\"态度非常差\",\"code\":\"509\"},{\"text\":\"效率极低\",\"code\":\"510\"}]}"
                       "]}
* 设备返回结果:
*       通过设置 set_callback 回调接收
* 返回值:
*       成功 0  失败 -1(服务未启动) -2(连接失败)
**************************/
DLL_API_EXPORT int DLL_API_CALL DoGWQ_accumulationFundEvaluator(const char *UserJson);

/*************************
* 功能:
*       娄底市公积金评价器
* 参数:
*       UserJson        -       评价器参数Json字符串
* json字符串样例(detail 选项最多八项, 必须每条一样多,否则解析失败!):
*       {"\"evaluator\":[{\"evaluatorText\":\"非常满意\",\"evaluatorLevel\":\"0\",\"detail\":[
                                            {\"text\":\"一窗受理一次办结\",\"code\":\"510\"},{\"text\":\"可以先受理后补材料\",\"code\":\"511\"},
                                            {\"text\":\"不用提交证明\",\"code\":\"512\"},{\"text\":\"可以全程网上办理\",\"code\":\"513\"},
                                            {\"text\":\"可以使用手机办理\",\"code\":\"514\"},{\"text\":\"可以就近办理\",\"code\":\"515\"},
                                            {\"text\":\"无需材料直接办理\",\"code\":\"516\"},{\"text\":\"服务热情效率高\",\"code\":\"517\"}]},"
                            "{\"evaluatorText\":\"满意\",\"evaluatorLevel\":\"1\",\"detail\":[
                                            {\"text\":\"填写一张表单就可完成申报\",\"code\":\"406\"},{\"text\":\"在线提交材料窗口核验\",\"code\":\"407\"},
                                            {\"text\":\"一张清单告知全部申报材料\",\"code\":\"408\"},{\"text\":\"用告知承诺减免申报材料\",\"code\":\"409\"},
                                            {\"text\":\"可以在线预约办理\",\"code\":\"410\"},{\"text\":\"跑大厅一次办完\",\"code\":\"411\"},
                                            {\"text\":\"可以使用自助机办理\",\"code\":\"412\"},{\"text\":\"服务态度较好\",\"code\":\"413\"}]},"
                            "{\"evaluatorText\":\"一般\",\"evaluatorLevel\":\"2\",\"detail\":[
                                            {\"text\":\"一次性告知需要补正的材料\",\"code\":\"307\"},{\"text\":\"提供申报材料样本\",\"code\":\"308\"},
                                            {\"text\":\"在承诺的时间内办结\",\"code\":\"309\"},{\"text\":\"办事指南指引准确\",\"code\":\"310\"},
                                            {\"text\":\"按办事指南要求的材料即可办理\",\"code\":\"311\"},{\"text\":\"可以快递送达\",\"code\":\"312\"},
                                            {\"text\":\"跑动次数与承诺的一致\",\"code\":\"313\"},{\"text\":\"服务态度一般\",\"code\":\"314\"}]},"
                            "{\"evaluatorText\":\"不满意\",\"evaluatorLevel\":\"3\",\"detail\":[
                                            {\"text\":\"没有提供材料样本\",\"code\":\"207\"},{\"text\":\"没有提供材料清单\",\"code\":\"208\"},
                                            {\"text\":\"未在承诺时间内办结\",\"code\":\"209\"},{\"text\":\"同样内容的证明材料被要求多次提交\",\"code\":\"210\"},
                                            {\"text\":\"承诺网办但无法在线办理\",\"code\":\"211\"},{\"text\":\"在线预约办理后到实体大厅重复取号排队\",\"code\":\"212\"},
                                            {\"text\":\"窗口人员业务不熟练\",\"code\":\"213\"},{\"text\":\"服务态度生硬\",\"code\":\"214\"}]},"
                            "{\"evaluatorText\":\"非常不满意\",\"evaluatorLevel\":\"4\",\"detail\":[
                                            {\"text\":\"在办事指南之外增加新的审批条件\",\"code\":\"108\"},{\"text\":\"需提供办事指南之外的申报材料\",\"code\":\"109\"},
                                            {\"text\":\"无理由超过法定办理时间\",\"code\":\"110\"},{\"text\":\"办事指南提供样本有错\",\"code\":\"111\"},
                                            {\"text\":\"承诺在线收取申报材料实际无法收取\",\"code\":\"112\"},{\"text\":\"多头跑窗口和部门\",\"code\":\"113\"},
                                            {\"text\":\"跑动次数与承诺的不一致\",\"code\":\"114\"},{\"text\":\"服务态度差效率低\",\"code\":\"115\"}]}"
                       "]}
* 设备返回结果:
*       通过设置 set_callback 回调接收
* 返回值:
*       成功 0  失败 -1(服务未启动) -2(连接失败)
**************************/
DLL_API_EXPORT int DLL_API_CALL loudiCityEvaluate(const char *UserJson);

/*********************************
 * 功能:
 *      手写名字2（采集手写图片和轨迹数据(轨迹数据x,y,p进行sm4加密)）
 * 参数1:
 *      签字图片保存路径(路径错误为空或错误保存在默认目录下)
 * 参数2:
 *      签字xml数据文件保存路径(路径错误为空或错误保存在默认目录下)
 * 参数3:
 *      签字笔线宽(小于或等于0 默认 6)
 * 参数4:
 *      签字超时时间,单位: 秒(小于或等于0 默认 1000秒)
 * 参数 5:
 *      xml签字轨迹数据x,y,p是否进行sm4加密 1 加密 其他值不进行加密
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_SignNameEx2(const char *signPath, const char* xmlPath, const int linewidth, const int timeout, const int crypto);
DLL_API_EXPORT int DLL_API_CALL GWQ_SignNameEx3(const char *dir, const int linewidth, const int timeout);

/*********************************
 * 功能:
 *      播放视频
 * 参数1:
 *      视频绝对路径
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL Video_play(const char *path);

/*********************************
 * 功能:
 *      设置的播放文件
 * 参数:
 *      array       -       图片路径数组
 *      len         -       图片路径数量
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL add_play_File(const char* array[], const int len);

/*********************************
 * 功能:
 *      播放设置的文件
 * 参数:
 *      index       -       1 播放 其他停止
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL play_File(const char* index);

/*********************************
 * 功能:
 *      播放声音文件
 * 参数:
 *      type       -        0 播放传入文件 大于1播放设备内置语音
 *      path       -       type == 0 时生效, 音频文件绝对路径
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL music_Play_File(const char* type, const char* path = nullptr);

/*********************************
 * 功能:
 *      读取社保卡信息
 * 参数:
 *      timeout       -       超时时间
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_ReadMedicalCard(const int timeout);

/*********************************
 * 功能:
 *      读取银行卡信息
 * 参数:
 *      timeout       -       超时时间
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_ReadBankCard(const int timeout);

/*********************************
 * 功能:
 *      安装人脸识别模型文件
 * 参数:
 *      path       -       模型压缩包mode.zip
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_UPDataFaceFile(const char* path);

/*********************************
 * 功能:
 *      pdf预览确认并签字上传签字图片轨迹
 * 参数:
 *      path       -       pdf路径
 *      timeout    -       超时时间
 *      linewidth  -       线宽
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL loudiCityPDF(const char* path, const int timeout, const int linewidth);

/*********************************
 * 功能:
 *      显示员工信息,可更改背景图片
 * 参数:
 *      type    -       0 显示柜员信息 1 设置背景图片(在下一次打开界面生效) 2 清除设置的背景图片恢复默认值(在下一次打开界面生效)
 *      name    -       员工姓名(type 为 1 时 传 nullptr)
 *      number  -       员工工号(type 为 1 时 传 nullptr)
 *      post    -       岗位职责(type 为 1 时 传 nullptr)
 *      path    -       文件路径(员工照片或设置背景图片的路径)
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL loudiCityTellerInfo(const int type, const char *name, const char* number, const char* post, const char* path);

/*********************************
 * 功能:
 *      PDF预览并签字按指纹(先签字后按指纹,没有指纹模块直接跳过指纹采集)
 * 参数:
 *      path    -       PDF路径
 *      time    -       超时时间(默认不超时 小于或等于0)
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_PDFPostil2(const char* path, const int time = -1);

/*************************************
* 功能:
*       评价器5
* 参数:
*   type        -       评价器操作编号
*   TellerName  -       姓名
*   TellerNo    -       工号
*   TellerPhoto -       员工照片绝对路径
*   UserJson    -       动态评价参数列表
*       输入参数样例:"{\"evaluator\":[{\"evaluatorText\":\"非常满意\",\"evaluatorLevel\":\"0\",\"detail\":[{\"text\":\"态度很好\",\"code\":\"501\"},{\"text\":\"效率很高\",\"code\":\"502\"}]},
*                                   {\"evaluatorText\":\"满意\",\"evaluatorLevel\":\"1\",\"detail\":[{\"text\":\"态度好\",\"code\":\"503\"},{\"text\":\"效率高\",\"code\":\"504\"}]},
*                                   {\"evaluatorText\":\"一般\",\"evaluatorLevel\":\"2\",\"detail\":[{\"text\":\"态度一般\",\"code\":\"505\"},{\"text\":\"效率一般\",\"code\":\"506\"}]},
*                                   {\"evaluatorText\":\"不满意\",\"evaluatorLevel\":\"3\",\"detail\":[{\"text\":\"态度不好\",\"code\":\"507\"},{\"text\":\"效率不高\",\"code\":\"508\"}]},
*                                   {\"evaluatorText\":\"非常不满意\",\"evaluatorLevel\":\"4\",\"detail\":[{\"text\":\"态度非常差\",\"code\":\"509\"},{\"text\":\"效率极低\",\"code\":\"510\"}]}]}"
*   Timeout     -       超时时间
* 设备返回结果:
*       通过设置 callback_StartAppraise5 回调接收
* 返回值:
*       参见: 错误代码
*************************************/
typedef void (*callback_StartAppraise5)(const char* json);
DLL_API_EXPORT int DLL_API_CALL StartAppraise5(const int type, const char* TellerName, const char* TellerNo, const char* TellerPhoto, const char* UserJson,const int Timeout, callback_StartAppraise5 cb);

/*********************************
 * 功能:
 *      让设备进入烧录固件模式
 * 参数:
 *      无
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL YF_UpdateFile_Loader();


/*********************************
 * 功能:
 *      获取设备日志
 * 参数:
 *      无
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_GetLogTxtFile();

/*********************************
 * 功能:
 *      设备保存文件到本地
 * 参数:
 *      type        -        操作类型：1.增改 2.删 3.查
 *      key         -        保存到设备本地的key,通过key重新拿到文件
 *                           type 为2时传入-1清空设备全部保存的文件
 *      path        -        type 为1是传入,其他传入nullptr
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_FileOperation(const int type, const char* key, const char* path = nullptr);

/******************************pdf签字回调******************************************
*函数名称: GWQ_MoralityCB
*功能描述: 回调
*输入参数: 无
*输出参数: ErrorCode----------参见: 错误代码
          json-----------设备返回的json
          pathDir--------文件保存路径
*返回值: 无
*/
typedef void (DLL_API_CALL* GWQ_MoralityCB)(int ErrorCode, const char* json, const char* pathDir);

/*********************************pdf签字展示***********************************
*函数名称: GWQ_Morality
*功能描述: pdf签字展示
*输入参数:
*       batchId------批次ID
*       pattern------当前签字模式 1 固定位置  2 指定位置 3固定加指定位置
*       type---------签字类型 1 常规签名 2 规范签名
*       typeBatch----指定位置是否批量签字：1是批量，2不是批量
*       fileView-----1 开启文件预览 2 关闭文件预览
*       SignPosition----------固定签字位置数组 x,y,w,h
*           {"Page": -1,    //页码  -1 全部签印
*           "x": 0,
*           "y": 0,
*           "Width": 100,
*           "Height": 100}
*       SignPositionLen-----固定签字位置数组长度
*       path---------pdf文件组
*       pathLen------pdf文件组中数据数量
*输出参数: 无
*返回值: 参见: 错误代码
*/
DLL_API_EXPORT int DLL_API_CALL GWQ_Morality(const char* batchId, int pattern, int type, int typeBatch, int fileView, const char *SignPosition[], int SignPositionLen, const char *path[], int pathLen, GWQ_MoralityCB callback);

/******************************信息交互******************************************
*函数名称: GWQ_StartInfoWithRec
*功能描述: 信息交互(阅读指定文字并录像)
*输入参数:
*       FileName    -       视频保存路径
*       Info        -       交互信息
*       Timeout     -       超时时间
*       callback    -       回调函数
*回调输出参数:    ErrorCode----------参见: 错误代码
                endTime-----------录像开始时间与结束时间，用;分割，时间格式： yyyyMMddHHm mss
                                    例: 20200702153000;20200702153559
*返回值: 参见: 错误代码
*/
typedef void (*CallBackGWQ_StartInfoWithRec)(int ErrorCode, void* endTime);
DLL_API_EXPORT int DLL_API_CALL GWQ_StartInfoWithRec(const char* FileName, const char* Info, int Timeout, CallBackGWQ_StartInfoWithRec callback);

/******************************电子签名******************************************
*函数名称: GWQ_StartSignWithRec
*功能描述: 电子签名
*输入参数:
*       PDFPath     - 凭证路径
*       SignType    - 签名类型，固定 1
*       Location    - SignType 为 1 时不起作用，传任意值即可
*       VideoPath   - 录像文件存放路径
*       Timeout     - 超时时间
*       FPWidth     - 指纹宽度
*       SignWidth   - 签名宽度
*       callback    - 回调函数
*回调输出参数:
*       ErrorCode----------参见: 错误代码
*       SignPdfBase64------成功后返回pdf的base64数据
*       SignNameBase64-----签名图片数据，返回是json形式签名集合。
*       FingerPrintBase64--指纹图片数据，返回是json形式指纹集合。
*       XML----------------签名轨迹数据，返回json集合。
*       endTime------------录像开始时间与结束时间，用;分割，时间格式： yyyyMMddHHm mss
*                         例: 20200702153000;20200702153559
*返回值: 参见: 错误代码
*
* a) SignNameBase64 参数的 json 说明：SignNameCount------签名个数 SignName+序号 ---签名 base64 数据。
例：{
    "SignNameCount": 2,
    "SignName0": "图片 base64 数据",
    "SignName1": "图片 base64 数据", (以此类推)
}
b) FingerPrintBase64 参数的 json 说明：FingerCount-----指纹个数，FingerPrint+序号--- 指纹 base64 数据。
例：{
    "FingerCount": 3,
    "FingerPrint0":
    "图片 base64 数据",
    "FingerPrint1":
    "图片 base64 数据",
    "FingerPrint2":
    "图片 base64 数据", (以此类推)
}
c) XML 参数的 json 说明：XMLCount---xml 个数，XML+序号-----xml 的数据。
例：{
    "XMLCount": 2,
    "XML0": "xml 数据",
    "XML1": "xml 数据". (以此类推，xml 数据中如有英文引号需进行转义，否则会解析失败)
}
d)endTime 参数示例：20200702153000;20200702153559
*/
typedef void (*CallBackGWQ_StartSignWithRec)(int ErrorCode, void* SignPdfBase64, void *SignNameBase64, void* FingerPrintBase64, void* XML, void* endTime);
DLL_API_EXPORT int DLL_API_CALL GWQ_StartSignWithRec(const char* PDFPath, int SignType, const char* Location, const char* VideoPath, int Timeout, int FPWidth, int SignWidth, CallBackGWQ_StartSignWithRec callback);

/*********************************
 * 功能:
 *      设备软件升级接口2(软件名称必须是pdfviewer,否则设备不予处理)
 * 参数:
 *      FileName      -       pdfviewer文件绝对路径
 * 回调输出参数:
 *       ErrorCode----------参见: 错误代码
 *       Value--------------更新进度值0-100之间
 * 返回值:
 *      参见: 错误代码
 **********************************/
typedef void (*CallBack_GWQ_UpdateEx)(int ErrorCode, float Value);
DLL_API_EXPORT int DLL_API_CALL GWQ_UpdateEx(const char* FileName, CallBack_GWQ_UpdateEx callback);

/*********************************
 * 功能:
 *      获取设备信息
 * 参数:
 *      JsonData      -       设备信息jaon字符串
 * 返回值:
 *      参见: 错误代码
 * 备注：输出参数 JsonData 数据为 Json 格式，字段说明如下：
 *      DeviceSN---------设备序列号
 *      DeviceModel---------设备型号
 *      Manufacturer---------厂商
 *      FactoryTime---------出厂时间
 * 例 ：{
 *      "DeviceSN":"XXXXXXXXX",
 *      "DeviceModel":"XXX",
 *      "Manufacturer":"XXXXX",
 *      "FactoryTime":"yyyy-MM-dd HH:mm:ss"
 * }
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_GetDeviceInfo(char* JsonData);

/*********************************
 * 功能:
 *      获取授权码
 * 参数:
 *      OperateType----------操作类型：固定为 1 (0 设置授权码, 出厂设置完成)
 *      CodeBuf--------------授权码内存指针
 * 输出参数:
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_OperateAuthorizationCode(int OperateType, char* CodeBuf);

/*********************************
 * 功能:
 *      电脑画面发送到设备显示
 * 参数:
 *      hWnd     -       窗口句柄(为空时，桌面截取)
 *      x        -       截取x起点
 *      y        -       截取y起点
 *      width    -       截取width终点
 *      height   -       截取height起点
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_StartScreenCapture(void* hWnd, const int x, const int y, const int width, const int height);
DLL_API_EXPORT int DLL_API_CALL GWQ_stopScreenCapture();

/*********************************
 * 功能:
 *      设备画面发送到电脑显示
 * 参数:
 *      hWnd     -       窗口句柄(为空时，桌面截取)
 * 设备返回结果:
 *      通过设置 set_callback 回调接收
 * 返回值:
 *      参见: 错误代码
 **********************************/
typedef void(*GWQ_StartPreviewCB)(const char* data, const int size);
#if defined(_WIN32)
DLL_API_EXPORT int DLL_API_CALL GWQ_StartPreview(void* hWnd);
#endif
DLL_API_EXPORT int DLL_API_CALL GWQ_StartPreview2(GWQ_StartPreviewCB callback); //同屏2
DLL_API_EXPORT int DLL_API_CALL GWQ_stopPreview();

/************************
 * jx人社
 * 功能：推送html
 *
 * 输入参数：
 *  html_name     html页面名字    "index.html"
 *   html_path               html路径           "c:\\index.html","*.zip","www.baidu.com"
 *
 * 返回值：
 *       0                   推送成功
 *      -1                   空路径
 *      -2                   打开失败
 *  -3                   json字符串为空
 *  -6                   html文件名字有空格
 *
 *
 *
*/
DLL_API_EXPORT int DLL_API_CALL GWQ_HTMLSN(const char *html_name, const char *html_path);

/*********************************
 * 功能:
 *      支付信息json字符串显示
 * 参数:
 *      json     -       json字符串
 * 设备返回结果:
 *      通过设置 CallBack_GWQ_InfoPreviewSignature 回调接收
 *      ErrorCode       -   0 成功 其他失败
 *      signBase64      -   签字base64数据(png) 失败为 nullptr
 *      signXmlBase64   -   签字轨迹base64数据 失败为 nullptr
 * 返回值:
 *      参见: 错误代码
 **********************************/
typedef void (*CallBack_GWQ_InfoPreviewSignature)(int ErrorCode, const char* signBase64, const char* signXmlBase64);
DLL_API_EXPORT int DLL_API_CALL GWQ_InfoPreviewSignature(const char* json, CallBack_GWQ_InfoPreviewSignature callback);

/*********************************
 * 功能:
 *      显示登记表,完成后返回登记表图标
 * 参数:
 *      Timeout     -       超时时间
 *      Title       -       头部显示文字(可为空,设备显示默认文字)
 *      number      -       操作流水号, 发送什么回什么
 *      index       -       签名人数量 1 - 10 默认 1
 *      type        -       操作类型(1,2,3 设备默认模板 4上位机传值, 其他报错)
 *      dataJson    -       type == 4时生效 内部存储json 例子 {"data":["登记表名称","1.xxxx","回答:|是|否","2.xxxx","回答:|清楚|不清楚清楚,"经被询问人确认，以上询问事项均回答真实、无误。"]}
 * 设备返回结果:
 *      通过设置 CallBack_GWQ_RegistrationRecord_Value 回调接收
 *      ErrorCode   -   0 成功 其他失败
 *      json        -   json数据 失败为 nullptr {"number":流水号,"img":Base64图片数据}
 * 返回值:
 *      参见: 错误代码
 **********************************/
typedef void (*CallBack_GWQ_RegistrationRecord)(int ErrorCode, const char* json);
DLL_API_EXPORT int DLL_API_CALL GWQ_RegistrationRecord(const char* Title, const char* number, const int index, const int type, const int Timeout, const char* dataJson, CallBack_GWQ_RegistrationRecord callback);

/*********************************
 * 功能:
 *      签字指纹二合一功能,返回合成好的图片
 * 参数:
 *      Timeout         -       超时时间
 *      Title           -       头部显示文字(可为空,设备显示默认文字)
 *      linewidth       -       线宽,默认6
 *      IsUpDoen        -       1 指纹在上 0或其他 指纹在下
 *      IsCompoundImg   -       是否返回为合成的签字图片与指纹 1 返回 其他不返回
 * 设备返回结果:
 *      通过设置 CallBack_GWQ_fingerOrSign 回调接收
 *      ErrorCode       -   0 成功 其他失败
 *      imgBase64       -   登记图片base64数据(jpg) 失败为 nullptr
 *      (不合成为json字符串: {"signImg":Base64,"finger":Base64, "compoundImg":Base64})
 *      path            -   登记图片base64数据(jpg)时有效, 其他为nullptr
 * 返回值:
 *      参见: 错误代码
 **********************************/
typedef void (*CallBack_GWQ_fingerOrSign)(int ErrorCode, const char* imgBase64, const char* path);
DLL_API_EXPORT int DLL_API_CALL GWQ_fingerOrSign(const char* Title, const int linewidth, const int Timeout, const int IsUpDoen, CallBack_GWQ_fingerOrSign callback);
DLL_API_EXPORT int DLL_API_CALL GWQ_fingerOrSign2(const char* Title, const int linewidth, const int Timeout, const int IsUpDoen, const int IsCompoundImg, CallBack_GWQ_fingerOrSign callback);

/*********************************
 * 功能:
 *      指纹2固件升级
 * 参数:
 *      type            -       1 安装升级工具 2 升级固件
 *      password        -       密码
 *      path            -       升级文件或工具路径
 * 设备返回结果:
 *      0   -   成功
 *      -1  -   升级文件不存在
 *      -2  -   密码错误
 *      -3  -   文件打开失败
 *      -4  -   升级失败
 *      -5  -   当前指纹不支持升级
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_FingerUpData(const int type, const char* password, const char* path);

/*********************************
 * 功能:
 *      评价器
 * 参数:
 *      json            -       评价器json字符串
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_Evaluator(const char* json);

/*********************************
 * 功能:
 *      1016S数字证书安装
 * 参数:
 *      file_path		-       证书绝对路径字符串
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_FileSend(const char *file_path);

//社保卡加密机操作
//读基本信息
DLL_API_EXPORT int DLL_API_CALL iReadCardBas(int iType, char* pOutInfo);

//通用读卡
DLL_API_EXPORT int DLL_API_CALL iReadCard(int iType, int iAuthType, char* pCardInfo, char* pFileAddr, char* pOutInfo);

//PIN 校验
DLL_API_EXPORT int DLL_API_CALL iVerifyPIN(int iType, char* pOutInfo);

//PIN 修改
DLL_API_EXPORT int DLL_API_CALL iChangePIN(int iType, char* pOutInfo);

//PIN 重置
DLL_API_EXPORT int DLL_API_CALL iReloadPIN(int iType, char* pCardInfo, char* pOutInfo);

//PIN 解锁
DLL_API_EXPORT int DLL_API_CALL iUnblockPIN(int iType, char* pCardInfo, char* pOutInfo);

//基于加密机认证
//基于加密机的读基本信息（步骤一）
DLL_API_EXPORT int DLL_API_CALL iReadCardBas_HSM_Step1(int iType, char* pOutInfo);

//基于加密机的读基本信息（步骤二）
DLL_API_EXPORT int DLL_API_CALL iReadCardBas_HSM_Step2(char* pKey, char* pOutInfo);
//基于加密机的通用读卡（步骤一）
DLL_API_EXPORT int DLL_API_CALL iReadCard_HSM_Step1(int iType, char* pCardInfo, char* pFileAddr, char* pOutInfo);

//基于加密机的通用读卡（步骤二）
DLL_API_EXPORT int DLL_API_CALL iReadCard_HSM_Step2(char* pKey, char* pOutInfo);

//基于加密机的 PIN 重置（步骤一）
DLL_API_EXPORT int DLL_API_CALL iReloadPIN_HSM_Step1(int iType, char* pCardInfo, char* pOutInfo);

//基于加密机的 PIN 重置（步骤二）
DLL_API_EXPORT int DLL_API_CALL iReloadPIN_HSM_Step2(char* pKey, char* pOutInfo);

//基于加密机的 PIN 重置（步骤三）
DLL_API_EXPORT int DLL_API_CALL iReloadPIN_HSM_Step3(char* pKey, char* pOutInfo);

//基于加密机的 PIN 解锁（步骤一）
DLL_API_EXPORT int DLL_API_CALL iUnblockPIN_HSM_Step1(int iType, char* pCardInfo, char* pOutInfo);

//基于加密机的 PIN 解锁（步骤二）
DLL_API_EXPORT int DLL_API_CALL iUnblockPIN_HSM_Step2(char* pKey, char* pOutInfo);

//基于加密机的 PIN 解锁（步骤三）
DLL_API_EXPORT int DLL_API_CALL iUnblockPIN_HSM_Step3(char* pKey, char* pOutInfo);


//公共接口
//读取银行卡号
DLL_API_EXPORT int DLL_API_CALL iReadICCardNum(char* pCardNum, char *pErrMsg);

//读取身份证号码
DLL_API_EXPORT int DLL_API_CALL iReadIdentityCard(char *pOutInfo, char *pErrMsg);

//openssl
/*********************************
 * 功能:
 *      文件转Sha256
 * 参数:
 *      path  - 文件绝对路径
 * 返回值:
 *      成功返回 Sha256 16进制值, 否则为空 nullptr
 **********************************/
DLL_API_EXPORT const char* DLL_API_CALL GWQ_FileToSha256(const char* path);

#if defined(_WIN32)
/*********************************
 * 功能:
 *      私钥解密
 * 参数:
 *      pemPath  - 需要解密的文件绝对路径
 *      keyPath  - 私钥文件绝对路径
 * 返回值:
 *      成功返回 解密内容, 否则为空 nullptr
 **********************************/
DLL_API_EXPORT const char* DLL_API_CALL GWQ_OpenSslDecode(const char* pemPath, const char* keyPath);

#endif

/*********************************
 * 功能:
 *      多人签字(安卓功能, linux暂无)
 * 参数:
 *      NameList    -   签名人数组
 *      len         -   签名人数组长度
 * 返回值:
 *      成功返回 解密内容, 否则为空 nullptr
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_MultipleSign(const char *NameList[128], const int len);

/*********************************
 * 功能:
 *      评价器6
 * 参数:
 *      url             -   网络评价器地址
 *      pageTimeOut     -   超时时间(默认300);
 *      cb              -   结果回调 0 成功 其他失败
 * 返回值:
 *      参见: 错误代码
 **********************************/
typedef void (*DoGWQ_OpenEvaluate)(int ErrorCode);
DLL_API_EXPORT int DLL_API_CALL GWQ_OpenEvaluate(const char *url, const int pageTimeOut, DoGWQ_OpenEvaluate cb);


/*********************************
 * 功能:
 *      评价器6
 * 参数:
 *      url             -   网络评价器地址
 *      pageTimeOut     -   超时时间(默认300);
 *      cb              -   结果回调 0 成功 其他失败
 * 返回值:
 *      参见: 错误代码
 **********************************/
typedef void (*DoGWQ_GetFevInfo)(int ErrorCode, const char* json);
DLL_API_EXPORT int DLL_API_CALL GWQ_GetFevInfo(DoGWQ_GetFevInfo cb);

/*********************************
 * 功能:
 *      pdf待添加功能
 * 参数:
 * 返回值:
 *      参见: 错误代码
 **********************************/
//DLL_API_EXPORT int DLL_API_CALL  GWQ_PDFPostil3();
/*********************************
 * 功能:
 *      设置系统时间
 * 参数:
 *      date    -   时间,格式: yyyy-MM-dd hh:mm:ss(传空自动获取系统时间)
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_UPDate(const char* date = nullptr);

/************************************
* 功能:
*   人脸注册功能
*   输入参数：
*       userId--------------员工工号 1
*       userName------------员工姓名 张三
*       userSex-------------员工性别 男|女
*       userDepath----------员工部门 工程部
*       userPicturePath --- 图片路径 c:\a.jpg
*   返回值：
*       参见: 错误代码
* 备注:
*       GWQ_UserRegister 是 Face_register 兼容版本, 功能相同
**************************************/
DLL_API_EXPORT int DLL_API_CALL Face_register(const char *id, const char *name, const char *sex, const char *userDepath, const char *userPicturePath = nullptr);
DLL_API_EXPORT int DLL_API_CALL GWQ_UserRegister(const char *id, const char *name, const char *sex, const char *userDepath, const char *userPicturePath = nullptr);

/************************************
* 功能:
*   人脸识别功能
* 返回值：
*   参见: 错误代码
**************************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_FaceCompare();

/************************************
* 功能:
*   指纹注册功能
*   输入参数：
*       userId--------------员工工号 1
*       userName------------员工姓名 张三
*       userSex-------------员工性别 男|女
*       userDepath----------员工部门 工程部
*   返回值：
*       参见: 错误代码
* 备注:
*       GWQ_UserRegister 是 Face_register 兼容版本, 功能相同
**************************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_FingerUserRegister(const char *id, const char *name, const char *sex, const char *userDepath);

/************************************
* 功能:
*   指纹识别功能(匹配指纹注册数据库中的指纹)
* 返回值：
*   参见: 错误代码
**************************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_FingerFaceCompare();


/************************************
* 功能:
*   删除单个用户信息功能
* 输入参数：
*   userId--------------员工工号 001
*
*   返回值：
*       参见: 错误代码
* 备注:
*       GWQ_Deletexml 是 Face_Delete 兼容版本, 功能相同
**************************************/
DLL_API_EXPORT int DLL_API_CALL Face_Delete(const char *userId);
DLL_API_EXPORT int DLL_API_CALL GWQ_Deletexml(const char *userId);

/************************************
* 功能:
*   删除所有用户信息功能
* 输入参数：
*   无
*
*   返回值：
*       参见: 错误代码
**************************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_DeleteXMLData();

/************************************
* 功能:
*   PDF预览签字按指纹, 不合成, 只返回签字图片,指纹图片
* 输入参数：
*   path        -       pdf绝对路径
*   text        -       需要抄录的文字
*   linewidth   -       签字线宽(可选,默认 "6")
*   title       -       标题文字(可选, 默认 "文档批注")
*   timeout     -       超时时间(默认没有超时)
* 返回值：
*       参见: 错误代码
* 设备返回json说明:
*   SignType    -   0 本人签 1 代签署
*   TextType    -   0 没有文本 1 有文本
**************************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_PreviewSignFinger(const char* path, const char* text, const int linewidth = 6, const char* title = nullptr, const int timeout = -1);

/************************************
* 功能:
*   PDF预览确认
* 输入参数：
*   path        -       pdf绝对路径
*   title       -       标题文字(可选, 默认 "文档确认")
* 返回值：
*       参见: 错误代码
* 设备返回json说明:
*   0 确认 -1 取消
**************************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_PreviewSignFingerAffirm(const char* path, const char *title, const int timeout);

/************************************
* 功能:
*   PDF预览 或 签字按指纹
* 输入参数：
*   json        -       json配置信息
*   path        -       pdf绝对路径
* json配置信息列表(可选):
*   type        -       1 签字模式 2 预览模式(必须的)
*   SignWidth   -       签字图片缩放后宽度(必须的)
*   FPWidth     -       指纹图片缩放后宽度(必须的)
*   isVideo     -       是否自动录像(可选, 默认不录像, 需要自动录像传 "1")
*   linewidth   -       签字线宽(可选, 默认 "6")
*   title       -       标题文字(可选, 默认 "文档批注")
*   timeout     -       超时时间(可选, 默认没有超时)
*   signtimeout -       签字框打开超时时间(可选, 默认没有超时)
*   signtext    -       签字框底部显示文本(默认显示 以上笔录已看过，和我说的一致。)
*   moveX       -       用户点击位置向左移动多少百分百(小于 0 默认 10%)
*   moveY       -       用户点击位置向上移动多少百分百(小于 0 默认 10%)
*   样例: {"data":{"type":"1","SignWidth":200,"FPWidth":100,"linewidth":6,"title":"文档批注","timeout":-1,"signtimeout",-1,"signtext":"以上笔录已看过，和我说的一致。\n姓名:XX  XXXX年XX月XX日","moveX":10,"moveY":20}}
* 设备返回值说明:
*   json GWQ_PDFAnnotationPreview 值说明:
*               0       -       设备确认签字并返回签字文件
*               1       -       设备点击签字按钮
*               2       -       设备关闭签字框
* 回调参数说明:
*       ErrorCode       -       0 确认签字预览 1 打开签字框 2 关闭签字框 其他失败
*       json            -       ErrorCode == 0 时返回文件路径json 其他时为 nullptr
*                               样例: {"paths":["文件1","文件2"...]}
* 返回值：
*       参见: 错误代码
**************************************/
typedef void (*DoGWQ_PDFAnnotationPreview)(int ErrorCode, const char * json);
DLL_API_EXPORT int DLL_API_CALL GWQ_PDFAnnotationPreview(const char* json, const char* path, DoGWQ_PDFAnnotationPreview cb);

/************************************
* 功能:
*       录屏录像
* 输入参数：
*       type        -       1 开始录屏录像 0 停止录屏录像
*       isTimestamp -       是否添加水印 1 添加 0 不添加
* 返回值：
*       参见: 错误代码
**************************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_ScreeRecorder(const int type, const int m_isTimestamp = 1);

/*********************************
 * 功能:
 *      xml轨迹还原(笔记还原, 调用后阻塞, 直到窗口关闭)
 * 参数:
 *      XmlPath----------xml绝对路径
 * 输出参数:
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_XMLRestore(const char * XmlPath);

/*********************************播放音频设置***********************************
*函数名称：GWQ_InputMP3File
*功能描述：播放音频设置
*输入参数：
            path---------mp3文件路径(文件格式: mp3, 采样率 16000, 其他格式不能正常播放)
            order--------设置的编号 0 恢复默认 状态
*输出参数：无
*返回值：参见：错误代码
*/
DLL_API_EXPORT int DLL_API_CALL GWQ_InputMP3File(const char *path, const char *order);

/************************************
* 功能:
*   PDF预览并签字, 返回合成好后的图片
* 输入参数：
*   json        -       json配置信息
*   path        -       pdf绝对路径
* json配置信息列表(可选):
*   type        -       1 签字模式 2 预览模式(必须的)
*   signRects   -       签字矩形坐标(百分比), 如(页码, x, y, w(x + w), h(y + h))[{0,10,10,20,20},...](目前只支持单次签字)
*   linewidth   -       签字线宽(可选, 默认 "6")
*   title       -       标题文字(可选, 默认 "文档批注")
*   timeout     -       超时时间(可选, 默认没有超时)
*   format      -       返回文件格式(0=jpg(默认) 1=pdf)
*   样例: {"data":{"SignRects":[[0,10,10,20,20]],"linewidth":6,"title":"文档批注","timeout":-1,"format":0}}
* 回调参数说明:
*       ErrorCode       -       0 确认签字 其他失败
*       json            -       ErrorCode == 0 时返回图片文件base64 json 其他时为 nullptr
*                               样例: {"base64":["图片base64数据1", "图片base64数据2", ...]}
* 返回值：
*       参见: 错误代码
**************************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_PdfSignToImage(const char* json, const char* path, DoGWQ_PDFAnnotationPreview cb);     //pdf预览签字后返回jpg图片

/*********************************
 * 功能:
 *      评价器8
 * 参数:
 *      AfterAppraise      -       评价器结果回调
 *      json               -       自定义评价信息(nullptr或""为默认参数)
 *      样例:{"\"evaluator\":[{\"evaluatorText\":\"非常满意\",\"evaluatorLevel\":\"5\",\"detail\":[
                                            {\"text\":\"一窗受理一次办结\",\"code\":\"510\"},{\"text\":\"可以先受理后补材料\",\"code\":\"511\"},
                                            {\"text\":\"不用提交证明\",\"code\":\"512\"},{\"text\":\"可以全程网上办理\",\"code\":\"513\"},
                                            {\"text\":\"可以使用手机办理\",\"code\":\"514\"},{\"text\":\"可以就近办理\",\"code\":\"515\"},
                                            {\"text\":\"无需材料直接办理\",\"code\":\"516\"},{\"text\":\"服务热情效率高\",\"code\":\"517\"}]},"
                            "{\"evaluatorText\":\"满意\",\"evaluatorLevel\":\"4\",\"detail\":[
                                            {\"text\":\"填写一张表单就可完成申报\",\"code\":\"406\"},{\"text\":\"在线提交材料窗口核验\",\"code\":\"407\"},
                                            {\"text\":\"一张清单告知全部申报材料\",\"code\":\"408\"},{\"text\":\"用告知承诺减免申报材料\",\"code\":\"409\"},
                                            {\"text\":\"可以在线预约办理\",\"code\":\"410\"},{\"text\":\"跑大厅一次办完\",\"code\":\"411\"},
                                            {\"text\":\"可以使用自助机办理\",\"code\":\"412\"},{\"text\":\"服务态度较好\",\"code\":\"413\"}]},"
                            "{\"evaluatorText\":\"一般\",\"evaluatorLevel\":\"3\",\"detail\":[
                                            {\"text\":\"一次性告知需要补正的材料\",\"code\":\"307\"},{\"text\":\"提供申报材料样本\",\"code\":\"308\"},
                                            {\"text\":\"在承诺的时间内办结\",\"code\":\"309\"},{\"text\":\"办事指南指引准确\",\"code\":\"310\"},
                                            {\"text\":\"按办事指南要求的材料即可办理\",\"code\":\"311\"},{\"text\":\"可以快递送达\",\"code\":\"312\"},
                                            {\"text\":\"跑动次数与承诺的一致\",\"code\":\"313\"},{\"text\":\"服务态度一般\",\"code\":\"314\"}]},"
                            "{\"evaluatorText\":\"不满意\",\"evaluatorLevel\":\"2\",\"detail\":[
                                            {\"text\":\"没有提供材料样本\",\"code\":\"207\"},{\"text\":\"没有提供材料清单\",\"code\":\"208\"},
                                            {\"text\":\"未在承诺时间内办结\",\"code\":\"209\"},{\"text\":\"同样内容的证明材料被要求多次提交\",\"code\":\"210\"},
                                            {\"text\":\"承诺网办但无法在线办理\",\"code\":\"211\"},{\"text\":\"在线预约办理后到实体大厅重复取号排队\",\"code\":\"212\"},
                                            {\"text\":\"窗口人员业务不熟练\",\"code\":\"213\"},{\"text\":\"服务态度生硬\",\"code\":\"214\"}]},"
                            "{\"evaluatorText\":\"非常不满意\",\"evaluatorLevel\":\"1\",\"detail\":[
                                            {\"text\":\"在办事指南之外增加新的审批条件\",\"code\":\"108\"},{\"text\":\"需提供办事指南之外的申报材料\",\"code\":\"109\"},
                                            {\"text\":\"无理由超过法定办理时间\",\"code\":\"110\"},{\"text\":\"办事指南提供样本有错\",\"code\":\"111\"},
                                            {\"text\":\"承诺在线收取申报材料实际无法收取\",\"code\":\"112\"},{\"text\":\"多头跑窗口和部门\",\"code\":\"113\"},
                                            {\"text\":\"跑动次数与承诺的不一致\",\"code\":\"114\"},{\"text\":\"服务态度差效率低\",\"code\":\"115\"}]}"
                       "]}
 * 回调接收参数demo(OnAfterAppraise):
 *      ErrorCode：程序执行代码 0：执行成功 非0：执行失败
        AppraiseResult：评价结果信息，Json结构，具体如下：
        {
            "appraiseLevel": "", // 评价等级
            "appraiseContent": "", // 评价内容，为评价内容代码串，以“|”分割
        }
 * 返回值:
 *      参见: 错误代码
 **********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_Evaluator8(OnAfterAppraise AfterAppraise, const char* json);

/**********************************
 *  功能:
 *      显示签署文件并点签合成
 *  参数:
 *      outTimes        -   超时时间，单位秒，超过该时间后，自动结束签署任务，返回签署取消状态。
 *      isVideo         -   是否采集签署音视频：
 *                              1：采集音视频
 *                              2：不采集音视频
 *      signType        -   签署方式：
 *                              0：只确认或取消文件内容；
 *                              1：签字；
 *                              2：加盖指纹；
 *                              3：签字并加盖指纹。
 *      docPath         -   待签文件路径，文件类别可以是PDF
 *      signedDocPath   -   签署后的文件存储路径
 *                              如：d:\20230601\sign.pdf
 *      signImgPath     -   签署后的笔迹图片存储路径
 *                              如：d:\20230601\signimg.png
 *      signDataPath    -   签署后的笔迹数据存储文件路径
 *                              如：d:\20230601\signData.xml
 *      fingerImgPath   -   签署后的指纹图片存储目录
 *                              如：d:\20230601\fingerImg.png
 *      videoPath       -   签署后音视频存储文件路径
 *                              如：d:\20230601\vidio.mp4
 *  设备返回值:
 *      0：签署完成
 *      1：取消签署
 *      2：拒绝签署
 *      其他：签署错误
 *  接口返回值:
 *      参见: 错误代码
 ***********************************/
DLL_API_EXPORT int DLL_API_CALL XG_ShowDocumentSignOrFingerPoints(
        int outTimes,
        int isVideo,
        int signType,
        const char* docPath,
        const char* signedDocPath,
        const char* signImgPath,
        const char* signDataPath,
        const char* fingerImgPath,
        const char* videoPath);

/**********************************
 *  功能:
 *      显示签署文件并点签合成,返回base64数据
 *  参数:
 *      outTimes        -   超时时间，单位秒，超过该时间后，自动结束签署任务，返回签署取消状态。
 *      isVideo         -   是否采集签署音视频：
 *                              1：采集音视频
 *                              2：不采集音视频
 *      signType        -   签署方式：
 *                              0：只确认或取消文件内容；
 *                              1：签字；
 *                              2：加盖指纹；
 *                              3：签字并加盖指纹。
 *      docPath         -   待签文件路径，文件类别可以是PDF
 *      signedDocBase64   -   签名合成的PDF文件BASE64编码（DLL内部会分配空间，外部使用完后需要释放）
 *      signImgBase64     -   签名图片BASE64编码（DLL内部会分配空间，外部使用完后需要释放）
 *      signDataBase64    -   签名数据BASE64编码（DLL内部会分配空间，外部使用完后需要释放）
 *      fingerImgBase64   -   指纹图片BASE64编码（DLL内部会分配空间，外部使用完后需要释放）
 *      videoBase64       -   录像视频BASE64编码（DLL内部会分配空间，外部使用完后需要释放）
 *  设备返回值:
 *      0：签署完成
 *      1：取消签署
 *      2：拒绝签署
 *      其他：签署错误
 *  接口返回值:
 *      参见: 错误代码
 ***********************************/
DLL_API_EXPORT int DLL_API_CALL XG_ShowDocumentSignOrFingerPoints_Base64(
        int outTimes,
        int isVideo,
        int signType,
        const char* docPath,
        char** signedDocBase64,
        char** signImgBase64,
        char** signDataBase64,
        char** fingerImgBase64,
        char** videoBase64);

/**********************************
 *  功能:
 *      显示签署文件并按坐标签署合成
 *  参数:
 *      outTimes        -   超时时间，单位秒，超过该时间后，自动结束签署任务，返回签署取消状态。
 *      isVideo         -   是否采集签署音视频：
 *                              1：采集音视频
 *                              2：不采集音视频
 *      signType        -   签署方式：
 *                              0：只确认或取消文件内容；
 *                              1：签字；
 *                              2：加盖指纹；
 *                              3：签字并加盖指纹。
 *      docPath         -   待签文件路径，文件类别可以是PDF或者OFD
 *      sPos            -   页码及坐标，JSON格式的数组，其中,属性page为页码，
 *                          当为0时表示所有页，属性x表示PDF文档的横坐标，
 *                          属性y表示PDF文档的纵坐标，属性width表示合成图片的宽，
 *                          属性height 表示合成图片的高，可以有多个页码及坐标。
 *                          数据实例如：
 *                          [{"height":120,"page":1,"width":80,"x":10,"y":10},
 *                           {"height":120,"page":2,"width":80,"x":0,"y":0}]
 *      signedDocPath   -   签署后的文件存储路径
 *                              如：d:\20230601\sign.pdf
 *      signImgPath     -   签署后的笔迹图片存储路径
 *                              如：d:\20230601\signimg.png
 *      signDataPath    -   签署后的笔迹数据存储文件路径
 *                              如：d:\20230601\signData.xml
 *      fingerImgPath   -   签署后的指纹图片存储目录
 *                              如：d:\20230601\fingerImg.png
 *      videoPath       -   签署后音视频存储文件路径
 *                              如：d:\20230601\vidio.mp4
 *  设备返回值:
 *      0：签署完成
 *      1：取消签署
 *      2：拒绝签署
 *      其他：签署错误
 *  接口返回值:
 *      参见: 错误代码
 ***********************************/
DLL_API_EXPORT int DLL_API_CALL XG_ShowDocumentSignOrFingerCoordinates(
        int outTimes,
        int isVideo,
        int signType,
        const char* docPath,
        const char* sPos,
        const char* signedDocPath,
        const char* signImgPath,
        const char* signDataPath,
        const char* fingerImgPath,
        const char* videoPath);

/**********************************
 *  功能:
 *      显示签署文件并按坐标签署合成,返回base64数据
 *  参数:
 *      outTimes        -   超时时间，单位秒，超过该时间后，自动结束签署任务，返回签署取消状态。
 *      isVideo         -   是否采集签署音视频：
 *                              1：采集音视频
 *                              2：不采集音视频
 *      signType        -   签署方式：
 *                              0：只确认或取消文件内容；
 *                              1：签字；
 *                              2：加盖指纹；
 *                              3：签字并加盖指纹。
 *      docPath         -   待签文件路径，文件类别可以是PDF或者OFD
 *      sPos            -   页码及坐标，JSON格式的数组，其中,属性page为页码，
 *                          当为0时表示所有页，属性x表示PDF文档的横坐标，
 *                          属性y表示PDF文档的纵坐标，属性width表示合成图片的宽，
 *                          属性height 表示合成图片的高，可以有多个页码及坐标。
 *                          数据实例如：
 *                          [{"height":120,"page":1,"width":80,"x":10,"y":10},
 *                           {"height":120,"page":2,"width":80,"x":0,"y":0}]
 *      signedDocBase64   -   签名合成的PDF文件BASE64编码（DLL内部会分配空间，外部使用完后需要释放）
 *      signImgBase64     -   签名图片BASE64编码（DLL内部会分配空间，外部使用完后需要释放）
 *      signDataBase64    -   签名数据BASE64编码（DLL内部会分配空间，外部使用完后需要释放）
 *      fingerImgBase64   -   指纹图片BASE64编码（DLL内部会分配空间，外部使用完后需要释放）
 *      videoBase64       -   录像视频BASE64编码（DLL内部会分配空间，外部使用完后需要释放）
 *  设备返回值:
 *      0：签署完成
 *      1：取消签署
 *      2：拒绝签署
 *      其他：签署错误
 *  接口返回值:
 *      参见: 错误代码
 ***********************************/
DLL_API_EXPORT int DLL_API_CALL XG_ShowDocumentSignOrFingerCoordinates_Base64(
        int outTimes,
        int isVideo,
        int signType,
        const char* docPath,
        const char* sPos,
        char** signedDocBase64,
        char** signImgBase64,
        char** signDataBase64,
        char** fingerImgBase64,
        char** videoBase64);

/**********************************
 *  功能:
 *      显示签署文件并按坐标签署合成
 *  参数:
 *      outTimes        -   超时时间，单位秒，超过该时间后，自动结束签署任务，返回签署取消状态。
 *      signType        -   签署方式：
 *                              1：自定义；
 *                              2：固定；
 *                              3：关键字。
 *      docPath         -   待签文件路径，文件类别可以是PDF或者OFD
 *      sPos            -   签署方式为2生效(其他情况传空):
 *                          页码及坐标，JSON格式的数组，其中,属性page为页码，
 *                          当为0时表示所有页，属性x表示PDF文档的横坐标，
 *                          属性y表示PDF文档的纵坐标，属性width表示合成图片的宽，
 *                          属性height 表示合成图片的高，可以有多个页码及坐标。
 *                          数据实例如：
 *                          [{"height":120,"page":1,"width":80,"x":10,"y":10},
 *                           {"height":120,"page":2,"width":80,"x":0,"y":0}]
 *      sKey            -   签署方式为3生效(其他情况传空):
 *                          PDF中查询最后找到的关键字尾部插入签字
 *  设备返回值:
 *      0：签署完成
 *      1：取消签署
 *      2：拒绝签署
 *      其他：签署错误
 *  接口返回值:
 *      参见: 错误代码
 ***********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_PDFPostilNm(
        int outTimes,
        int signType,
        const char* docPath,
        const char* sPos,
        const char* sKey);

/**********************************
 *  功能:
 *      设备显示错误提示
 *  参数:
 *      info        -       需要显示的文本
 *      showTime    -       显示时间, 单位: 毫秒
 *  接口返回值:
 *      参见: 错误代码
 ***********************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_ShowErrorInfo(const char* info, const int showTime = 2000);

/************************************************************************
*函数名称:GWQ_GetDeviceModule
*功能描述:获取设备模块
*输入参数:type -----  1、单目摄像头
                     2、双目摄像头
                     3、二代证
                     4、指纹
*输出参数:
*   -12模块不存在
*   1、单目摄像头     -   1 存在
*   2、双目摄像头     -   2 存在
*   3、二 代 证      -   0 存在
*   4、指 纹         -   1/2/3 存在 不同编号代表不同指纹模块
*   其他值: 参考错误码定义
************************************************************************/
DLL_API_EXPORT int DLL_API_CALL GWQ_GetDeviceModule(int type);


#ifdef __cplusplus
}

#endif

#endif // DEVICE10_SDK_H
