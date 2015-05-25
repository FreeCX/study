using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Data;
using System.Data.SqlClient;

[WebService(Namespace = "http://tempuri.org/")]
[WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
public class service : System.Web.Services.WebService {

    public service () {
    }

    [WebMethod]
    public string HelloWorld() {
        return "Hello World";
    }
    [WebMethod]
    public string getSumPersonList() {
        String sCon = "Data Source=.\\SQLEXPRESS;AttachDbFilename=|DataDirectory|\\Database.mdf;Integrated Security=True;User Instance=True";
        SqlConnection conn = new SqlConnection(sCon);
        SqlCommand cmd = new SqlCommand("selectAvgPersonList", conn);
        cmd.CommandType = CommandType.StoredProcedure;
        SqlParameter sum = new SqlParameter("sum", SqlDbType.Int);
        sum.Direction = ParameterDirection.Output;
        cmd.Parameters.Add(sum);
        try {
            conn.Open();
            cmd.ExecuteNonQuery();
        } catch (Exception ex) {
            throw (ex);
        } finally {
            if (conn.State == ConnectionState.Open) {
                conn.Close();
            }
        }
        return sum.Value.ToString();
    }
}
