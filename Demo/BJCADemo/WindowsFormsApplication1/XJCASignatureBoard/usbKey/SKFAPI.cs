using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.Security.Cryptography;

namespace XJCAServiceslib
{

    public class SKFApi
    {



        public const UInt32 MAX_IV_LEN = 32;                                //初始化向量的最大长度
        public const UInt32 MAX_FILE_NAME_LEN = 32;                         //文件名最大长度
        public const UInt32 MIN_PIN_LEN = 6;                                //最小的PIN长度
        public const UInt32 MAX_RSA_MODULUS_LEN = 256;                      //RSA算法模数的最大长度
        public const UInt32 MAX_RSA_EXPONENT_LEN = 4;                       //RSA算法指数的最大长度
        public const UInt32 ECC_MAX_XCOORDINATE_BITS_LEN = 512;             //ECC算法X坐标的最大长度
        public const UInt32 ECC_MAX_YCOORDINATE_BITS_LEN = 512;             //ECC算法Y坐标的最大长度
        public const UInt32 ECC_MAX_MODULUS_BITS_LEN = 512;                 //ECC算法模数的最大长度
        public const UInt32 SGD_SM1_ECB = 0x00000101;                       //SM1算法ECB加密模式
        public const UInt32 SGD_SM1_CBC = 0x00000102;                       //SM1算法CBC加密模式
        public const UInt32 SGD_SM1_CFB = 0x00000104;                       //SM1算法CFB加密模式
        public const UInt32 SGD_SM1_OFB = 0x00000108;                       //SM1算法OFB加密模式
        public const UInt32 SGD_SM1_MAC = 0x00000110;                       //SM1算法MAC运算
        public const UInt32 SGD_SSF33_ECB = 0x00000201;                     //SSF33算法ECB加密模式
        public const UInt32 SGD_SSF33_CBC = 0x00000202;                     //SSF33算法CBC加密模式
        public const UInt32 SGD_SSF33_CFB = 0x00000204;                     //SSF33算法CFB加密模式
        public const UInt32 SGD_SSF33_OFB = 0x00000208;                     //SSF33算法OFB加密模式
        public const UInt32 SGD_SSF33_MAC = 0x00000210;                     //SSF33算法MAC运算
        public const UInt32 SGD_SM4_ECB = 0x00000401;                       //SMS4算法ECB加密模式
        public const UInt32 SASGD_SM4_CBCR_OK = 0x00000402;                 //SMS4算法CBC加密模式
        public const UInt32 SGD_SM4_CFB = 0x00000404;                       //SMS4算法CFB加密模式
        public const UInt32 SGD_SM4_OFB = 0x00000408;                       //SMS4算法OFB加密模式
        public const UInt32 SGD_SM4_MAC = 0x00000410;                       //SMS4算法MAC运算

        //非对称密码算法标识
        public const UInt32 SGD_RSA = 0x00010000;                           //RSA算法
        public const UInt32 SGD_SM2_1 = 0x00020100;                         //椭圆曲线签名算法
        public const UInt32 SGD_SM2_2 = 0x00020200;                         //椭圆曲线密钥交换协议
        public const UInt32 SGD_SM2_3 = 0x00020400;                         //椭圆曲线加密算法

        //密码杂凑算法标识

        public const UInt32 SGD_SM3 = 0x00000001;                           //SM3杂凑算法
        public const UInt32 SGD_SHA1 = 0x00000002;                          //SHA1杂凑算法
        public const UInt32 SGD_SHA256 = 0x00000004;                        //SHA256杂凑算法

        //设别状态

        public const UInt32 DEV_ABSENT_STATE = 0x00000000;                  //设备不存在
        public const UInt32 DEV_PRESENT_STATE = 0x00000001;                 //设备存在
        public const UInt32 DEV_UNKNOW_STATE = 0x00000002;                  //设备状态未知

        //设备权限
        public const UInt32 SECURE_NEVER_ACCOUNT = 0x00000000;              //不允许
        public const UInt32 SECURE_ADM_ACCOUNT = 0x00000001;                //管理员权限
        public const UInt32 SECURE_USER_ACCOUNT = 0x00000010;               //用户权限
        public const UInt32 SECURE_EVERYONE_ACCOUNT = 0x000000FF;           //任何人

        //PIN码类型
        public const UInt32 ADMIN_TYPE = 0x00000000;                        //管理员PIN
        public const UInt32 USER_TYPE = 0x00000001;                         //用户PIN

        public static string DLL_Path = System.AppDomain.CurrentDomain.BaseDirectory;



        public struct Version
        {
            public byte major;	//主版本号
            public byte minor;	//次版本号
        }

        public struct DEVINFO
        {
            public Version Version;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
            public string Manufacturer;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
            public string Issuer;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            public string Label;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            public string SerialNumber;
            public Version HWVersion;
            public Version FirmwareVersion;
            public UInt32 AlgSymCap;
            public UInt32 AlgAsymCap;
            public UInt32 AlgHashCap;
            public UInt32 DevAuthAlgId;
            public UInt32 TotalSpace;
            public UInt32 FreeSpace;
            public UInt32 MaxECCBufferSize;
            public UInt32 MaxBufferSize;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
            public byte[] Reserved;

        }

        public struct BLOCKCIPHERPARAM
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
            public byte[] IV;
            public UInt32 IVLen;
            public UInt32 PaddingType;
            public UInt32 FeedBitLen;
        }

        //RSA公钥交换数据块
        public struct Struct_RSAPUBLICKEYBLOB
        {
            public UInt32 AlgID;                                                    //算法标识号
            public UInt32 BitLen;                                                   //模数的实际位长度，必须是8的倍数          
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
            public byte[] Modulus;                                           //模数n=p*q，实际长度为BitLen/8字节
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
            public byte[] PublicExponent;                                    //公开密钥e， 一般为00010001
        }



        //RSA私钥交换数据块
        public struct Struct_RSAPRIVATEKEYBLOB
        {
            public UInt32 AlgID;                                                   //算法标识号          
            public UInt32 BitLen;                                                  //模数的实际位长度，必须是8的倍数
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
            public Byte[] Modulus;              //模数n=p*q，实际长度为BitLen/8字节
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
            public Byte[] PublicExponent;         //公开密钥e， 一般为00010001
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
            public Byte[] PrivateExponent;        //私有密钥d，实际长度为BitLen/8字节
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
            public Byte[] Prime1;              //素数p，实际长度为BitLen/16字节
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
            public Byte[] Prime2;              //素数q，实际长度为BitLen/16字节
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
            public Byte[] Prime1Exponent;      //d mod (p-1)的值, 实际长度为BitLen/16字节
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
            public Byte[] Prime2Exponent;      //d mod (q-1)的值，实际长度为BitLen/16字节
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
            public Byte[] Coefficient;         //q模p的乘法逆元，实际长度为BitLen/16字节
        }


        //ECC公钥交换数据块
        public struct Struct_ECCPUBLICKEYBLOB
        {
            public UInt32 BitLen;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
            public Byte[] XCoordinate;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
            public Byte[] YCoordinate;
        }


        //ECC私钥交换数据块
        public struct Struct_ECCPRIVATEKEYBLOB
        {
            public UInt32 BitLen;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
            public Byte[] PrivateKey;
        }


