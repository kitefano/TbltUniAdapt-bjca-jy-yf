using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace XJCAPadDll
{
    class CppDll
    {
        // SignPad.dll.GetDeviceStatus(); // 用于判断bjca的板子是否在线。
        [DllImport("SignPad.dll", EntryPoint="GetDeviceStatus", CallingConvention=CallingConvention.Cdecl)]
        public static extern int GetDeviceStatus();

        // device10_server_sdk.dll 有方的dll库。
        [DllImport("device10_server_sdk.dll", EntryPoint = "GWQ_GetSN", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GWQ_GetSN(StringBuilder sn);

        [DllImport("device10_server_sdk.dll", EntryPoint = "GWQ_DeviceOnline", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GWQ_DeviceOnline();
#if true1
         * 使用
            public void YourMethod()
            {
                StringBuilder sn = new StringBuilder(512); // 512 是最大的字符数，根据实际情况调整
                int result = GWQ_GetSN(sn);
                // 进行后续操作
            }         
#endif

        //[DllImport("JYPadDll.dll", EntryPoint = "add122", CallingConvention = CallingConvention.Cdecl)]
        //public static extern int add122(int a, int b);

        //[DllImport("JYPadDll.dll", EntryPoint = "func111", CallingConvention = CallingConvention.Cdecl)]
        //public static extern void func111();




    }
}
