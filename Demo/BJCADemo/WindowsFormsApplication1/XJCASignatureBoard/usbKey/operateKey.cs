using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
namespace XJCAServiceslib
{
    class operateKey
    {

        private UInt32 pDev;
        private UInt32 pApp;
        private UInt32 pCon;
        private UInt32 rtn;
        private string err;
        public operateKey()
        {

        }

        /// <summary>
        /// 返回设备序列号 &为分割符
        /// </summary>
        /// <returns></returns>
        public string[] SOF_GetUserList()
        {
            UInt32 pulSize = 255;
            byte[] szNameList = new byte[255];
            rtn = SKFApi.SKF_EnumDev(true, szNameList, ref pulSize);
            if (rtn != 0)
            {
                err = "SKF_EnumDev err";
                return null;
            }
            string[] NameList = getStringName(szNameList);
            return NameList;
        }
        /// <summary>
        /// 导出证书
        /// </summary>
        /// <param name="CertID"></param>
        /// <returns></returns>
        public byte[] SOF_ExportUserCert(string CertID, bool type)
        {
            if (!OpenContainer(CertID))
            {
                return null;
            }
            string result = "";
            byte[] pbCert = null;
            UInt32 pbCertlENGTH = 2048;
            rtn = SKFApi.SKF_ExportCertificate(pCon, type, pbCert, ref pbCertlENGTH);
            pbCert = new byte[pbCertlENGTH];
            rtn = SKFApi.SKF_ExportCertificate(pCon, type, pbCert, ref pbCertlENGTH);

            if (rtn != 0)
            {
                err = "SKF_ExportCertificate err";
                return null;
            }

            return pbCert;
        }

        public bool SOF_Login(string CertID, string pass)
        {
            if (!OpenApplication(CertID))
            {
                return false;
            }
            StringBuilder upin = new StringBuilder();
            upin.Append(pass);
            UInt32 pulRetryCOunt = 10;
            rtn = SKFApi.SKF_VerifyPIN(pApp, 1, upin, ref pulRetryCOunt);
            if (rtn != 0)
            {
                err = "SKF_VerifyPIN err";
                return false;
            }

            return true;
        }

        public bool SOF_Verify(string CertID, string SM3Data, string base64DER)
        {
            if (!OpenContainer(CertID))
            {
                return false;
            }
            byte[] pbData = Convert.FromBase64String(SM3Data);
            UInt32 pbDataLen = 32;//模长为 256/8

            SKFApi.Struct_ECCPUBLICKEYBLOB publickey = new SKFApi.Struct_ECCPUBLICKEYBLOB();
            byte[] pbpublickey = new byte[132];
            UInt32 pulBlobLen = 1024;
            rtn = SKFApi.SKF_ExportPublicKey(pCon, true, pbpublickey, ref pulBlobLen);
            if (rtn != 0)
            {
                err = "SKF_ExportPublicKey err";
                return false;
            }
            //处理公钥
            publickey.BitLen = 256;
            byte[] xPub = new byte[pulBlobLen];
            byte[] yPub = new byte[pulBlobLen];
            Array.Copy(pbpublickey, 4, xPub, 0, 64);
            Array.Copy(pbpublickey, 68, yPub, 0, 64);
            publickey.XCoordinate = xPub;
            publickey.YCoordinate = yPub;

            byte[] srcBse64 = Convert.FromBase64String(base64DER);

            CertHelp.RAndS ItemRS = CertHelp.DER2RS(srcBse64, srcBse64.Length);
            SKFApi.Struct_ECCSIGNATUREBLOB VerifySignature = new SKFApi.Struct_ECCSIGNATUREBLOB();
            byte[] V_RS128 = new byte[128];

            Array.Copy(ItemRS.R, 0, V_RS128, 32, 32);
            Array.Copy(ItemRS.S, 0, V_RS128, 96, 32);

            VerifySignature = (SKFApi.Struct_ECCSIGNATUREBLOB)SKFApi.BytesToStruct(V_RS128, VerifySignature.GetType());


            string txtSM2SignData = Convert.ToBase64String(SKFApi.StructToBytes(VerifySignature));

            rtn = SKFApi.SKF_ECCVerify(pDev, ref publickey, pbData, pbDataLen, ref VerifySignature);
            return rtn == 0 ? true : false;
        }

