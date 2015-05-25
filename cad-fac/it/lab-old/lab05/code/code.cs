using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;
using System.Data;

public partial class _Default : System.Web.UI.Page {
    protected void Button1_Click(object sender, EventArgs e) {
        dsList.SelectParameters["sel_min"].DefaultValue = TextBox1.Text.ToString();
    }
}