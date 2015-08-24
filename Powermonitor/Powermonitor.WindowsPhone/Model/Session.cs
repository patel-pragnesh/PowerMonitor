using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Model
{
    public class Session
    {
        public string token { get; set; }
        public UInt64 userId { get; set; }
        public Session(string t = "", UInt64 u = 0)
        {
            token = t;
            userId = u;
        }

        public bool IsEmpty() { return token.Length == 0; }
    }
}
