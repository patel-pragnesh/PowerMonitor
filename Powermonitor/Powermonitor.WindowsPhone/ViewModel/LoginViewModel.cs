using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GalaSoft.MvvmLight;
using Windows.UI.Xaml.Controls;
using System.Windows.Input;
using GalaSoft.MvvmLight.Command;
using Powermonitor.Common;
using Newtonsoft.Json.Linq;
using Powermonitor.View;
using GalaSoft.MvvmLight.Views;

namespace Powermonitor.ViewModel
{
    public class LoginViewModel : ViewModelBase
    {
        INavigationService _nav;
        public LoginViewModel(INavigationService navigationService)
        {
            _nav = navigationService;
        }

        public void GoToHomeIfConnected()
        {
            if (!Communication.getInstance.Session.IsEmpty())
                _nav.NavigateTo("Home");
        }

        public void Login(string email, string password)
        {
            Communication.getInstance.sendFuncs["login"].DynamicInvoke((Action<JObject, JObject>)LoginCallback, email, password);
        }

        private void LoginCallback(JObject request, JObject response)
        {
            if (response["returnCode"].Value<UInt64>() == 0)
                _nav.NavigateTo("Home");
            else
                MessengerInstance.Send("test");
        }
    }
}
