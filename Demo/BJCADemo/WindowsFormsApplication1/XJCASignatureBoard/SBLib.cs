using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web.Script.Serialization;

namespace XJCASignatureBoard
{
    public class SBLib
    {

        public String UnifiedEntrance(String data)
        {
            JavaScriptSerializer serializer = new JavaScriptSerializer();
            String result = "";
            Dictionary<string, object> DicJson = JsonUtil.analysisJson(data);
            string manufacturer = DicJson["manufacturer"].ToString();
            Dictionary<string, object> json = new Dictionary<string, object>();
            switch (manufacturer)
            {
                case "BJCA":result= BJCASignatureBoard(DicJson);
                    break;
            }

            return result;
        }
		
        BJCASBLib bjcaLib = null;
        private String BJCASignatureBoard(Dictionary<string, object> DicJson)
        {
            JavaScriptSerializer serializer = new JavaScriptSerializer();
            Dictionary<string, object> json = new Dictionary<string, object>();
            String result = "";
            if (bjcaLib == null)
            {
                bjcaLib = new BJCASBLib();
            }
            string method = DicJson["method"].ToString();
        
            switch (method)
            {
                case "AS_GetSignEvidenceData": result =bjcaLib.WB_GetSignEvidenceData(DicJson);
                    break;
                case "GetVersion": result = bjcaLib.WB_GetVersion(DicJson);
                         break;
                case "AS_AddSignEvidenceData": result = bjcaLib.WB_AddSignEvidenceData(DicJson);
                         break;
          
            }
            json.Add("data", result);
            return    serializer.Serialize(json);;
        }

    }
}
