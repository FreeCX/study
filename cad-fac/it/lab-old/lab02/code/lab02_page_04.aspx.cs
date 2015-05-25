using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class page_04 : System.Web.UI.Page
{
    static int last_oper = 0;
    enum OPER { EQU = 0, PLUS, MINUS, MUL, DIV }
    private void calculate(int operation)
    {
        if (mem.Text.Length > 0 )
        {
            double val1 = Convert.ToDouble(mem.Text);
            double val2 = Convert.ToDouble(input_box.Text);
            string val3 = "";
            switch (last_oper)
            {
                case (int)OPER.PLUS:
                    val3 = Convert.ToString(val1 + val2);
                    break;
                case (int)OPER.MINUS:
                    val3 = Convert.ToString(val1 - val2);
                    break;
                case (int)OPER.MUL:
                    val3 = Convert.ToString(val1 * val2);
                    break;
                case (int)OPER.DIV:
                    if (val2 != 0)
                    {
                        val3 = Convert.ToString(val1 / val2);
                    }
                    else
                    {
                        val3 = "error: divide by zero!";
                    }
                    break;
            }
            last_oper = operation;
            if (operation != (int)OPER.EQU)
            {
                mem.Text = val3;
                input_box.Text = "";
            }
            else
            {
                input_box.Text = val3;
                mem.Text = "";
            }
        }
        else
        {
            mem.Text = input_box.Text;
            input_box.Text = "";
            last_oper = operation;
        }
    }
    protected void Page_Load(object sender, EventArgs e)
    {
    }
    protected void Button14_Click(object sender, EventArgs e)
    {
        input_box.Text = "";
        mem.Text = "";
    }
    protected void Button15_Click(object sender, EventArgs e)
    {
        input_box.Text += "0";
    }
    protected void Button1_Click(object sender, EventArgs e)
    {
        input_box.Text += "1";
    }
    protected void Button2_Click(object sender, EventArgs e)
    {
        input_box.Text += "2";
    }
    protected void Button3_Click(object sender, EventArgs e)
    {
        input_box.Text += "3";
    }
    protected void Button4_Click(object sender, EventArgs e)
    {
        input_box.Text += "4";
    }
    protected void Button5_Click(object sender, EventArgs e)
    {
        input_box.Text += "5";
    }
    protected void Button6_Click(object sender, EventArgs e)
    {
        input_box.Text += "6";
    }
    protected void Button7_Click(object sender, EventArgs e)
    {
        input_box.Text += "7";
    }
    protected void Button8_Click(object sender, EventArgs e)
    {
        input_box.Text += "8";
    }
    protected void Button9_Click(object sender, EventArgs e)
    {
        input_box.Text += "9";
    }
    protected void Button10_Click(object sender, EventArgs e)
    {
        calculate((int)OPER.PLUS);
    }
    protected void Button11_Click(object sender, EventArgs e)
    {
        calculate((int)OPER.MINUS);
    }
    protected void Button12_Click(object sender, EventArgs e)
    {
        calculate((int)OPER.MUL);
    }
    protected void Button13_Click(object sender, EventArgs e)
    {
        calculate((int)OPER.DIV);
    }
    protected void Button16_Click(object sender, EventArgs e)
    {
        calculate((int)OPER.EQU);
    }
    protected void main_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/page_01.aspx");
    }
    protected void spec_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/page_05.aspx");
    }
}