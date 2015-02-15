using Powermonitor.Common;
using Powermonitor.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using GalaSoft.MvvmLight.Command;
using GalaSoft.MvvmLight;
using Windows.UI.Xaml.Controls;

namespace Powermonitor.ViewModel
{
    public class ConfigurationViewModel : ViewModelBase
    {
        public ObservableCollection<Profile> Profiles { get; private set; }
       // public TrulyObservableCollection<Module> Modules { get; private set; }
        public ObservableCollection<Module> Modules { get; private set; }
        private Profile _internalProfile;
        public Profile InternalProfile
        {
            get;
            private set;
        }

        public ICommand bTurnOnOff_Command { get { return new RelayCommand(turnOnOffCommand); } }
        public ICommand bSelectAssociatedProfile_Command { get { return new RelayCommand(selectAssociatedProfileCommand); } }
        public ICommand bDeleteProfile_Command { get { return new RelayCommand(deleteProfileCommand); } }

        #region IsKeyboardFocusWithin
        private bool _IsKeyboardFocusWithin;
        public bool IsKeyboardFocusWithin
        {
            get
            {
                return _IsKeyboardFocusWithin;
            }
            set
            {
                if (value == _IsKeyboardFocusWithin)
                    return;
                _IsKeyboardFocusWithin = value;
                RaisePropertyChanged("IsKeyboardFocusWithin");
            }

        }
        #endregion
        #region SelectedModule
        private Module _selectedModule;
        public Module SelectedModule
        {
            get
            {
                return _selectedModule;
            }
            set
            {
                if (value == _selectedModule)
                    return;
                _selectedModule = value;
                RaisePropertyChanged("SelectedModule");
            }
        }
        #endregion
        #region SelectedAssociatedProfile
        private Profile _selectedAssociatedProfile;
        public Profile SelectedAssociatedProfile
        {
            get
            {
                return _selectedAssociatedProfile;
            }
            set
            {
                if (value == _selectedAssociatedProfile)
                    return;
                _selectedAssociatedProfile = value;
                RaisePropertyChanged("SelectedAssociatedProfile");
            }
        }
        #endregion
        #region SelectedProfile
        private Profile _selectedProfile;
        public Profile SelectedProfile
        {
            get
            {
                return _selectedProfile;
            }
            set
            {
                if (value == _selectedProfile)
                    return;
                _selectedProfile = value;
                RaisePropertyChanged("SelectedProfile");
            }
        }
        #endregion
        public ConfigurationViewModel()
        {
            ResourceManager.getInstance.InternalProfileHandler.PropertyChanged += InternalProfileHandler_PropertyChanged;
            ResourceManager.getInstance.Profiles.PropertyChanged += Profiles_PropertyChanged;
            Profiles = ResourceManager.getInstance.Profiles.ProfileList;
            Modules = ResourceManager.getInstance.Modules.ModuleList;
            InternalProfile = ResourceManager.getInstance.InternalProfileHandler.getProfile(1);
            SelectedModule = null;
            SelectedAssociatedProfile = null;
        }

        private void Profiles_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            Profiles = ResourceManager.getInstance.Profiles.ProfileList;
            RaisePropertyChanged("Profiles");
        }

        private void InternalProfileHandler_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            InternalProfile = ResourceManager.getInstance.InternalProfileHandler.getProfile(1);
            RaisePropertyChanged("InternalProfile");
        }

        public void rename(string newName)
        {
            if (SelectedModule != null)
            {
                SelectedModule.Name = newName;
                Communication.getInstance.sendFuncs["renameModule"].DynamicInvoke(newName, SelectedModule.Id);
            }
        }

        private void turnOnOffCommand()
        {
            if (SelectedModule != null)
            {
                //SelectedModule.Status = !SelectedModule.Status;
            }
        }

        private void selectAssociatedProfileCommand()
        {
            if (SelectedAssociatedProfile != null)
            {
                Communication.getInstance.sendFuncs["changeAssociatedProfile"].DynamicInvoke(SelectedModule.Id, SelectedAssociatedProfile.Id);
            }
        }

        private void deleteProfileCommand()
        {
            if (SelectedProfile != null)
            {
                Communication.getInstance.sendFuncs["deleteProfile"].DynamicInvoke(SelectedProfile.Id);
            }
        }
    }
}
