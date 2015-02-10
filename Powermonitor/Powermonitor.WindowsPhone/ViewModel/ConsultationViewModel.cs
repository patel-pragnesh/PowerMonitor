using GalaSoft.MvvmLight;
using Powermonitor.Common;
using Powermonitor.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI;
using WinRTXamlToolkit.Controls.DataVisualization.Charting;

namespace Powermonitor.ViewModel
{
    public class ConsultationViewModel : ViewModelBase
    {
        #region Test
        private ObservableCollection<Tuple<int, int>> _test;
        public ObservableCollection<Tuple<int, int>> Test
        {
            get
            {
                return _test;
            }
            set
            {
                if (value == _test)
                    return;
                _test = value;
                RaisePropertyChanged("Test");
            }

        }
        #endregion
        #region Test2
        private ObservableCollection<Tuple<int, int>> _test2;
        public ObservableCollection<Tuple<int, int>> Test2
        {
            get
            {
                return _test2;
            }
            set
            {
                if (value == _test2)
                    return;
                _test2 = value;
                RaisePropertyChanged("Test2");
            }

        }
        #endregion

        #region Series
        Collection<ISeries> _series;
        public Collection<ISeries> Series
        {
            get
            {
                return _series;
            }
            set
            {
                if (value == _series)
                    return;
                _series = value;
                RaisePropertyChanged("Series");
            }

        }
        #endregion

        private Chart _power;
        private Chart _voltage;
        private Chart _amperage;
        public ObservableCollection<Module> Modules { get; private set; }
        public ConsultationViewModel(Chart power, Chart voltage, Chart amperage)
        {
            _power = power;
            _voltage = voltage;
            _amperage = amperage;
            Modules = new ObservableCollection<Module>();
            Modules.Add(new Module("module 1", true, new Profile("test")));
            Modules.Add(new Module("module 2", false, new Profile("test")));

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
    }
}
