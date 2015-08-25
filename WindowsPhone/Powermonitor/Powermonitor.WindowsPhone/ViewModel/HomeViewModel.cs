using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Input;
using Powermonitor.Common;
using GalaSoft.MvvmLight.Command;
using GalaSoft.MvvmLight;
using WinRTXamlToolkit.Controls.DataVisualization.Charting;
using System.Collections.ObjectModel;
using GalaSoft.MvvmLight.Views;
using Newtonsoft.Json.Linq;

namespace Powermonitor.ViewModel
{
    public class HomeViewModel : MyViewModelBase
    {
        public ICommand bConsulter_Command { get; set; }
        public ICommand bConfigurer_Command { get; set; }

        private Chart _power;
        private Chart _voltage;
        private Chart _amperage;
        public HomeViewModel(INavigationService navigationService) : base(navigationService)
        {
        }

        public void SetGraphs(Chart power, Chart voltage, Chart amperage)
        {
            _power = power;
            _voltage = voltage;
            _amperage = amperage;
            bConfigurer_Command = new RelayCommand(Configurer_Command);

            ObservableCollection<Tuple<int, int>> Test2 = new ObservableCollection<Tuple<int, int>>();
            Test2.Add(new Tuple<int, int>(0, 30));
            Test2.Add(new Tuple<int, int>(1, 20));
            Test2.Add(new Tuple<int, int>(2, 50));
            _power.Series.Add(new LineSeries());
            (_power.Series[0] as LineSeries).ItemsSource = Test2;
            (_power.Series[0] as LineSeries).IndependentValuePath = "Item1";
            (_power.Series[0] as LineSeries).DependentValuePath = "Item2";

            ObservableCollection<Tuple<int, int>> Test3 = new ObservableCollection<Tuple<int, int>>();
            Test3.Add(new Tuple<int, int>(0, 20));
            Test3.Add(new Tuple<int, int>(1, 10));
            Test3.Add(new Tuple<int, int>(2, 60));
            _power.Series.Add(new LineSeries());
            (_power.Series[1] as LineSeries).ItemsSource = Test3;
            (_power.Series[1] as LineSeries).IndependentValuePath = "Item1";
            (_power.Series[1] as LineSeries).DependentValuePath = "Item2";

            _voltage.Series.Add(new LineSeries());
            (_voltage.Series[0] as LineSeries).ItemsSource = Test3;
            (_voltage.Series[0] as LineSeries).IndependentValuePath = "Item1";
            (_voltage.Series[0] as LineSeries).DependentValuePath = "Item2";

            _amperage.Series.Add(new LineSeries());
            (_amperage.Series[0] as LineSeries).ItemsSource = Test3;
            (_amperage.Series[0] as LineSeries).IndependentValuePath = "Item1";
            (_amperage.Series[0] as LineSeries).DependentValuePath = "Item2";
        }

        private void Configurer_Command()
        {
        }
    }
}
