using Powermonitor.Common;
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
        #region Status
        private bool _status;
        public bool Status
        {
            get
            {
                return _status;
            }
            set
            {
                if (value == _status)
                    return;
                _status = value;
                Communication.getInstance.sendFuncs["turnOnOff"].DynamicInvoke(_status, Id);
                RaisePropertyChanged("Status");
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
        #region Profile
        private Profile _profile;
        public Profile Profile
        {
            get
            {
                if (_profile == null)
                    _profile = ResourceManager.getInstance.Profiles.getById(Id);
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
        public UInt64 Id { get; private set; }
        public UInt64? DefaultProfile { get; private set; }
        public UInt64 InternalProfile { get; private set; }

        public Module(string name = "", bool status = false, UInt64 id = 0, UInt64? defaultProfile = null, UInt64 internalProfile = 0)
        {
            Name = name;
            _status = status;
            IsSelected = true;
            Id = id;
            DefaultProfile = defaultProfile;
            InternalProfile = internalProfile;
            _profile = null;
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
