#ifndef  _PROTOCOL_Optics
#define  _PROTOCOL_Optics

#ifdef _OT_CPP_
#undef _OT_CPP_
#endif

#define PS_MAXWAITTIME 2000
#define DELAY_TIME     150
///////////////////���󷵻���////////////////////
#define PS_OK                0x00
#define PS_COMM_ERR          0x01
#define PS_NO_FINGER         0x02
#define PS_GET_IMG_ERR       0x03
#define PS_FP_TOO_DRY        0x04
#define PS_FP_TOO_WET        0x05
#define PS_FP_DISORDER       0x06
#define PS_LITTLE_FEATURE    0x07
#define PS_NOT_MATCH         0x08
#define PS_NOT_SEARCHED      0x09
#define PS_MERGE_ERR         0x0a
#define PS_ADDRESS_OVER      0x0b
#define PS_READ_ERR          0x0c
#define PS_UP_TEMP_ERR       0x0d
#define PS_RECV_ERR          0x0e
#define PS_UP_IMG_ERR        0x0f
#define PS_DEL_TEMP_ERR      0x10
#define PS_CLEAR_TEMP_ERR    0x11
#define PS_SLEEP_ERR         0x12
#define PS_INVALID_PASSWORD  0x13
#define PS_RESET_ERR         0x14
#define PS_INVALID_IMAGE     0x15
#define PS_HANGOVER_UNREMOVE 0X17
 

///////////////������//////////////////////////////
#define CHAR_BUFFER_A          0x01
#define CHAR_BUFFER_B          0x02
#define MODEL_BUFFER           0x03

//////////////////���ں�////////////////////////
#define COM1                   0x01
#define COM2                   0x02
#define COM3                   0x03

//////////////////������////////////////////////
#define BAUD_RATE_9600         0x00
#define BAUD_RATE_19200        0x01
#define BAUD_RATE_38400        0x02
#define BAUD_RATE_57600        0x03   //default
#define BAUD_RATE_115200       0x04

#define MAX_PACKAGE_SIZE_		350   // ���ݰ���󳤶�
#define CHAR_LEN_AES1711		1024  // 512->1024 [2009.11.12] AES1711ʹ��1024��Сģ��
#define CHAR_LEN_NORMAL			512	  // 512 ͨ�ð汾ʹ��512��С��ģ��


#define DEVICE_USB		0
#define DEVICE_COM		1
#define DEVICE_UDisk	2

#define IMAGE_X 256
#define IMAGE_Y 288

