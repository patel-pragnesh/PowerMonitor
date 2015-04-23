using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;
using GalaSoft.MvvmLight.Views;
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
    }
}
