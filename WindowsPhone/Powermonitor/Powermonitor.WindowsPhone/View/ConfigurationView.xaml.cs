using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Messaging;
using Powermonitor.Common;
using Powermonitor.Model;
using Powermonitor.ViewModel;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Graphics.Display;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// Pour en savoir plus sur le modèle d'élément Page de base, consultez la page http://go.microsoft.com/fwlink/?LinkID=390556

namespace Powermonitor.View
{
    /// <summary>
    /// Une page vide peut être utilisée seule ou constituer une page de destination au sein d'un frame.
    /// </summary>
    public sealed partial class ConfigurationView : BasePage
    {
        private NavigationHelper navigationHelper;
        private ViewModelBase defaultViewModel;

        public ConfigurationView()
        {
            this.InitializeComponent();
           // this.TopAppBar.Content = new TopAppBar();
            this.navigationHelper = new NavigationHelper(this);
            this.navigationHelper.LoadState += this.NavigationHelper_LoadState;
            this.navigationHelper.SaveState += this.NavigationHelper_SaveState;
            defaultViewModel = this.DataContext as ViewModelBase;
            LayoutRoot.DataContext = DefaultViewModel;
            Messenger.Default.Register<string>(this, HandleError);
        }

        async private void HandleError(string msg)
        {
            errorMsg.Text = msg;
            await error.ShowAsync();
        }

        /// <summary>
        /// Obtient le <see cref="NavigationHelper"/> associé à ce <see cref="Page"/>.
        /// </summary>
        public NavigationHelper NavigationHelper
        {
            get { return this.navigationHelper; }
        }

        /// <summary>
        /// Obtient le modèle d'affichage pour ce <see cref="Page"/>.
        /// Cela peut être remplacé par un modèle d'affichage fortement typé.
        /// </summary>
        public ViewModelBase DefaultViewModel
        {
            get { return this.defaultViewModel; }
        }

        /// <summary>
        /// Remplit la page à l'aide du contenu passé lors de la navigation. Tout état enregistré est également
        /// fourni lorsqu'une page est recréée à partir d'une session antérieure.
        /// </summary>
        /// <param name="sender">
        /// La source de l'événement ; en général <see cref="NavigationHelper"/>
        /// </param>
        /// <param name="e">Données d'événement qui fournissent le paramètre de navigation transmis à
        /// <see cref="Frame.Navigate(Type, Object)"/> lors de la requête initiale de cette page et
        /// un dictionnaire d'état conservé par cette page durant une session
        /// antérieure.  L'état n'aura pas la valeur Null lors de la première visite de la page.</param>
        private void NavigationHelper_LoadState(object sender, LoadStateEventArgs e)
        {
        }

        /// <summary>
        /// Conserve l'état associé à cette page en cas de suspension de l'application ou de
        /// suppression de la page du cache de navigation.  Les valeurs doivent être conformes aux
        /// exigences en matière de sérialisation de <see cref="SuspensionManager.SessionState"/>.
        /// </summary>
        /// <param name="sender">La source de l'événement ; en général <see cref="NavigationHelper"/></param>
        /// <param name="e">Données d'événement qui fournissent un dictionnaire vide à remplir à l'aide de l'
        /// état sérialisable.</param>
        private void NavigationHelper_SaveState(object sender, SaveStateEventArgs e)
        {
        }

        #region Inscription de NavigationHelper

        /// <summary>
        /// Les méthodes fournies dans cette section sont utilisées simplement pour permettre
        /// NavigationHelper pour répondre aux méthodes de navigation de la page.
        /// <para>
        /// La logique spécifique à la page doit être placée dans les gestionnaires d'événements pour  
        /// <see cref="NavigationHelper.LoadState"/>
        /// et <see cref="NavigationHelper.SaveState"/>.
        /// Le paramètre de navigation est disponible dans la méthode LoadState 
        /// en plus de l'état de page conservé durant une session antérieure.
        /// </para>
        /// </summary>
        /// <param name="e">Fournit des données pour les méthodes de navigation et
        /// les gestionnaires d'événements qui ne peuvent pas annuler la requête de navigation.</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            (this.DefaultViewModel as ConfigurationViewModel).Refresh();
            this.navigationHelper.OnNavigatedTo(e);
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            this.navigationHelper.OnNavigatedFrom(e);
        }

