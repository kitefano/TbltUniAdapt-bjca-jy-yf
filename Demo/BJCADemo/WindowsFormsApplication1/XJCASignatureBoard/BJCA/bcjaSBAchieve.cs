using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace XJCASignatureBoard
{
 
    [ComVisible(true)]
   [Guid("AE5CCBBC-35D8-4103-8FE1-D8D205C1B2AB"), ClassInterface(ClassInterfaceType.None)]
    [ProgId("XjcaYxqUtil.XjcaSignUtil")]
    class bcjaSBAchieve : BJCASBInterface
    {
        BJCASBLib bjcaLib = new BJCASBLib();
        public string GetVersion()
        {
            return bjcaLib.GetVersion();
        }


        public string AS_GetSignEvidenceData(int dataType)
        {
            return bjcaLib.AS_GetSignEvidenceData(dataType);
        }
    }
}
