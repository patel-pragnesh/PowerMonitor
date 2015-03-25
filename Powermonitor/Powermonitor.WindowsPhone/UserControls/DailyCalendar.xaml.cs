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
        private readonly int BorderHeight = 50; 
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
                newTime.SetValue(HeightProperty, BorderHeight);
                newEvent.SetValue(HeightProperty, BorderHeight);
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
                                int newHeight = (int)(((ts.DateEnd - ts.DateBeginning).TotalMinutes * BorderHeight) / 60);
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

        private void EmptyPlanning()
        {
            var children = this.EventStackPanel.Children;
            foreach (Border e in children)
            {
                e.Child = null;
                e.Height = BorderHeight;
            }
        }

        private void SetPlanning()
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
                            VerticalAlignment = Windows.UI.Xaml.VerticalAlignment.Top,
                        };
                        e.Child.Tapped += Child_Tapped;
                    }
                }
            }
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs rea)
        {
            if (DataContext != null)
            {
                SetPlanning();
            }
        }

        private void Child_Tapped(object sender, TappedRoutedEventArgs e)
        {
            FlyoutBase flyoutBase = FlyoutBase.GetAttachedFlyout((((sender as FrameworkElement).Parent as FrameworkElement).Parent as FrameworkElement).Parent as FrameworkElement);

          //  flyoutBase.ShowAt((sender as FrameworkElement).Parent as FrameworkElement);
        }

        async private void TimeBorder_Tapped(object sender, TappedRoutedEventArgs e)
        {
            await ChooseTimeDialog.ShowAsync();
        }

        async private void EventBorder_Tapped(object sender, TappedRoutedEventArgs e)
        {
            Border b = sender as Border;
            int h = int.Parse(b.Name);
            BeginTimePicker.Time = new TimeSpan(h, 0, 0);
            EndTimePicker.Time = new TimeSpan(h + 1, 0, 0);
            await ChooseTimeDialog.ShowAsync();
        }

        private void ChooseTimeDialog_PrimaryButtonClick(ContentDialog sender, ContentDialogButtonClickEventArgs args)
        {
            EmptyPlanning();
            DateTime tmp = GetNextWeekday(DateTime.Now, DayOfWeek.Tuesday);
            DateTime b = new DateTime(tmp.Year, tmp.Month, tmp.Day, BeginTimePicker.Time.Hours, BeginTimePicker.Time.Minutes, 0);
            DateTime e = new DateTime(tmp.Year, tmp.Month, tmp.Day, EndTimePicker.Time.Hours, EndTimePicker.Time.Minutes, 0);
            (DataContext as ObservableCollection<TimeSlot>).Add(new TimeSlot(b.Ticks, e.Ticks));
            SetPlanning();
        }

        public static DateTime GetNextWeekday(DateTime start, DayOfWeek day)
        {
            // The (... + 7) % 7 ensures we end up with a value in the range [0, 6]
            int daysToAdd = ((int)day - (int)start.DayOfWeek + 7) % 7;
            return start.AddDays(daysToAdd);
        }
    }
}
