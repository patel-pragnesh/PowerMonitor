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
        //private Dictionary<string, ObservableCollection<TimeSlot>> _timeSlots;
        //public Dictionary<string, ObservableCollection<TimeSlot>> TimeSlots
        //{
        //    get
        //    {
        //        return _timeSlots;
        //    }
        //    set
        //    {
        //        _timeSlots = value;
        //        RaisePropertyChanged("TimeSlots");
        //    }
        //}

        //public ScheduleViewModel()
        //{
        //    TimeSlots = new Dictionary<string, ObservableCollection<TimeSlot>>();
        //}

        //public void Init()
        //{
        //    //TimeSlots.Add("Monday", new ObservableCollection<TimeSlot>() { new TimeSlot() });
        //    //TimeSlots.Add("Tuesday", new ObservableCollection<TimeSlot>() { new TimeSlot(UnixTimeStampToDateTime(1425309000).Ticks, UnixTimeStampToDateTime(1425316800).Ticks) });
        //    //TimeSlots.Add("Wednesday", new ObservableCollection<TimeSlot>() { new TimeSlot() });
        //    //TimeSlots.Add("Thursday", new ObservableCollection<TimeSlot>() { new TimeSlot() });
        //    //TimeSlots.Add("Friday", new ObservableCollection<TimeSlot>() { new TimeSlot() });
        //    //TimeSlots.Add("Saturday", new ObservableCollection<TimeSlot>() { new TimeSlot() });
        //    //TimeSlots.Add("Sunday", new ObservableCollection<TimeSlot>() { new TimeSlot() });
        //}

        //public static DateTime UnixTimeStampToDateTime(double unixTimeStamp)
        //{
        //    // Unix timestamp is seconds past epoch
        //    System.DateTime dtDateTime = new DateTime(1970, 1, 1, 0, 0, 0, 0, System.DateTimeKind.Utc);
        //    dtDateTime = dtDateTime.AddSeconds(unixTimeStamp).ToLocalTime();
        //    return dtDateTime;
        //}

        //public static double DateTimeToUnixTimestamp(DateTime dateTime)
        //{
        //    return (dateTime - new DateTime(1970, 1, 1).ToLocalTime()).TotalSeconds;
        //}

        public static Profile ToUpdate;
        #region Profile
        private Profile _profile;
        public Profile Profile
        {
            get
            {
                return _profile;
            }
            set
            {
                if (value == _profile)
                    return;
                _profile = value;
                RaisePropertyChanged("Profile");
            }

        }
        #endregion
        private Dictionary<string, TimeSlotsContainer> _timeSlots;
        public Dictionary<string, TimeSlotsContainer> TimeSlots
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
        }

        public void Refresh()
        {
            Profile = ToUpdate;
            TimeSlots = new Dictionary<string, TimeSlotsContainer>();
            TimeSlots.Add("Monday", new TimeSlotsContainer(Profile.Id, DayOfWeek.Monday));
            TimeSlots.Add("Tuesday", new TimeSlotsContainer(Profile.Id, DayOfWeek.Tuesday));
            TimeSlots.Add("Wednesday", new TimeSlotsContainer(Profile.Id, DayOfWeek.Wednesday));
            TimeSlots.Add("Thursday", new TimeSlotsContainer(Profile.Id, DayOfWeek.Thursday));
            TimeSlots.Add("Friday", new TimeSlotsContainer(Profile.Id, DayOfWeek.Friday));
            TimeSlots.Add("Saturday", new TimeSlotsContainer(Profile.Id, DayOfWeek.Saturday));
            TimeSlots.Add("Sunday", new TimeSlotsContainer(Profile.Id, DayOfWeek.Sunday));
            foreach (TimeSlot t in ToUpdate.TimeSlots)
            {
                TimeSlots[t.Beg.Day.ToString()].TimeSlots.Add(t);
            }
        }
    }
}
