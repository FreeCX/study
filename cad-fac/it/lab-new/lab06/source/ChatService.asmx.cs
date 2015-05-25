using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Data;
using System.Data.SqlClient;
using System.Text;
using System.Configuration;

namespace Lab06.Web
{
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    public class ChatService : System.Web.Services.WebService
    {

        [WebMethod]
        public List<User> GetChat()
        {
            List<User> userList = new List<User>();
            using (SqlConnection connect = new SqlConnection(ConfigurationManager.ConnectionStrings["DB"].ConnectionString))
            {
                if (connect != null)
                {
                    StringBuilder sb = new StringBuilder();
                    sb.Append("select * from Users");
                    SqlDataAdapter da = new SqlDataAdapter(sb.ToString(), connect);
                    DataTable dt = new DataTable();
                    da.Fill(dt);
                    if (dt.Rows.Count > 0)
                    {
                        foreach (DataRow curr in dt.Rows)
                        {
                            userList.Add(new User(curr["Name"].ToString(), curr["Message"].ToString()));
                        }
                    }
                }
            }
            return userList;
        }
        [WebMethod]
        public void InsertMessage(User msg) 
        {
            SqlConnection sqlCon = new SqlConnection(ConfigurationManager.ConnectionStrings["DB"].ConnectionString);
            SqlCommand nonqueryCommand = sqlCon.CreateCommand();
            sqlCon.Open();
            nonqueryCommand.CommandText = "INSERT INTO Users (Name, Message) VALUES (@Name, @Message)";
            nonqueryCommand.Parameters.Add("@Name", SqlDbType.VarChar, 50);
            nonqueryCommand.Parameters.Add("@Message", SqlDbType.VarChar, msg.Message.Length);
            nonqueryCommand.Parameters["@Name"].Value = msg.Name;
            nonqueryCommand.Parameters["@Message"].Value = msg.Message;
            nonqueryCommand.ExecuteNonQuery();
        }
    }
    public class User
    {
        public User() { }
        public User(string name, string message)
        {
            _name = name;
            _message = message;
        }
        private string _name;
        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }
        private string _message;
        public string Message
        {
            get { return _message; }
            set { _message = value; }
        }
    }
}