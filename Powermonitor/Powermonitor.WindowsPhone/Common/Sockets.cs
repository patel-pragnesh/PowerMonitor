using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Networking.Sockets;
using System.Threading;
using Windows.Networking;

namespace Powermonitor.Common
{
    public class Sockets
    {
        StreamSocket _socket = null;
        private HostName serverHost;
        private string serverHostnameString;
        private string serverPort;
        private bool connected = false;
        private bool closing = false;

        public Sockets()
        {
            _socket = new StreamSocket();
        }
    }
}
