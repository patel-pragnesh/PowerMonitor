using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;
using GalaSoft.MvvmLight.Views;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
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
using Windows.UI;
using Windows.UI.Xaml;
using WinRTXamlToolkit.Controls.DataVisualization.Charting;

namespace Powermonitor.ViewModel
{
    public class ConsultationViewModel : MyViewModelBase
    {
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

        #region PowerNoDataVisibility
        private Visibility _powerNoDataVisibility;
        public Visibility PowerNoDataVisibility
        {
            get
            {
                return _powerNoDataVisibility;
            }
            set
            {
                if (value == _powerNoDataVisibility)
                    return;
                _powerNoDataVisibility = value;
                RaisePropertyChanged("PowerNoDataVisibility");
            }
        }
        #endregion
        #region VoltageNoDataVisibility
        private Visibility _voltageNoDataVisibility;
        public Visibility VoltageNoDataVisibility
        {
            get
            {
                return _voltageNoDataVisibility;
            }
            set
            {
                if (value == _voltageNoDataVisibility)
                    return;
                _voltageNoDataVisibility = value;
                RaisePropertyChanged("VoltageNoDataVisibility");
            }
        }
        #endregion
        #region AmperageNoDataVisibility
        private Visibility _amperageNoDataVisibility;
        public Visibility AmperageNoDataVisibility
        {
            get
            {
                return _amperageNoDataVisibility;
            }
            set
            {
                if (value == _amperageNoDataVisibility)
                    return;
                _amperageNoDataVisibility = value;
                RaisePropertyChanged("AmperageNoDataVisibility");
            }
        }
        #endregion

        private Chart _power;
        private Chart _voltage;
        private Chart _amperage;


        public ConsultationViewModel(INavigationService navigationService) : base(navigationService)
        {
            Communication.GetInstance.sendFuncs["getModules"].DynamicInvoke((Action<JObject, JObject>)GetModulesCallback);
            PowerNoDataVisibility = Visibility.Collapsed;
            VoltageNoDataVisibility = Visibility.Collapsed;
            AmperageNoDataVisibility = Visibility.Collapsed;
        }

        public void SetGraphs(Chart power, Chart voltage, Chart amperage) {
            _power = power;
            _voltage = voltage;
            _amperage = amperage;
            Communication.GetInstance.sendFuncs["getModules"].DynamicInvoke((Action<JObject, JObject>)GetModulesCallback);
        }

        public void GetConso(uint beg, uint end)
        {
            List<Module> selectedModules = Modules.Where(m => m.IsSelected == true).ToList();
            _power.Series.Clear();
            _voltage.Series.Clear();
            _amperage.Series.Clear();
            PowerNoDataVisibility = Visibility.Collapsed;
            VoltageNoDataVisibility = Visibility.Collapsed;
            AmperageNoDataVisibility = Visibility.Collapsed;
            foreach (Module m in selectedModules)
            {
                Communication.GetInstance.sendFuncs["getModuleConso"].DynamicInvoke((Action<JObject, JObject>)GetConsoCallback, m.Id, beg, end, (UInt64)1);
                if (m.Id != 2)
                    Communication.GetInstance.sendFuncs["getModuleConso"].DynamicInvoke((Action<JObject, JObject>)GetConsoCallback, m.Id, beg, end, (UInt64)2);
                Communication.GetInstance.sendFuncs["getModuleConso"].DynamicInvoke((Action<JObject, JObject>)GetConsoCallback, m.Id, beg, end, (UInt64)3);
            }
        }

        public static DateTime UnixTimeStampToDateTime(double unixTimeStamp)
        {
            // Unix timestamp is seconds past epoch
            System.DateTime dtDateTime = new DateTime(1970, 1, 1, 0, 0, 0, 0, System.DateTimeKind.Utc);
            dtDateTime = dtDateTime.AddSeconds(unixTimeStamp).ToLocalTime();
            return dtDateTime;
        }

        private void GetConsoCallback(JObject request, JObject response)
        {
            //if ((response["returnCode"] == null || response["returnCode"].ToObject<UInt64>() == 0) && response["modules"] != null)
            //{
            ObservableCollection<Tuple<DateTime, int>> values = new ObservableCollection<Tuple<DateTime, int>>();
            List<Info> tmp = JsonConvert.DeserializeObject<List<Info>>(response["infos"].ToString());
            foreach (Info i in tmp) {
                values.Add(new Tuple<DateTime, int>(UnixTimeStampToDateTime(i.Time), i.Value));
            }
            string moduleName = Modules.First(m => m.Id == request["moduleId"].ToObject<UInt64>()).Name;
            if (request["unitId"].ToObject<UInt64>() == 1)
            {
                if (values.Count == 0)
                    PowerNoDataVisibility = Visibility.Visible;
                _power.Series.Add(new LineSeries());
                int i = _power.Series.Count - 1;
                (_power.Series[i] as LineSeries).Title = moduleName;
                (_power.Series[i] as LineSeries).ItemsSource = values;
                (_power.Series[i] as LineSeries).IndependentValuePath = "Item1";
                (_power.Series[i] as LineSeries).DependentValuePath = "Item2";
            }
            else if (request["unitId"].ToObject<UInt64>() == 2)
            {
                if (values.Count == 0)
                    VoltageNoDataVisibility = Visibility.Visible;
                _voltage.Series.Add(new LineSeries());
                int i = _voltage.Series.Count - 1;
                (_voltage.Series[i] as LineSeries).Title = moduleName;
                (_voltage.Series[i] as LineSeries).ItemsSource = values;
                (_voltage.Series[i] as LineSeries).IndependentValuePath = "Item1";
                (_voltage.Series[i] as LineSeries).DependentValuePath = "Item2";
            }
            else if (request["unitId"].ToObject<UInt64>() == 3)
            {
                if (values.Count == 0)
                    AmperageNoDataVisibility = Visibility.Visible;
                _amperage.Series.Add(new LineSeries());
                int i = _amperage.Series.Count - 1;
                (_amperage.Series[i] as LineSeries).Title = moduleName;
                (_amperage.Series[i] as LineSeries).ItemsSource = values;
                (_amperage.Series[i] as LineSeries).IndependentValuePath = "Item1";
                (_amperage.Series[i] as LineSeries).DependentValuePath = "Item2";
            }
            //}
        }

        private void GetModulesCallback(JObject request, JObject response)
        {
            if ((response["returnCode"] == null || response["returnCode"].ToObject<UInt64>() == 0) && response["modules"] != null)
                Modules = new ObservableCollection<Module>(JsonConvert.DeserializeObject<List<Module>>(response["modules"].ToString()));
            else
                HandleError(response);
        }
    }
}
