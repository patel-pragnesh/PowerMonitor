using GalaSoft.MvvmLight;
using Powermonitor.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.ViewModel
{
    public class ModifyProfilViewModel : ViewModelBase
    {
        #region Profil
        private Profile _profil;
        public Profile Profil
        {
            get
            {
                return _profil;
            }
            set
            {
                if (value == _profil)
                    return;
                _profil = value;
                RaisePropertyChanged("Profil");
            }

        }
        #endregion
        public ModifyProfilViewModel()
        {

        }
    }
}
