using GalaSoft.MvvmLight;
using Powermonitor.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.ViewModel
{
    public class ScheduleViewModel : ViewModelBase
    {
        private ModifyProfilViewModel _ModifyViewModel;
        public ModifyProfilViewModel ModifyViewModel {
            get
            {
                return _ModifyViewModel;
            }
            set
            {
                _ModifyViewModel = value;
                RaisePropertyChanged("ModifyViewModel");
            }
        }

        private Dictionary<string, ObservableCollection<TimeSlot>> _timeSlots;
        public Dictionary<string, ObservableCollection<TimeSlot>> TimeSlots
        {
            get
            {
                return _timeSlots;
            }
            set
            {
                _timeSlots = value;
                RaisePropertyChanged("TimeSlots");
            }
        }

        public ScheduleViewModel()
        {
            ModifyViewModel = new ModifyProfilViewModel();
            //TimeSlots = new Dictionary<string, ObservableCollection<TimeSlot>>();
        }

        public void Init()
        {
            TimeSlots.Add("Monday", new ObservableCollection<TimeSlot>() { new TimeSlot() });
            TimeSlots.Add("Tuesday", new ObservableCollection<TimeSlot>() { new TimeSlot(UnixTimeStampToDateTime(1425309000).Ticks, UnixTimeStampToDateTime(1425316800).Ticks) });
            TimeSlots.Add("Wednesday", new ObservableCollection<TimeSlot>() { new TimeSlot() });
            TimeSlots.Add("Thursday", new ObservableCollection<TimeSlot>() { new TimeSlot() });
            TimeSlots.Add("Friday", new ObservableCollection<TimeSlot>() { new TimeSlot() });
            TimeSlots.Add("Saturday", new ObservableCollection<TimeSlot>() { new TimeSlot() });
            TimeSlots.Add("Sunday", new ObservableCollection<TimeSlot>() { new TimeSlot() });
        }

        public static DateTime UnixTimeStampToDateTime(double unixTimeStamp)
        {
            // Unix timestamp is seconds past epoch
            System.DateTime dtDateTime = new DateTime(1970, 1, 1, 0, 0, 0, 0, System.DateTimeKind.Utc);
            dtDateTime = dtDateTime.AddSeconds(unixTimeStamp).ToLocalTime();
            return dtDateTime;
        }

        public static double DateTimeToUnixTimestamp(DateTime dateTime)
        {
            return (dateTime - new DateTime(1970, 1, 1).ToLocalTime()).TotalSeconds;
        }
    }
}
