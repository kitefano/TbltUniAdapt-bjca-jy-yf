using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using Newtonsoft.Json.Linq;
using System.Reflection;
using System.Threading;
using MySql.Data.MySqlClient;


namespace XJCAPadDll
{
    public class PadDllClass
    {
        public static string handSig = "";
        public static string finger = "";
        public static string currDeptName;

        public static void initPadDll(string deptName)
        {
            // 初始化padDll库

            // 注册程序集。
            // RegisterAssembly();

            currDeptName = deptName;


            return ;
        }

        private static bool ExecMFCExe(string mfcExecutablePath)
        {
            // 执行MFC可执行文件。
            // 路径为 MFC 可执行文件的完整路径
            // string mfcExecutablePath = @"JYMFCAppActiveX.exe";
            // 返回值：如果返回 true，表示程序已经执行完毕；如果返回 false，表示程序在执行中。
            // 传递给 MFC 程序的命令行参数
            string commandLineArgs = "";
            // 创建 ProcessStartInfo 对象
            ProcessStartInfo startInfo = new ProcessStartInfo
            {
                FileName = mfcExecutablePath,
                Arguments = commandLineArgs,
                UseShellExecute = false,        // 必须设置为 false
                RedirectStandardOutput = true,  // 如果需要获取 MFC 程序的输出，设置为 true
                CreateNoWindow = true           // 设置为 true 则不显示 MFC 程序的窗口
            };
            // 创建 Process 对象
            using (Process process = new Process { StartInfo = startInfo })
            {
                // 启动 MFC 程序
                process.Start();
                // 如果需要获取 MFC 程序的输出，可以使用 StandardOutput 属性
                string output = process.StandardOutput.ReadToEnd();
                // 等待 MFC 程序退出
                process.WaitForExit();
                bool exited = process.WaitForExit(Timeout.Infinite);
                return exited;
            }
        }

        private static void GetHandSigData(string filePath)
        {
            // 读取txt文件中的JSON数据
            string jsonData = File.ReadAllText(filePath);

            // 解析JSON数据
            JObject json = JObject.Parse(jsonData);
            // 提取特定字段的数据

            handSig = (string)json["signImage"];

            //finger = (string)json["fingerImage"];
        }


        private static void GetFingerprintData(string filePath)
        {
            // 读取txt文件中的JSON数据
            string jsonData = File.ReadAllText(filePath);

            // 解析JSON数据
            JObject json = JObject.Parse(jsonData);
            // 提取特定字段的数据

            //handSig = (string)json["signImage"];

            finger = (string)json["fingerImage"];
        }



