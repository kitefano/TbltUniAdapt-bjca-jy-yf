using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using XJCAPadDll;
using System.Diagnostics;

using MySql.Data.MySqlClient;


namespace test001
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
            textBox2.Text = "";

            PadDllClass.initPadDll("科室1001");
            int res = PadDllClass.TbltDevInitSet();

            if (res == 0)
            {
                // 返回值：0-签名完成，1-没有找到适合的平板签名。
                MessageBox.Show("客户已完成签名。", "提示：", MessageBoxButtons.OK, MessageBoxIcon.Information);
                string handSign = PadDllClass.handSig;
                string finger = PadDllClass.finger;

                textBox1.Text = handSign;
                textBox2.Text = finger;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("https://www.json.cn");
        }

        private void linkLabel2_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("https://tool.jisuapi.com/base642pic.html");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("notepad.exe", "SignFile.txt");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("notepad.exe", "SignFile.txt");

        }

        private void button5_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("notepad.exe", "sign.txt");

        }

        private void button6_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("notepad.exe", "zkfpr.txt");
        }

        private void button7_Click(object sender, EventArgs e)
        {
            //string connectionString = "server=rm-cn-jia3moj7900052vo.rwlb.rds.aliyuncs.com;user=user001;password=kai_123123;database=schools";
            //using (var connection = new MySqlConnection(connectionString))
            //{
            //    connection.Open();
            //    string query = "SELECT * FROM hospdept";
            //    using (var command = new MySqlCommand(query, connection))
            //    {
            //        using (var reader = command.ExecuteReader())
            //        {
            //            mysqltextBox3.Text = "";
            //            while (reader.Read())
            //            {
            //                string strc = reader.GetString("deptName");
            //                //mysqltextBox3.Text += "devID: " + reader["devID"] + ", devNum: " + reader["devNum"];
            //                mysqltextBox3.Text += strc;
            //            }
            //        }
            //    }
            //}


            string deptName = "科室1001";
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
                                // devsum = int.Parse(reader.GetString("devsum"));
                                string strc = reader.GetString("devsum");
                                mysqltextBox3.Text += strc;
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
                    }
                }
            }
            catch (Exception ex)
            {
                // 数据库连接，查询 失败。
            }
            


            button7.Text = "0k";
        }
    }
}