        // ECC密文数据结构
        public struct Struct_ECCCIPHERBLOB
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
            public Byte[] XCoordinate;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
            public Byte[] YCoordinate;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
            public Byte[] HASH;
            public UInt32 CipherLen;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
            public Byte[] Cipher;
        }
        public static Byte[] StructToBytes(Object structure)
        {
            Int32 size = Marshal.SizeOf(structure);
            //Console.WriteLine(size);
            IntPtr buffer = Marshal.AllocHGlobal(size);
            try
            {
                Marshal.StructureToPtr(structure, buffer, false);
                Byte[] bytes = new Byte[size];
                Marshal.Copy(buffer, bytes, 0, size);
                return bytes;
            }
            finally
            {
                Marshal.FreeHGlobal(buffer);
            }
        }

        public static Object BytesToStruct(Byte[] bytes, Type strcutType)
        {
            Int32 size = Marshal.SizeOf(strcutType);
            IntPtr buffer = Marshal.AllocHGlobal(size);
            try
            {
                Marshal.Copy(bytes, 0, buffer, size);
                return Marshal.PtrToStructure(buffer, strcutType);
            }
            finally
            {
                Marshal.FreeHGlobal(buffer);
            }
        }


        // ECC签名数据结构
        public struct Struct_ECCSIGNATUREBLOB
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
            public Byte[] r;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
            public Byte[] s;

        }


        //ECC加密密钥对保护结构

        public struct Struct_ENVELOPEDKEYBLOB
        {

            public UInt32 Version;                                     // 当前版本为 1
            public UInt32 ulSymmAlgID;                                 // 规范中的算法标识，限定ECB模式
            public UInt32 ulBits;                                     // 加密密钥对的密钥位长度
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
            public Byte[] cbEncryptedPriKey;                          // 加密保护的加密私钥
            public Struct_ECCPUBLICKEYBLOB PubKey; // 加密密钥对的公钥
            public Struct_ECCCIPHERBLOB ECCCipherBlob; // 用保护公钥加密的对称密钥密文。
        }

        ////////////////////////////////////////////////////////////////////////////////////

        public struct Struct_BLOCKCIPHERPARAM
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
            public Byte[] IV;                                        //初始向量，MAX_IV_LEN为初始向量的最大长度
            public UInt32 IVLen;                                   //初始向量实际长度，按字节计算
            public UInt32 PaddingType;                             //填充方式，0表示不填充，1表示按照PKCS#5方式进行填充
            public UInt32 FeedBitLen;                              //反馈值的位长度，按字节计算，只针对OFB、CFB模式

        }

        public struct Struct_FILEATTRIBUTE
        {
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            public String FileName;
            public UInt32 FileSize;
            public UInt32 ReadRights;
            public UInt32 WriteRights;
        }


        /************************************************************************/
        /*	1. 设备管理	系列函数														*/
        /*	SKF_WaitForDevEvent		    等待设备的插拔事件											*/
        /*	SKF_CancelWaitForDevEvent	 								*/
        /*	SKF_EnumDev					获得当前系统中的设备列表										*/
        /*	SKF_ConnectDev				通过设备名称连接设备，返回设备的句柄										*/
        /*	SKF_DisconnectDev			断开一个已经连接的设备，并释放句柄。										*/
        /*	SKF_GetDevState				获取设备是否存在的状态									*/
        /*	SKF_SetLable				获取设备的一些特征信息，包括设备标签、厂商信息、支持的算法等										*/
        /*	SKF_GetDevInfo				获取设备的一些特征信息，包括设备标签、厂商信息、支持的算法等										*/
        /*	SKF_LockDev					获得设备的独占使用权										*/
        /*	SKF_UnlockDev				释放对设备的独占使用权										*/
        /*	SKF_Transmit				将命令直接发送给设备，并返回结果										*/
        /************************************************************************/

        /*
        *	等待设备的插拔事件
        *	szDevName		[OUT]返回发生事件的设备名称
        *	pulDevNameLen	[IN,OUT]输入/输出参数，当输入时表示缓冲区长度，输出时表示设备名称的有效长度,长度包含字符串结束符
        *	pulEvent		[OUT]事件类型。1表示插入，2表示拔出
        *	备注: 该函数是阻塞调用的*/
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_WaitForDevEvent(string szDevName, UInt32 UiUpulDevNameLen, ref UInt32 pulEvent);
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_CancelWaitForDevEvent();

        /*
        *	获得当前系统中的设备列表
        *	bPresent		[IN]为TRUE表示取当前设备状态为存在的设备列表。为FALSE表示取当前驱动支持的设备列表
        *	szNameList		[OUT]设备名称列表。如果该参数为NULL，将由pulSize返回所需要的内存空间大小。每个设备的名称以单个'\0'结束，以双'\0'表示列表的结束
        *	pulSize			[IN,OUT]输入参数，输入设备名称列表的缓冲区长度，输出参数，返回szNameList所需要的空间大小
        */
        [DllImport("mtoken_gm3000_xjca.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        public static extern UInt32 SKF_EnumDev(bool bPresent, byte[] szNameList, ref UInt32 pulSize);
        /*
        *	通过设备名称连接设备，返回设备的句柄
        *	szName		[IN]设备名称
        *	phDev		[OUT]返回设备操作句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ConnectDev(string szName, ref UInt32 phDev);
        /*
        *	断开一个已经连接的设备，并释放句柄。
        *	hDev		[IN]连接设备时返回的设备句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_DisConnectDev(UInt32 phDev);
        /*
        *	获取设备是否存在的状态
        *	szDevName	[IN]连接名称
        *	pulDevState	[OUT]返回设备状态
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_GetDevState(string szDevName, ref UInt32 pulDevState);
        /*
        *	设置设备标签
        *	hDev		[IN]连接设备时返回的设备句柄
        *	szLabel		[OUT]设备标签字符串。该字符串应小于32字节
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_SetLabel(UInt32 hDev, string szLabel);
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ECCPrvKeyDecrypt(UInt32 hContainer, ref Struct_ECCCIPHERBLOB pCipherText, byte[] pbData, ref UInt32 pbDataLen);

        /*
        *	获取设备的一些特征信息，包括设备标签、厂商信息、支持的算法等
        *	hDev		[IN]连接设备时返回的设备句柄
        *	pDevInfo	[OUT]返回设备信息
        */

        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_GetDevInfo(UInt32 hDev, ref DEVINFO pDevInfo);


        /*
        *	获得设备的独占使用权
        *	hDev		[IN]连接设备时返回的设备句柄
        *	ulTimeOut	[IN]超时时间，单位为毫秒。如果为0xFFFFFFFF表示无限等待
        */

        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_SetLabel(UInt32 hDev, UInt32 ulTimeOut);

        /*
        *	释放对设备的独占使用权
        *	hDev		[IN]连接设备时返回的设备句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_UnlockDev(UInt32 hDev);

        /*
        *	将命令直接发送给设备，并返回结果
        *	hDev			[IN]设备句柄
        *	pbCommand		[IN]设备命令
        *	ulCommandLen	[IN]命令长度
        *	pbData			[OUT]返回结果数据
        *	pulDataLen		[IN,OUT]输入缓冲区长度，输出返回数据长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_LockDev(UInt32 hDev, UInt32 ulCommandLen);

        /*
        *	将命令直接发送给设备，并返回结果
        *	hDev			[IN]设备句柄
        *	pbCommand		[IN]设备命令
        *	ulCommandLen	[IN]命令长度
        *	pbData			[OUT]返回结果数据
        *	pulDataLen		[IN,OUT]输入缓冲区长度，输出返回数据长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_Transmit(UInt32 hDev, Byte[] pbCommand, UInt32 ulCommandLen, byte[] pbData, UInt32 pulDataLen);


        /************************************************************************/
        /*  2. 访问控制	系列函数                                           */
        /*	SKF_ChangeDevAuthKey	更改设备认证密钥											*/
        /*	SKF_DevAuth				设备认证是设备对应用程序的认证											*/
        /*	SKF_ChangePIN			修改PIN，可以修改Admin和User的PIN，如果原PIN错误，返回剩余重试次数，当剩余次数为0时，表示PIN已经被锁死											*/
        /*	SKF_GetPINInfo			获取PIN码信息，包括最大重试次数、当前剩余重试次数，以及当前PIN码是否为出厂默认PIN码											*/
        /*	SKF_VerifyPIN			校验PIN码。校验成功后，会获得相应的权限，如果PIN码错误，会返回PIN码的重试次数，当重试次数为0时表示PIN码已经锁死											*/
        /*	SKF_UnblockPIN			当用户的PIN码锁死后，通过调用该函数来解锁用户PIN码。											*/
        /*	SKF_ClearSecureState	清除应用当前的安全状态											*/
        /************************************************************************/

        /*
        *	更改设备认证密钥
        *	hDev		[IN]连接时返回的设备句柄
        *	pbKeyValue	[IN]密钥值
        *	ulKeyLen	[IN]密钥长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ChangeDevAuthKey(UInt32 hDev, Byte[] pbKeyValue, UInt32 ulKeyLen);

        /*
        *	设备认证是设备对应用程序的认证
        *	hDev			[IN]连接时返回的设备句柄
        *	pbAuthData		[IN]认证数据
        *	ulLen			[IN]认证数据的长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_DevAuth(UInt32 hDev, Byte[] pbAuthData, UInt32 ulLen);
        /*
        *	修改PIN，可以修改Admin和User的PIN，如果原PIN错误，返回剩余重试次数，当剩余次数为0时，表示PIN已经被锁死
        *	hApplication	[IN]应用句柄
        *	ulPINType		[IN]PIN类型，可以为ADMIN_TYPE=0，或USER_TYPE=1
        *	szOldPIN		[IN]原PIN值
        *	szNewPIN		[IN]新PIN值
        *	pulRetryCount	[OUT]出错后重试次数
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ChangePIN(UInt32 hApplication, UInt32 ulPINType, StringBuilder szOldPin, StringBuilder szNewPin, ref UInt32 pulRetryCount);

        /*
        *	获取PIN码信息，包括最大重试次数、当前剩余重试次数，以及当前PIN码是否为出厂默认PIN码
        *	hApplication		[IN]应用句柄
        *	ulPINType			[IN]PIN类型
        *	pulMaxRetryCount	[OUT]最大重试次数
        *	pulRemainRetryCount	[OUT]当前剩余重试次数，当为0时表示已锁死
        *	pbDefaultPin		[OUT]是否为出厂默认PIN码
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_GetPINInfo(UInt32 hApplication, UInt32 ulPINType, ref UInt32 pulMaxRetryCount, ref UInt32 pulRemainRetryCount, ref Boolean pbDefaultPin);

        /*
        *	校验PIN码。校验成功后，会获得相应的权限，如果PIN码错误，会返回PIN码的重试次数，当重试次数为0时表示PIN码已经锁死
        *	hApplication	[IN]应用句柄
        *	ulPINType		[IN]PIN类型，可以为ADMIN_TYPE=0，或USER_TYPE=1
        *	szPIN			[IN]PIN值
        *	pulRetryCount	[OUT]出错后返回的重试次数
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_VerifyPIN(UInt32 hApplication, UInt32 ulPINType, StringBuilder szPIN, ref UInt32 pulRetryCount);
        /*
        *	当用户的PIN码锁死后，通过调用该函数来解锁用户PIN码。
        *	解锁后，用户PIN码被设置成新值，用户PIN码的重试次数也恢复到原值。
        *	hApplication	[IN]应用句柄
        *	szAdminPIN		[IN]管理员PIN码
        *	szNewUserPIN	[IN]新的用户PIN码
        *	pulRetryCount	[OUT]管理员PIN码错误时，返回剩余重试次数
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_UnblockPIN(UInt32 hApplication, StringBuilder szAdminPIN, StringBuilder szNewUserPIN, ref UInt32 pulRetryCount);

        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_GenRemoteUnblockRequest(UInt32 hApplication, Byte[] pbRandom, UInt32 ulRandomLen);

        /*
        *	当用户的PIN码锁死后，通过调用该函数来解锁用户PIN码。
        *	解锁后，用户PIN码被设置成新值，用户PIN码的重试次数也恢复到原值。
        *	hApplication	[IN]应用句柄
        *	pbCipherPIN		[IN]管理员PIN做sha1，取16位做为KEY，用KEY加密新的用户PIN得到密文，用随机数对KEY做MAC，加到密文的后面
        *	pulRetryCount	[OUT]管理员PIN码错误时，返回剩余重试次数
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_RemoteUnblockPIN(UInt32 hApplication, Byte[] pbCipherPIN, UInt32 ulCipherPINLen, Byte[] pulRetryCount);

        /*
        *	清除应用当前的安全状态
        *	hApplication	[IN]应用句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ClearSecureState(UInt32 hApplication);

        /************************************************************************/
        /*  3. 应用管理系列函数                                           */
        /*	SKF_CreateApplication		创建一个应用										*/
        /*	SKF_EnumApplication			枚举设备中所存在的所有应用										*/
        /*	SKF_DeleteApplication		删除指定的应用										*/
        /*	SKF_OpenApplication			打开指定的应用										*/
        /*	SKF_CloseApplication		关闭应用并释放应用句柄										*/
        /************************************************************************/

        /*
        *	创建一个应用
        *	hDev					[IN]连接设备时返回的设备句柄
        *	szAppName				[IN]应用名称
        *	szAdminPIN				[IN]管理员PIN
        *	dwAdminPinRetryCount	[IN]管理员PIN最大重试次数
        *	szUserPIN				[IN]用户PIN
        *	dwAdminPinRetryCount	[IN]用户PIN最大重试次数
        *	dwCreateFileRights		[IN]在该应用下创建文件和容器的权限
        *	phApplication			[OUT]应用的句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_CreateApplication(UInt32 hDev, StringBuilder szAppName, StringBuilder szAdminPin, UInt32 dwAdminPinRetryCount, StringBuilder szUserPin, UInt32 dwUserPinRetryCount, UInt32 dwCreateFileRights, ref UInt32 phApplication);

        /*
        *	枚举设备中所存在的所有应用
        *	hDev			[IN]连接设备时返回的设备句柄
        *	szAppName		[OUT]返回应用名称列表, 如果该参数为空，将由pulSize返回所需要的内存空间大小。
        *						 每个应用的名称以单个'\0'结束，以双'\0'表示列表的结束。
        *	pulSize			[IN,OUT]输入参数，输入应用名称的缓冲区长度，输出参数，返回szAppName所占用的的空间大小
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_EnumApplication(UInt32 hDev, byte[] szAppName, ref UInt32 pulSize);
        /*
        *	删除指定的应用
        *	hDev			[IN]连接设备时返回的设备句柄
        *	szAppName		[IN]应用名称
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_DeleteApplication(UInt32 hDev, String szAppName);
        /*
        *	打开指定的应用
        *	hDev			[IN]连接设备时返回的设备句柄
        *	szAppName		[IN]应用名称
        *	phApplication	[OUT]应用的句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_OpenApplication(UInt32 hDev, String szAppName, ref UInt32 phApplication);
        /*
        *	关闭应用并释放应用句柄
        *	hApplication	[IN]应用的句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_CloseApplication(UInt32 hApplication);

        /************************************************************************/
        /*  4. 文件管理				                                            */
        /*	SKF_CreateFile		创建一个文件。创建文件时要指定文件的名称，大小，以及文件的读写权限												*/
        /*	SKF_DeleteFile		删除指定文件，文件删除后，文件中写入的所有信息将丢失。文件在设备中的占用的空间将被释放。												*/
        /*	SKF_EnumFiles		枚举一个应用下存在的所有文件												*/
        /*	SKF_GetFileInfo		获取应用文件的属性信息，例如文件的大小、权限等												*/
        /*	SKF_ReadFile		读取文件内容												*/
        /*	SKF_WriteFile		写数据到文件中												*/
        /************************************************************************/

        /*
        *	创建一个文件。创建文件时要指定文件的名称，大小，以及文件的读写权限
        *	hApplication		[IN]应用句柄
        *	szFileName			[IN]文件名称，长度不得大于32个字节
        *	ulFileSize			[IN]文件大小
        *	ulReadRights		[IN]文件读权限
        *	ulWriteRights		[IN]文件写权限
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_CreateFile(UInt32 hApplication, StringBuilder szFileName, UInt32 ulFileSize, UInt32 ulReadRights, UInt32 ulWriteRights);

        /*
        *	删除指定文件，文件删除后，文件中写入的所有信息将丢失。文件在设备中的占用的空间将被释放。
        *	hApplication		[IN]要删除文件所在的应用句柄
        *	szFileName			[IN]要删除文件的名称
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_DeleteFile(UInt32 hApplication, StringBuilder szFileName);
        /*
        *	枚举一个应用下存在的所有文件
        *	hApplication		[IN]应用的句柄
        *	szFileList			[OUT]返回文件名称列表，该参数为空，由pulSize返回文件信息所需要的空间大小。每个文件名称以单个'\0'结束，以双'\0'表示列表的结束。
        *	pulSize				[OUT]输入为数据缓冲区的大小，输出为实际文件名称的大小
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_EnumFiles(UInt32 hApplication, Byte[] szFileList, ref UInt32 pulSize);

        /*
        *	获取应用文件的属性信息，例如文件的大小、权限等
        *	hApplication		[IN]文件所在应用的句柄
        *	szFileName			[IN]文件名称
        *	pFileInfo			[OUT]文件信息，指向文件属性结构的指针
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_GetFileInfo(UInt32 hApplication, StringBuilder szFileName, ref Struct_FILEATTRIBUTE pFileInfo);

        /*
        *	读取文件内容
        *	hApplication		[IN]文件所在的应用句柄
        *	szFileName			[IN]文件名
        *	ulOffset			[IN]文件读取偏移位置
        *	ulSize				[IN]要读取的长度
        *	pbOutData			[OUT]返回数据的缓冲区
        *	pulOutLen			[OUT]输入表示给出的缓冲区大小；输出表示实际读取返回的数据大小
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ReadFile(UInt32 hApplication, StringBuilder szFileName, UInt32 ulOffset, UInt32 ulSize, Byte[] pbOutData, ref UInt32 pulOutLen);

        /*
        *	写数据到文件中
        *	hApplication		[IN]文件所在的应用句柄
        *	szFileName			[IN]文件名
        *	ulOffset			[IN]写入文件的偏移量
        *	pbData				[IN]写入数据缓冲区
        *	ulSize				[IN]写入数据的大小
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_WriteFile(UInt32 hApplication, StringBuilder szFileName, UInt32 ulOffset, StringBuilder pbData, ref UInt32 ulSize);


        /************************************************************************/
        /*  5. 容器管理	系列函数                                           */
        /*	SKF_CreateContainer		在应用下建立指定名称的容器并返回容器句柄											*/
        /*	SKF_DeleteContainer		在应用下删除指定名称的容器并释放容器相关的资源											*/
        /*	SKF_EnumContainer		枚举应用下的所有容器并返回容器名称列表											*/
        /*	SKF_OpenContainer		获取容器句柄											*/
        /*	SKF_CloseContainer		关闭容器句柄，并释放容器句柄相关资源											*/
        /*	SKF_GetContainerType	获取容器的类型											*/
        /*	SKF_ImportCertificate	向容器内导入数字证书											*/
        /*	SKF_ExportCertificate	导出容器内的数字证书											*/
        /************************************************************************/

        /*
        *	在应用下建立指定名称的容器并返回容器句柄
        *	hApplication		[IN]应用句柄
        *	szContainerName		[IN]ASCII字符串，表示所建立容器的名称，容器名称的最大长度不能超过64字节
        *	phContainer			[OUT]返回所建立容器的容器句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_CreateContainer(UInt32 hApplication, StringBuilder szContainerName, ref UInt32 phContainer);
        /*
        *	在应用下删除指定名称的容器并释放容器相关的资源
        *	hApplication		[IN]应用句柄
        *	szContainerName		[IN]指向删除容器的名称
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_DeleteContainer(UInt32 hApplication, StringBuilder szContainerName);
        /*
        *	枚举应用下的所有容器并返回容器名称列表
        *	hApplication		[IN]应用句柄
        *	szContainerName		[OUT]指向容器名称列表缓冲区，如果此参数为NULL时，pulSize表示返回数据所需要缓冲区的长度，如果此参数不为NULL时，返回容器名称列表，每个容器名以单个'\0'为结束，列表以双'\0'结束
        *	pulSize				[OUT]调用前表示szContainerName缓冲区的长度，返回容器名称列表的长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_EnumContainer(UInt32 hApplication, byte[] szContainerName, ref UInt32 pulSize);
        /*
        *	获取容器句柄
        *	hApplication		[IN]应用句柄
        *	szContainerName		[IN]容器名称
        *	phContainer			[OUT]返回所打开容器的句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_OpenContainer(UInt32 hApplication, string szContainerName, ref UInt32 phContainer);

        /*
        *	关闭容器句柄，并释放容器句柄相关资源
        *	hContainer			[OUT]容器句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_CloseContainer(UInt32 hContainer);

        /*
        获取容器的类型
        hContainer	[IN] 容器句柄。
        pulContainerType	[OUT] 获得的容器类型。指针指向的值为0表示未定、尚未分配类型或者为空容器，为1表示为RSA容器，为2表示为ECC容器。
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_GetContainerType(UInt32 hContainer, ref UInt32 pulContainerType);

        /*
        向容器内导入数字证书
        hContainer	[IN] 容器句柄。
        bSignFlag	[IN] TRUE表示签名证书，FALSE表示加密证书
        pbCert		[IN] 证书缓冲区
        ulCertLen	[IN] 缓冲区长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ImportCertificate(UInt32 hContainer, Boolean bSignFlag, Byte[] pbCert, UInt32 ulCertLen);

        /*
        导出容器内的数字证书
        hContainer	[IN] 容器句柄。
        bSignFlag	[IN] TRUE表示签名证书，FALSE表示加密证书
        pbCert		[OUT] 证书缓冲区
        ulCertLen	[IN,OUT] 输入缓冲区长度，输出证书内容长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ExportCertificate(UInt32 hContainer, Boolean bSignFlag, Byte[] pbCert, ref UInt32 ulCertLen);

        /************************************************************************/
        /*  6. 密码服务	系列函数                                           */
        /*	SKF_GetRandom			        产生指定长度的随机数											*/
        /*	SKF_GenRSAKeyPair			    由设备生成RSA密钥对并明文输出									*/
        /*	SKF_ImportRSAKeyPair			导入RSA加密公私钥对									*/
        /*	SKF_RSASignData					使用hContainer指定容器的签名私钥，对指定数据pbData进行数字签名。签名后的结果存放到pbSignature缓冲区，设置pulSignLen为签名的长度									*/
        /*	SKF_RSAVerify														*/
        /*	SKF_RSAExportSessionKey												*/
        /*	SKF_GenECCKeyPair													*/
        /*	SKF_ImportECCKeyPair												*/
        /*	SKF_ECCSignData														*/
        /*	SKF_ECCVerify														*/
        /*	SKF_GenerateAgreementDataWithECC									*/
        /*	SKF_GenerateAgreementDataAndKeyWithECC								*/
        /*	SKF_GenerateKeyWithECC												*/
        /*	SKF_ECCExportSessionKey												*/
        /*	SKF_ExportPublicKey													*/
        /*	SKF_ImportSessionKey												*/
        /*	SKF_EncryptInit														*/
        /*	SKF_Encrypt															*/
        /*	SKF_EncryptUpdate													*/
        /*	SKF_EncryptFinal													*/
        /*	SKF_DecryptInit														*/
        /*	SKF_Decrypt															*/
        /*	SKF_DecryptUpdate													*/
        /*	SKF_DecryptFinal													*/
        /*	SKF_DigestInit														*/
        /*	SKF_Digest															*/
        /*	SKF_DigestUpdate													*/
        /*	SKF_DegistFinal														*/
        /*	SKF_MACInit															*/
        /*	SKF_MAC																*/
        /*	SKF_MACUpdate														*/
        /*	SKF_MACFinal														*/
        /*	SKF_CloseUInt32														*/
        /************************************************************************/

        /*
        *	产生指定长度的随机数
        *	hDev			[IN] 设备句柄
        *	pbRandom		[OUT] 返回的随机数
        *	ulRandomLen		[IN] 随机数长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_GenRandom(UInt32 hDev, Byte[] pbRandom, UInt32 ulRandomLen);

        /*
        *	由设备生成RSA密钥对并明文输出
        *	hDev			[IN] 设备句柄
        *	ulBitsLen		[IN] 密钥模长
        *	pBlob			[OUT] 返回的公钥数据结构
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_GenRSAKeyPair(UInt32 hContainer, UInt32 ulBitsLen, ref Struct_RSAPUBLICKEYBLOB pBlob);



        /*
        *	导入RSA加密公私钥对
        *	hContainer		[IN] 容器句柄
        *	ulSymAlgId		[IN] 对称算法密钥标识
        *	pbWrappedKey	[IN] 使用该容器内签名公钥保护的对称算法密钥
        *	ulWrappedKeyLen	[IN] 保护的对称算法密钥长度
        *	pbEncryptedData	[IN] 对称算法密钥保护的RSA加密私钥。私钥的格式遵循PKCS #1 v2.1: RSA Cryptography Standard中的私钥格式定义
        *	ulEncryptedDataLen	[IN] 对称算法密钥保护的RSA加密公私钥对长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ImportRSAKeyPair(UInt32 hContainer, UInt32 ulSymAlgId,
                                           Byte[] pbWrappedKey, UInt32 ulWrappedKeyLen,
                                           Byte[] pbEncryptedData, UInt32 ulEncryptedDataLen);

        /*
        *	使用hContainer指定容器的签名私钥，对指定数据pbData进行数字签名。签名后的结果存放到pbSignature缓冲区，设置pulSignLen为签名的长度
        *	hContainer		[IN] 用来签名的私钥所在容器句柄
        *	pbData			[IN] 被签名的数据
        *	ulDataLen		[IN] 签名数据长度，应不大于RSA密钥模长-11
        *	pbSignature		[OUT] 存放签名结果的缓冲区指针，如果值为NULL，用于取得签名结果长度
        *	pulSigLen		[IN,OUT] 输入为签名结果缓冲区大小，输出为签名结果长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_RSASignData(UInt32 hContainer, Byte[] pbData, UInt32 ulDataLen, Byte[] pbSignature,
ref UInt32 pulSignLen);



        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_RSASignEx(UInt32 hContainer, Boolean type, UInt32 ulHashAlgID, Byte[] pbData, UInt32 ulDataLen,
                        Byte[] pbSignature,ref UInt32 pulSignLen);
        /*
        *	验证RSA签名。用pRSAPubKeyBlob内的公钥值对待验签数据进行验签。
        *	hDev			[IN] 连接设备时返回的设备句柄
        *	pRSAPubKeyBlob	[IN] RSA公钥数据结构
        *	pbData			[IN] 待验证签名的数据
        *	ulDataLen		[IN] 数据长度，应不大于公钥模长-11
        *	pbSignature		[IN] 待验证的签名值
        *	ulSigLen		[IN] 签名值长度，必须为公钥模长
        */
        [DllImport("mtoken_gm3000_xjca.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern UInt32 SKF_RSAVerify(UInt32 hDev, ref Struct_RSAPUBLICKEYBLOB pRSAPubKeyBlob, Byte[] pbData, UInt32 ulDataLen, Byte[] pbSignature, UInt32 ulSignLen);


        [DllImport("mtoken_gm3000_xjca.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern UInt32 SKF_RSAVerifyEx(UInt32 hDev, Boolean bSignFlag, UInt32 ulHashAlgID, Byte[] pbData, UInt32 ulDataLen,
                        Byte[] pbSignature, UInt32 ulSignLen);

        /*
        *	生成会话密钥并用外部公钥加密输出。
        *	hContainer		[IN] 容器句柄
        *	ulAlgID			[IN] 会话密钥的算法标识
        *	pPubKey			[IN] 加密会话密钥的RSA公钥数据结构
        *	pbData			[OUT] 导出的加密会话密钥密文，按照PKCS#1v1.5的要求封装
        *	pulDataLen		[OUT] 返回导出数据长度
        *	phSessionKey	[OUT] 导出的密钥句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_RSAExportSessionKey(UInt32 hContainer, UInt32 ulAlgId, Byte[] pPubKey, Byte[] pbData, UInt32[] pulDataLen, UInt32[] phSessionKey);

        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ExtRSAPubKeyOperation(UInt32 hDev, ref Struct_RSAPUBLICKEYBLOB pRSAPubKeyBlob, Byte[] pbInput, UInt32 ulInputLen, Byte[] pbOutput, ref UInt32 pulOutputLen);

        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ExtRSAPriKeyOperation(UInt32 hDev, ref Struct_RSAPRIVATEKEYBLOB pRSAPriKeyBlob, Byte[] pbInput, UInt32 ulInputLen, Byte[] pbOutput, ref UInt32 pulOutputLen);


        /*
        *	直接使用外部传入的RSA公钥对输入数据做PKCS1加密运算并输出结果
        *	hDev			[IN] 设备句柄
        *	pRSAPubKeyBlob	[IN] RSA公钥数据结构
        *	pbInput			[IN] 指向待运算的原始数据缓冲区
        *	ulInputLen		[IN] 待运算原始数据的长度，必须为公钥模长
        *	pbOutput		[OUT] 指向RSA公钥运算结果缓冲区，如果该参数为NULL，则由pulOutputLen返回运算结果的实际长度
        *	pulOutputLen	[in, OUT] 调用前表示pbOutput缓冲区的长度，返回RSA公钥运算结果的实际长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ExtRSAEncrypt(UInt32 hDev, ref Struct_RSAPUBLICKEYBLOB pRSAPubKeyBlob, Byte[] pbInput, UInt32 ulInputLen, Byte[] pbOutput, ref UInt32 pulOutputLen);


        /*
        *	生成ECC签名密钥对并输出签名公钥。
        *	hContainer		[IN] 容器句柄
        *	只支持SGD_SM2_1算法
        *	pBlob			[OUT] 返回ECC公钥数据结构
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_GenECCKeyPair(UInt32 hContainer, UInt32 ulAlgId, ref Struct_ECCPUBLICKEYBLOB pBlob);

        /*
        *	导入ECC公私钥对
        *	hContainer		[IN] 容器句柄
        *	pbWrapedData	[IN] 加密保护的ECC加密公私钥对密文
        *	ulWrapedLen		[IN] 数据长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ImportECCKeyPair(UInt32 hContainer, ref Struct_ENVELOPEDKEYBLOB pEnvelopedKeyBlob);

        /*
        *	ECC数字签名。采用ECC算法和指定私钥hKey，对指定数据pbData进行数字签名。签名后的结果存放到pbSignature缓冲区，设置pulSignLen为签名值的长度
        *	hContainer		[IN] 用来签名的私钥所在容器句柄
        *	pbData			[IN] 被签名的数据
        *	ulDataLen		[IN] 待签名数据长度，必须小于密钥模长
        *	pbSignature		[OUT] 签名值，为NULL时用于获得签名值的长度
        *	pulSigLen		[IN,OUT] 返回签名值长度的指针 
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ECCSignData(UInt32 hContainer, Byte[] pbData, UInt32 ulDataLen, ref Struct_ECCSIGNATUREBLOB pSignature);

        /*
        *	用ECC公钥对数据进行验签
        *	hDev			[IN] 设备句柄
        *	pECCPubKeyBlob	[IN] ECC公钥数据结构
        *	pbData			[IN] 待验证签名的数据
        *	ulDataLen		[IN] 数据长度
        *	pbSignature		[IN] 待验证的签名值
        *	ulSigLen		[IN] 签名值长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ECCVerify(UInt32 hDev, ref Struct_ECCPUBLICKEYBLOB pECCPubKeyBlob, Byte[] pbData, UInt32 ulDataLen, ref Struct_ECCSIGNATUREBLOB pSignature);

        /*
        *	生成会话密钥并用外部公钥加密输出。
        *	hContainer		[IN] 容器句柄
        *	ulAlgID			[IN] 会话密钥的算法标识
        *	pPubKey			[IN] 用来导出密钥的密钥结构
        *	pbData			[OUT] 导出的加密会话密钥密文, 注意此处传入的长度要大于ECCCIPHERBLOB结构的长度，结构内含指针
        *	phSessionKey	[OUT] 会话密钥句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ECCExportSessionKey(UInt32 hContainer, UInt32 ulAlgId, Byte[] pPubKey, Byte[] pData, UInt32[] phSessionKey);


        /*
        *	使用ECC密钥协商算法，为计算会话密钥而产生协商参数，返回临时ECC密钥对的公钥及协商句柄
        *	hContainer		[IN] 容器句柄
        *	ulAlgId			[IN] 会话密钥算法标识
        *	pTempECCPubKeyBlob	[OUT] 发起方临时ECC公钥
        *	pbID			[IN] 发起方的ID
        *	ulIDLen			[IN] 发起方ID的长度，不大于32
        *	phAgreementUInt32	[OUT] 返回的密钥协商句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_GenerateAgreementDataWithECC(UInt32 hContainer, UInt32 ulAlgId, Byte[] pTempECCPubKeyBlob, Byte[] pbID, UInt32 ulIDLen, UInt32[] phAgreementUInt32);

        /*
        *	使用ECC密钥协商算法，产生协商参数并计算会话密钥，输出临时ECC密钥对公钥，并返回产生的密钥句柄
        *	hContainer					[IN] 容器句柄
        *	ulAlgId						[IN] 会话密钥算法标识
        *	pSponsorECCPubKeyBlob		[IN] 发起方的ECC公钥
        *	pSponsorTempECCPubKeyBlob	[IN] 发起方的临时ECC公钥
        *	pTempECCPubKeyBlob			[OUT] 响应方的临时ECC公钥
        *	pbID						[IN] 响应方的ID
        *	ulIDLen						[IN] 响应方ID的长度，不大于32
        *	pbSponsorID					[IN] 发起方的ID
        *	ulSponsorIDLen				[IN] 发起方ID的长度，不大于32
        *	phKeyUInt32					[OUT] 返回的对称算法密钥句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_GenerateAgreementDataAndKeyWithECC(
            String hContainer, UInt32 ulAlgId,
            Byte[] pSponsorECCPubKeyBlob,
            Byte[] pSponsorTempECCPubKeyBlob,
            Byte[] pTempECCPubKeyBlob,
            Byte[] pbID, UInt32 ulIDLen, Byte[] pbSponsorID, UInt32 ulSponsorIDLen,
            UInt32[] phKeyUInt32);

        /*
        *	使用ECC密钥协商算法，使用自身协商句柄和响应方的协商参数计算会话密钥，同时返回会话密钥句柄
        *	hAgreementUInt32			[IN] 密钥协商句柄
        *	pECCPubKeyBlob				[IN] 外部输入的响应方ECC公钥
        *	pTempECCPubKeyBlob			[IN] 外部输入的响应方临时ECC公钥
        *	pbID						[IN] 响应方的ID
        *	ulIDLen						[IN] 响应方ID的长度，不大于32
        *	phKeyUInt32					[OUT] 返回的密钥句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_GenerateKeyWithECC(UInt32 hAgreementUInt32,
                                             Byte[] pECCPubKeyBlob,
                                             Byte[] pTempECCPubKeyBlob,
                                             Byte[] pbID, UInt32 ulIDLen, UInt32[] phKeyUInt32);


        /*
        *	导出容器中的签名公钥或者加密公钥
        *	hContainer		[IN] 容器句柄
        *	bSignFlag		[IN] TRUE表示导出签名公钥，FALSE表示导出加密公钥
        *	pbBlob			[OUT] 指向RSA公钥结构（Byte[]）或者ECC公钥结构（ECCPUBLICKEYBLOB），如果此参数为NULL时，由pulBlobLen返回pbBlob的长度
        *	pulBlobLen		[IN,OUT] 调用时表示pbBlob的长度，返回导出公钥结构的大小
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ExportPublicKey(UInt32 hContainer, Boolean bSignFlag, Byte[] pbBlob, ref UInt32 pulBlobLen);

        /*
        *	导入会话密钥
        *	hDev			[IN] 设备句柄
        *	pECCPubKeyBlob	[IN] 加密使用的公钥
        *	pbPlainText		[IN] 要加密的数据
        *	ulPlainTextLen	[IN] 数据长度
        *	pCipherText		[OUT] 返回的密文
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ExtECCEncrypt(UInt32 hDev, ref Struct_ECCPUBLICKEYBLOB pECCPubKeyBlob,
                                       Byte[] pbPlainText, UInt32 ulPlainTextLen,
                                      ref Struct_ECCCIPHERBLOB pCipherText);

        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ECCPrvKeyDecryptEx(UInt32 hContainer, bool bSignFlag,ref Struct_ECCCIPHERBLOB pCipherText, byte[] pbData, ref UInt32 pbDataLen);
        //hCont[IN] 容器句柄
        //DigestMethod[IN] 摘要算法标识
        //pbId[IN] 用户ID
        //ulIdLen[IN] 用户ID长度
        //InData[IN] 待签名数据
        //ulInDataLen[IN] 待签名数据数据长度
        //ulDetached[IN] 是否带原文 1不带原文，0带原文
        //OutData[OUT] 签名后的数据缓冲区指针
        //OutDataLen[IN][OUT] 输入，给出的缓冲区大小；输出，返回签名后的数据长度
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_SignDataToPKCS7(UInt32 hContainer, UInt32 DigestMethod, byte[] pbId, UInt32 ulIdLen, byte[] InData, UInt32 ulInDataLen, UInt32 ulDetached, byte[] OutData, ref UInt32 OutDataLen);
        /*
        *	导入会话密钥
        *	hContainer		[IN] 容器句柄
        *	ulAlgID			[IN] 会话密钥的算法标识
        *	pbWrapedData	[IN] 要导入的数据
        *	ulWrapedLen		[IN] 数据长度
        *	phKey			[OUT] 返回会话密钥句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ImportSessionKey(UInt32 hContainer, UInt32 ulAlgId, Byte[] pbWrapedData, UInt32 ulWrapedLen,ref UInt32 phKey);


        /*
        *	数据加密初始化。设置数据加密的算法相关参数。
        *	hKey			[IN] 加密密钥句柄
        *	EncryptParam	[IN] 分组密码算法相关参数：算法标识号、密钥长度、初始向量、初始向量长度、填充方法、加密模式、反馈值的位长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_EncryptInit(UInt32 hKey, BLOCKCIPHERPARAM EncryptParam);

        /*
        *	单一分组数据的加密操作。
        用指定加密密钥对指定数据进行加密，被加密的数据只包含一个分组，加密后的密文保存到指定的缓冲区中。
        SKF_Encrypt只对单个分组数据进行加密，在调用SKF_Encrypt之前，必须调用SKF_EncryptInit初始化加密操作。
        SKF_Encypt等价于先调用SKF_EncryptUpdate再调用SKF_EncryptFinal。
        *	hKey			[IN] 加密密钥句柄
        *	pbData			[IN] 待加密数据
        *	ulDataLen		[IN] 待加密数据长度
        *	pbEncryptedData [OUT] 加密后的数据缓冲区指针
        *	pulEncryptedLen [IN,OUT] 输入，给出的缓冲区大小；输出，返回加密后的数据
        长度
        *	成功: SAR_OK
        *	失败: SAR_FAIL SAR_MEMORYERR SAR_UNKNOWNERR  SAR_INVALIDPARAMERR SAR_BUFFER_TOO_SMALL   
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_Encrypt(UInt32 hKey, Byte[] pbData, UInt32 ulDataLen, Byte[] pbEncryptedData, ref UInt32 pulEncryptedLen);


        /*
        *	多个分组数据的加密操作。
        用指定加密密钥对指定数据进行加密，被加密的数据包含多个分组，加密后的密文保存到指定的缓冲区中。
        SKF_EncryptUpdate对多个分组数据进行加密，在调用SKF_EncryptUpdate之前，必须调用SKF_EncryptInit初始化加密操作；
        在调用SKF_EncryptUpdate之后，必须调用SKF_EncryptFinal结束加密操作。
        *	hKey			[IN] 加密密钥句柄
        *	pbData			[IN] 待加密数据
        *	ulDataLen		[IN] 待加密数据长度
        *	pbEncryptedData [OUT] 加密后的数据缓冲区指针
        *	pulEncryptedLen [OUT] 返回加密后的数据长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_EncryptUpdate(UInt32 hKey, Byte[] pbData, UInt32 ulDataLen, Byte[] pbEncryptedData, Byte[] pulEncryptedLen);

        /*
        *	结束多个分组数据的加密，返回剩余加密结果。
        先调用SKF_EncryptInit初始化加密操作，
        再调用SKF_EncryptUpdate对多个分组数据进行加密，
        最后调用SKF_EncryptFinal结束多个分组数据的加密。
        *	hKey			[IN] 加密密钥句柄
        *	pbEncryptedData [OUT] 加密结果的缓冲区
        *	pulEncryptedLen [OUT] 加密结果的长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_EncryptFinal(UInt32 hKey, Byte[] pbEncryptedData, Byte[] ulEncryptedDataLen);

        /*
        *	数据解密初始化，设置解密密钥相关参数。
        调用SKF_DecryptInit之后，可以调用SKF_Decrypt对单个分组数据进行解密，
        也可以多次调用SKF_DecryptUpdate之后再调用SKF_DecryptFinal完成对多个分组数据的解密。
        *	hKey [IN] 解密密钥句柄
        *	DecryptParam [IN] 分组密码算法相关参数：算法标识号、密钥长度、初始向量、初始向量长度、填充方法、加密模式、反馈值的位长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_DecryptInit(UInt32 hKey, BLOCKCIPHERPARAM DecryptParam);

        /*
        *	单个分组数据的解密操作
        用指定解密密钥对指定数据进行解密，被解密的数据只包含一个分组，解密后的明文保存到指定的缓冲区中
        SKF_Decrypt只对单个分组数据进行解密，在调用SKF_Decrypt之前，必须调用SKF_DecryptInit初始化
        解密操作
        SKF_Decypt等价于先调用SKF_DecryptUpdate再调用SKF_DecryptFinal
        *	hKey			[IN] 解密密钥句柄
        *	pbEncryptedData [IN] 待解密数据
        *	ulEncryptedLen	[IN] 待解密数据长度
        *	pbData			[OUT] 指向解密后的数据缓冲区指针，当为NULL时可获得解密后的数据长度
        *	pulDataLen		[IN，OUT] 返回解密后的数据长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_Decrypt(UInt32 hKey, Byte[] pbEncryptedData, UInt32 ulEncryptedLen, Byte[] pbData, ref UInt32 pulDataLen);

        /*
        *	多个分组数据的解密操作。
        用指定解密密钥对指定数据进行解密，被解密的数据包含多个分组，解密后的明文保存到指定的缓冲区中。
        SKF_DecryptUpdate对多个分组数据进行解密，在调用SKF_DecryptUpdate之前，必须调用SKF_DecryptInit初始化解密操作；
        在调用SKF_DecryptUpdate之后，必须调用SKF_DecryptFinal结束解密操作。
        *	hKey			[IN] 解密密钥句柄
        *	pbEncryptedData [IN] 待解密数据
        *	ulEncryptedLen	[IN] 待解密数据长度
        *	pbData			[OUT] 指向解密后的数据缓冲区指针
        *	pulDataLen		[IN，OUT] 返回解密后的数据长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_DecryptUpdate(UInt32 hKey, Byte[] pbEncryptedData, UInt32 ulEncryptedLen, Byte[] pbData, Byte[] pulDataLen);

        /*
        *	结束多个分组数据的解密。
        *	hKey				[IN] 解密密钥句柄
        *	pbPlainText			[OUT] 指向解密结果的缓冲区，如果此参数为NULL时，由pulPlainTextLen返回解密结果的长度
        *	pulDecyptedDataLen	[IN，OUT] 调用时表示pbPlainText缓冲区的长度，返回解密结果的长度 
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_DecryptFinal(UInt32 hKey, Byte[] pbDecryptedData, Byte[] pulDecryptedDataLen);

        /*
        *	初始化消息杂凑计算操作，指定计算消息杂凑的算法。
        *	hDev			[IN] 连接设备时返回的设备句柄
        *	ulAlgID			[IN] 杂凑算法标识
        *	phHash			[OUT] 杂凑对象句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_DigestInit(UInt32 hDev, UInt32 ulAlgID, ref Struct_ECCPUBLICKEYBLOB pPubKey, Byte[] pucID, UInt32 ulIDLen, ref UInt32 phHash);


        /*
        *	对单一分组的消息进行杂凑计算。
        *	hHash			[IN] 杂凑对象句柄
        *	pbData			[IN] 指向消息数据的缓冲区
        *	ulDataLen		[IN] 消息数据的长度
        *	pbHashData		[OUT] 杂凑数据缓冲区指针，当此参数为NULL时，由pulHashLen返回杂凑结果的长度
        *	pulHashLen		[IN，OUT] 调用时表示pbHashData缓冲区的长度，返回杂凑结果的长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_Digest(UInt32 hHash, Byte[] pbData, UInt32 ulDataLen, Byte[] pbHashData, ref UInt32 pulHashLen);
        /*
        *	对多个分组的消息进行杂凑计算。
        *	hHash			[IN] 杂凑对象句柄
        *	pbPart			[IN] 指向消息数据的缓冲区
        *	ulPartLen		[IN] 消息数据的长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_DigestUpdate(UInt32 hHash, Byte[] pbData, UInt32 ulDataLen);
        /*
        *	结束多个分组消息的杂凑计算操作，将杂凑保存到指定的缓冲区。
        *	hHash			[IN] 哈希对象句柄
        *	pHashData		[OUT] 返回的杂凑数据缓冲区指针，如果此参数NULL时，由pulHashLen返回杂凑结果的长度
        *	pulHashLen		[IN，OUT] 调用时表示杂凑结果的长度，返回杂凑数据的长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_DigestFinal(UInt32 hHash, Byte[] pHashData, ref UInt32 pulHashLen);

        /*
        *	初始化消息认证码计算操作，设置计算消息认证码的密钥参数，并返回消息认证码句柄。
        *	hKey			[IN] 计算消息认证码的密钥句柄
        *	MacParam		[IN] 消息认证计算相关参数，包括初始向量、初始向量长度、填充方法等
        *	phMac			[OUT] 消息认证码对象句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]

        public static extern UInt32 SKF_MacInit(UInt32 hKey, Byte[] pMacParam, UInt32[] phMac);

        /*
        *	SKF_Mac计算单一分组数据的消息认证码。
        *	hMac			[IN] 消息认证码句柄
        *	pbData			[IN] 指向待计算数据的缓冲区
        *	ulDataLen		[IN] 待计算数据的长度
        *	pbMacData		[OUT] 指向计算后的Mac结果，如果此参数为NULL时，由pulMacLen返回计算后Mac结果的长度
        *	pulMacLen		[IN，OUT] 调用时表示pbMacData缓冲区的长度，返回计算Mac结果的长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_Mac(UInt32 hMac, Byte[] pbData, UInt32 ulDataLen, Byte[] pbMacData, Byte[] pulMacLen);
        /*
        *	计算多个分组数据的消息认证码。
        *	hMac			[IN] 消息认证码句柄
        *	pbData			[IN] 指向待计算数据的缓冲区
        *	plDataLen		[IN] 待计算数据的长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_MacUpdate(UInt32 hMac, Byte[] pbData, UInt32 ulDataLen);
        /*
        *	结束多个分组数据的消息认证码计算操作
        *	hMac			[IN] 消息认证码句柄
        *	pbMacData		[OUT] 指向消息认证码的缓冲区，当此参数为NULL时，由pulMacDataLen返回消息认证码返回的长度
        *	pulMacDataLen	[OUT] 调用时表示消息认证码缓冲区的最大长度，返回消息认证码的长度
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_MacFinal(UInt32 hMac, Byte[] pbMacData, Byte[] pulMacDataLen);
        /*
        *	关闭会话密钥、杂凑、消息认证码句柄。
        *	hUInt32			[IN] 要关闭的对象句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_CloseUInt32(UInt32 hUInt32);

        [DllImport("mtoken_gm3000_xjca.dll")]
        public static extern UInt32 SKF_ImportExtECCKeyPair(UInt32 hContainer, bool bSignFlag,ref Struct_ECCPUBLICKEYBLOB sm2PubKey, ref Struct_ECCPRIVATEKEYBLOB sm2PriKey);
        /*****************************以下为方便用户使用所提供的补充API********************************************/

        /*
        *	设置明文对称密钥，返回密钥句柄
        *	hDev			[IN] 设备句柄
        *	pbKey			[IN] 指向会话密钥值的缓冲区
        *	ulAlgID			[IN] 会话密钥的算法标识
        *	phKey			[OUT] 返回会话密钥句柄
        */
        [DllImport("mtoken_gm3000_xjca.dll")]

        public static extern UInt32 SKF_SetSymmKey(UInt32 hDev, Byte[] pbKey, UInt32 ulAlgID, ref UInt32 phKey);

        [DllImport("mtoken_gm3000_finger.dll")]
        public static extern UInt32 SKF_QueryContainerFinger(UInt32 hApplication, UInt32 ulPINType, ref UInt32 pulFingerId,
    Byte[] Description, StringBuilder ContainerName, ref bool bSign);
        //
        [DllImport("mtoken_gm3000_finger.dll")]
        public static extern UInt32 SKF_VerifyContainerFinger(UInt32 hApplication, UInt32 ulPINType,
        UInt32 hContainer, UInt32 bSign, ref UInt32[] pulLeftTimes);

        //0x0A  --  0A
        public static String byteHEX(Byte ib)
        {
            String _str = String.Empty;
            try
            {
                char[] Digit = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A',
                'B', 'C', 'D', 'E', 'F' };
                char[] ob = new char[2];
                ob[0] = Digit[(ib >> 4) & 0X0F];
                ob[1] = Digit[ib & 0X0F];
                _str = new String(ob);
            }
            catch (Exception)
            {
                new Exception("非法数据，转换有误！");
            }
            return _str;
        }

        //0x0A0B  --  0A0B
        public static string ToHexString(byte[] bytes)
        {
            String hexString = String.Empty;
            for (int i = 0; i < bytes.Length; i++)
                hexString += byteHEX(bytes[i]);

            return hexString;
        }

        public static void RSAKey(out string xmlKeys, out string xmlPublicKey)
        {
            try
            {
                System.Security.Cryptography.RSACryptoServiceProvider rsa = new RSACryptoServiceProvider();

                xmlKeys = rsa.ToXmlString(true);
                xmlPublicKey = rsa.ToXmlString(false);
            }
            catch (Exception ex)
            {
                throw new ArgumentOutOfRangeException("不支持此格式!");
            }
        }


        ////操作
        //public static byte[] GetXmlNodeInformation(string privateKey, string publicKey)
        //{
        //    try
        //    //{
        //    //    //定义并从xml文件中加载节点（根节点）
        //    //    XElement privateKeyNode = XElement.Parse(privateKey);
        //    //    XElement publicKeyNode = XElement.Parse(publicKey);
        //    //    Struct_RSAPRIVATEKEYBLOB rsa = new Struct_RSAPRIVATEKEYBLOB();
        //    //    rsa.AlgID = 0x00010000;
        //    //    rsa.BitLen = 1024;
        //    //    rsa.Modulus = Convert.FromBase64String(privateKeyNode.Element("Modulus").Value);
        //    //    rsa.PublicExponent = Convert.FromBase64String(privateKeyNode.Element("Exponent").Value);
        //    //    rsa.PrivateExponent = Convert.FromBase64String(privateKeyNode.Element("D").Value);
        //    //    rsa.Prime1 = Convert.FromBase64String(privateKeyNode.Element("P").Value);
        //    //    rsa.Prime2 = Convert.FromBase64String(privateKeyNode.Element("Q").Value);
        //    //    rsa.Prime1Exponent = Convert.FromBase64String(privateKeyNode.Element("DP").Value);
        //    //    rsa.Prime2Exponent = Convert.FromBase64String(privateKeyNode.Element("DQ").Value);
        //    //    rsa.Coefficient = Convert.FromBase64String(privateKeyNode.Element("InverseQ").Value);


        //    //    byte[] AlgID = System.BitConverter.GetBytes(rsa.AlgID);
        //    //    byte[] BitLen = System.BitConverter.GetBytes(rsa.BitLen);
        //    //    byte[] privateKeyValue = new byte[2048];

        //    //    //COPY ---> privateKeyValue 
        //    //    AlgID.CopyTo(privateKeyValue, 0);  //ID
        //    //    BitLen.CopyTo(privateKeyValue, 4); // LEN
        //    //    rsa.Modulus.CopyTo(privateKeyValue, 136); //Modulus
        //    //    rsa.PublicExponent.CopyTo(privateKeyValue, 264); //E
        //    //    rsa.PrivateExponent.CopyTo(privateKeyValue, 396); //D
        //    //    rsa.Prime1.CopyTo(privateKeyValue, 588);
        //    //    rsa.Prime2.CopyTo(privateKeyValue, 716);
        //    //    rsa.Prime1Exponent.CopyTo(privateKeyValue, 844);
        //    //    rsa.Prime2Exponent.CopyTo(privateKeyValue, 972);
        //    //    rsa.Coefficient.CopyTo(privateKeyValue, 1100);
        //    //    Array.Resize(ref privateKeyValue, 1164);
        //    //    return privateKeyValue;

        //    }
        //    catch (Exception ex)
        //    {
        //        throw new ArgumentOutOfRangeException("xml格式问题!");
        //        return null;

        //    }
        //}


        //处理RSA公钥
        public static Struct_RSAPUBLICKEYBLOB GetRsaPublicKey(byte[] pblo)
        {
            try
            {
                SKFApi.Struct_RSAPUBLICKEYBLOB rsaPublickey = new Struct_RSAPUBLICKEYBLOB();
                byte[] algid = new byte[4];
                byte[] bitLen = new byte[4];
                byte[] modules = new byte[256];
                byte[] exponent = new byte[4];
                Array.Copy(pblo, 0, algid, 0, 4);
                Array.Copy(pblo, 4, bitLen, 0, 4);
                Array.Copy(pblo, 8, modules, 0, 256);
                Array.Copy(pblo, 264, exponent, 0, 4);
                rsaPublickey.AlgID = BitConverter.ToUInt32(algid, 0);
                rsaPublickey.BitLen = BitConverter.ToUInt32(bitLen, 0);
                rsaPublickey.Modulus = modules;
                rsaPublickey.PublicExponent = exponent;
                return rsaPublickey;
            }
            catch (Exception ex)
            {

                throw new ArgumentOutOfRangeException("不支持此格式!");
            }


        }
        //处理ECC公钥
        public static Struct_ECCPUBLICKEYBLOB GetEccPublicKey(byte[] pblo)
        {
            try
            {
                UInt32 bitlen = 256;
                Struct_ECCPUBLICKEYBLOB eccPublickey = new Struct_ECCPUBLICKEYBLOB();
                byte[] bitLen = new byte[4];
                byte[] x = new byte[64];
                byte[] y = new byte[64];
                if (pblo.Length == 128) //带填充的 0，没有bitLen
                {
                    Array.Copy(pblo, 0, x, 0, 64);
                    Array.Copy(pblo, 64, y, 0, 64);
                    eccPublickey.BitLen = bitlen;
                    eccPublickey.XCoordinate = x;
                    eccPublickey.YCoordinate = y;
                
                }
                else if (pblo.Length == 132) 
                {
                    Array.Copy(pblo, 0, bitLen, 0, 4);
                    Array.Copy(pblo, 4, x, 0, 64);
                    Array.Copy(pblo, 68, y, 0, 64);
                    eccPublickey.BitLen = BitConverter.ToUInt32(bitLen, 0);
                    eccPublickey.XCoordinate = x;
                    eccPublickey.YCoordinate = y;
        
                }
                else if(pblo.Length == 64) //只有 XY
                {
                    Array.Copy(pblo, 0, x, 32, 32);
                    Array.Copy(pblo, 32, y, 32, 32);
                    eccPublickey.BitLen = bitlen;
                    eccPublickey.XCoordinate = x;
                    eccPublickey.YCoordinate = y;
                   

                }
                else
                {
                    throw new ArgumentOutOfRangeException("不支持此格式");
                }
                return eccPublickey;

            }
            catch (Exception ex)
            {

                throw new ArgumentOutOfRangeException("不支持此格式");
            }


        }
        //处理外部公钥格式


    }
}
