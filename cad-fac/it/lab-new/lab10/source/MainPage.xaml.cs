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
using System.Windows.Threading;

namespace Lab10
{
    public partial class MainPage : UserControl
    {
        private DispatcherTimer timerVideoTime = new DispatcherTimer();
        private RotateTransform hour_rotate = new RotateTransform();
        private RotateTransform minute_rotate = new RotateTransform();
        private RotateTransform second_rotate = new RotateTransform();

        public void AddText(Canvas canvas, String text, int X, int Y) {
            TextBlock tmp = new TextBlock();
            tmp.Text = text;
            tmp.RenderTransform = new TranslateTransform {
                X = X,
                Y = Y,
            };
            canvas.Children.Add(tmp);
        }
        public MainPage()
        {
            InitializeComponent();
            timerVideoTime.Interval = TimeSpan.FromMilliseconds(500);
            timerVideoTime.Tick += new EventHandler( timer_Tick );
            Ellipse clock = new Ellipse();
            SolidColorBrush brush = new SolidColorBrush();
            brush.Color = Color.FromArgb(80, 204, 204, 255);
            clock.RenderTransform = new TranslateTransform
            {
                X = 95,
                Y = 25
            };
            clock.Width = 225;
            clock.Height = 220;
            clock.Fill = brush;
            canvas.Children.Add(clock);
            const double angle = 0.01745329251994329576923690768489;
            for (int i = 0; i < 360; i++)
            {
                int x = Convert.ToInt32((Math.Cos((double)i * angle - Math.PI / 2.0f) + 2) * 100);
                int y = Convert.ToInt32((Math.Sin((double)i * angle - Math.PI / 2.0f) + 1.25) * 100);
                if (i % 30 == 0)
                {
                    AddText(canvas, Convert.ToString(i/30).PadLeft(2, '0'), x, y);
                }
                else if ( i % 10 == 0)
                {
                    AddText(canvas, ".", x, y);
                }
            }
            hour.SetValue(Canvas.LeftProperty, (double)200);
            minute.SetValue(Canvas.LeftProperty, (double)200);
            second.SetValue(Canvas.LeftProperty, (double)200);
            hour_rotate.CenterX = hour.Width / 2;
            hour_rotate.CenterY = hour.Height;
            minute_rotate.CenterX = minute.Width / 2;
            minute_rotate.CenterY = minute.Height;
            second_rotate.CenterX = second.Width / 2;
            second_rotate.CenterY = second.Height;
            hour.RenderTransform = hour_rotate;
            minute.RenderTransform = minute_rotate;
            second.RenderTransform = second_rotate;
            timerVideoTime.Start();
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            double hour = (double) DateTime.Now.TimeOfDay.Hours;
            double minute = (double)DateTime.Now.TimeOfDay.Minutes;
            double seconds = (double) DateTime.Now.TimeOfDay.Seconds;

            hour_rotate.Angle = hour * 30;
            minute_rotate.Angle = minute * 6; 
            second_rotate.Angle = seconds * 6;
        }
    }
}