        public string SKF_SignData(string CertID, string src)
        {

            if (!OpenContainer(CertID))
            {
                return "";
            }
            SKFApi.Struct_ECCPUBLICKEYBLOB publickey = new SKFApi.Struct_ECCPUBLICKEYBLOB();
            byte[] pbpublickey = new byte[132];
            UInt32 pulBlobLen = 1024;
            rtn = SKFApi.SKF_ExportPublicKey(pCon, true, pbpublickey, ref pulBlobLen);
            if (rtn != 0)
            {
                err = "SKF_ExportPublicKey err";
                return "";
            }

            //处理公钥
            publickey.BitLen = 256;
            byte[] xPub = new byte[pulBlobLen];
            byte[] yPub = new byte[pulBlobLen];
            Array.Copy(pbpublickey, 4, xPub, 0, 64);
            Array.Copy(pbpublickey, 68, yPub, 0, 64);
            publickey.XCoordinate = xPub;
            publickey.YCoordinate = yPub;
            byte[] pucID = Encoding.UTF8.GetBytes("1234567812345678");
            UInt32 phHash = 1024;
            rtn = SKFApi.SKF_DigestInit(pDev, SKFApi.SGD_SM3, ref publickey, pucID, 16, ref phHash);
            if (rtn != 0)
            {

                err = "SKF_DigestInit err";
                return ""; ;
            }
            byte[] data = Encoding.UTF8.GetBytes(src);
            byte[] pbHashData = new byte[32];
            UInt32 pulHashLen = 32;
            rtn = SKFApi.SKF_Digest(phHash, data, (uint)data.Length, pbHashData, ref pulHashLen);
            if (rtn != 0)
            {

                err = "SKF_Digest err";
                return "";

            }
            SKFApi.Struct_ECCSIGNATUREBLOB pSignature = new SKFApi.Struct_ECCSIGNATUREBLOB();

            //*签名
            rtn = SKFApi.SKF_ECCSignData(pCon, pbHashData, pulHashLen, ref pSignature);
            byte[] pSignatureByte = SKFApi.StructToBytes(pSignature);

            if (rtn != 0)
            {
                err = "SKF_ECCSignData err";
                return "";
            }
            byte[] R = new byte[32];
            byte[] S = new byte[32];
            Array.Copy(pSignatureByte, 32, R, 0, 32);
            Array.Copy(pSignatureByte, 96, S, 0, 32);

            byte[] strSignTure = CertHelp.RS2DER(R, S);
            string base64DER = Convert.ToBase64String(strSignTure);

            return base64DER;
        }

