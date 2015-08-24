using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Model
{
    public class Info : INotifyPropertyChanged
    {
        #region Time
        private int _time;
        [JsonProperty("time")]
        public int Time
        {
            get
            {
                return _time;
            }
            set
            {
                if (value == _time)
                    return;
                _time = value;
                RaisePropertyChanged("Time");
            }

        }
        #endregion

        #region Value
        private int _value;
        [JsonProperty("value")]
        public int Value
        {
            get
            {
                return _value;
            }
            set
            {
                if (value == _value)
                    return;
                _value = value;
                RaisePropertyChanged("Value");
            }

        }
        #endregion

        public Info(int time = 0, int value = 0)
        {
            Time = time;
            Value = value;
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
