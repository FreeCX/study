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

namespace Lab06
{
    public partial class MainPage : UserControl
    {
        public MainPage()
        {
            InitializeComponent();
            System.Windows.Threading.DispatcherTimer myDispatcherTimer = new System.Windows.Threading.DispatcherTimer();
            myDispatcherTimer.Interval = new TimeSpan(0, 0, 0, 0, 1000);
            myDispatcherTimer.Tick += new EventHandler(CheckBD);
            myDispatcherTimer.Start();
        }

        public void CheckBD(object o, EventArgs sender)
        {
            ChatService.ChatServiceSoapClient catalogService = new ChatService.ChatServiceSoapClient();
            catalogService.GetChatCompleted += new EventHandler<ChatService.GetChatCompletedEventArgs>(getChat);
            catalogService.GetChatAsync();
        }

        private void getChat(object sender, ChatService.GetChatCompletedEventArgs e)
        {
            if (e.Error == null)
            {
                ChatBox.ItemsSource = e.Result;
            }
        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            ChatService.ChatServiceSoapClient catalogService = new ChatService.ChatServiceSoapClient();
            ChatService.User user = new ChatService.User();
            user.Name = username.Text;
            user.Message = messagebox.Text;
            catalogService.InsertMessageAsync(user);
        }
    }
}
