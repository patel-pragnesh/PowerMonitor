using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Practices.ServiceLocation;
using GalaSoft.MvvmLight.Ioc;
using GalaSoft.MvvmLight;
using Powermonitor.ViewModel;
using GalaSoft.MvvmLight.Views;
using Powermonitor.View;

namespace Powermonitor
{
    public class ViewModelLocator
    {
        static ViewModelLocator()
        {
            ServiceLocator.SetLocatorProvider(() => SimpleIoc.Default);

            SimpleIoc.Default.Register<INavigationService>(() => new NavigationService());

            SimpleIoc.Default.Register<InitViewModel>();
            SimpleIoc.Default.Register<ConfigurationViewModel>();
            SimpleIoc.Default.Register<ConsultationViewModel>();
            SimpleIoc.Default.Register<CreateProfilViewModel>();
            SimpleIoc.Default.Register<HomeViewModel>();
            SimpleIoc.Default.Register<LoginViewModel>();
            SimpleIoc.Default.Register<ScheduleViewModel>();
            (SimpleIoc.Default.GetInstance<INavigationService>() as NavigationService).Configure("Init", typeof(InitView));
            (SimpleIoc.Default.GetInstance<INavigationService>() as NavigationService).Configure("Login", typeof(LoginView));
            (SimpleIoc.Default.GetInstance<INavigationService>() as NavigationService).Configure("Home", typeof(HomeView));
            (SimpleIoc.Default.GetInstance<INavigationService>() as NavigationService).Configure("Configuration", typeof(ConfigurationView));
            (SimpleIoc.Default.GetInstance<INavigationService>() as NavigationService).Configure("Consultation", typeof(ConsultationView));
            (SimpleIoc.Default.GetInstance<INavigationService>() as NavigationService).Configure("Schedule", typeof(ScheduleView));
        }

        public InitViewModel InitVM
        {
            get { return ServiceLocator.Current.GetInstance<InitViewModel>(); }
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

        public ScheduleViewModel ScheduleVM
        {
            get { return ServiceLocator.Current.GetInstance<ScheduleViewModel>(); }
        }
    }
}