        public string SOF_SM3Data(string CertID, string src)
        {
            if (!OpenContainer(CertID))
            {
                return "";
            }
            SKFApi.Struct_ECCPUBLICKEYBLOB publickey = new SKFApi.Struct_ECCPUBLICKEYBLOB();
            byte[] pbpublickey = new byte[132];
            UInt32 pulBlobLen = 1024;
            rtn = SKFApi.SKF_ExportPublicKey(pCon, true, pbpublickey, ref pulBlobLen);
            if (rtn != 0)
            {
                err = "SKF_ExportPublicKey err";
                return "";
            }

            //处理公钥
            publickey.BitLen = 256;
            byte[] xPub = new byte[pulBlobLen];
            byte[] yPub = new byte[pulBlobLen];
            Array.Copy(pbpublickey, 4, xPub, 0, 64);
            Array.Copy(pbpublickey, 68, yPub, 0, 64);
            publickey.XCoordinate = xPub;
            publickey.YCoordinate = yPub;
            byte[] pucID = Encoding.UTF8.GetBytes("1234567812345678");
            UInt32 phHash = 1024;
            rtn = SKFApi.SKF_DigestInit(pDev, SKFApi.SGD_SM3, ref publickey, pucID, 16, ref phHash);
            if (rtn != 0)
            {

                err = "SKF_DigestInit err";
                return ""; ;
            }
            byte[] data = Encoding.UTF8.GetBytes(src);
            byte[] pbHashData = new byte[32];
            UInt32 pulHashLen = 32;
            rtn = SKFApi.SKF_Digest(phHash, data, (uint)data.Length, pbHashData, ref pulHashLen);
            if (rtn != 0)
            {

                err = "SKF_Digest err";
                return "";

            }
            return Convert.ToBase64String(pbHashData);

        }
        public string SOF_SignDataToPKCS7(string CertID, string src)
        {

            if (!OpenContainer(CertID))
            {
                return "";
            }

            byte[] pucID = Encoding.UTF8.GetBytes("1234567812345678");
            byte[] data = Encoding.UTF8.GetBytes(src);
            uint SM3 = 1;
            uint Soriginal = 0;
            byte[] pbP7SignTureData = new byte[2048];
            UInt32 pulpbP7SignTureDataLen = 2048;
            //*签名
            rtn = SKFApi.SKF_SignDataToPKCS7(pCon, SM3, pucID, 16, data, (uint)data.Length, Soriginal, pbP7SignTureData, ref pulpbP7SignTureDataLen);
            if (rtn != 0)
            {
                err = "SKF_SignDataToPKCS7 err";
                return "";
            }
            byte[] strSignTure = new byte[pulpbP7SignTureDataLen];
            Array.Copy(pbP7SignTureData, 0, strSignTure, 0, pulpbP7SignTureDataLen);
            string base64DER = Convert.ToBase64String(strSignTure);

            return base64DER;

        }
        public string SOF_SignData(string CertID, string SM3src)
        {
            if (!OpenContainer(CertID))
            {
                return "";
            }
            byte[] pbData = Convert.FromBase64String(SM3src);
            UInt32 pbDataLen = 32;//模长为 256/8
            SKFApi.Struct_ECCSIGNATUREBLOB pSignature = new SKFApi.Struct_ECCSIGNATUREBLOB();

            //*签名
            rtn = SKFApi.SKF_ECCSignData(pCon, pbData, pbDataLen, ref pSignature);
            byte[] pSignatureByte = SKFApi.StructToBytes(pSignature);

            if (rtn != 0)
            {
                err = "SKF_ECCSignData err";
                return "";
            }
            byte[] R = new byte[32];
            byte[] S = new byte[32];
            Array.Copy(pSignatureByte, 32, R, 0, 32);
            Array.Copy(pSignatureByte, 96, S, 0, 32);

            byte[] strSignTure = CertHelp.RS2DER(R, S);
            string base64DER = Convert.ToBase64String(strSignTure);

            string txtSM2SignData = Convert.ToBase64String(SKFApi.StructToBytes(pSignature));
            return base64DER;
        }

        private bool OpenApplication(string CertID)
        {
            bool result = false;
            UInt32 pulSize = 1024;
            rtn = SKFApi.SKF_ConnectDev(CertID, ref pDev);
            if (rtn != 0)
            {
                err = "SKF_ConnectDev err";
                return result;
            }
            pulSize = 1024;
            byte[] szAppName = new byte[2048];
            rtn = SKFApi.SKF_EnumApplication(pDev, szAppName, ref pulSize);
            if (rtn != 0)
            {
                err = "SKF_EnumApplication err";
                return result;

            }
            string[] appName = getStringName(szAppName);
            rtn = SKFApi.SKF_OpenApplication(pDev, appName[0], ref pApp);
            if (rtn != 0)
            {

                err = "SKF_OpenApplication err";
                return result;
            }
            return true;

        }
        private bool OpenContainer(string CertID)
        {
            bool result = false;
            UInt32 pulSize = 1024;
            if (!OpenApplication(CertID))
            {
                err = "SKF_OpenApplication err";
                return result;
            }

            byte[] szContainerName = new byte[1024];
            pulSize = 1024;
            rtn = SKFApi.SKF_EnumContainer(pApp, szContainerName, ref pulSize);
            if (rtn != 0)
            {
                err = "SKF_EnumContainer err";
                return result;

            }
            string conName = getStringName(szContainerName)[0];
   
       
            rtn = SKFApi.SKF_OpenContainer(pApp, conName, ref pCon);
            if (rtn != 0)
            {
                err = "SKF_OpenContainer err";
                return result;
            }

            return true;

        }

