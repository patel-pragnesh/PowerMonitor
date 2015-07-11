package com.powermonitor.epitech;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import com.powermonitor.epitech.Utils.Communication;
import com.powermonitor.epitech.Utils.Storage;
import com.powermonitor.epitech.Utils.RequestHandler;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.json.JSONException;
import org.json.JSONObject;

/**
 *
 * Remove NoAnimActivity Handle intent creation manually (or create no anim
 * intent) REMINDER : Data must be load before the view and given as params.
 *
 * @author jourda_c
 */
public class Login extends Activity {

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        ((Button) findViewById(R.id.signin)).setOnClickListener(new Button.OnClickListener() {
            public void onClick(final View view) {
                EditText email = (EditText) findViewById(R.Main.email);
                EditText pass = (EditText) findViewById(R.Main.pass);
                Communication.INSTANCE.login(email.getText().toString(), pass.getText().toString(), new RequestHandler(Login.this) {

                    @Override
                    public void onResult(JSONObject result, JSONObject params) {
                        try {
                            if (result.getInt("returnCode") == 0) {
                                Intent i = new Intent(view.getContext(), Home.class);
                                i.setFlags(Intent.FLAG_ACTIVITY_NO_ANIMATION);
                                startActivity(i);
                                Login.this.finish();
                            }
                        } catch (JSONException ex) {
                            Logger.getLogger(Login.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }

                });
            }
        });
    }
}
