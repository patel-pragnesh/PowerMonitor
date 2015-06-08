using Newtonsoft.Json;
using Powermonitor.Common;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Model
{
    public class Alert : INotifyPropertyChanged
    {
        [JsonProperty("id")]
        public UInt64 Id { get; private set; }

        #region UnitId
        private UInt64 _unitId;
        [JsonProperty("unitId")]
        public UInt64 UnitId
        {
            get
            {
                return _unitId;
            }
            set
            {
                if (value == _unitId)
                    return;
                _unitId = value;
                RaisePropertyChanged("UnitId");
                RaisePropertyChanged("UnitName");
            }

        }
        #endregion

        #region Value
        private double _value;
        [JsonProperty("value")]
        public double Value
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

        [JsonIgnore]
        public string UnitName
        {
            get
            {
                return Units.units.ElementAt((int)this.UnitId - 1);
            }
        }

        public Alert(UInt64 id = 0, UInt64 unitId = 0, double value = 0)
        {
            Id = id;
            UnitId = unitId;
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