        #endregion

        private void bCreate_Click(object sender, RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(CreateProfileView));
        }

        private async void bDelete_Click(object sender, RoutedEventArgs e)
        {
            await confirmDelete.ShowAsync();
        }

        private void bUpdate_Click(object sender, RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(UpdateProfileView));
        }

        private void gProfilItem_Holding(object sender, HoldingRoutedEventArgs e)
        {
            FlyoutBase flyoutBase = FlyoutBase.GetAttachedFlyout(sender as FrameworkElement);

            flyoutBase.ShowAt(sender as FrameworkElement);
        }

        private void TextBox_KeyDown(object sender, KeyRoutedEventArgs e)
        {
            if (e.Key == Windows.System.VirtualKey.Enter)
            {
                (sender as TextBox).IsEnabled = false;
                (sender as TextBox).IsEnabled = true;
            }
        }

        private void ModuleListViewItem_Holding(object sender, HoldingRoutedEventArgs e)
        {
            if (e.HoldingState == Windows.UI.Input.HoldingState.Started)
            {
                var tmp = (sender as ListViewItem).DataContext;
                ModuleList.SelectedItem = tmp;

                FlyoutBase flyoutBase = FlyoutBase.GetAttachedFlyout(sender as FrameworkElement);

                flyoutBase.ShowAt(sender as FrameworkElement);
            }
        }

        private void ModuleListViewItem_Tapped(object sender, TappedRoutedEventArgs e)
        {
            //var tmp = (sender as ListViewItem).DataContext;
            //ModuleList.SelectedItem = tmp;
        }

        private void ProfileListViewItem_Holding(object sender, HoldingRoutedEventArgs e)
        {
            if (e.HoldingState == Windows.UI.Input.HoldingState.Started)
            {
                var tmp = (sender as ListViewItem).DataContext;
                ProfileList.SelectedItem = tmp;

                FlyoutBase flyoutBase = FlyoutBase.GetAttachedFlyout(sender as FrameworkElement);

                flyoutBase.ShowAt(sender as FrameworkElement);
            }
        }

        private void Pivot_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            Pivot p = sender as Pivot;
            if (p.SelectedIndex == 0)
                NewProfileButton.Visibility = Windows.UI.Xaml.Visibility.Collapsed;
            else if (p.SelectedIndex == 1)
                NewProfileButton.Visibility = Windows.UI.Xaml.Visibility.Visible;
        }

        private void bRename_Click(object sender, RoutedEventArgs e)
        {
            CancelPreviousAndShowDialog(moduleRenameDialog);
        }

        private void bChangeDefaultProfile_Click(object sender, RoutedEventArgs e)
        {
            DefaultProfile_List.SelectedItem = null;
            CancelPreviousAndShowDialog(moduleDefaultProfileDialog);
        }

        private void bDissociatDefaultProfile_Click(object sender, RoutedEventArgs e)
        {
            (DefaultViewModel as ConfigurationViewModel).DissociateProfile();
        }

        private void RenameDialog_Opened(ContentDialog sender, ContentDialogOpenedEventArgs args)
        {
            renameTextBox.Text = (ModuleList.SelectedItem as Module).Name;
        }

        private void RenameDialog_PrimaryButtonClick(ContentDialog sender, ContentDialogButtonClickEventArgs args)
        {
            (DefaultViewModel as ConfigurationViewModel).Rename(renameTextBox.Text);
        }

        private void DefaultProfileListBox_Tapped(object sender, TappedRoutedEventArgs e)
        {
            DefaultProfile_List.SelectedItem = (sender as ListBoxItem).DataContext;
        }

        private void ToggleButton_Click(object sender, RoutedEventArgs e)
        {
            var tmp = (((sender as ToggleButton).Parent as Grid).Parent as ListViewItem).DataContext;
            ModuleList.SelectedItem = tmp;
        }
    }
}
