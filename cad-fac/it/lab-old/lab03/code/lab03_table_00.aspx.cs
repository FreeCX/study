using System;
using System.Data;  
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;

public partial class _Default : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e) {
        if ( !IsPostBack ) {
            IDataReader reader = (IDataReader)dsRegister.Select(new DataSourceSelectArguments());
            try
            {
                while (reader.Read())
                {
                    HtmlTableRow row = new HtmlTableRow();
                    HtmlTableCell cell = new HtmlTableCell();
                    cell.InnerText = reader["DepName"].ToString();
                    row.Cells.Add(cell);
                    TableViewRegister.Rows.Add(row);

                    cell = new HtmlTableCell();
                    cell.InnerText = reader["ToolName"].ToString();
                    row.Cells.Add(cell);
                    TableViewRegister.Rows.Add(row);

                    cell = new HtmlTableCell();
                    cell.InnerText = reader["PersName"].ToString();
                    row.Cells.Add(cell);
                    TableViewRegister.Rows.Add(row);

                    cell = new HtmlTableCell();
                    cell.InnerText = reader["ManufName"].ToString();
                    row.Cells.Add(cell);
                    TableViewRegister.Rows.Add(row);

                    cell = new HtmlTableCell();
                    cell.InnerText = reader["CouName"].ToString();
                    row.Cells.Add(cell);
                    TableViewRegister.Rows.Add(row);

                    cell = new HtmlTableCell();
                    cell.InnerText = reader["MarkName"].ToString();
                    row.Cells.Add(cell);
                    TableViewRegister.Rows.Add(row);

                    cell = new HtmlTableCell();
                    cell.InnerText = reader["Count_l"].ToString();
                    row.Cells.Add(cell);
                    TableViewRegister.Rows.Add(row);
                }
            }
            finally
            {
                reader.Close();
            }
        }
    }
    protected void button_click( object sender, CommandEventArgs e ) {
        string page = e.CommandArgument.ToString();
        Response.Redirect( "~/table_0" + page + ".aspx" );
    }
}