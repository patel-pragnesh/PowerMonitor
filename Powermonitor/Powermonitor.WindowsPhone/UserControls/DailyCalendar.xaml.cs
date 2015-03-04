using Powermonitor.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Xaml.Shapes;

// The User Control item template is documented at http://go.microsoft.com/fwlink/?LinkId=234236

namespace Powermonitor.UserControls
{
    public sealed partial class DailyCalendar : UserControl
    {
        public DailyCalendar()
        {
            this.InitializeComponent();
            //this.DataContext = this;
            //var yolo = this.DataContext;
            DataTemplate TimeTemplate = Resources["TimeTemplate"] as DataTemplate;
            DataTemplate EventTemplate = Resources["EventTemplate"] as DataTemplate;
            for (int i = 0; i < 24; ++i)
            {
                var newTime = TimeTemplate.LoadContent() as UIElement;
                var newEvent = EventTemplate.LoadContent() as UIElement;
                string s = i.ToString("00") + ":00";
                newTime.SetValue(DataContextProperty, s);
                newTime.SetValue(HeightProperty, 50);
                newEvent.SetValue(HeightProperty, 50);
                newEvent.SetValue(NameProperty, i.ToString());
                TimeStackPanel.Children.Add(newTime);
                EventStackPanel.Children.Add(newEvent);
            }
        }

        private void UserControl_DataContextChanged(FrameworkElement sender, DataContextChangedEventArgs args)
        {
            if (args.NewValue != null && args.NewValue.GetType() == typeof(ObservableCollection<TimeSlot>))
            {
                var children = this.EventStackPanel.Children;
                foreach (TimeSlot ts in args.NewValue as ObservableCollection<TimeSlot>)
                {
                    foreach (Border e in children)
                    {
                        var toto = e.Name;
                        var titi = ts.DateBeginning.Hour.ToString();
                        if (e.Name == ts.DateBeginning.Hour.ToString())
                        {
                            int hourDiff = (ts.DateEnd.Hour - ts.DateBeginning.Hour);
                            if (hourDiff > 0)
                            {
                                int newHeight = (int)(((ts.DateEnd - ts.DateBeginning).TotalMinutes * 50) / 60);
                                e.Height = newHeight;
                            }
                            e.Child = new Rectangle()
                            {
                                Height = (int)(((ts.DateEnd - ts.DateBeginning).TotalMinutes * e.Height) / 60),
                                Width = e.Width,
                                Fill = new SolidColorBrush(Colors.Blue),
                                Margin = new Thickness(0, (int)((ts.DateBeginning.Minute * e.Height) / 60), 0, 0),
                                VerticalAlignment = Windows.UI.Xaml.VerticalAlignment.Top
                            };
                        }
                    }
                }
            }
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs rea)
        {
            if (DataContext != null)
            {
                var children = this.EventStackPanel.Children;
                foreach (TimeSlot ts in DataContext as ObservableCollection<TimeSlot>)
                {
                    foreach (Border e in children)
                    {
                        if (e.Name == ts.DateBeginning.Hour.ToString())
                        {
                            int hourDiff = (ts.DateEnd.Hour - ts.DateBeginning.Hour);
                            double oldHeight = e.Height;
                            if (hourDiff > 0)
                            {
                                int current = int.Parse(e.Name);
                                int newHeight = (int)(((ts.DateEnd - ts.DateBeginning).TotalMinutes * e.Height) / 60) + (int)((ts.DateBeginning.Minute * oldHeight) / 60);
                                (children.ElementAt(current + hourDiff) as Border).Height = e.Height - (newHeight % e.Height);
                                for (int i = current + 1; i < current + hourDiff; ++i)
                                    (children.ElementAt(i) as Border).Height = 0;
                                e.Height = newHeight;
                            }
                            e.Child = new Rectangle()
                            {
                                Height = (int)(((ts.DateEnd - ts.DateBeginning).TotalMinutes * oldHeight) / 60),
                                Width = e.Width,
                                Fill = new SolidColorBrush(Colors.Blue),
                                Margin = new Thickness(0, (int)((ts.DateBeginning.Minute * oldHeight) / 60), 0, 0),
                                VerticalAlignment = Windows.UI.Xaml.VerticalAlignment.Top
                            };
                        }
                    }
                }
            }
        }
    }
}
