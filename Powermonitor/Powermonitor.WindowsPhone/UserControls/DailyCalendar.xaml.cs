using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Powermonitor.Common;
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
        private UInt64 current;
        public DailyCalendar()
        {
            this.InitializeComponent();
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
            current = 0;
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
            foreach (TimeSlot ts in (DataContext as TimeSlotsContainer).TimeSlots)
            {
                foreach (Border e in children)
                {
                    if (e.Name == ts.Beg.AsHours().ToString())
                    {
                        int hourDiff = (ts.End.AsHours() - ts.Beg.AsHours());
                        double oldHeight = e.Height;
                        if (hourDiff > 0)
                        {
                            int current = int.Parse(e.Name);
                            int newHeight = (int)(((ts.End.Minute - ts.Beg.Minute) * e.Height) / 60) + (int)((ts.Beg.MinutesInHour() * oldHeight) / 60);
                            (children.ElementAt(current + hourDiff) as Border).Height = e.Height - (newHeight % e.Height);
                            for (int i = current + 1; i < current + hourDiff; ++i)
                                (children.ElementAt(i) as Border).Height = 0;
                            e.Height = newHeight;
                        }
                        e.Child = new Rectangle()
                        {
                            Name = ts.Id.ToString(),
                            Height = (int)(((ts.End.Minute - ts.Beg.Minute) * oldHeight) / 60),
                            Width = e.Width,
                            Fill = new SolidColorBrush(Colors.Blue),
                            Margin = new Thickness(0, (int)((ts.Beg.MinutesInHour() * oldHeight) / 60), 0, 0),
                            VerticalAlignment = Windows.UI.Xaml.VerticalAlignment.Top,
                        };
                        e.Child.Holding += Child_Holding;
                    }
                }
            }
        }

        private void Child_Holding(object sender, HoldingRoutedEventArgs e)
        {
            current = UInt64.Parse((sender as Rectangle).Name);
            FlyoutBase flyoutBase = FlyoutBase.GetAttachedFlyout((((sender as FrameworkElement).Parent as FrameworkElement).Parent as FrameworkElement).Parent as FrameworkElement);
//            FlyoutBase flyoutBase = FlyoutBase.GetAttachedFlyout(sender as FrameworkElement);

            flyoutBase.ShowAt(sender as FrameworkElement); 
            
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs rea)
        {
            if (DataContext != null)
            {
                SetPlanning();
            }
        }

        async private void EventBorder_Tapped(object sender, TappedRoutedEventArgs e)
        {
            Border b = sender as Border;
            int h = int.Parse(b.Name);
            if (b.Child == null)
                current = 0;
            else
                current = UInt64.Parse((b.Child as Rectangle).Name);
            BeginTimePicker.Time = new TimeSpan(h, 0, 0);
            EndTimePicker.Time = new TimeSpan(h + 1, 0, 0);
            await ChooseTimeDialog.ShowAsync();
        }

        private void ChooseTimeDialog_PrimaryButtonClick(ContentDialog sender, ContentDialogButtonClickEventArgs args)
        {
            TimeSlotsContainer container = (DataContext as TimeSlotsContainer);
            if (current == 0)
                Communication.getInstance.sendFuncs["addTimeSlot"].DynamicInvoke((Action<JObject, JObject>)AddTimeSlotCallback,
                    container.ProfileId, new Time(container.DayOfWeek, (int)BeginTimePicker.Time.TotalMinutes), new Time(container.DayOfWeek, (int)EndTimePicker.Time.TotalMinutes));
            else
                Communication.getInstance.sendFuncs["updateTimeSlot"].DynamicInvoke((Action<JObject, JObject>)UpdateTimeSlotCallback,
                    current, new Time(container.DayOfWeek, (int)BeginTimePicker.Time.TotalMinutes), new Time(container.DayOfWeek, (int)EndTimePicker.Time.TotalMinutes));
            //DateTime tmp = GetNextWeekday(DateTime.Now, DayOfWeek.Tuesday);
            //DateTime b = new DateTime(tmp.Year, tmp.Month, tmp.Day, BeginTimePicker.Time.Hours, BeginTimePicker.Time.Minutes, 0);
            //DateTime e = new DateTime(tmp.Year, tmp.Month, tmp.Day, EndTimePicker.Time.Hours, EndTimePicker.Time.Minutes, 0);
            //(DataContext as ObservableCollection<TimeSlot>).Add(new TimeSlot(b.Ticks, e.Ticks));
        }
        private void AddTimeSlotCallback(JObject request, JObject response)
        {
            if (response["returnCode"] == null || response["returnCode"].ToObject<UInt64>() == 0)
            {
                TimeSlotsContainer container = (DataContext as TimeSlotsContainer);
                EmptyPlanning();
                container.TimeSlots.Add(new TimeSlot(response["id"].ToObject<UInt64>(),
                    JsonConvert.DeserializeObject<Time>(request["beg"].ToString()),
                    JsonConvert.DeserializeObject<Time>(request["end"].ToString())));
                SetPlanning();
            }
            //else
            //    HandleError(response);
        }

        private void UpdateTimeSlotCallback(JObject request, JObject response)
        {
            if (response["returnCode"] == null || response["returnCode"].ToObject<UInt64>() == 0)
            {
                TimeSlotsContainer container = (DataContext as TimeSlotsContainer);
                EmptyPlanning();
                container.TimeSlots.RemoveAll(ts => ts.Id == request["id"].ToObject<UInt64>());
                container.TimeSlots.Add(new TimeSlot(request["id"].ToObject<UInt64>(),
                    JsonConvert.DeserializeObject<Time>(request["beg"].ToString()),
                    JsonConvert.DeserializeObject<Time>(request["end"].ToString())));
                SetPlanning();
            }
            //else
            //    HandleError(response);
        }

        private void DeleteTimeSlotCallback(JObject request, JObject response)
        {
            if (response["returnCode"] == null || response["returnCode"].ToObject<UInt64>() == 0)
            {
                TimeSlotsContainer container = (DataContext as TimeSlotsContainer);
                EmptyPlanning();
                container.TimeSlots.RemoveAll(ts => ts.Id == request["id"].ToObject<UInt64>());
                SetPlanning();
            }
            //else
            //    HandleError(response);
        }

        private void confirmDelete_PrimaryButtonClick(ContentDialog sender, ContentDialogButtonClickEventArgs args)
        {
            Communication.getInstance.sendFuncs["deleteTimeSlot"].DynamicInvoke((Action<JObject, JObject>)DeleteTimeSlotCallback, current);
        }

        private async void bDelete_Click(object sender, RoutedEventArgs e)
        {
            await confirmDelete.ShowAsync();
        }

        private async void bUpdate_Click(object sender, RoutedEventArgs e)
        {
            TimeSlotsContainer container = (DataContext as TimeSlotsContainer);
            TimeSlot ts = container.TimeSlots.First(t => t.Id == current) as TimeSlot;
            BeginTimePicker.Time = new TimeSpan(ts.Beg.AsHours(), 0, 0);
            EndTimePicker.Time = new TimeSpan(ts.End.AsHours(), 0, 0);
            await ChooseTimeDialog.ShowAsync();
        }
    }
}