        private bool CreateContainer(string CertID)
        {
            bool result = false;
            UInt32 pulSize = 1024;
            if (!OpenApplication(CertID))
            {
                err = "SKF_OpenApplication err";
                return result;
            }
            byte[] szContainerName = new byte[1024];
            pulSize = 1024;
            rtn = SKFApi.SKF_EnumContainer(pApp, szContainerName, ref pulSize);
            if (rtn != 0)
            {
                err = "SKF_EnumContainer err";
                return result;

            }
            string conName = getStringName(szContainerName)[0];
            if (pulSize == 0)
            {
                StringBuilder upin = new StringBuilder();
                upin.Append("12345678");
                UInt32 pulRetryCOunt = 10;
                rtn = SKFApi.SKF_VerifyPIN(pApp, 1, upin, ref pulRetryCOunt);
                StringBuilder contName = new StringBuilder();
                contName.Append("xjca");
                rtn = SKFApi.SKF_CreateContainer(pApp, contName, ref pCon);
                if (rtn != 0)
                {
                    err = "SKF_CreateContainer err";
                    return result;

                }
                conName = contName.ToString();
            }
            rtn = SKFApi.SKF_OpenContainer(pApp, conName, ref pCon);
            if (rtn != 0)
            {
                err = "SKF_OpenContainer err";
                return result;
            }

            return true;
        }
        public void test(string CertID)
        {
            StringBuilder szNameList = new StringBuilder(256);
            UInt32 pulSize = 1024;

            rtn = SKFApi.SKF_ConnectDev(CertID, ref pDev);
            if (rtn != 0)
            {
                messageOut("SKF_ConnectDev", rtn);
                return;
            }
            messageOut("SKF_ConnectDev Success,\n szNameList = ", szNameList.ToString());

            pulSize = 1024;
            byte[] szAppName = new byte[2048];
            rtn = SKFApi.SKF_EnumApplication(pDev, szAppName, ref pulSize);
            if (rtn != 0)
            {
                messageOut("SKF_EnumApplication", rtn);
                return;

            }
            string[] appName = getStringName(szAppName);
            messageOut("AppName = ", appName[0]);
            rtn = SKFApi.SKF_OpenApplication(pDev, appName[0], ref pApp);
            if (rtn != 0)
            {
                messageOut("SKF_OpenApplication", rtn);
                return;
            }
            messageOut("SKF_OpenApplication ");

            byte[] szContainerName = new byte[1024];
            pulSize = 1024;

            rtn = SKFApi.SKF_EnumContainer(pApp, szContainerName, ref pulSize);
            if (rtn != 0)
            {
                messageOut("SKF_EnumContainer", rtn);
                return;
            }
            string[] conName = getStringName(szContainerName);
            messageOut("conName = ", conName[0]);

            rtn = SKFApi.SKF_OpenContainer(pApp, conName[0], ref pCon);
            if (rtn != 0)
            {
                messageOut("SKF_OpenContainer", rtn);
                return;
            }
            messageOut("SKF_OpenContainer ");

            SKFApi.Struct_ECCPUBLICKEYBLOB publickey = new SKFApi.Struct_ECCPUBLICKEYBLOB();
            byte[] pbpublickey = new byte[132];
            UInt32 pulBlobLen = 1024;
            rtn = SKFApi.SKF_ExportPublicKey(pCon, true, pbpublickey, ref pulBlobLen);
            if (rtn != 0)
            {
                messageOut("SKF_ExportPublicKey", rtn);
                return;
            }

            string pin = "123456";
            StringBuilder upin = new StringBuilder();
            upin.Append(pin);
            UInt32 pulRetryCOunt = 10;
            rtn = SKFApi.SKF_VerifyPIN(pApp, 1, upin, ref pulRetryCOunt);
            if (rtn != 0)
            {
                messageOut("SKF_VerifyPIN", rtn);
                return;
            }
            messageOut("SKF_VerifyPIN ");
            //处理公钥
            publickey.BitLen = 256;
            //for (int i = 0; i < 64; i++)
            //{
            //    pbpublickey[i + 4] = publickey.XCoordinate[i];
            //    pbpublickey[i + 68] = publickey.YCoordinate[i];
            //}
            byte[] xPub = new byte[pulBlobLen];
            byte[] yPub = new byte[pulBlobLen];
            //Array.Copy(pbpublickey, 0, publickey.XCoordinate, 0, 64);
            //Array.Copy(pbpublickey, 0, publickey.YCoordinate, 0, 64);
            Array.Copy(pbpublickey, 4, xPub, 0, 64);
            Array.Copy(pbpublickey, 68, yPub, 0, 64);
            publickey.XCoordinate = xPub;
            publickey.YCoordinate = yPub;
            byte[] pucID = Encoding.Default.GetBytes("1234567812345678");
            UInt32 phHash = 1024;
            rtn = SKFApi.SKF_DigestInit(pDev, SKFApi.SGD_SM3, ref publickey, pucID, 16, ref phHash);
            if (rtn != 0)
            {
                messageOut("SKF_DigestInit", rtn);
                return;
            }
            byte[] data = Encoding.Default.GetBytes("12345678");
            byte[] pbHashData = new byte[1024];
            UInt32 pulHashLen = 1024;
            rtn = SKFApi.SKF_Digest(phHash, data, 8, pbHashData, ref pulHashLen);
            if (rtn != 0)
            {
                messageOut("SKF_Digest", rtn);
                return;
            }
            messageOut("SKF_Digest");

            byte[] sigData = new byte[pulHashLen];
            Array.Copy(pbHashData, 0, sigData, 0, pulHashLen);
            SKFApi.Struct_ECCSIGNATUREBLOB pSignature = new SKFApi.Struct_ECCSIGNATUREBLOB();

            rtn = SKFApi.SKF_ECCSignData(pCon, sigData, pulHashLen, ref pSignature);
            rtn = SKFApi.SKF_ECCVerify(pDev, ref publickey, sigData, pulHashLen, ref pSignature);
            if (rtn != 0)
            {
                messageOut("SKF_ECCSignData", rtn);
                return;
            }
        }

