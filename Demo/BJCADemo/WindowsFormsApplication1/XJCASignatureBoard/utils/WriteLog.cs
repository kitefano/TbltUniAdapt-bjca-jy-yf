using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XJCACoreSvr
{
    class WriteLog
    {
        /// <summary>
        /// 将错误写入文件中
        /// </summary>
        /// <param name="fileName">文件名</param>
        /// <param name="exception">发生的异常</param>
        public static void WriteErorrLog(string fileName, Exception exception)
        {
            if (exception == null) return; //ex = null 返回 
            DateTime dt = DateTime.Now; // 设置日志时间 
            string time = dt.ToString("yyyy-MM-dd HH:mm:ss"); //年-月-日 时：分：秒 
            string logName = dt.ToString("yyyy-MM-dd"); //日志名称 
            string logPath = Path.Combine(System.AppDomain.CurrentDomain.BaseDirectory, Path.Combine("log", fileName)); //日志存放路径 
            string log = Path.Combine(logPath, string.Format("{0}.log", logName)); //路径 + 名称
            try
            {
                FileInfo info = new FileInfo(log);
                if (info.Directory != null && !info.Directory.Exists)
                {
                    info.Directory.Create();
                }
                using (StreamWriter write = new StreamWriter(log, true, Encoding.GetEncoding("utf-8")))
                {
                    write.WriteLine(time);
                    write.WriteLine(exception.Message);
                    write.WriteLine("异常信息：" + exception);
                    write.WriteLine("异常堆栈：" + exception.StackTrace);
                    write.WriteLine("异常简述：" + exception.Message);
                    write.WriteLine("\r\n----------------------------------\r\n");
                    write.Flush();
                    write.Close();
                    write.Dispose();
                }
            }
            catch { }
        }

        /// <summary>
        /// 将终端内容打印到文件中
        /// </summary>
        /// <param name="fileName">文件名</param>
        /// <param name="message">所要写入的内容</param>
        public static bool WriteMessage(string fileName, string message)
        {
            //ex = null 返回 
            DateTime dt = DateTime.Now; // 设置日志时间 
            string time = dt.ToString("yyyy-MM-dd HH:mm:ss"); //年-月-日 时：分：秒 
            string logName = dt.ToString("yyyy-MM-dd"); //日志名称 
            string logPath = Path.Combine(System.AppDomain.CurrentDomain.BaseDirectory, Path.Combine("log", fileName)); //日志存放路径 
            string log = Path.Combine(logPath, string.Format("{0}.log", logName)); //路径 + 名称
            try
            {
                FileInfo info = new FileInfo(log);
                if (info.Directory != null && !info.Directory.Exists)
                {
                    info.Directory.Create();
                }
                using (StreamWriter write = new StreamWriter(log, true, Encoding.GetEncoding("utf-8")))
                {
                    write.WriteLine(time);
                    write.WriteLine("信息：" + message);
                    write.WriteLine("\r\n----------------------------------\r\n");
                    write.Flush();
                    write.Close();
                    write.Dispose();
                }
                return true;
            }
            catch (Exception e)
            {
                WriteErorrLog("WriteMessageException", e);
                return false;
            }
        }


        /// <summary>
        /// 将错误写入文件中
        /// </summary>
        /// <param name="exception">发生的错误</param>
        /// <param name="message">需要写入的消息</param>
        public static bool WriteErorrLog(Exception exception, string message)
        {
            if (exception == null) return false; //ex = null 返回 
            DateTime dt = DateTime.Now; // 设置日志时间 
            string time = dt.ToString("yyyy-MM-dd HH:mm:ss"); //年-月-日 时：分：秒 
            string logName = dt.ToString("yyyy-MM-dd"); //日志名称 
            string logPath = System.AppDomain.CurrentDomain.BaseDirectory; //日志存放路径 
            string log = Path.Combine(Path.Combine(logPath, "log"), string.Format("{0}.log", logName)); //路径 + 名称
            try
            {
                FileInfo info = new FileInfo(log);
                if (info.Directory != null && !info.Directory.Exists)
                {
                    info.Directory.Create();
                }
                using (StreamWriter write = new StreamWriter(log, true, Encoding.GetEncoding("utf-8")))
                {
                    write.WriteLine(time);
                    write.WriteLine(exception.Message);
                    write.WriteLine("异常信息：" + exception);
                    write.WriteLine("异常堆栈：" + exception.StackTrace);
                    write.WriteLine("异常简述：" + message);
                    write.WriteLine("\r\n----------------------------------\r\n");
                    write.Flush();
                    write.Close();
                    write.Dispose();
                }
                return true;
            }
            catch (Exception e)
            {
                WriteMessage("ErrorLogException", e.ToString());
                return false;
            }
        }

        /// <summary>
        /// 将消息写入文件
        /// </summary>
        /// <param name="message">需要写入的内容</param>
        public static bool WriteMessage(string message)
        {
            //ex = null 返回 
            DateTime dt = DateTime.Now; // 设置日志时间 
            string time = dt.ToString("yyyy-MM-dd HH:mm:ss"); //年-月-日 时：分：秒 
            string logName = dt.ToString("yyyy-MM-dd"); //日志名称 
            string logPath = System.AppDomain.CurrentDomain.BaseDirectory; //日志存放路径 
            // System.Console.WriteLine(logPath);
            string log = Path.Combine(Path.Combine(logPath, "log"), string.Format("{0}.log", logName)); //路径 + 名称
            try
            {
                FileInfo info = new FileInfo(log);
                if (info.Directory != null && !info.Directory.Exists)
                {
                    info.Directory.Create();
                }
                using (StreamWriter write = new StreamWriter(log, true, Encoding.GetEncoding("utf-8")))
                {
                    write.WriteLine(time);
                    write.WriteLine("信息：" + message);
                    write.WriteLine("\r\n----------------------------------\r\n");
                    write.Flush();
                    write.Close();
                    write.Dispose();
                }
                return true;
            }
            catch (Exception e)
            {
                WriteErorrLog("WriteMessageException", e);
                return false;
            }
        }
    }
}
