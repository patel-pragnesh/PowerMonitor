using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Practices.ServiceLocation;
using GalaSoft.MvvmLight.Ioc;
using GalaSoft.MvvmLight;
using Powermonitor.ViewModel;

namespace Powermonitor
{
    public class ViewModelLocator
    {
        static ViewModelLocator()
        {
            ServiceLocator.SetLocatorProvider(() => SimpleIoc.Default);

            SimpleIoc.Default.Register<ConfigurationViewModel>();
            SimpleIoc.Default.Register<ConsultationViewModel>();
            SimpleIoc.Default.Register<CreateProfilViewModel>();
            SimpleIoc.Default.Register<HomeViewModel>();
            SimpleIoc.Default.Register<LoginViewModel>();
        }

        public ConfigurationViewModel ConfigurationVM
        {
            get { return ServiceLocator.Current.GetInstance<ConfigurationViewModel>(); }
        }

        public ConsultationViewModel ConsultationVM
        {
            get { return ServiceLocator.Current.GetInstance<ConsultationViewModel>(); }
        }

        public CreateProfilViewModel CreateProfilVM
        {
            get { return ServiceLocator.Current.GetInstance<CreateProfilViewModel>(); }
        }

        public HomeViewModel HomeVM
        {
            get { return ServiceLocator.Current.GetInstance<HomeViewModel>(); }
        }

        public LoginViewModel LoginVM
        {
            get { return ServiceLocator.Current.GetInstance<LoginViewModel>(); }
        }
    }
}
