using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Common
{
    public interface IResource
    {
        string serialize();
        bool deserialize(Trame trame);
    }
}
