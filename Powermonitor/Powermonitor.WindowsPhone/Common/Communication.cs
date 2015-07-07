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
        public Session Session { get; private set; }
        public Communication()
        {
            Windows.Storage.ApplicationDataContainer roamingSettings = Windows.Storage.ApplicationData.Current.RoamingSettings;
            if (roamingSettings.Values.ContainsKey("session"))
                Session = JsonConvert.DeserializeObject<Session>(roamingSettings.Values["session"].ToString());
            else
                Session = new Session();
            _socket = new Socket();
            _socket.Received.CollectionChanged += ReceivedMsgs;
            sendFuncs = new Dictionary<string, Delegate>();
            recvFuncs = new Dictionary<string, Func<Trame, bool>>();
            sentRequests = new Queue<Request>();

            sendFuncs.Add("login", new Action<Action<JObject, JObject>, string, string>(Login));
            sendFuncs.Add("change_username", new Action<Action<JObject, JObject>, int, string>(ChangeUsername));
            sendFuncs.Add("change_password", new Action<Action<JObject, JObject>, int, string>(ChangePassword));
            sendFuncs.Add("new_account", new Action<Action<JObject, JObject>, int, string, string>(NewAccount));
            sendFuncs.Add("getModules", new Action<Action<JObject, JObject>>(GetModules));
            sendFuncs.Add("getProfiles", new Action<Action<JObject, JObject>>(GetProfiles));
            sendFuncs.Add("getProfile", new Action<Action<JObject, JObject>, UInt64>(GetProfile));
            sendFuncs.Add("getInternalProfile", new Action<Action<JObject, JObject>, UInt64>(GetInternalProfile));
            sendFuncs.Add("renameModule", new Action<Action<JObject, JObject>, string, UInt64>(RenameModule));
            sendFuncs.Add("turnOnOff", new Action<Action<JObject, JObject>, bool, UInt64>(TurnOnOff));
            sendFuncs.Add("updateModuleDefaultProfile", new Action<Action<JObject, JObject>, UInt64, UInt64?>(UpdateModuleDefaultProfile));
            sendFuncs.Add("deleteProfile", new Action<Action<JObject, JObject>, UInt64>(DeleteProfile));
            sendFuncs.Add("addProfile", new Action<Action<JObject, JObject>, string, int>(AddProfile));
            sendFuncs.Add("addTimeSlot", new Action<Action<JObject, JObject>, UInt64, Time, Time>(AddTimeSlot));
            sendFuncs.Add("deleteTimeSlot", new Action<Action<JObject, JObject>, UInt64>(DeleteTimeSlot));
            sendFuncs.Add("updateTimeSlot", new Action<Action<JObject, JObject>, UInt64, Time, Time>(UpdateTimeSlot));
            sendFuncs.Add("addAlert", new Action<Action<JObject, JObject>, UInt64, double, UInt64>(AddAlert));
            sendFuncs.Add("deleteAlert", new Action<Action<JObject, JObject>, UInt64>(DeleteAlert));
            sendFuncs.Add("updateAlert", new Action<Action<JObject, JObject>, UInt64, double, UInt64>(UpdateAlert));
            sendFuncs.Add("updateProfileName", new Action<Action<JObject, JObject>, UInt64, string>(UpdateProfileName));
            sendFuncs.Add("updateProfilePolling", new Action<Action<JObject, JObject>, UInt64, uint>(UpdateProfilePolling));
        }

        async public Task<bool> Connect()
        {
            return await _socket.Connect();
        }

        private void ReceivedMsgs(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (_socket.Received.Count > 0 && e.Action == NotifyCollectionChangedAction.Add)
            {
                String msg = _socket.Received.First();
                //var jObj = JsonConvert.DeserializeObject<Dictionary<string, JToken>>(msg);
                var jObj = JsonConvert.DeserializeObject<JObject>(msg);
                if (jObj["session"] != null)
                {
                    string sessionStr = jObj["session"].ToString();
                    Session = JsonConvert.DeserializeObject<Session>(sessionStr);
                    Windows.Storage.ApplicationDataContainer roamingSettings = Windows.Storage.ApplicationData.Current.RoamingSettings;
                    roamingSettings.Values["session"] = sessionStr;
                }
                Request req = sentRequests.ElementAt(0);
                req.Callback.DynamicInvoke(req.Message, jObj);
                _socket.Received.Remove(msg);
                sentRequests.Dequeue();
                SendRemainingMessages();
            }
        }

        private void SendRemainingMessages()
        {
            if (sentRequests.Count > 0)
            {
                sentRequests.ElementAt(0).Message["session"] = JObject.FromObject(Session);
                _socket.SendRawMessage(sentRequests.ElementAt(0).Message.ToString());
            }
        }

        private void AddMsg(Action<JObject, JObject> callback, JObject json)
        {
            if (!Session.IsEmpty())
                json["session"] = JObject.FromObject(Session);
            sentRequests.Enqueue(new Request(json, callback));
            if (sentRequests.Count == 1)
                _socket.SendRawMessage(json.ToString());
        }

        public bool AddFunc(string key, Func<Trame, bool> f)
        {
            if (recvFuncs.Keys.Contains(key))
                return false;
            recvFuncs.Add(key, f);
            return true;
        }

        #region SendCmds
        private void Login(Action<JObject, JObject> callback, string email, string password)
        {
            JObject json = new JObject() { { "cmd", "login" }, { "email", email }, { "password", password } };
            AddMsg(callback, json);
        }

        private void ChangeUsername(Action<JObject, JObject> callback, int userid, string username)
        {
            JObject json = new JObject() { { "cmd", "change_username" }, { "userid", userid }, { "username", username } };
            AddMsg(callback, json);
        }

        private void ChangePassword(Action<JObject, JObject> callback, int userid, string password)
        {
            JObject json = new JObject() { { "cmd", "change_password" }, { "userid", userid }, { "password", password } };
            AddMsg(callback, json);
        }

        private void NewAccount(Action<JObject, JObject> callback, int userid, string username, string password)
        {
            JObject json = new JObject() { { "cmd", "new_account" }, { "userid", userid }, { "username", username }, { "password", password } };
            AddMsg(callback, json);
        }

        private void GetModules(Action<JObject, JObject> callback)
        {
            JObject json = new JObject() { { "cmd", "getModules" } };
            AddMsg(callback, json);
        }

        private void GetProfiles(Action<JObject, JObject> callback)
        {
            JObject json = new JObject() { { "cmd", "getProfiles" } };
            AddMsg(callback, json);
        }

        private void GetProfile(Action<JObject, JObject> callback, UInt64 id)
        {
            JObject json = new JObject() { { "cmd", "getProfile" }, { "id", id } };
            AddMsg(callback, json);
        }

        private void GetInternalProfile(Action<JObject, JObject> callback, UInt64 id)
        {
            JObject json = new JObject() { { "cmd", "getInternalProfile" }, { "id", id } };
            AddMsg(callback, json);
        }

        private void RenameModule(Action<JObject, JObject> callback, string name, UInt64 id)
        {
            JObject json = new JObject() { { "cmd", "renameModule" }, { "name", name }, { "id", id } };
            AddMsg(callback, json);
        }

        private void TurnOnOff(Action<JObject, JObject> callback, bool status, UInt64 id)
        {
            JObject json = new JObject() { { "cmd", "turnOnOff" }, { "status", status }, { "id", id } };
            AddMsg(callback, json);
        }

        private void UpdateModuleDefaultProfile(Action<JObject, JObject> callback, UInt64 moduleId, UInt64? profileId)
        {
            JObject json = new JObject() { { "cmd", "updateModuleDefaultProfile" }, { "id", moduleId }, { "defaultProfileId", profileId } };
            AddMsg(callback, json);
        }

        private void DeleteProfile(Action<JObject, JObject> callback, UInt64 id)
        {
            JObject json = new JObject() { { "cmd", "deleteProfile" }, { "id", id } };
            AddMsg(callback, json);
        }

        private void AddProfile(Action<JObject, JObject> callback, string name, int polling)
        {
            JObject json = new JObject() { { "cmd", "addProfile" }, { "name", name }, { "polling", polling } };
            AddMsg(callback, json);
        }

        private void AddTimeSlot(Action<JObject, JObject> callback, UInt64 profileId, Time beg, Time end)
        {
            JObject json = new JObject() { { "cmd", "addTimeSlot" }, { "profileId", profileId }, { "beg", JObject.FromObject(beg) }, { "end", JObject.FromObject(end) } };
            AddMsg(callback, json);
        }

        private void DeleteTimeSlot(Action<JObject, JObject> callback, UInt64 timeslotId)
        {
            JObject json = new JObject() { { "cmd", "deleteTimeSlot" }, { "id", timeslotId } };
            AddMsg(callback, json);
        }

        private void UpdateTimeSlot(Action<JObject, JObject> callback, UInt64 timeslotId, Time beg, Time end)
        {
            JObject json = new JObject() { { "cmd", "updateTimeSlot" }, { "id", timeslotId }, { "beg", JObject.FromObject(beg) }, { "end", JObject.FromObject(end) } };
            AddMsg(callback, json);
        }

        private void AddAlert(Action<JObject, JObject> callback, UInt64 profileId, double value, UInt64 unitId)
        {
            JObject json = new JObject() { { "cmd", "addAlert" }, { "profileId", profileId }, { "value", value }, { "unitId", unitId } };
            AddMsg(callback, json);
        }

        private void DeleteAlert(Action<JObject, JObject> callback, UInt64 id)
        {
            JObject json = new JObject() { { "cmd", "deleteAlert" }, { "id", id } };
            AddMsg(callback, json);
        }

        private void UpdateAlert(Action<JObject, JObject> callback, UInt64 alertId, double value, UInt64 unitId)
        {
            JObject json = new JObject() { { "cmd", "updateAlert" }, { "id", alertId }, { "value", value }, { "unitId", unitId } };
            AddMsg(callback, json);
        }

        private void UpdateProfileName(Action<JObject, JObject> callback, UInt64 id, string name)
        {
            JObject json = new JObject() { { "cmd", "updateProfileName" }, { "id", id }, { "name", name } };
            AddMsg(callback, json);
        }

        private void UpdateProfilePolling(Action<JObject, JObject> callback, UInt64 id, uint polling)
        {
            JObject json = new JObject() { { "cmd", "updateProfilePolling" }, { "id", id }, { "polling", polling } };
            AddMsg(callback, json);
        }
        #endregion
    }
}
