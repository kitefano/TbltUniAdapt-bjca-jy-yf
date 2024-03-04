using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ASAppComLib;
using XJCACoreSvr;
using Newtonsoft.Json;
using System.Reflection;


namespace XJCASignatureBoard
{
    public class BJCASBLib
    {
        ASAppComLib.ASAppComClass asappcomlib = null;
        public BJCASBLib()
        {
            asappcomlib = new ASAppComClass();
        }
  

        public String AS_GetSignEvidenceData(int dataType)
        {
     
            String imgData = asappcomlib.AS_GetSignEvidenceData(dataType);
            return imgData;
        }
        public int AS_AddSignEvidenceData()  /*lxk-imp 显示界面*/
        {
            int status = 0;

            status = asappcomlib.AS_InitSign(1);
            status = asappcomlib.AS_SetSignerInfo("张三", "1", "110101190001011009");
            string id = asappcomlib.AS_GetIDCardInfo();
            status = asappcomlib.AS_AddSignEvidenceData(); /* lxk-imp 这是一个com组件显示的一个界面。 */
            return status;
        }

        public String GetVersion()
        {
#if true1  // lxkbug：自动获取Revision号总是为0
            //return asappcomlib.AS_GetVersion();
            Assembly assembly = Assembly.GetExecutingAssembly();
            Version version = assembly.GetName().Version;


            // 获取主版本号
            int majorVersion = version.Major;

            // 获取次版本号
            int minorVersion = version.Minor;

            // 获取生成号
            int buildNumber = version.Build;

            // 获取修订号
            int revisionNumber = version.Revision;

            return "V" + majorVersion + "." + minorVersion + "." + buildNumber + "." + revisionNumber ;
#endif

            return "V" + 1 + "." + 0 + "." + 0 + "." + 1;
        }


        public String WB_GetSignEvidenceData(Dictionary<string, object> DicJson)
        {        
            AS_AddSignEvidenceData();
            //String dataType = DicJson["dataType"].ToString();i
         //   WriteLog.WriteMessage("调用平板获取接口开始 参数：" + dataType);
            String img1=  AS_GetSignEvidenceData(0);
            String img2  = AS_GetSignEvidenceData(2);
            
            var jsObjTmp = new Dictionary<string, object>
            {
                {"Handwritten Data", img1},
                {"Fingerprint Data", img2}
            };

            string ret = JsonConvert.SerializeObject(jsObjTmp);
            return ret;

        }

        public String WB_GetVersion(Dictionary<string, object> DicJson)
        {
            return GetVersion();
        }

        public String WB_AddSignEvidenceData(Dictionary<string, object> DicJson)
        {
            return AS_AddSignEvidenceData().ToString();
        }

        /* add by lxk@2023.9.19 for:获取本地服务状态 GetLocalSvcStat */
        public String Form_GetLocalSvcStat(out int stat)
        {
            stat = 123;
            return "Form_GetLocalSvcStat";
        }

        /* add by lxk@2023.9.19 for:获取远程服务状态 GetRemoteSvcStat */
        public string Form_GetRemoteSvcStat(ref int stat)
        {
            return "Form_GetRemoteSvcStat";
        }

        /* add by lxk@2023.9.19 for:获取设备信息 GetDevInfo begin */
        int devStat;
        int rv;
        public int  Form_GetDevInfo(out string devInfo)
        {
#if true1
            devStat = asappcomlib.AS_GetDeviceStatus();

            if(0 != devStat)
            {
                devInfo = "平板设备USB连接状态：已断开, code = " + devStat + Environment.NewLine;// +Environment.NewLine;
                return devStat;
            }
            else
            {
                devInfo = "平板设备USB连接状态：已连接, code = " + devStat + Environment.NewLine;// +Environment.NewLine;
                return devStat;
            }
#else
            devInfo = "这里有一个报错，需要修改下。";
            return 0;
#endif
        }
        /* add by lxk@2023.9.19 for:获取设备信息 GetDevInfo end */
    }
}
