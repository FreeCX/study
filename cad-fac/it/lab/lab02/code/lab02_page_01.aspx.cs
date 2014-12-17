using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class page_01 : System.Web.UI.Page {
    protected void Page_Load( object sender, EventArgs e ) {
    }
    protected void clear_button_click( object sender, EventArgs e ) {
        Session.Clear();
        Response.Redirect( "~/page_01.aspx" );
    }
    protected void next_button_click(object sender, EventArgs e)
    {
        Session["name"]  = name_textbox.Text.ToString();
        Session["sex"]   = sex_list.SelectedItem.Text;
        Session["numb"]  = numb_textbox.Text.ToString();
        Session["ice"]   = ice_textbox.Text.ToString();
        Session["pet"]   = pet_textbox.Text.ToString();
        Session["movie"] = movie_list.SelectedItem.Text;
        Response.Redirect("~/page_02.aspx");
    }
    protected void Button1_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/page_04.aspx");
    }
    protected void Button2_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/page_05.aspx");
    }
}