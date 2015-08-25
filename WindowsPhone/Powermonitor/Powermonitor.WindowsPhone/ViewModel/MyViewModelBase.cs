using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Views;
using Newtonsoft.Json.Linq;
using Powermonitor.Common;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.ViewModel
{
    public class MyViewModelBase : ViewModelBase
    {
        protected INavigationService _nav;

        public MyViewModelBase(INavigationService navigationService)
        {
            _nav = navigationService;
        }

        protected void HandleError(JObject response)
        {
            var code = response["returnCode"].ToObject<UInt64>();
            if (code == 0x103 || code == 0x104)
            {
                Communication.GetInstance.ResetSession();
                this._nav.NavigateTo("Login");
            }
            MessengerInstance.Send(new Error(code, Errors.GetErrorMessage(code)));
        }
    }
}
