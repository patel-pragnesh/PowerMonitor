using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Powermonitor.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Common
{
    public class ModulesHandler : AResource
    {
        private DateTime? _lastCheck = null;
        private ObservableCollection<Module> _moduleList;
        public ObservableCollection<Module> ModuleList {
            get
            {
                if (ResourceManager.getInstance != null && ResourceManager.getInstance.Profiles != null)
                    ResourceManager.getInstance.Profiles.PropertyChanged += Profiles_PropertyChanged;
                var now = DateTime.Now;
                if (_moduleList.Count == 0 || _lastCheck == null || (now - _lastCheck) > new TimeSpan(0, 5, 0))
                {
                    _lastCheck = DateTime.Now;
                    Communication.getInstance.sendFuncs["getModules"].DynamicInvoke();
                }
                return _moduleList;
            }
            private set
            {
                if (value == _moduleList)
                    return;
                _moduleList = value;
            }
        }

        public ModulesHandler()
        {
            ModuleList = new ObservableCollection<Module>();
        }

        private void Profiles_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            var profiles = ResourceManager.getInstance.Profiles;
            foreach (var m in _moduleList)
            {
                if (m.DefaultProfile.HasValue)
                    m.Profile = profiles.getById(m.DefaultProfile.Value);
            }
        }

        public override bool deserialize(Trame trame)
        {
            _moduleList.Clear();
            var tmp = new ObservableCollection<Module>(JsonConvert.DeserializeObject<List<Module>>(trame._content.ToString()));
            foreach (var module in tmp)
                _moduleList.Add(module);
            return true;
        }

        public override string serialize()
        {
            return "";
        }
    }
}
