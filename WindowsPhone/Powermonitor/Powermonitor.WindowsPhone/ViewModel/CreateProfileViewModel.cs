using Powermonitor.Common;
using Powermonitor.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GalaSoft.MvvmLight;
using System.Windows.Input;
using GalaSoft.MvvmLight.Command;
using Newtonsoft.Json.Linq;
using GalaSoft.MvvmLight.Views;

namespace Powermonitor.ViewModel
{
    public class CreateProfileViewModel : MyViewModelBase
    {
        #region Name
        private string _name;
        public String Name
        {
            get
            {
                return _name;
            }
            set
            {
                if (value == _name)
                    return;
                _name = value;
                RaisePropertyChanged("Name");
            }

        }
        #endregion
        #region Polling
        private int _polling;
        public int Polling
        {
            get
            {
                return _polling;
            }
            set
            {
                if (value == _polling)
                    return;
                _polling = value;
                RaisePropertyChanged("Polling");
            }

        }
        #endregion

        public ICommand bSaveProfile_Command { get { return new RelayCommand(SaveProfileCommand); } }

        public CreateProfileViewModel(INavigationService navigationService) : base(navigationService)
        {
        }

        private void SaveProfileCommand()
        {
            Communication.GetInstance.sendFuncs["addProfile"].DynamicInvoke((Action<JObject, JObject>)SaveProfileCallback, Name, Polling);
        }

        private void SaveProfileCallback(JObject request, JObject response)
        {
            if (response["returnCode"] == null || response["returnCode"].ToObject<UInt64>() == 0)
                this._nav.NavigateTo("Configuration");
            else
                HandleError(response);
        }
    }
}
