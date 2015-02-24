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
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace Powermonitor.ViewModel
{
    public class ConfigurationViewModel : ViewModelBase
    {
        #region Profiles
        private ObservableCollection<Profile> _profiles;
        public ObservableCollection<Profile> Profiles
        {
            get
            {
                return _profiles;
            }
            set
            {
                if (value == _profiles)
                    return;
                _profiles = value;
                RaisePropertyChanged("Profiles");
            }

        }
        #endregion
        #region Modules
        private ObservableCollection<Module> _modules;
        public ObservableCollection<Module> Modules
        {
            get
            {
                return _modules;
            }
            set
            {
                if (value == _modules)
                    return;
                _modules = value;
                RaisePropertyChanged("Modules");
            }

        }
        #endregion
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

        private Profile _internalProfile;
        public Profile InternalProfile
        {
            get;
            private set;
        }

        public ICommand bTurnOnOff_Command { get { return new RelayCommand(turnOnOffCommand); } }
        public ICommand bSelectAssociatedProfile_Command { get { return new RelayCommand(selectAssociatedProfileCommand); } }
        public ICommand bDeleteProfile_Command { get { return new RelayCommand(deleteProfileCommand); } }

        public ConfigurationViewModel()
        {
            Communication.getInstance.sendFuncs["getModules"].DynamicInvoke((Action<string, string>)getModulesCallback);
            Communication.getInstance.sendFuncs["getProfiles"].DynamicInvoke((Action<string, string>)getProfilesCallback);
            Profiles = null;
            Modules = null;
            InternalProfile = null;
            SelectedModule = null;
            SelectedAssociatedProfile = null;
        }

        private void getModulesCallback(string request, string response)
        {
            var json = JsonConvert.DeserializeObject<Dictionary<string, JToken>>(response);
            Modules = new ObservableCollection<Module>(JsonConvert.DeserializeObject<List<Module>>(json["Modules"].ToString()));
        }

        private void getProfilesCallback(string request, string response)
        {
            var json = JsonConvert.DeserializeObject<Dictionary<string, JToken>>(response);
            Profiles = new ObservableCollection<Profile>(JsonConvert.DeserializeObject<List<Profile>>(json["Profiles"].ToString()));
        }

        private void deleteProfileCallback(string request, string response)
        {
            var jsonResponse = JsonConvert.DeserializeObject<Dictionary<string, JToken>>(response);
            var jsonRequest = JsonConvert.DeserializeObject<Dictionary<string, JToken>>(request);
            var code = jsonResponse["returnCode"].ToObject<UInt64>();
            Profile save = null;
            if (code == 0)
            {
                foreach (var profile in Profiles) {
                    if (profile.Id == jsonRequest["id"].ToObject<UInt64>())
                        save = profile;
                }
                if (save != null)
                    Profiles.Remove(save);
            }
        }

        private void InternalProfileHandler_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            //InternalProfile = ResourceManager.getInstance.InternalProfileHandler.getProfile(1);
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
                Communication.getInstance.sendFuncs["deleteProfile"].DynamicInvoke((Action<string, string>)deleteProfileCallback, SelectedProfile.Id);
            }
        }
    }
}
