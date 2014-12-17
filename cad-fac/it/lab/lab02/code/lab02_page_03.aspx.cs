using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class page_03 : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        name_label.Text = Session["name"].ToString();
        sex_label.Text = Session["sex"].ToString();
        numb_label.Text = Session["numb"].ToString();
        ice_label.Text = Session["ice"].ToString();
        pet_label.Text = Session["pet"].ToString();
        movie_label.Text = Session["movie"].ToString();
        superhero_label.Text = Session["superhero"].ToString();
        why_label.Text = Session["why"].ToString();
    }
    protected void Button1_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/page_01.aspx");
    }
    protected void Button2_Click(object sender, EventArgs e)
    {
        Session["name"] = name_label.Text;
        Session["sex"] = sex_label.Text;
        Session["numb"] = numb_label.Text;
        Session["ice"] = ice_label.Text;
        Session["pet"] = pet_label.Text;
        Session["movie"] = movie_label.Text;
        Response.Redirect("~/page_02.aspx");
    }
    protected void Button3_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/page_04.aspx");
    }
    protected void Button4_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/page_05.aspx");
    }
}