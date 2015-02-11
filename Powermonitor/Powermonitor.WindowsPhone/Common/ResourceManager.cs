using Newtonsoft.Json;
using Powermonitor.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Common
{
    public class ResourceManager : Singleton<ResourceManager>
    {
        public Modules Modules { get; private set; }
        public Profiles Profiles { get; private set; }

        public ResourceManager()
        {
            Modules = new Modules();
            Profiles = new Profiles();

            Communication com = Communication.getInstance;
            com.addFunc("Modules", Modules.deserialize);
            com.addFunc("Profiles", Profiles.deserialize);
        }
    }
}
