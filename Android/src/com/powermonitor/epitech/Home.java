/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import com.powermonitor.epitech.Utils.Communication;
import com.powermonitor.epitech.Utils.RequestHandler;
import org.json.JSONObject;

/**
 *
 * @author jourda_c
 */
public class Home extends Activity {

    @Override
    public void onCreate(Bundle instance) {
        super.onCreate(instance);
        setTitle("Accueil");
        setContentView(R.layout.home);
        ((Button) findViewById(R.id.bView)).setOnClickListener(new Button.OnClickListener() {
            public void onClick(View view) {
                Intent i = new Intent(view.getContext(), ViewModules.class);
                i.setFlags(Intent.FLAG_ACTIVITY_NO_ANIMATION);
                startActivity(i);
            }
        });
        ((Button) findViewById(R.id.bConfig)).setOnClickListener(new Button.OnClickListener() {
            public void onClick(View view) {
                Communication.INSTANCE.getModulesList(new RequestHandler(Home.this) {
                    @Override
                    public void onResult(JSONObject result, JSONObject params) {
                        final JSONObject modulesList = result;
                        Communication.INSTANCE.getProfilesList(new RequestHandler(Home.this) {
                            @Override
                            public void onResult(JSONObject result, JSONObject params) {
                                final JSONObject profilesList = result;
                                Intent i = new Intent(Home.this, ConfigView.class);
                                i.setFlags(Intent.FLAG_ACTIVITY_NO_ANIMATION);
                                i.putExtra("modules", modulesList.toString());
                                i.putExtra("profiles", profilesList.toString());
                                startActivity(i);
                            }
                        });
                    }
                });
            }
        });
    }
}
