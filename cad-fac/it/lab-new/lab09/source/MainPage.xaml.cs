using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using System.IO;
using System.Windows.Threading;

namespace Lab09
{
    public partial class MainPage : UserControl
    {
        private TimeSpan TotalTime;
        private DispatcherTimer timerVideoTime = new DispatcherTimer();
        private List<Stream> streams = new List<Stream>();
        private int sindex = 0;
        public MainPage()
        {
            InitializeComponent();
            slider.AddHandler(MouseLeftButtonUpEvent, new MouseButtonEventHandler(slider_MouseLeftButtonUp), true);
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {

        }
        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            if (media.CurrentState == MediaElementState.Paused)
            {
                media.Play();
            }
            else
            {
                media.Pause();
            }
        }

        private void stop_Click(object sender, RoutedEventArgs e)
        {
            media.Stop();
        }

        private void listBox_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
        }

        private void media_MediaOpened(object sender, RoutedEventArgs e)
        {
            TotalTime = media.NaturalDuration.TimeSpan;

            // Create a timer that will update the counters and the time slider
            timerVideoTime.Interval = TimeSpan.FromMilliseconds(1000);
            timerVideoTime.Tick += new EventHandler(timer_Tick);
            timerVideoTime.Start();
            slider.Maximum = media.NaturalDuration.TimeSpan.TotalSeconds;
            slider.Minimum = 0;
        }
        void timer_Tick(object sender, EventArgs e)
        {
            slider.Value = media.Position.TotalSeconds;
            if (media.Position.TotalSeconds == media.NaturalDuration.TimeSpan.TotalSeconds)
            {
                video_list(+1);
            }
        }

        private void slider_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            int pos = Convert.ToInt32(slider.Value);
            media.Position = new TimeSpan(0, 0, 0, pos, 0);
        }

        private void open_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog fdlg = new OpenFileDialog();
            fdlg.Multiselect = true;
            fdlg.Filter = "All suported files|*.wmv;*.mp4;*.avi";
            if (fdlg.ShowDialog() != true)
            {
                return;
            }
            playlist.Items.Clear();
            foreach (var file in fdlg.Files)
            {
                Stream fileStream = file.OpenRead();
                streams.Add(fileStream);
                playlist.Items.Add(file.Name);
            }
            video_list(0);
        }

        private void video_list(int adder)
        {
            int tmp = sindex + adder;
            if (tmp >= 0 && tmp < streams.Count)
            {
                sindex += adder;
                media.SetSource(streams[sindex]);
                playlist.SelectedIndex = sindex;
                media.Position = new TimeSpan(0);
            }
        }
        private void next_Click(object sender, RoutedEventArgs e)
        {
            video_list(+1);
        }

        private void prev_Click(object sender, RoutedEventArgs e)
        {
            video_list(-1);
        }

        private void playlist_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            sindex = playlist.SelectedIndex;
            video_list(0);
        }
    }
}
