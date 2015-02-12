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
        private Socket _socket;
        private ObservableCollection<String> _toSend;
        public Dictionary<string, Delegate> sendFuncs { get; private set; }
        private Dictionary<string, Func<Trame, bool>> recvFuncs;

        public Communication()
        {
            _socket = new Socket();
            _socket.Connect();
            _toSend = new ObservableCollection<string>();
            _toSend.CollectionChanged += sendMsgs;
            _socket.Received.CollectionChanged += receivedMsgs;
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

        private void sendMsgs(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (_toSend.Count > 0)
            {
                String msg = _toSend.First();
                _socket.SendRawMessage(msg);
                _toSend.Remove(msg);
            }
        }

        private void receivedMsgs(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (_socket.Received.Count > 0)
            {
                String msg = _socket.Received.First();
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
                _socket.Received.Remove(msg);
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
