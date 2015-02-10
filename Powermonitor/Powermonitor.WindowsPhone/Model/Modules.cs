using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Model
{
    public class Modules
    {
        private ObservableCollection<Module> _modules;

        public Modules()
        {
            _modules = new ObservableCollection<Module>();
        }
    }
}