#ifdef _OT_CPP_
extern "C"
{
#endif

	//==============================================================================//
	//��ȡ FG_USB �豸��
	int WINAPI	ZAZGetUSBDevNum(int* iNums);	
	int WINAPI	ZAZGetUDiskNum(int* iNums);		
	//��ȡ UDISK �豸��


	//���豸
	int WINAPI	ZAZOpenDeviceEx(HANDLE* pHandle, int nDeviceType,int iCom=1,int iBaud=1,int nPackageSize=2,int iDevNum=0);
	int WINAPI	ZAZCloseDeviceEx(HANDLE hHandle);
	//�ر��豸

	//���ݴ���Ż�ȡ������Ϣ
	char* WINAPI	ZAZErr2Str(int nErrCode);

	//�����ָ��¼ȡͼ��
	int WINAPI	ZAZGetImage(HANDLE hHandle,int nAddr);	
	//����ԭʼͼ������ָ������
	int WINAPI	ZAZGenChar(HANDLE hHandle,int nAddr,int iBufferID);
	//ֱ���ڴ�������ʾָ��ͼ��
	int WINAPI	ZAZShowFingerData(HWND hWnd,unsigned char *pFingerData);
	//��CharBufferA��CharBufferB�е������ļ��ϲ�����ģ�����ModelBuffer
	int	WINAPI	ZAZRegModule(HANDLE hHandle,int nAddr);
	//��ModelBuffer�е��ļ����浽flashָ�ƿ���
	int WINAPI	ZAZStoreChar(HANDLE hHandle,int nAddr,int iBufferID, int iPageID);
	//��ȷ�ȶ�CharBufferA��CharBufferB�е������ļ�
	int WINAPI	ZAZMatch(HANDLE hHandle,int nAddr,int* iScore);	
	//��CharBufferA��CharBufferB�е������ļ����������򲿷�ָ�ƿ�
	int WINAPI	ZAZSearch(HANDLE hHandle,int nAddr,int iBufferID, int iStartPage, int iPageNum, int *iMbAddress,int *iscore=NULL);
	//++��������
	int WINAPI	ZAZHighSpeedSearch(HANDLE hHandle,int nAddr,int iBufferID, int iStartPage, int iPageNum, int *iMbAddress,int *iscore=NULL);	
	//ɾ��flashָ�ƿ��е�һ�������ļ�
	int WINAPI	ZAZDelChar(HANDLE hHandle,int nAddr,int iStartPageID,int nDelPageNum);
	//���flashָ�ƿ�
	int WINAPI	ZAZEmpty(HANDLE hHandle,int nAddr);

	
	
	//��������
	int WINAPI	ZAZReadParTable(HANDLE hHandle,int nAddr,unsigned char* pParTable);
	//++��Flash
	int WINAPI	ZAZReadInfPage(HANDLE hHandle,int nAddr, unsigned char* pInf);
	//++����Чģ�����
	int WINAPI	ZAZTemplateNum(HANDLE hHandle,int nAddr,int *iMbNum);
	//++дģ��Ĵ���
	int WINAPI	ZAZWriteReg(HANDLE hHandle,int nAddr,int iRegAddr,int iRegValue);
	//дģ��Ĵ���������������
	int WINAPI	ZAZSetBaud(HANDLE hHandle,int nAddr,int nBaudNum);
	//дģ��Ĵ�������ȫ�ȼ�����
	int WINAPI	ZAZSetSecurLevel(HANDLE hHandle,int nAddr,int nLevel);
	//дģ��Ĵ��������ݰ���С����
	int WINAPI	ZAZSetPacketSize(HANDLE hHandle,int nAddr,int nSize);
	//��ȡ�����
	int WINAPI	ZAZGetRandomData(HANDLE hHandle,int nAddr,unsigned char* pRandom);
	//����оƬ��ַ
	int WINAPI	ZAZSetChipAddr(HANDLE hHandle,int nAddr,unsigned char* pChipAddr);
	//��ģ��������	nPage,0,1,2,3��Ӧģ���0-256��256-512��512-768��768-1024
	int WINAPI	ZAZReadIndexTable(HANDLE hHandle,int nAddr,int nPage,unsigned char* UserContent);
	//���ú��̵�
	int WINAPI	ZAZDoUserDefine(HANDLE hHandle,int nAddr,int GPIO,int STATE);
	//��ԭʼ���ݴ�Ϊͼ���ʽ
	int WINAPI	ZAZFingerData2BMPData(unsigned char *pFingerData, unsigned char *pBMPData,int* nBMPDataLen);




	//��flashָ�ƿ��ж�ȡһ��ģ�嵽ModelBuffer
	int WINAPI	ZAZLoadChar(HANDLE hHandle,int nAddr,int iBufferID,int iPageID);
	//�������������е��ļ��ϴ�����λ��
	int WINAPI	ZAZUpChar(HANDLE hHandle,int nAddr,int iBufferID, unsigned char* pTemplet, int* iTempletLength);	
	//����λ������һ�������ļ�������������
	int WINAPI	ZAZDownChar(HANDLE hHandle,int nAddr,int iBufferID, unsigned char* pTemplet, int iTempletLength);


	//�ϴ�ԭʼͼ��
	int WINAPI	ZAZUpImage(HANDLE hHandle,int nAddr,unsigned char* pImageData, int* iImageLength);
	int WINAPI	ZAZDownImage(HANDLE hHandle,int nAddr,unsigned char *pImageData, int iLength);
	//����ԭʼͼ��	

	//�ϴ�ԭʼͼ��
	int WINAPI	ZAZImgData2BMP(unsigned char* pImgData,const char* pImageFile);
	int WINAPI	ZAZGetImgDataFromBMP(HANDLE hHandle,const char *pImageFile,unsigned char *pImageData,int *pnImageLen);
	//����ԭʼͼ��

	//�����±�
	int WINAPI	ZAZReadInfo(HANDLE hHandle,int nAddr,int nPage,unsigned char* UserContent);
	int WINAPI	ZAZWriteInfo(HANDLE hHandle,int nAddr,int nPage,unsigned char* UserContent);
	//д���±�

	//�����豸���ֿ���
	int WINAPI	ZAZSetPwd(HANDLE hHandle,int nAddr,unsigned char* pPassword);
	int WINAPI	ZAZVfyPwd(HANDLE hHandle,int nAddr,unsigned char* pPassword);
	//��֤�豸���ֿ���

	//�ϴ�ָ��Ϊ.BAT�ļ�
	int WINAPI	ZAZUpChar2File(HANDLE hHandle,int nAddr,int iBufferID, const char* pFileName);
	int WINAPI	ZAZDownCharFromFile(HANDLE hHandle,int nAddr,int iBufferID, const char* pFileName);
	//.BAT�ļ�תָ��

	//��������ģ���Ĵ�С ͨ��-512 AES1711-1024
	int WINAPI  ZAZSetCharLen(int nLen = CHAR_LEN_NORMAL);
	int WINAPI	ZAZGetCharLen(int *pnLen);
	//��ȡ1ö�����Ĵ�С
 
	//���Ƶ�
	int WINAPI ZAZSetledsound(HANDLE hHandle,int nAddr,unsigned char red, unsigned char green, unsigned char sound, unsigned char moveflag,int timecount);
 

#ifdef _OT_CPP_
}
#endif

#endif                                                     