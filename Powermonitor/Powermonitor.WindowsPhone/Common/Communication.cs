using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Networking.Sockets;
using System.Threading;
using Windows.Networking;
using Windows.Storage.Streams;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Collections;
using Newtonsoft.Json.Linq;

namespace Powermonitor.Common
{
    public class Communication
    {
        private readonly StreamSocket _clientSocket;
        private bool _connected;
        private DataReader _dataReader;
        private ObservableCollection<String> _toSend;
        private ObservableCollection<String> _received;
        public Dictionary<string, Delegate> sendFuncs { get; private set; }
        private Dictionary<string, Func<Trame, bool>> recvFuncs;

        public Communication()
        {
            _clientSocket = new StreamSocket();
            this.Connect();
            _toSend = new ObservableCollection<string>();
            _toSend.CollectionChanged += sendMsgs;
            _received = new ObservableCollection<string>();
            sendFuncs = new Dictionary<string, Delegate>();
            recvFuncs = new Dictionary<string, Func<Trame, bool>>();

            sendFuncs.Add("login", new Action<string, string>(login));
            sendFuncs.Add("change_username", new Action<int, string>(changeUsername));
            sendFuncs.Add("change_password", new Action<int, string>(changePassword));
            sendFuncs.Add("new_account", new Action<int, string, string>(newAccount));
            sendFuncs.Add("getModules", new Action(getModules));
        }
        
       private async Task<bool> Connect()
        {
            if (_connected) return false;
            var hostname = new HostName("127.0.0.1");
            await _clientSocket.ConnectAsync(hostname, "4242");
            _connected = true;
            _dataReader = new DataReader(_clientSocket.InputStream)
            {
                InputStreamOptions = InputStreamOptions.Partial
            };
            ReadData();
            return true;

        }

        async private void ReadData()
        {
            if (!_connected || _clientSocket == null) return;
            uint s = await _dataReader.LoadAsync(4);
            byte[] test = new byte[4];
            _dataReader.ReadBytes(test);
            uint size = BitConverter.ToUInt32(test, 0);
            uint totalRead = 0;
            string data = "";
            while (totalRead < size)
            {
                uint actual = await _dataReader.LoadAsync(size - totalRead);
                data += _dataReader.ReadString(actual);
                totalRead += actual;
            }
//            string data = _dataReader.ReadString(s);
            _received.Add(data);
            ReadData();
        }

        async private void SendRawMessage(string message)
        {
            var writer = new DataWriter(_clientSocket.OutputStream);
            byte[] header = BitConverter.GetBytes(message.Length);
            writer.WriteBytes(header);
            writer.WriteString(message + "\r\n");
            await writer.StoreAsync();
            await writer.FlushAsync();
            writer.DetachStream();
           //_clientSocket.Dispose();
            //_connected = false;
        }

        private void sendMsgs(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (_toSend.Count > 0)
            {
                String msg = _toSend.First();
                SendRawMessage(msg);
                _toSend.Remove(msg);
            }
        }

        public void addMsg(string msg)
        {
            _toSend.Add(msg);
        }

        public bool addFunc(string key, Func<Trame, bool> f)
        {
            if (recvFuncs.Keys.Contains(key))
                return false;
            recvFuncs.Add(key, f);
            return true;
        }

        #region SendCmds
        private void login(string username, string password)
        {
            JObject json = new JObject() { { "cmd", "login" }, { "username", username }, { "password", password } };
            addMsg(json.ToString());
        }

        private void changeUsername(int userid, string username)
        {
            JObject json = new JObject() { { "cmd", "change_username" }, { "userid", userid }, { "username", username } };
            addMsg(json.ToString());
        }

        private void changePassword(int userid, string password)
        {
            JObject json = new JObject() { { "cmd", "change_password" }, { "userid", userid }, { "password", password } };
            addMsg(json.ToString());
        }

        private void newAccount(int userid, string username, string password)
        {
            JObject json = new JObject() { { "cmd", "new_account" }, { "userid", userid }, { "username", username }, { "password", password } };
            addMsg(json.ToString());
        }

        private void getModules()
        {
            JObject json = new JObject() { "cmd", "getModules" };
            addMsg(json.ToString());
        }
        #endregion
    }
}
