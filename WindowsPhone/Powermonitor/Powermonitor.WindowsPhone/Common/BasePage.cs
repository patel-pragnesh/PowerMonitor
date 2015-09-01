using GalaSoft.MvvmLight.Messaging;
using Powermonitor.View;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;

namespace Powermonitor.Common
{
    public class BasePage : Page
    {
        static IAsyncInfo LastDialogControl = null;

        public BasePage()
        {
            Loaded += BasePage_Loaded;
            previous = null;
        }

        protected void HandleError(Error error)
        {
            ContentDialog errorDialog = new ContentDialog();
            TextBlock errorMsg = new TextBlock();
            errorMsg.Text = error.Text;
            errorDialog.Content = errorMsg;
            errorDialog.PrimaryButtonText = "Ok";
            CancelPreviousAndShowDialog(errorDialog);
        }

        void BasePage_Loaded(object sender, Windows.UI.Xaml.RoutedEventArgs e)
        {
            CommandBar commandBar = ((this.BottomAppBar == null) ? new CommandBar() : this.BottomAppBar as CommandBar);

            AppBarButton consultationButton = new AppBarButton();
            AppBarButton configurationButton = new AppBarButton();
            AppBarButton disconnectButton = new AppBarButton();

            consultationButton.Label = "Consultation";
            configurationButton.Label = "Configuration";
            disconnectButton.Label = "Deconnexion";

            consultationButton.Click += consultationButton_Click;
            configurationButton.Click += configurationButton_Click;

            commandBar.SecondaryCommands.Add(consultationButton);
            commandBar.SecondaryCommands.Add(configurationButton);
            commandBar.SecondaryCommands.Add(disconnectButton);
            this.BottomAppBar = commandBar;
        }

        private void consultationButton_Click(object sender, Windows.UI.Xaml.RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(ConsultationView));
        }

        private void configurationButton_Click(object sender, Windows.UI.Xaml.RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(ConfigurationView));
        }

        ContentDialog previous;

        protected void CancelPreviousAndShowDialog(ContentDialog dialog)
        {
            if (previous == null)
                previous = dialog;
            CancelPreviousDialog();
            LastDialogControl = dialog.ShowAsync();
        }

        protected void CancelPreviousDialog()
        {
            if (LastDialogControl != null)
            {
                LastDialogControl.Cancel();
                LastDialogControl = null;
            }
        }
    }
}
