using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Model
{
    public class Profile : INotifyPropertyChanged
    {
        #region Name
        private string _name;
        public string Name
        {
            get
            {
                return _name;
            }
            set
            {
                if (value == _name)
                    return;
                _name = value;
                RaisePropertyChanged("Name");
            }

        }
        #endregion
        #region Polling
        private uint _polling;
        public uint Polling
        {
            get
            {
                return _polling;
            }
            set
            {
                if (value == _polling)
                    return;
                _polling = value;
                RaisePropertyChanged("Polling");
            }

        }
        #endregion

        public UInt64 Id { get; private set; }
        public ObservableCollection<Alert> Alerts { get; private set; }
        public ObservableCollection<TimeSlot> TimeSlots { get; private set; }
        public Profile(String name = "", UInt64 id = 0, uint polling = 1, ObservableCollection<Alert> alerts = null, ObservableCollection<TimeSlot> timeslots = null)
        {
            Name = name;
            Id = id;
            Polling = polling;
            Alerts = alerts;
            TimeSlots = timeslots;
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void RaisePropertyChanged(string propertyName)
        {
            if (this.PropertyChanged != null)
            {
                this.PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }
    }
}
