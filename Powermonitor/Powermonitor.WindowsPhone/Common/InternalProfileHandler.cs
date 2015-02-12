using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Powermonitor.Model;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Common
{
    public class InternalProfileHandler : AResource
    {
        private DateTime? _lastCheck = null;
        private Profile _profile;
        private Profile Profile
        {
            get
            {
                //var now = DateTime.Now;
                //if (_lastCheck == null || (now - _lastCheck) > new TimeSpan(0, 5, 0))
                //{
                //    _lastCheck = DateTime.Now;
                //    Communication.getInstance.sendFuncs["getInternalProfile"].DynamicInvoke();
                //}
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

        public Profile getProfile(UInt64 id)
        {
            var now = DateTime.Now;
            if (_lastCheck == null || (now - _lastCheck) > new TimeSpan(0, 5, 0) || id != _profile.Id)
            {
                _lastCheck = DateTime.Now;
                Communication.getInstance.sendFuncs["getInternalProfile"].DynamicInvoke(id);
            }
            return _profile;
        }

        public InternalProfileHandler()
        {
            Profile = new Profile("toto");
        }

        public override bool deserialize(Trame trame)
        {
            Profile = JsonConvert.DeserializeObject<Profile>(trame._content.ToString());
            return true;
        }

        public override string serialize()
        {
            return "";
        }
    }
}
