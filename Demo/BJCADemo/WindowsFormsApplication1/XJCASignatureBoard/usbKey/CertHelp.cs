using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;
using System.Web.Script.Serialization;

namespace XJCAServiceslib
{
    class CertHelp
    {
        int SGD_CERT_ISSUER_CN = 0x00000021;
        int SGD_CERT_ISSUER_O = 0x00000022;
        int SGD_CERT_ISSUER_OU = 0x00000023;
        int SGD_CERT_ISSUER_C = 0x00000024;
        int SGD_CERT_ISSUER_P = 0x00000025;
        int SGD_CERT_ISSUER_L = 0x00000026;
        int SGD_CERT_ISSUER_S = 0x00000027;
        int SGD_CERT_ISSUER_EMAIL = 0x00000028;

        int SGD_CERT_SUBJECT_CN = 0x00000031;
        int SGD_CERT_SUBJECT_O = 0x00000032;
        int SGD_CERT_SUBJECT_OU = 0x00000033;
        int SGD_CERT_SUBJECT_EMALL = 0x00000034;
        int SGD_REMAIN_TIME = 0x00000035;
        int SGD_SIGNATURE_ALG = 0x00000036;
        int SGD_CERT_SUBJECT_C = 0x00000037;
        int SGD_CERT_SUBJECT_P = 0x00000038;
        int SGD_CERT_SUBJECT_L = 0x00000039;
        int SGD_CERT_SUBJECT_S = 0x0000003A;

        private string analysisCert(Byte[] StrCert, int type)
        {

            X509Certificate2 cert = new X509Certificate2(StrCert);
            string Result = "";
            switch (type)
            {
                case 0x00000021: Result = cert.Subject;
                    break;
                case 0x00000022: Result = cert.SubjectName.Name;
                    break;
                case 0x00000023: Result = cert.SubjectName.Name;
                    break;
                case 0x00000024: Result = cert.SubjectName.Name;
                    break;
                case 0x00000025: Result = cert.SubjectName.Name;
                    break;
                case 0x00000031: Result = cert.SubjectName.Name;
                    break;
                case 0x00000032: Result = cert.SubjectName.Name;
                    break;
                case 0x00000033: Result = cert.SubjectName.Name;
                    break;
                case 0x00000034: Result = cert.SubjectName.Name;
                    break;
                case 0x00000035: Result = cert.SubjectName.Name;
                    break;
                default: Result = "";
                    break;
            }
            return Result;
        }
        public struct RAndS
        {
            public byte[] R;
            public byte[] S;
        }
        public Dictionary<string, object> analysisJson(String str)
        {
            Dictionary<string, object> json = new Dictionary<string, object>();
            JavaScriptSerializer serializer = new JavaScriptSerializer();
            string err = "";
            try
            {
                json = (Dictionary<string, object>)serializer.DeserializeObject(str);
            }
            catch (Exception e)
            {
                err = e.Message;
                json.Add("err", err);
            }
            return json;
        }

        public static RAndS DER2RS(byte[] pucDERSignature, int pulDERSignatureLen)
        {

            RAndS r_s = new RAndS();
            r_s.R = new byte[32];
            r_s.S = new byte[32];

            byte tab = pucDERSignature[3];
            int item = 0;
            byte[] TempR = new byte[32];
            byte[] TempS = new byte[32];
            switch (tab)
            {
                case 0x21:
                    item = 5;
                    break;
                case 0x20:
                    item = 4;
                    break;
                default:
                    break;
            }
            int item_r = 0;
            for (int i = item; i < item + 32; i++)
            {
                TempR[item_r] = pucDERSignature[i];
                item_r++;
            }
            int item_s = pulDERSignatureLen - 32;
            item_r = 0;
            for (int i = item_s; i < pulDERSignatureLen; i++)
            {
                TempS[item_r] = pucDERSignature[i];
                item_r++;
            }
            for (int i = 0; i < 32; i++)
            {
                r_s.R[i] = TempR[i];
            }
            for (int i = 0; i < 32; i++)
            {
                r_s.S[i] = TempS[i];
            }

            return r_s;
        }
        public static byte[] RS2DER(Byte[] R, Byte[] S)
        {
            string result = "";
            const int R_S_BLOCK_SIZE = 32;
            int nPos = 0;
            byte[] ucTemp = new byte[128];
            ucTemp[0] = 0x30;
            ucTemp[1] = 0x44;
            ucTemp[2] = 0x02;
            if (R[0] < 0x80)
            {
                ucTemp[3] = 0x20;
                nPos = 4;
            }
            else
            {
                ucTemp[3] = 0x21;
                ucTemp[4] = 0x00;
                ucTemp[1] += 1;
                nPos = 5;
            }
            int item = 0;
            for (int i = nPos; item < R_S_BLOCK_SIZE; i++)
            {
                ucTemp[i] = R[item];
                item++;

            }
            nPos += R_S_BLOCK_SIZE;


            //S
            ucTemp[nPos] = 0x02;
            nPos += 1;
            if (S[0] < 0x80)
            {
                ucTemp[nPos] = 0x20;
                nPos += 1;
            }
            else
            {
                ucTemp[nPos] = 0x21;
                nPos += 1;
                ucTemp[nPos] = 0x00;
                nPos += 1;
                ucTemp[1] += 1;
            }
            item = 0;
            for (int i = nPos; item < R_S_BLOCK_SIZE; i++)
            {
                ucTemp[i] = S[item];
                item++;
            }
            nPos += R_S_BLOCK_SIZE;
            byte[] final = new byte[nPos];
            for (int i = 0; i < nPos; i++)
            {
                final[i] = ucTemp[i];
            }



            return final;

        }
        public byte[] RS2DER_lm(byte[] R, byte[] S)
        {

            byte[] temp = new byte[1];

            int R_S_BLOCK_SIZE = 32;
            int nPos = 0;
            byte[] ucTemp = new byte[128];
            byte[] len = new byte[1];
            ucTemp[0] = 0x30;
            ucTemp[1] = 0x44;
            temp[0] = ucTemp[1];
            // R
            ucTemp[2] = 0x02;
            int b = S[0] & 0xff;
            if (b < 128)
            {
                ucTemp[3] = 0x20;
                nPos = 4;
            }
            else
            {
                ucTemp[3] = 0x21;
                ucTemp[4] = 0x00;
                len[0] = (byte)(temp[0] + 1);
                ucTemp[1] = len[0];
                nPos = 5;
            }
            // memcpy(ucTemp+nPos, R, R_S_BLOCK_SIZE);
            Array.Copy(R, 0, ucTemp, nPos, R_S_BLOCK_SIZE);

            nPos += R_S_BLOCK_SIZE;
            // S
            ucTemp[nPos] = 0x02;
            nPos += 1;
            int a = S[0] & 0xff;
            if (a < 128)
            {
                ucTemp[nPos] = 0x20;
                nPos += 1;
            }
            else
            {
                ucTemp[nPos] = 0x21;
                nPos += 1;
                ucTemp[nPos] = 0x00;
                nPos += 1;
                len[0] = (byte)(len[0] + 1);
                ucTemp[1] = len[0];

            }

            // memcpy(ucTemp+nPos, S, R_S_BLOCK_SIZE);
            Array.Copy(S, 0, ucTemp, nPos, R_S_BLOCK_SIZE);
            nPos += R_S_BLOCK_SIZE;
            byte[] final = new byte[nPos];
            for (int i = 0; i < nPos; i++)
            {
                final[i] = ucTemp[i];
            }

            return final;
        }
    }
}