        static void RegisterAssembly()
        {
            try
            {
                // 获取程序集的路径
                string assemblyPath = Assembly.GetExecutingAssembly().Location;

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

        // 判断是否是xjca的板子
        public static int IsXJCABoard(string str)
        {
            // 返回： 0-是公司的板子； 1-不是公司的板子；

            if (str.StartsWith("XJCA"))
            {
                return 0;
            }
            else
            {
                // return 1;  // 暂时注释。
                return 0;
            }
        }

        // 判断板子数量是否超标。
        private static int IsBrdQtyWthExcd(string deptName)
        {
            // 返回值：0-未超标， 1-超标， 2-数据库连接，查询 失败。
            int devsum=0, devsumNow=0;
            string connectionString = "server=rm-cn-jia3moj7900052vo.rwlb.rds.aliyuncs.com;user=user001;password=kai_123123;database=schools";
            try
            {
                using (var connection = new MySqlConnection(connectionString))
                {
                    connection.Open();

                    // 获取 科室 平板可用总数。
                    string query = "SELECT devsum FROM hospdept WHERE deptName="+"'"+deptName+"'";
                    using (var command = new MySqlCommand(query, connection))
                    {
                        using (var reader = command.ExecuteReader())
                        {
                            while (reader.Read())
                            {
                                devsum = int.Parse(reader.GetString("devsum"));
                            }
                        }
                    }

                    // 获取 现在 的科室总共有多少平板在使用（xcja结尾）。
                    string query2 = "SELECT COUNT(*) AS devSumNow FROM tbltdev WHERE devID LIKE '%xjca'";
                    using (var command = new MySqlCommand(query2, connection))
                    {
                        using (var reader = command.ExecuteReader())
                        {
                            while (reader.Read())
                            {
                                devsumNow = reader.GetInt32("devSumNow");
                            }
                        }
                    }

                    // 判断板子数量是否超标。
                    if (devsumNow > devsum)
                    {
                        // 板子数量超标。
                        return 1;
                    }
                }
            }
            catch (Exception ex)
            {
                // 数据库连接，查询 失败。
                return 2; 
            }
            
            // 板子数量正常。
            return 0;
        }

        // 获取科室名
        private string GetDeptName()
        {

            return "xxx";
        }


        // 判断使用的是哪个平板
        //public static void TbltDevInitSet(string padstr)
        public static int TbltDevInitSet()
        {
            // 返回值：0-签名完成，1-没有找到适合的平板签名。
            int res = 0;



            // bjca 的板子
            res = CppDll.GetDeviceStatus();
            if (res == 0)
            {
                // res == 0 表示bjca的板子在线。
                BJCAPadDllClass bjcapad = new BJCAPadDllClass();
                bjcapad.GetEvidence();
                handSig = bjcapad.handSig;
                finger = bjcapad.finger;
                return 0;
            }

            // 有方（youfang）的板子
            StringBuilder sn = new StringBuilder(512); // 512 是最大的字符数，根据实际情况调整
            res = CppDll.GWQ_GetSN(sn);  
            if (res == 0)
            {
                // res ==0 表示 youfang的板子在线。

                // 判断是否是xjca的板子
                res = IsXJCABoard(sn.ToString());
                // 原设备号arr="3d9b8674f4b94f6";
                // 修改后arr="XJCA3d9b8674f4b94f6"
                if(res == 0)
                {
                    // 返回： 0-是公司的板子； 1-不是公司的板子；

                    // 判断板子是否超标：
                    int resdevNum = 0;
                    resdevNum= IsBrdQtyWthExcd(currDeptName);
                    if(resdevNum != 0)
                    {
                        // 板子超过总数了。做出提醒。 
                    }
                    // 执行有方的代码。
                    bool exited = ExecMFCExe("YFMFCApp.exe");
                    // 读取txt文件中的JSON数据
                    GetHandSigData("sign.txt");
                    GetFingerprintData("zkfpr.txt");
                }
                return 0;
            }

            // 捷宇（jieyu）的板子
            // 首先执行捷宇的程序获取 设备号和设备状态。
            bool bl = ExecMFCExe("JYMFCAppActiveXGetDevNum.exe");
            string stres = File.ReadAllText("JYOnline.txt");
            res = int.Parse(stres);            
            if (res == 0)
            { // res == 0 表示 jieyu 的板子在线。
                // 判断是否是xjca的板子：1.获取捷宇的设备号。2.判断 是否是xjca的捷宇板子。
                string strDevNum = File.ReadAllText("DevNum.txt");
                res = IsXJCABoard(strDevNum);
                // strDevNum="JY01C0300261";
                // strDevNum="JY01C0300261xjca";

                if (res == 0)
                {
                    // 返回： 0-是公司的板子； 1-不是公司的板子；

                    // 判断板子是否超标：
                    int resdevNum = 0;
                    resdevNum = IsBrdQtyWthExcd(currDeptName);
                    if (resdevNum != 0)
                    {
                        // 板子超过总数了。做出提醒。 
                    }

                    // 执行捷宇的可执行文件。
                    bool  exited = ExecMFCExe("JYMFCAppActiveX.exe");
                    // 读取txt文件中的JSON数据
                    GetHandSigData("SignFile.txt");
                    GetFingerprintData("SignFile.txt");
                }
                return 0;
            }

            return 1;
        }

  
        public static int functest(int a, int b)
        {
            return a+b;
        }

    }
}
