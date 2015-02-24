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
        //public ModulesHandler Modules { get; private set; }
        //public ProfilesHandler Profiles { get; private set; }
        //public InternalProfileHandler InternalProfileHandler { get; private set; }

        public ResourceManager()
        {
            //Profiles = new ProfilesHandler();
            //Modules = new ModulesHandler();
            //InternalProfileHandler = new InternalProfileHandler();

            //Communication com = Communication.getInstance;
           // com.addFunc("Modules", Modules.deserialize);
           // com.addFunc("Profiles", Profiles.deserialize);
           // com.addFunc("InternalProfile", InternalProfileHandler.deserialize);
        }
    }
}
