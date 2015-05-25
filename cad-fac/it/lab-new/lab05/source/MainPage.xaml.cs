using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Data;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;     
using System.Globalization;

namespace Lab05
{
    public partial class MainPage : UserControl
    {
        public MainPage()
        {
            InitializeComponent();
        }
        void catalogServiceGetUserListCompleted(object sender, UserCatalog.GetUserListCompletedEventArgs e)
        {
            if (e.Error == null)
            {
                Users.ItemsSource = e.Result;
            }
        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            UserCatalog.UserCatalogSoapClient catalogService = new UserCatalog.UserCatalogSoapClient();
            catalogService.GetUserListCompleted += new EventHandler<UserCatalog.GetUserListCompletedEventArgs>(catalogServiceGetUserListCompleted);
            catalogService.GetUserListAsync(SearchBox.Text);
        }
    }
}
