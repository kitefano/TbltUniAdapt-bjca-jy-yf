using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace XJCASignatureBoard
{
  
    [ComVisible(true)]
    [Guid("A4B3874E-C131-41DF-B9E5-6CE7C3CCA984"), InterfaceType(ComInterfaceType.InterfaceIsIDispatch)]
    public  interface BJCASBInterface
    {
        [DispId(1)]
        String GetVersion();
        [DispId(2)]
        String AS_GetSignEvidenceData(int dataType);
    }
}
