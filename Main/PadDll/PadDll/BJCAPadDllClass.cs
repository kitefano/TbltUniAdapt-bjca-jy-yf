using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ASAppComLib;
using System.Reflection;
using System.Diagnostics;


namespace XJCAPadDll
{
    class BJCAPadDllClass
    {
        public string handSig = "";
        public string finger = "";

        static void RegisterAssembly()
        {
            try
            {
                // 获取程序集的路径
                string assemblyPath = "Interop.ASAppComLib.dll";

                // 构建 regsvcs 命令
                string command = "regsvcs \"{assemblyPath}\"";

                // 在命令行执行 regsvcs 命令
                Process process = new Process();
                process.StartInfo.FileName = "cmd.exe";
                process.StartInfo.Arguments = "/c {command}";
                process.StartInfo.RedirectStandardOutput = true;
                process.StartInfo.UseShellExecute = false;
                process.StartInfo.CreateNoWindow = true;

                process.Start();

                // 等待命令执行完毕
                process.WaitForExit();

                Console.WriteLine("Registration successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error during registration: " + ex.Message);
            }
        }

        public void GetEvidence()
        {

            // RegisterAssembly();

            ASAppComLib.ASAppComClass asappcomlib = null;
            asappcomlib = new ASAppComClass();

            int status = 0;
            status = asappcomlib.AS_GetDeviceStatus();
            status = asappcomlib.AS_InitSign(1);
            status = asappcomlib.AS_SetSignerInfo("张三", "1", "110101190001011009");
            string id = asappcomlib.AS_GetIDCardInfo();

            status = asappcomlib.AS_AddSignEvidenceData(); /* lxk-imp 这是一个com组件显示的一个界面。 */

            handSig = "";
            finger = "";

            handSig = asappcomlib.AS_GetSignEvidenceData(0);
            finger = asappcomlib.AS_GetSignEvidenceData(2);
        }
        
    }
}
