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
        public ObservableCollection<Profile> Profils { get; private set; }
       // public TrulyObservableCollection<Module> Modules { get; private set; }
        public ObservableCollection<Module> Modules { get; private set; }
        public ICommand bRename_Command { get { return new RelayCommand(renameCommand); } }
        public ICommand bModifyAssiociatedProfil_Command { get { return new RelayCommand(modifyAssiociatedProfilCommand); } }
        public ICommand bAcceptRename_Command { get { return new RelayCommand(acceptRenameCommand); } }
        public ICommand bTurnOnOff_Command { get { return new RelayCommand(turnOnOffCommand); } }

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
        #region Test
        private string _test;
        public string Test
        {
            get
            {
                return _test;
            }
            set
            {
                if (value == _test)
                    return;
                _test= value;
                RaisePropertyChanged("Test");
            }

        }
#endregion
        #region RenameStackVisibility
        private string _renameStackVisibility;
        public string RenameStackVisibility
        {
            get
            {
                return _renameStackVisibility;
            }
            set
            {
                if (value == _renameStackVisibility)
                    return;
                _renameStackVisibility = value;
                RaisePropertyChanged("RenameStackVisibility");
            }

        }
        #endregion#region RenameStackVisibility
        #region ModifyAssiociatedProfilStackVisibility
        private string _modifyAssiociatedProfilStackVisibility;
        public string ModifyAssiociatedProfilStackVisibility
        {
            get
            {
                return _modifyAssiociatedProfilStackVisibility;
            }
            set
            {
                if (value == _modifyAssiociatedProfilStackVisibility)
                    return;
                _modifyAssiociatedProfilStackVisibility = value;
                RaisePropertyChanged("ModifyAssiociatedProfilStackVisibility");
            }

        }
        #endregion
        #region RenameText
        private string _renameText;
        public string RenameText
        {
            get
            {
                return _renameText;
            }
            set
            {
                if (value == _renameText)
                    return;
                _renameText = value;
                RaisePropertyChanged("RenameText");
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

        public ConfigurationViewModel()
        {
            Profils = new ObservableCollection<Profile>();
            Profils.Add(new Profile("Profil 1"));
            Profils.Add(new Profile("Profil 2"));
            Profils.Add(new Profile("Profil 3"));
            Profils.Add(new Profile("Profil 4"));
            Profils.Add(new Profile("Profil 5"));
            Profils.Add(new Profile("Profil 6"));
            Modules = new ObservableCollection<Module>();
            Modules.Add(new Module("module 1", true, new Profile("Profil 1")));
            Modules.Add(new Module("module 2", false, new Profile("Profil 2")));
            Modules.Add(new Module("module 3", false, new Profile("Profil 3")));
            Modules.Add(new Module("module 4", false, new Profile("Profil 4")));
            Modules.Add(new Module("module 5", false, new Profile("Profil 5")));
            Modules.Add(new Module("module 6", false, new Profile("Profil 6")));
            Modules.Add(new Module("module 7", false, new Profile("Profil 7")));
            Modules.Add(new Module("module 8", false, new Profile("Profil 8")));
            Modules.Add(new Module("module 8", false, new Profile("Profil 8")));
            Modules.Add(new Module("module 8", false, new Profile("Profil 8")));
            Modules.Add(new Module("module 8", false, new Profile("Profil 8")));
            Test = "sdfwsdf";
            RenameStackVisibility = "Collapsed";
            ModifyAssiociatedProfilStackVisibility = "Collapsed";
            SelectedModule = null;
            RenameText = "";
        }

        private void renameCommand()
        {
            if (RenameStackVisibility == "Collapsed")
                RenameStackVisibility = "Visible";
            else
                RenameStackVisibility = "Collapsed";
        }

        private void acceptRenameCommand()
        {
            if (SelectedModule != null)
                SelectedModule.Name = RenameText;
        }

        public void rename(string newName)
        {
            if (SelectedModule != null)
                SelectedModule.Name = newName;
        }

        private void modifyAssiociatedProfilCommand()
        {
            if (ModifyAssiociatedProfilStackVisibility == "Collapsed")
                ModifyAssiociatedProfilStackVisibility = "Visible";
            else
                ModifyAssiociatedProfilStackVisibility = "Collapsed";
        }

        private void turnOnOffCommand()
        {
            if (SelectedModule != null)
                SelectedModule.On = !SelectedModule.On;
        }
    }
}
