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
using System.Windows.Controls.Pivot;

namespace Lab08
{
    public partial class MainPage : UserControl
    {
        private CxmlCollectionSource _cxml;
        public MainPage()
        {
            InitializeComponent();
            pViewer.Loaded += new RoutedEventHandler(pViewer_Loaded);
        }

        private void _cxml_StateChanged(object sender, CxmlCollectionStateChangedEventArgs e)
        {
            if (e.NewState == CxmlCollectionState.Loaded)
            {
                pViewer.PivotProperties = _cxml.ItemProperties.ToList();
                pViewer.ItemTemplates = _cxml.ItemTemplates;
                pViewer.ItemsSource = _cxml.Items;
            }
        }

        private void pViewer_Loaded(object sender, RoutedEventArgs e)
        {
            _cxml = new CxmlCollectionSource(new Uri(
                "http://pivot.blob.core.windows.net/msdn-magazine/msdnmagazine.cxml", UriKind.Absolute));
            _cxml.StateChanged += _cxml_StateChanged;
        }
    }
}
