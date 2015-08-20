/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech.Dialogs;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import com.powermonitor.epitech.Utils.ErrorCodes;

/**
 *
 * @author jourda_c
 */

/*
 Lazy class to create an error dialog
 Do not inherite AlertDialog since is way harder than this
 */
public class ErrorDialog {

    private final AlertDialog alert;
    private final boolean show;

    public ErrorDialog(Context c, ErrorCodes.Error error, DialogInterface.OnClickListener listener) {
        alert = new AlertDialog.Builder(c).create();
        alert.setTitle("Erreur");
        alert.setMessage(error.text);
        alert.setButton(DialogInterface.BUTTON_POSITIVE, "OK", listener != null ? listener : defaultListener);
        this.show = error.show;
    }

    public ErrorDialog(Context c, String error, DialogInterface.OnClickListener listener) {
        alert = new AlertDialog.Builder(c).create();
        alert.setTitle("Erreur");
        alert.setMessage(error);
        alert.setButton(DialogInterface.BUTTON_POSITIVE, "OK", listener != null ? listener : defaultListener);
        this.show = true;
    }

    public void show() {
        if (this.show) {
            alert.show();
        }
    }

    public DialogInterface.OnClickListener defaultListener = new DialogInterface.OnClickListener() {

        public void onClick(DialogInterface dialog, int which) {
        }
    };
}
