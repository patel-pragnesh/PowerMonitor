using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Common
{
    public class Trame
    {
        public JToken _content;
        public Trame(JToken content)
        {
            _content = content;
        }

        public JToken this[string s]
        {
            get
            {
                return _content[s];
            }
            private set
            {
                _content[s] = value;
            }
        }
    }
}
