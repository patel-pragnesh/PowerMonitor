using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Input;
using Powermonitor.Common;
using GalaSoft.MvvmLight.Command;
using GalaSoft.MvvmLight;

namespace Powermonitor.ViewModel
{
    public class HomeViewModel : ViewModelBase
    {
        public ICommand bConsulter_Command { get; set; }
        public ICommand bConfigurer_Command { get; set; }

        public HomeViewModel()
        {
            bConfigurer_Command = new RelayCommand(configurer_Command);
        }

        private void configurer_Command()
        {
        }
    }
}