        private void messageOut(string v)
        {

        }

        private void messageOut(string v, object p)
        {

        }


        private string[] getStringName(byte[] name)
        {
            string appName = Encoding.UTF8.GetString(name);
            string[] sArray = Regex.Split(appName, "\0", RegexOptions.IgnoreCase);
            return sArray;
        }







        /// <summary>
        /// 导入数字证书到key
        /// </summary>
        /// <param name="CertID">设备id</param>
        /// <param name="sign_cert">签名证书</param>
        /// <param name="enc_cert">加密证书</param>
        /// <returns></returns>
        public int SOF_ImportUserCer(string CertID,  byte[] sign_cert, byte[] enc_cert)
        {
          
            int rec = 0;
            if (!CreateContainer(CertID))
            {
                return 1;
            }

            rtn = SKFApi.SKF_ImportCertificate(pCon, false, enc_cert, (UInt32)enc_cert.Length);
            if (rtn != 0)
            {
                err = "SKF_ExportCertificate err";
                return 2;
            }
            rtn = SKFApi.SKF_ImportCertificate(pCon, true, sign_cert, (UInt32)sign_cert.Length);

            if (rtn != 0)
            {
                err = "SKF_ExportCertificate err";
                return 2;
            }
            return rec;
        }
        /// <summary>
        /// SM4CBC对称加密
        /// </summary>
        /// <param name="对称密钥"></param>
        /// <param name="原文"></param>
        /// <returns></returns>
            
