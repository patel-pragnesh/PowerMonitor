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
using GalaSoft.MvvmLight.Views;

namespace Powermonitor.ViewModel
{
    public class ConfigurationViewModel : MyViewModelBase
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
        #region SelectedDefaultProfile
        private Profile _selectedDefaultProfile;
        public Profile SelectedDefaultProfile
        {
            get
            {
                return _selectedDefaultProfile;
            }
            set
            {
                if (value == _selectedDefaultProfile)
                    return;
                _selectedDefaultProfile = value;
                RaisePropertyChanged("SelectedDefaultProfile");
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

        public ICommand bTurnOnOff_Command { get { return new RelayCommand(TurnOnOffCommand); } }
        public ICommand bSelectDefaultProfile_Command { get { return new RelayCommand(SelectDefaultProfileCommand); } }
        public ICommand bDeleteProfile_Command { get { return new RelayCommand(DeleteProfileCommand); } }
        public ICommand bUpdate_Command { get { return new RelayCommand(UpdateCommand); } }
        public ICommand bUpdateInternalProfile_Command { get { return new RelayCommand(UpdateInternalProfileCommand); } }

        public ConfigurationViewModel(INavigationService navigationService) : base(navigationService)
        {
            Profiles = null;
            Modules = null;
            SelectedModule = null;
            SelectedDefaultProfile = null;
        }

        public void Refresh()
        {
            Communication.GetInstance.sendFuncs["getModules"].DynamicInvoke((Action<JObject, JObject>)GetModulesCallback);
            Communication.GetInstance.sendFuncs["getProfiles"].DynamicInvoke((Action<JObject, JObject>)GetProfilesCallback);
        }

        private void InternalProfileHandler_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            //InternalProfile = ResourceManager.getInstance.InternalProfileHandler.getProfile(1);
            RaisePropertyChanged("InternalProfile");
        }

        public void Rename(string newName)
        {
            if (SelectedModule != null)
            {
                if (newName.Count() == 0)
                    MessengerInstance.Send("Nom incorrect");
                else
                    Communication.GetInstance.sendFuncs["renameModule"].DynamicInvoke((Action<JObject, JObject>)RenameModuleCallback, newName, SelectedModule.Id);
            }
        }

        #region Commands

        private void TurnOnOffCommand()
        {
            if (SelectedModule != null)
            {
                Communication.GetInstance.sendFuncs["turnOnOff"].DynamicInvoke((Action<JObject, JObject>)TurnOnOffCallback, !SelectedModule.Status, SelectedModule.Id);
                //SelectedModule.Status = !SelectedModule.Status;
            }
        }

        private void SelectDefaultProfileCommand()
        {
            if (SelectedDefaultProfile != null)
            {
                Communication.GetInstance.sendFuncs["updateModuleDefaultProfile"].DynamicInvoke((Action<JObject, JObject>)UpdateModuleDefaultProfileCallback, SelectedModule.Id, SelectedDefaultProfile.Id);
            }
        }

        private void DeleteProfileCommand()
        {
            if (SelectedProfile != null)
            {
                Communication.GetInstance.sendFuncs["deleteProfile"].DynamicInvoke((Action<JObject, JObject>)DeleteProfileCallback, SelectedProfile.Id);
            }
        }

        public void DissociateProfile()
        {
            Communication.GetInstance.sendFuncs["updateModuleDefaultProfile"].DynamicInvoke((Action<JObject, JObject>)UpdateModuleDefaultProfileCallback, SelectedModule.Id, null);
        }

        public void UpdateCommand()
        {
            Communication.GetInstance.sendFuncs["getProfile"].DynamicInvoke((Action<JObject, JObject>)GetProfileCallback, SelectedProfile.Id);
        }

        public void UpdateInternalProfileCommand()
        {
            Communication.GetInstance.sendFuncs["getProfile"].DynamicInvoke((Action<JObject, JObject>)GetProfileCallback, SelectedModule.InternalProfileId);
        }
        #endregion

        #region Callbacks

        private void GetModulesCallback(JObject request, JObject response)
        {
            if ((response["returnCode"] == null || response["returnCode"].ToObject<UInt64>() == 0) && response["modules"] != null)
                Modules = new ObservableCollection<Module>(JsonConvert.DeserializeObject<List<Module>>(response["modules"].ToString()));
            else
                HandleError(response);
        }

        private void GetProfilesCallback(JObject request, JObject response)
        {
            if (response["returnCode"] == null || response["returnCode"].ToObject<UInt64>() == 0 && response["profiles"] != null)
                Profiles = new ObservableCollection<Profile>(JsonConvert.DeserializeObject<List<Profile>>(response["profiles"].ToString()));
            else
                HandleError(response);
        }

        private void TurnOnOffCallback(JObject request, JObject response)
        {
            if (response["returnCode"] == null || response["returnCode"].ToObject<UInt64>() == 0)
                SelectedModule.Status = !SelectedModule.Status;
            else
                HandleError(response);
        }

        private void RenameModuleCallback(JObject request, JObject response)
        {
            if (response["returnCode"] == null || response["returnCode"].ToObject<UInt64>() == 0)
                Modules.First(m => m.Id == request["id"].ToObject<UInt64>()).Name = request["name"].ToString();
            else
                HandleError(response);
        }

        private void UpdateModuleDefaultProfileCallback(JObject request, JObject response)
        {
            var id = request["defaultProfileId"].ToObject<UInt64?>();
            if (response["returnCode"] == null || response["returnCode"].ToObject<UInt64>() == 0)
                Modules.First(m => m.Id == request["id"].ToObject<UInt64>()).DefaultProfile = id == null ? null : Profiles.First(p => p.Id == request["defaultProfileId"].ToObject<UInt64?>());
            else
                HandleError(response);
        }

        private void DeleteProfileCallback(JObject request, JObject response)
        {
            var code = response["returnCode"].ToObject<UInt64>();
            Profile save = null;
            if (code == 0)
            {
                foreach (var profile in Profiles)
                {
                    if (profile.Id == request["id"].ToObject<UInt64>())
                        save = profile;
                }
                if (save != null)
                    Profiles.Remove(save);
            }
            else
                HandleError(response);
        }

        private void GetProfileCallback(JObject request, JObject response)
        {
            var code = response["returnCode"].ToObject<UInt64>();
            if (code == 0)
            {
                Profile tmp = JsonConvert.DeserializeObject<Profile>(response["profile"].ToString()); ;
                UpdateProfileViewModel.ToUpdate = tmp;
                _nav.NavigateTo("UpdateProfile");
            }
            else
                HandleError(response);
        }
        #endregion
    }
}
