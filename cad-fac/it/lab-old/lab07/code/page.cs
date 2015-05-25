using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class _Default : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {
            int sum = 0;
            localhost.serviceSoapClient client = new localhost.serviceSoapClient();
            TextBox1.Text = client.HelloWorld();
            TextBox2.Text = client.getSumPersonList();
            foreach (GridViewRow row in GridView1.Rows)
            {
                sum += Convert.ToInt32(row.Cells[3].Text);
            }
            Label1.Text = sum.ToString();
        }
    }
}