        public byte[] SM4_CBC_Encrypt(byte[] redomKEY,string SRC)
        {
            SKFApi.BLOCKCIPHERPARAM bp = new SKFApi.BLOCKCIPHERPARAM();
            bp.IV = System.Text.Encoding.UTF8.GetBytes("12345678123456781234567812345678");
            bp.IVLen = 16;
            bp.PaddingType = 1;
            bp.FeedBitLen = 0;
          
            if (pDev == 0)
            {
                MessageBox.Show("请先连接设备！");
                return null;
            }
            UInt32 phKey = 10;
            rtn = SKFApi.SKF_SetSymmKey(pDev, redomKEY, SKFApi.SASGD_SM4_CBCR_OK, ref phKey);
            if (rtn != 0)
            {
                MessageBox.Show("SKF_SetSymmKey Error:" + rtn.ToString("x8"));
                return null;
            }  
            rtn = SKFApi.SKF_EncryptInit(phKey, bp);
            if (rtn != 0)
            {
                MessageBox.Show("SKF_EncryptInit Error:" + rtn.ToString("x8"));
                return null;
            }

            byte[] pData = System.Text.Encoding.UTF8.GetBytes(SRC);

            byte[] pbEncrypt = new byte[256];
            UInt32 ulEncryptLen = 256;
            rtn = SKFApi.SKF_Encrypt(phKey, pData, (UInt32)pData.Length, pbEncrypt, ref ulEncryptLen);
            if (rtn != 0)
            {
                MessageBox.Show("SKF_Encrypt Error:" + rtn.ToString("x8"));
                return null;
            }

            byte[] pbDataEnByte = new byte[ulEncryptLen];
            Array.Copy(pbEncrypt, 0, pbDataEnByte, 0, ulEncryptLen);
   
             return pbDataEnByte;
        }
        /// <summary>
        /// SM4CBC对称解密
        /// </summary>
        /// <param name="对称密钥"></param>
        /// <param name="密文"></param>
        /// <returns></returns>
        public string SM4_CBC_Decrypt(byte[] pbKey,string en)
        {
            SKFApi.BLOCKCIPHERPARAM blockCipherpAram = new SKFApi.BLOCKCIPHERPARAM();
            blockCipherpAram.IV = Encoding.UTF8.GetBytes("12345678123456781234567812345678");
            blockCipherpAram.IVLen = 16;
            blockCipherpAram.PaddingType = 1;//填充方式，0表示不填充，1表示按照PKCS#5方式进行填充
            blockCipherpAram.FeedBitLen = 0;
            //对称会话密钥
         
            UInt32 phKey = 0;
            if (pDev == 0)
            {
                MessageBox.Show("请先连接设备！");
                return null;
            }
         
            rtn = SKFApi.SKF_SetSymmKey(pDev, pbKey, SKFApi.SASGD_SM4_CBCR_OK, ref phKey);
            if (rtn != 0)
            {
                MessageBox.Show("SKF_SetSymmKey Error:" + rtn.ToString("x8"));
                return null;
            }

            rtn = SKFApi.SKF_DecryptInit(phKey, blockCipherpAram);
            if (rtn != 0)
            {
                MessageBox.Show("SKF_DecryptInit Error:" + rtn.ToString("x8"));
                return null;
            }

            byte[] enData = Convert.FromBase64String(en);
            UInt32 enDataLen = Convert.ToUInt32(enData.Length);

            byte[] pbData = new byte[256];
            UInt32 pbDataLen = Convert.ToUInt32(pbData.Length);
            rtn = SKFApi.SKF_Decrypt(phKey, enData, enDataLen, pbData, ref pbDataLen);
            if (rtn != 0)
            {
                MessageBox.Show("SKF_Decrypt Error:" + rtn.ToString("x8"));
                return null;
            }
            byte[] pbDataByte = new byte[pbDataLen];
            Array.Copy(pbData, 0, pbDataByte, 0, pbDataLen);
           
            return Encoding.UTF8.GetString(pbDataByte);
        }
        byte[] redom = Encoding.UTF8.GetBytes("1234567812");
        bool enCerType = false;

