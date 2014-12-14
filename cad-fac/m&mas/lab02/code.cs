using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using Calculator.Resources;

namespace Calculator {
    public partial class MainPage : PhoneApplicationPage {
        bool dot_set = false;
        int last_oper = 0;
        enum OPER { EQU = 0, PLUS, MINUS, MUL, DIV }
        
        public MainPage() {
            InitializeComponent();
        }
        private void calculate( int operation ) {
            if (mem.Text != "") {
                double val1 = Convert.ToDouble(mem.Text);
                double val2 = Convert.ToDouble(input_box.Text);
                string val3 = "";
                switch (last_oper) {
                    case (int)OPER.PLUS:
                        val3 = Convert.ToString(val1 + val2);
                        break;
                    case (int)OPER.MINUS:
                        val3 = Convert.ToString(val1 - val2);
                        break;
                    case (int)OPER.MUL:
                        val3 = Convert.ToString(val1 * val2);
                        break;
                    case (int)OPER.DIV:
                        if (val2 != 0) {
                            val3 = Convert.ToString(val1 / val2);
                        } else {
                            val3 = "error: divide by zero!";
                        }
                        break;
                }
                last_oper = operation;
                if (operation != (int)OPER.EQU) {
                    mem.Text = val3;
                    input_box.Text = "";
                } else {
                    input_box.Text = val3;
                    mem.Text = "";
                }
            } else {
                mem.Text = input_box.Text;
                input_box.Text = "";
                dot_set = false;
                last_oper = operation;
            }
        }
        private void clear_Click(object sender, RoutedEventArgs e) {
            input_box.Text = "";
            mem.Text = "";
            dot_set = false;
        }
        private void n0_Click(object sender, RoutedEventArgs e) {
            input_box.Text += "0";
        }
        private void n2_Click(object sender, RoutedEventArgs e) {
            input_box.Text += "2";
        }
        private void n1_Click(object sender, RoutedEventArgs e) {
            input_box.Text += "1";
        }
        private void n3_Click(object sender, RoutedEventArgs e) {
            input_box.Text += "3";
        }
        private void dot_Click(object sender, RoutedEventArgs e) {
            if (dot_set == false) {
                dot_set = true;
                input_box.Text += ".";
            }
        }
        private void n7_Click(object sender, RoutedEventArgs e) {
            input_box.Text += "7";
        }
        private void n8_Click(object sender, RoutedEventArgs e) {
            input_box.Text += "8";
        }
        private void n9_Click(object sender, RoutedEventArgs e) {
            input_box.Text += "9";
        }
        private void n4_Click(object sender, RoutedEventArgs e) {
            input_box.Text += "4";
        }
        private void n5_Click(object sender, RoutedEventArgs e) {
            input_box.Text += "5";
        }
        private void n6_Click(object sender, RoutedEventArgs e) {
            input_box.Text += "6";
        }
        private void sqrt_Click(object sender, RoutedEventArgs e) {
            if (input_box.Text != "") {
                double value = Math.Sqrt(Convert.ToDouble(input_box.Text));
                input_box.Text = value.ToString();
            }
        }
        private void pow_Click(object sender, RoutedEventArgs e) {
            if (input_box.Text != "") {
                double value = Math.Pow(Convert.ToDouble(input_box.Text), 2.0);
                input_box.Text = value.ToString();
            }
        }
        private void equ_Click(object sender, RoutedEventArgs e) {
            calculate((int)OPER.EQU);
        }
        private void plus_Click(object sender, RoutedEventArgs e) {
            calculate((int)OPER.PLUS);
        }
        private void minus_Click(object sender, RoutedEventArgs e) {
            calculate((int)OPER.MINUS);
        }
        private void mul_Click(object sender, RoutedEventArgs e) {
            calculate((int)OPER.MUL);
        }
        private void div_Click(object sender, RoutedEventArgs e) {
            calculate((int)OPER.DIV);
        }
        private void pm_Click(object sender, RoutedEventArgs e) {
            if (input_box.Text != "") {
                input_box.Text = Convert.ToString(-Convert.ToDouble(input_box.Text));
            }
        }
    }
}