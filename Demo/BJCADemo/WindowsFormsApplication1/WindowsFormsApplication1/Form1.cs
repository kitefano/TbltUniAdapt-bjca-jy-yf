using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using ASAppComLib;


namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {

        string img1;
        string img2;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ASAppComLib.ASAppComClass asappcomlib = null;
            asappcomlib = new ASAppComClass();

            int status = 0;
            status = asappcomlib.AS_InitSign(1);
            status = asappcomlib.AS_SetSignerInfo("张三", "1", "110101190001011009");
            string id = asappcomlib.AS_GetIDCardInfo();
            status = asappcomlib.AS_AddSignEvidenceData(); /* lxk-imp 这是一个com组件显示的一个界面。 */

            img1 = asappcomlib.AS_GetSignEvidenceData(0);
            img2= asappcomlib.AS_GetSignEvidenceData(2);
            img1 = "hell";

            label1.Text = img1;
            label2.Text = img2;

            //Close();
        }


    }
}
