/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech.Utils;

import android.content.Context;
import android.content.SharedPreferences;
import com.powermonitor.epitech.Utils.NetworkCommunication.Session;


/**
 *
 * @author jourda_c
 */
public enum Storage {
    INSTANCE;

    private Context ctx;
    
    public Preferences prefs;
    
    public void setContext(Context c){
        this.ctx = c;
        prefs = new Preferences();
    }
    
    public class Preferences {
        private static final String PREFS = "PrefsFile";
        private static final String KEY_SESSION_TOKEN = "sessionToken";
        private static final String KEY_SESSION_ID = "sessionID";
        
        public SharedPreferences handle = ctx.getSharedPreferences(PREFS, 0);
        public SharedPreferences.Editor editorHandle = handle.edit();
        
        public void saveSession(Session s){
            editorHandle.putString(KEY_SESSION_TOKEN, s.getSessionToken());
            editorHandle.putInt(KEY_SESSION_ID, s.getUserId());
            editorHandle.apply();
        }
        
        public void getSession(Session s){
            s.setSessionToken(handle.getString(KEY_SESSION_TOKEN, ""));
            s.setUserId(handle.getInt(KEY_SESSION_ID, -1));
        }
        
        public void resetSession(){
            editorHandle.putString(KEY_SESSION_TOKEN, "");
            editorHandle.putInt(KEY_SESSION_ID, 0);
            editorHandle.apply();            
        }
    }
}
