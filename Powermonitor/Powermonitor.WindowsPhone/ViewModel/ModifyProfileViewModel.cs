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
    public class ModifyProfileViewModel : ViewModelBase
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

        public ICommand bSchedule_Command { get { return new RelayCommand(ScheduleCommand); } }

        public ModifyProfileViewModel(INavigationService navigationService)
        {
            Profile = ToUpdate;
            _nav = navigationService;
        }

        private void ScheduleCommand()
        {
            ScheduleViewModel.ToUpdate = Profile;
            this._nav.NavigateTo("Schedule");
        }

        public void addAlert(double value, int unit)
        {
            Communication.getInstance.sendFuncs["addAlert"].DynamicInvoke((Action<JObject, JObject>)AddAlertCallback, this.Profile.Id, value, (UInt64)unit);
        }

        private void AddAlertCallback(JObject request, JObject response)
        {
            if (response["returnCode"] == null || response["returnCode"].ToObject<UInt64>() == 0)
                this.Profile.Alerts.Add(new Alert(response["id"].ToObject<UInt64>(), request["unitId"].ToObject<UInt64>(), request["value"].ToObject<int>()));
        }
    }
}
