using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Views;
using Powermonitor.Common;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.ViewModel
{
    public class InitViewModel : ViewModelBase
    {
        INavigationService _nav;

        public InitViewModel(INavigationService navigationService)
        {
            _nav = navigationService;
        }

        async public Task Init()
        {
            Communication com = Communication.getInstance;
            ResourceManager res = ResourceManager.getInstance;
            bool isConnected = await com.Connect();
            if (isConnected)
                _nav.NavigateTo("Login");
            else
            {
                MessengerInstance.Send("Connexion avec le serveur impossible");
            }
        }
    }
}
