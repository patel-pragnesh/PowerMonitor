using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Model
{
    public class Module : INotifyPropertyChanged
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
        #region On
        private bool _on;
        public bool On
        {
            get
            {
                return _on;
            }
            set
            {
                if (value == _on)
                    return;
                _on = value;
                RaisePropertyChanged("On");
            }

        }
        #endregion
        #region IsSelected
        private bool _isSelected;
        public bool IsSelected
        {
            get
            {
                return _isSelected;
            }
            set
            {
                if (value == _isSelected)
                    return;
                _isSelected = value;
                RaisePropertyChanged("IsSelected");
            }

        }
        #endregion
        #region Profil
        private Profile _profil;
        public Profile Profil
        {
            get
            {
                return _profil;
            }
            set
            {
                if (value == _profil)
                    return;
                _profil = value;
                RaisePropertyChanged("Profil");
            }

        }
        #endregion
        public Module(string name, bool on, Profile profil)
        {
            Name = name;
            On = on;
            IsSelected = true;
            Profil = profil;
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
