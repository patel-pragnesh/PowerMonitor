using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Powermonitor.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Common
{
    public class ProfilesHandler : AResource
    {
        private DateTime? _lastCheck = null;
        private ObservableCollection<Profile> _profileList;
        public ObservableCollection<Profile> ProfileList
        {
            get
            {
                var now = DateTime.Now;
                if (_profileList.Count == 0 || _lastCheck == null || (now - _lastCheck) > new TimeSpan(0, 5, 0))
                {
                    _lastCheck = DateTime.Now;
                    Communication.getInstance.sendFuncs["getProfiles"].DynamicInvoke();
                }
                return _profileList;
            }
            private set
            {
                if (value == _profileList)
                    return;
                RaisePropertyChanged("ProfileList");
                _profileList = value;
            }
        }

        public ProfilesHandler()
        {
            ProfileList = new ObservableCollection<Profile>();
        }

        public override bool deserialize(Trame trame)
        {
            ProfileList = new ObservableCollection<Profile>(JsonConvert.DeserializeObject<List<Profile>>(trame._content.ToString()));
            return true;
        }

        public override string serialize()
        {
            return "";
        }

        public Profile getById(UInt64 id)
        {
            foreach (var p in _profileList) {
                if (p.Id == id)
                    return p;
            }
            return null;
        }
    }
}
