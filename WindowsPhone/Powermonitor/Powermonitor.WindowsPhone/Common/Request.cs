using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Common
{
    public class Request
    {
        public JObject Message { get; private set; }
        public Action<JObject, JObject> Callback { get; private set; }
        public Request(JObject message = null, Action<JObject, JObject> callback = null)
        {
            Message = message;
            Callback = callback;
        }
    }
}
