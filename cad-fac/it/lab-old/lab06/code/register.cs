using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Microsoft.AspNet.Identity;
using Microsoft.AspNet.Identity.EntityFramework;
using Microsoft.Owin.Security;
using Microsoft.Owin;
using Microsoft.Owin.Security.Cookies;
using System.Net.Http;

namespace lab06 {
    public partial class Register : System.Web.UI.Page {
        protected void CreateUser_Click(object sender, EventArgs e) {
            var userStore = new UserStore<IdentityUser>();
            var manager = new UserManager<IdentityUser>(userStore);
            var user = new IdentityUser() { UserName = UserName.Text };
            IdentityResult result = manager.Create(user, Password.Text);
            if (result.Succeeded) {
                var authenticationManager = HttpContext.Current.GetOwinContext().Authentication;
                var userIdentity = manager.CreateIdentity(user, DefaultAuthenticationTypes.ApplicationCookie);
                authenticationManager.SignIn(new AuthenticationProperties() { }, userIdentity);
                Response.Redirect("~/Login.aspx");
            } else {
                StatusMessage.Text = result.Errors.FirstOrDefault();
            }
        }
    }
}