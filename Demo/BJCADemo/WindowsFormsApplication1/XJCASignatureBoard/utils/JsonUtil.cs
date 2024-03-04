using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web.Script.Serialization;

namespace XJCASignatureBoard
{
    class JsonUtil
    {

        public static Dictionary<string, object> analysisJson(String str)
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
    }
}
