using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class test : System.Web.UI.Page {
    protected void Button1_Click(object sender, EventArgs e) {
        // Add to DB
        String tmp;
        data.InsertParameters.Clear();
        tmp = TextBox4.Text.ToString();
        data.InsertParameters.Add(new Parameter("vc_name", TypeCode.String, tmp));
        data.Insert();
    }
    protected void GridView2_RowUpdating(object sender, GridViewUpdateEventArgs e) {
        // Updating Row
        string tmp = "";
        data.UpdateParameters.Clear();
        if (e.NewValues["vc_name"] != null) {
            tmp = e.NewValues["vc_name"].ToString();
        } else {
            tmp = "null-string";
        }
        data.UpdateParameters.Add(new Parameter("vc_name", TypeCode.String, tmp));
    }
    ...
}