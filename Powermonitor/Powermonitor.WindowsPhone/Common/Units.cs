using System;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Powermonitor.Common;
using System.Collections.ObjectModel;
using System.ComponentModel;

namespace Powermonitor.Common
{
    public class Units
    {
        #region units
        private static ObservableCollection<string> _units;
        public static ObservableCollection<string> units
        {
            get
            {
                return _units;
            }
            set
            {
                if (value == _units)
                    return;
                _units = value;
                RaisePropertyChanged("units");
            }

        }
        #endregion

        static Units() { UpdateUnits(); }
        public static void UpdateUnits()
        {
            units = new ObservableCollection<string>()
            {
                "Puissance", "Intensité", "Voltage"
            };
        }

        static public event EventHandler<PropertyChangedEventArgs> PropertyChanged;

        static private void RaisePropertyChanged(string propertyName)
        {
            EventHandler<PropertyChangedEventArgs> handler = PropertyChanged;
            if (handler != null)
            {
                handler(null, new PropertyChangedEventArgs(propertyName));
            }
        }
    }
}
