using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class page_05 : System.Web.UI.Page
{
    static int current = 1;
    int max = 11;
    protected void Page_Load(object sender, EventArgs e)
    {
        string val = "~/images/img";
        if (current < 10)
        {
            val += "0";
        }
        image_box.ImageUrl = val + current.ToString() + ".jpg";
    }
    protected void Button1_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/page_01.aspx");
    }
    protected void Button2_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/page_04.aspx");
    }
    protected void Button3_Click(object sender, EventArgs e)
    {
        if (current == max)
        {
            current = 1;
        }
        else
        {
            current += 1;
        }
    }
    protected void Button4_Click(object sender, EventArgs e)
    {
        if (current == 1)
        {
            current = max;
        }
        else
        {
            current -= 1;
        }
    }
}