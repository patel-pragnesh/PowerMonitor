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
                RaisePropertyChanged("Status");
            }

        }
        #endregion
        #region Profile
        private Profile _defaultProfile;
        public Profile DefaultProfile
        {
            get
            {
                return _defaultProfile;
            }
            set
            {
                if (value == _defaultProfile)
                    return;
                _defaultProfile = value;
                RaisePropertyChanged("DefaultProfile");
            }

        }
        #endregion
        public UInt64 Id { get; private set; }
        //public UInt64? DefaultProfile { get; private set; }
        public UInt64 InternalProfileId { get; private set; }

        public Module(string name = "", bool status = false, UInt64 id = 0, Profile defaultProfile = null, UInt64 internalProfileId = 0)
        {
            Name = name;
            _status = status;
            Id = id;
            DefaultProfile = defaultProfile;
            InternalProfileId = internalProfileId;
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
