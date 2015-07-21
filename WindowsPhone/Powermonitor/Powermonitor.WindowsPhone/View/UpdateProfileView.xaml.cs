﻿using GalaSoft.MvvmLight;
using Powermonitor.Common;
using Powermonitor.Model;
using Powermonitor.ViewModel;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
    public sealed partial class UpdateProfileView : Page
    {
        private NavigationHelper navigationHelper;
        private ViewModelBase defaultViewModel;

        public UpdateProfileView()
        {
            this.InitializeComponent();

            this.navigationHelper = new NavigationHelper(this);
            this.navigationHelper.LoadState += this.NavigationHelper_LoadState;
            this.navigationHelper.SaveState += this.NavigationHelper_SaveState;
            defaultViewModel = this.DataContext as ViewModelBase;
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
            this.navigationHelper.OnNavigatedTo(e);
            (this.DefaultViewModel as UpdateProfileViewModel).Refresh();
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            this.navigationHelper.OnNavigatedFrom(e);
        }

        #endregion

        private void bSchedule_Click(object sender, RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(ScheduleView));
        }

        async private void bAddAlert_Click(object sender, RoutedEventArgs e)
        {
            valueInput.Text = "";
            unitInput.SelectedIndex = 0;
            (this.DefaultViewModel as UpdateProfileViewModel).SelectedAlert = null;
            await addAlertDialog.ShowAsync();
        }

        private void addAlertDialog_PrimaryButtonClick(ContentDialog sender, ContentDialogButtonClickEventArgs args)
        {
            (this.DataContext as UpdateProfileViewModel).AddAlert(double.Parse(this.valueInput.Text), this.unitInput.SelectedIndex + 1);
        }

        private void Alert_Holding(object sender, HoldingRoutedEventArgs e)
        {
            if (e.HoldingState == Windows.UI.Input.HoldingState.Started)
            {
                var tmp = (sender as ListViewItem).DataContext;
                AlertListView.SelectedItem = tmp;
                FlyoutBase flyoutBase = FlyoutBase.GetAttachedFlyout(sender as FrameworkElement);

                flyoutBase.ShowAt(sender as FrameworkElement);
            } 
        }

        private async void bDeleteAlert_Click(object sender, RoutedEventArgs e)
        {
            await confirmDelete.ShowAsync();
        }

        private async void bUpdateAlert_Click(object sender, RoutedEventArgs e)
        {
            valueInput.Text = (AlertListView.SelectedItem as Alert).Value.ToString();
            unitInput.SelectedIndex = (int)(AlertListView.SelectedItem as Alert).UnitId - 1;
            await addAlertDialog.ShowAsync();
        }

        private void Alert_Tapped(object sender, TappedRoutedEventArgs e)
        {

        }

        private async void bRename_Click(object sender, RoutedEventArgs e)
        {
            await renameDialog.ShowAsync();
        }

        private async void bUpdatePolling_Click(object sender, RoutedEventArgs e)
        {
            await updatePollingDialog.ShowAsync();
        }

        private void updatePollingDialog_PrimaryButtonClick(ContentDialog sender, ContentDialogButtonClickEventArgs args)
        {
            (this.DataContext as UpdateProfileViewModel).UpdatePolling(newPollingTextBox.Text);
        }

        private void renameDialog_PrimaryButtonClick(ContentDialog sender, ContentDialogButtonClickEventArgs args)
        {
            (this.DataContext as UpdateProfileViewModel).Rename(newNameTextBox.Text);
        }
    }
}
