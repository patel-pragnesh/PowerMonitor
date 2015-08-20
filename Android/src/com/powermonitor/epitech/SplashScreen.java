/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.widget.TextView;
import com.powermonitor.epitech.Dialogs.ErrorDialog;
import com.powermonitor.epitech.Utils.Communication;
import com.powermonitor.epitech.Utils.ErrorCodes;
import com.powermonitor.epitech.Utils.RequestHandler;
import com.powermonitor.epitech.Utils.Storage;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.json.JSONObject;

/**
 *
 * @author jourda_c
 */
public class SplashScreen extends Activity {

    private boolean isCommunicationAvailable = false;
    private Handler initHandler = new Handler();
    private TextView infos;

    @Override
    public void onCreate(Bundle savedInstance) {
        super.onCreate(savedInstance);
        setContentView(R.layout.splashscreen);
        infos = (TextView) findViewById(R.SplashScreen.infos);
        // Should check if network is available
        infos.setText("Connexion en cours ...");
        new Thread(new Runnable() {

            public void run() {
                int nb = 0;
                try {
                    while ((nb <= 10000 && !isCommunicationAvailable) || (isCommunicationAvailable && nb <= 3000)) {
                        nb += 100;
                        Thread.sleep(100);
                    }
                    if (nb >= 10000) {
                        // Here, app did not init correctly
                        initHandler.post(new Runnable() {

                            public void run() {
                                ErrorDialog e = new ErrorDialog(SplashScreen.this, ErrorCodes.getMsg(ErrorCodes.NO_CONNECTION).text, new DialogInterface.OnClickListener() {
                                    public void onClick(DialogInterface dialog, int which) {
                                        SplashScreen.this.finish();
                                    }
                                });
                                e.show();
                            }
                        });
                    }
                } catch (InterruptedException ex) {
                    Logger.getLogger(SplashScreen.class.getName()).log(Level.SEVERE, null, ex);
                } finally {
                    if (isCommunicationAvailable) {

                        finish();
                        // Maybe create a command to check session token (since it can timeout)

                        Intent i;
                        if (Communication.INSTANCE.isNetworkSessionValid()) {
                            i = new Intent(SplashScreen.this, Home.class);
                        } else {
                            i = new Intent(SplashScreen.this, Login.class);
                        }
                        startActivity(i);
                    }
                }
            }
        }).start();
        Storage.INSTANCE.setContext(this); // Must be init first, since communication uses it
        infos.setText("Connexion en cours ...");
        Communication.INSTANCE.init(new RequestHandler(this) {

            @Override
            public void onResult(JSONObject result, JSONObject params) {
                isCommunicationAvailable = true;
            }
        });

    }

}
