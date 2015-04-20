using GalaSoft.MvvmLight;
using Powermonitor.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.ViewModel
{
    public class ModifyProfileViewModel : ViewModelBase
    {
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

        #region Title
        private string _Title;
        public string Title
        {
            get
            {
                return _Title;
            }
            set
            {
                if (value == _Title)
                    return;
                _Title = value;
                RaisePropertyChanged("Title");
            }

        }
        #endregion
        public ModifyProfileViewModel()
        {
            if (ToUpdate == null)
            {
                Profile = new Profile();
                Title = "Créer";
            }
            else
            {
                Profile = ToUpdate;
                Title = "Modifier";
            }
        }
    }
}