        public byte[] SM2Encrypt(byte[] pbPlainText, UInt32 pbPlainTextLen)
        {
            UInt32 pulSize = 1024;
            if (pDev == 0)
            {
                MessageBox.Show("请先连接设备！");
                return null;
            }
            pulSize = 1024;
            byte[] szAppName = new byte[2048];
            rtn = SKFApi.SKF_EnumApplication(pDev, szAppName, ref pulSize);
            if (rtn != 0)
            {
                messageOut("SKF_EnumApplication", rtn);
                return null;

            }
            string[] appName = getStringName(szAppName);
            messageOut("AppName = ", appName[0]);
            rtn = SKFApi.SKF_OpenApplication(pDev, appName[0], ref pApp);
            if (rtn != 0)
            {
                messageOut("SKF_OpenApplication", rtn);
                return null;
            }
            messageOut("SKF_OpenApplication ");

            byte[] szContainerName = new byte[1024];
            pulSize = 1024;

            rtn = SKFApi.SKF_EnumContainer(pApp, szContainerName, ref pulSize);
            if (rtn != 0)
            {
                messageOut("SKF_EnumContainer", rtn);
                return null;
            }
            string[] conName = getStringName(szContainerName);
            messageOut("conName = ", conName[0]);

            rtn = SKFApi.SKF_OpenContainer(pApp, conName[0], ref pCon);
            if (rtn != 0)
            {
                messageOut("SKF_OpenContainer", rtn);
                return null;
            }
            messageOut("SKF_OpenContainer ");


            SKFApi.Struct_ECCPUBLICKEYBLOB publickey = new SKFApi.Struct_ECCPUBLICKEYBLOB();
            byte[] pbpublickey = new byte[132];
            UInt32 pulBlobLen = 1024;
            rtn = SKFApi.SKF_ExportPublicKey(pCon, enCerType, pbpublickey, ref pulBlobLen);
            if (rtn != 0)
            {
                messageOut("SKF_ExportPublicKey", rtn);
                return null;
            }

         

      
           

     
            StringBuilder upin = new StringBuilder();
            upin.Append("123456");
            UInt32 pulRetryCOunt = 10;
            rtn = SKFApi.SKF_VerifyPIN(pApp, 1, upin, ref pulRetryCOunt);
            if (rtn != 0)
            {
                messageOut("SKF_VerifyPIN", rtn);
                return null;
            }
       
            //处理公钥
            publickey.BitLen = 256;
     
            byte[] xPub = new byte[pulBlobLen];
            byte[] yPub = new byte[pulBlobLen];
   
            Array.Copy(pbpublickey, 4, xPub, 0, 64);
            Array.Copy(pbpublickey, 68, yPub, 0, 64);
            publickey.XCoordinate = xPub;
            publickey.YCoordinate = yPub;

            SKFApi.Struct_ECCCIPHERBLOB eccCipherBlob = new SKFApi.Struct_ECCCIPHERBLOB();
            eccCipherBlob.CipherLen = 256;
            rtn = SKFApi.SKF_ExtECCEncrypt(pDev, ref publickey, pbPlainText, pbPlainTextLen, ref eccCipherBlob);
        
            if (rtn != 0)
            {

                MessageBox.Show("加密失败 Error:" + rtn.ToString("x8"));
                return null;
            }

          
    
        byte[] benSTR=    SKFApi.StructToBytes(eccCipherBlob);

      
        return benSTR;

        }
        public byte[] SM2Decrypt(byte[] ec)
        {
            if (pCon == 0)
            {
                messageOut("SKF_OpenContainer", rtn);
                return null;
            }

            SKFApi.Struct_ECCCIPHERBLOB eccCipherBlob = new SKFApi.Struct_ECCCIPHERBLOB();
      
            SKFApi.Struct_ECCCIPHERBLOB eccCipherBlob1 = (SKFApi.Struct_ECCCIPHERBLOB)SKFApi.BytesToStruct(ec, eccCipherBlob.GetType());
            byte[] pbData = new byte[1024];
            UInt32 pbDataLen = Convert.ToUInt32(pbData.Length);
            rtn = SKFApi.SKF_ECCPrvKeyDecryptEx(pCon, enCerType, ref eccCipherBlob1, pbData, ref pbDataLen);
            if (rtn != 0)
            {
                
                MessageBox.Show("SM2解密失败!Error:" + rtn.ToString("x8"));
                return null;
            }
            byte[] pbDataByte = new byte[pbDataLen];
            Array.Copy(pbData, 0, pbDataByte, 0, pbDataLen);
            return pbDataByte;
        }







    }

}
