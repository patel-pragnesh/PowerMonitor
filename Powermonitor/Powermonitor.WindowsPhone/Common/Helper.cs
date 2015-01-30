using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Data;

namespace Powermonitor.Common
{
    public class Helper
    {
        public static string GetIsSelectedContainerBinding(DependencyObject obj)
        {
            return (string)obj.GetValue(IsSelectedContainerBindingProperty);
        }

        public static void SetIsSelectedContainerBinding(DependencyObject obj, string value)
        {
            obj.SetValue(IsSelectedContainerBindingProperty, value);
        }

        // Using a DependencyProperty as the backing store for IsSelectedContainerBinding.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty IsSelectedContainerBindingProperty =
            DependencyProperty.RegisterAttached("IsSelectedContainerBinding", typeof(string), typeof(Helper), new PropertyMetadata(null, IsSelectedContainerBindingPropertyChangedCallback));

        public static void IsSelectedContainerBindingPropertyChangedCallback(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            BindingOperations.SetBinding(d, ListViewItem.IsSelectedProperty, new Binding()
            {
                Source = d,
                Path = new PropertyPath("Content." + e.NewValue),
                Mode = BindingMode.TwoWay
            });
        }
    }
}
