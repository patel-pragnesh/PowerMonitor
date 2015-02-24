using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Model
{
    public class Session
    {
        public string token { get; private set; }
        public UInt64 userId { get; private set; }
        public Session(string t = "", UInt64 u = 0)
        {
            token = t;
            userId = u;
        }

        public bool isEmpty() { return token.Length > 0; }
    }
}
