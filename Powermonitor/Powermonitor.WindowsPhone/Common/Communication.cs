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
using Powermonitor.Model;

namespace Powermonitor.Common
{
    public class Communication : Singleton<Communication>
    {
        private Socket _socket;
        public Dictionary<string, Delegate> sendFuncs { get; private set; }
        private Dictionary<string, Func<Trame, bool>> recvFuncs;
        private Queue<Request> sentRequests;
        private Session _session;
        public Communication()
        {
            _session = new Session();
            _socket = new Socket();
            _socket.Connect();
            _socket.Received.CollectionChanged += receivedMsgs;
            sendFuncs = new Dictionary<string, Delegate>();
            recvFuncs = new Dictionary<string, Func<Trame, bool>>();
            sentRequests = new Queue<Request>();

            sendFuncs.Add("login", new Action<Action<JObject, JObject>, string, string>(login));
            sendFuncs.Add("change_username", new Action<Action<JObject, JObject>, int, string>(changeUsername));
            sendFuncs.Add("change_password", new Action<Action<JObject, JObject>, int, string>(changePassword));
            sendFuncs.Add("new_account", new Action<Action<JObject, JObject>, int, string, string>(newAccount));
            sendFuncs.Add("getModules", new Action<Action<JObject, JObject>>(getModules));
            sendFuncs.Add("getProfiles", new Action<Action<JObject, JObject>>(getProfiles));
            sendFuncs.Add("getInternalProfile", new Action<Action<JObject, JObject>, UInt64>(getInternalProfile));
            sendFuncs.Add("renameModule", new Action<Action<JObject, JObject>, string, UInt64>(renameModule));
            sendFuncs.Add("turnOnOff", new Action<Action<JObject, JObject>, bool, UInt64>(turnOnOff));
            sendFuncs.Add("changeAssociatedProfile", new Action<Action<JObject, JObject>, UInt64, UInt64>(changeAssociatedProfile));
            sendFuncs.Add("deleteProfile", new Action<Action<JObject, JObject>, UInt64>(deleteProfile));
        }

        private void receivedMsgs(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (_socket.Received.Count > 0)
            {
                String msg = _socket.Received.First();
                //var jObj = JsonConvert.DeserializeObject<Dictionary<string, JToken>>(msg);
                var jObj = JsonConvert.DeserializeObject<JObject>(msg);
                if (jObj["session"] != null)
                    _session = JsonConvert.DeserializeObject<Session>(jObj["session"].ToString());
                Request req = sentRequests.Dequeue();
                req.Callback.DynamicInvoke(req.Message, jObj);
                _socket.Received.Remove(msg);
            }
        }

        private void addMsg(Action<JObject, JObject> callback, JObject json)
        {
            if (!_session.isEmpty())
                json.Add("session", JsonConvert.SerializeObject(_session));
            _socket.SendRawMessage(json.ToString());
            sentRequests.Enqueue(new Request(json, callback));
        }

        public bool addFunc(string key, Func<Trame, bool> f)
        {
            if (recvFuncs.Keys.Contains(key))
                return false;
            recvFuncs.Add(key, f);
            return true;
        }

        #region SendCmds
        private void login(Action<JObject, JObject> callback, string email, string password)
        {
            JObject json = new JObject() { { "cmd", "login" }, { "email", email }, { "password", password } };
            addMsg(callback, json);
        }

        private void changeUsername(Action<JObject, JObject> callback, int userid, string username)
        {
            JObject json = new JObject() { { "cmd", "change_username" }, { "userid", userid }, { "username", username } };
            addMsg(callback, json);
        }

        private void changePassword(Action<JObject, JObject> callback, int userid, string password)
        {
            JObject json = new JObject() { { "cmd", "change_password" }, { "userid", userid }, { "password", password } };
            addMsg(callback, json);
        }

        private void newAccount(Action<JObject, JObject> callback, int userid, string username, string password)
        {
            JObject json = new JObject() { { "cmd", "new_account" }, { "userid", userid }, { "username", username }, { "password", password } };
            addMsg(callback, json);
        }

        private void getModules(Action<JObject, JObject> callback)
        {
            JObject json = new JObject() { { "cmd", "getModules" } };
            addMsg(callback, json);
        }

        private void getProfiles(Action<JObject, JObject> callback)
        {
            JObject json = new JObject() { { "cmd", "getProfiles" } };
            addMsg(callback, json);
        }

        private void getInternalProfile(Action<JObject, JObject> callback, UInt64 id)
        {
            JObject json = new JObject() { { "cmd", "getInternalProfile" }, { "id", id } };
            addMsg(callback, json);
        }

        private void renameModule(Action<JObject, JObject> callback, string name, UInt64 id)
        {
            JObject json = new JObject() { { "cmd", "renameModule" }, { "name", name }, { "id", id } };
            addMsg(callback, json);
        }

        private void turnOnOff(Action<JObject, JObject> callback, bool status, UInt64 id)
        {
            JObject json = new JObject() { { "cmd", "turnOnOff" }, { "status", status }, { "id", id } };
            addMsg(callback, json);
        }

        private void changeAssociatedProfile(Action<JObject, JObject> callback, UInt64 moduleId, UInt64 profileId)
        {
            JObject json = new JObject() { { "cmd", "changeAssociatedProfile" }, { "moduleId", moduleId }, { "profileId", profileId } };
            addMsg(callback, json);
        }

        private void deleteProfile(Action<JObject, JObject> callback, UInt64 id)
        {
            JObject json = new JObject() { { "cmd", "deleteProfile" }, { "id", id } };
            addMsg(callback, json);
        }
        #endregion
    }
}
