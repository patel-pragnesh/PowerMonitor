using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;
using GalaSoft.MvvmLight.Views;
using Newtonsoft.Json.Linq;
using Powermonitor.Common;
using Powermonitor.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Powermonitor.ViewModel
{
    public class UpdateProfileViewModel : ViewModelBase
    {
        INavigationService _nav;
        public static Profile ToUpdate;
        #region Profile
        private Profile _profile;
        public Profile Profile
        {
            get
            {
                return _profile;
            }
            set
            {
                if (value == _profile)
                    return;
                _profile = value;
                RaisePropertyChanged("Profile");
            }

        }
        #endregion
        #region SelectedAlert
        private Alert _selectedAlert;
        public Alert SelectedAlert
        {
            get
            {
                return _selectedAlert;
            }
            set
            {
                if (value == _selectedAlert)
                    return;
                _selectedAlert = value;
                RaisePropertyChanged("Alert");
            }
        }
        #endregion

        public ICommand bSchedule_Command { get { return new RelayCommand(ScheduleCommand); } }
        public ICommand bDeleteAlert_Command { get { return new RelayCommand(DeleteAlertCommand); } }

        public UpdateProfileViewModel(INavigationService navigationService)
        {
            _nav = navigationService;
        }

        public void Refresh()
        {
            SelectedAlert = null;
            Profile = ToUpdate;
        }

        private void ScheduleCommand()
        {
            ScheduleViewModel.ToUpdate = Profile;
            this._nav.NavigateTo("Schedule");
        }

        public void AddAlert(double value, int unit)
        {
            if (SelectedAlert == null)
                Communication.getInstance.sendFuncs["addAlert"].DynamicInvoke((Action<JObject, JObject>)AddAlertCallback, this.Profile.Id, value, (UInt64)unit);
            else
                Communication.getInstance.sendFuncs["updateAlert"].DynamicInvoke((Action<JObject, JObject>)UpdateAlertCallback, SelectedAlert.Id, value, (UInt64)unit);
        }

        private void DeleteAlertCommand()
        {
            if (SelectedAlert != null)
            {
                Communication.getInstance.sendFuncs["deleteAlert"].DynamicInvoke((Action<JObject, JObject>)DeleteAlertCallback, SelectedAlert.Id);
            }
        }

        private void AddAlertCallback(JObject request, JObject response)
        {
            if (response["returnCode"] == null || response["returnCode"].ToObject<UInt64>() == 0)
                this.Profile.Alerts.Add(new Alert(response["id"].ToObject<UInt64>(), request["unitId"].ToObject<UInt64>(), request["value"].ToObject<int>()));
        }

        private void UpdateAlertCallback(JObject request, JObject response)
        {
            if (response["returnCode"] == null || response["returnCode"].ToObject<UInt64>() == 0)
            {
                Alert alert = this.Profile.Alerts.First(a => (a as Alert).Id == request["id"].ToObject<UInt64>());
                alert.UnitId = request["unitId"].ToObject<UInt64>();
                alert.Value = request["value"].ToObject<int>();
            }
        }

        private void DeleteAlertCallback(JObject request, JObject response)
        {
            if (response["returnCode"] == null || response["returnCode"].ToObject<UInt64>() == 0)
            {
                this.Profile.Alerts.Remove(this.Profile.Alerts.First(a => a.Id == SelectedAlert.Id));
            }
        }

        private void UpdateNameCallback(JObject request, JObject response)
        {
            if (response["returnCode"] == null || response["returnCode"].ToObject<UInt64>() == 0)
            {
                this.Profile.Name = request["name"].ToObject<string>();
            }
        }
    
        private void UpdatePollingCallback(JObject request, JObject response)
        {
            if (response["returnCode"] == null || response["returnCode"].ToObject<UInt64>() == 0)
            {
                this.Profile.Polling = request["polling"].ToObject<uint>();
            }
        }
    }
}
