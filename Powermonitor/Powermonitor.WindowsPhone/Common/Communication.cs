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
using Newtonsoft.Json;

namespace Powermonitor.Common
{
    public class Communication : Singleton<Communication>
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
            _received.CollectionChanged += receivedMsgs;
            sendFuncs = new Dictionary<string, Delegate>();
            recvFuncs = new Dictionary<string, Func<Trame, bool>>();

            sendFuncs.Add("login", new Action<string, string>(login));
            sendFuncs.Add("change_username", new Action<int, string>(changeUsername));
            sendFuncs.Add("change_password", new Action<int, string>(changePassword));
            sendFuncs.Add("new_account", new Action<int, string, string>(newAccount));
            sendFuncs.Add("getModules", new Action(getModules));
            sendFuncs.Add("getProfiles", new Action(getProfiles));
            sendFuncs.Add("getInternalProfile", new Action<UInt64>(getInternalProfile));
            sendFuncs.Add("renameModule", new Action<string, UInt64>(renameModule));
            sendFuncs.Add("turnOnOff", new Action<bool, UInt64>(turnOnOff));
            sendFuncs.Add("changeAssociatedProfile", new Action<UInt64, UInt64>(changeAssociatedProfile));
            sendFuncs.Add("deleteProfile", new Action<UInt64>(deleteProfile));
        }
        
       private async Task<bool> Connect()
        {
            if (_connected) return false;
            var hostname = new HostName("192.168.1.11");
            await _clientSocket.ConnectAsync(hostname, "8080");
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
            byte[] sizeBuff = new byte[4];
            _dataReader.ReadBytes(sizeBuff);
            if (BitConverter.IsLittleEndian)
                Array.Reverse(sizeBuff);
            uint size = BitConverter.ToUInt32(sizeBuff, 0);
            uint totalRead = 0;
            string data = "";
            while (totalRead < size)
            {
                uint actual = await _dataReader.LoadAsync(size - totalRead);
                data += _dataReader.ReadString(actual);
                totalRead += actual;
            }
            _received.Add(data);
            ReadData();
        }

        async private void SendRawMessage(string message)
        {
            var writer = new DataWriter(_clientSocket.OutputStream);
            byte[] header = BitConverter.GetBytes(message.Length);
            if (BitConverter.IsLittleEndian)
                Array.Reverse(header);
            writer.WriteBytes(header);
            writer.WriteString(message);
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

        private void receivedMsgs(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (_received.Count > 0)
            {
                String msg = _received.First();
                var jObj = JsonConvert.DeserializeObject<Dictionary<string, JToken>>(msg);
                foreach (var cmd in jObj)
                {
                    if (recvFuncs.Keys.Contains(cmd.Key))
                    {
                        var content = cmd.Value;
                        Trame trame = new Trame(content);
                        recvFuncs[cmd.Key].DynamicInvoke(trame);
                    }
                }
                _received.Remove(msg);
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
            addMsg("{\"cmd\":\"getModules\"}");
        }

        private void getProfiles()
        {
            addMsg("{\"cmd\":\"getProfiles\"}");
        }

        private void getInternalProfile(UInt64 id)
        {
            addMsg("{\"cmd\":\"getInternalProfile\", \"id\":" + id + "}");
        }

        private void renameModule(string name, UInt64 id)
        {
            addMsg("{\"cmd\":\"renameModule\", \"name\":\"" + name + "\", \"id\":" + id + "}");
        }

        private void turnOnOff(bool status, UInt64 id)
        {
            addMsg("{\"cmd\":\"turnOnOff\", \"status\":" + status + ", \"id\":" + id + "}");
        }

        private void changeAssociatedProfile(UInt64 moduleId, UInt64 profileId)
        {
            addMsg("{\"cmd\":\"changeAssociatedProfile\", \"moduleId\":" + moduleId + ", \"profileId\":" + profileId + "}");
        }

        private void deleteProfile(UInt64 id)
        {
            addMsg("{\"cmd\":\"deleteProfile\", \"id\":" + id + "}");
        }
        #endregion
    }
}
