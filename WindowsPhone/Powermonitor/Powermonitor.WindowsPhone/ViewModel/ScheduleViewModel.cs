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

        public void SetTimeSlots()
        {
            ObservableCollection<TimeSlot> ts = new ObservableCollection<TimeSlot>();
            foreach (TimeSlotsContainer container in TimeSlots.Values)
            {
                foreach (TimeSlot t in container.TimeSlots)
                {
                    ts.Add(t);
                }
            }
            ToUpdate.TimeSlots = ts;
        }
    }
}
