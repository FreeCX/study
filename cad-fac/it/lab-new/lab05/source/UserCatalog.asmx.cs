using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Data;
using System.Data.SqlClient;
using System.Text;
using System.Configuration;

namespace Lab05.Web
{
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    public class UserCatalog : System.Web.Services.WebService
    {
        [WebMethod]
        public List<User> GetUserList(string searchString)
        {
            List<User> userList = new List<User>();
            using (SqlConnection connect = new SqlConnection(ConfigurationManager.ConnectionStrings["DB"].ConnectionString))
            {
                if (connect != null)
                {
                    StringBuilder sb = new StringBuilder();
                    sb.Append("select * from Users");
                    if (!String.IsNullOrEmpty(searchString))
                    {
                        sb.AppendFormat(" where Name like '%{0}%' or LastName like '%{0}%' or Address like '%{0}%'", searchString);
                    }
                    SqlDataAdapter da = new SqlDataAdapter(sb.ToString(), connect);
                    DataTable dt = new DataTable();
                    da.Fill(dt);
                    if (dt.Rows.Count > 0)
                    {
                        foreach (DataRow curr in dt.Rows)
                        {
                            userList.Add(new User(curr["Name"].ToString(), curr["LastName"].ToString(),
                                curr["Address"].ToString(), curr["Avatar"].ToString()));
                        }
                    }
                }
            }
            return userList;
        }
    }

    public class User
    {
        public User() { }
        public User(string name, string last_name, string address, string avatar)
        {
            _name = name;
            _last_name = last_name;
            _address = address;
            _avatar = avatar;
        }
        private string _name;
        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }
        private string _last_name;
        public string LastName
        {
            get { return _last_name; }
            set { _last_name = value; }
        }
        private string _address;
        public string Address
        {
            get { return _address; }
            set { _address = value; }
        }
        private string _avatar;
        public string Avatar
        {
            get { return _avatar; }
            set { _avatar = value; }
        }
    }
}
