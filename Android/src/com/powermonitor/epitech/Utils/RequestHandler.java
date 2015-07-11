/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech.Utils;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import com.powermonitor.epitech.Dialogs.ErrorDialog;
import com.powermonitor.epitech.Login;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.json.JSONException;
import org.json.JSONObject;

/**
 *
 * @author jourda_c
 */
public abstract class RequestHandler {

    private final Context ctx;

    public RequestHandler(Context c) {
        this.ctx = c;
    }

    public abstract void onResult(JSONObject result, JSONObject params);

    public void onError(String error, Exception e) {
        Logger.getLogger(RequestHandler.class.getName()).log(Level.SEVERE, error, e);
    }

    ;
    public void onInvalidToken() {
        ErrorDialog e = new ErrorDialog(ctx, ErrorCodes.getMsg(ErrorCodes.GEN_INVALID_SESSION), new DialogInterface.OnClickListener() {

            public void onClick(DialogInterface dialog, int which) {
                Storage.INSTANCE.prefs.resetSession();
                Intent i = new Intent(ctx, Login.class);
                i.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                ctx.startActivity(i);
            }
        });
        e.show();
    }
    
    public boolean hasError(JSONObject result) {
        try {
            int returnCode = result.getInt("returnCode");
            if (returnCode != 0) {
                ErrorDialog e = new ErrorDialog(ctx, ErrorCodes.getMsg(returnCode), null);
                e.show();
                return true;
            }
            return false;
        } catch (JSONException ex) {
            Logger.getLogger(RequestHandler.class.getName()).log(Level.SEVERE, null, ex);
            return true;
        }
    }

}
