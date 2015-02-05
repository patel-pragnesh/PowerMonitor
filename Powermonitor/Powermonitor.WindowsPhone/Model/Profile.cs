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

        public ObservableCollection<Alert> Alerts { get; private set; }
        public Profile(String name)
        {
            Name = name;
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
