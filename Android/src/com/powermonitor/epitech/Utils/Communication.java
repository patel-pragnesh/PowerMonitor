/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech.Utils;

import com.powermonitor.epitech.EditProfileSlots;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.json.JSONException;
import org.json.JSONObject;

/**
 *
 * @author jourda_c
 */
/**
 * Communication Class (Singleton) Handle retrieving data for views Can retrieve
 * data from : - Network source - Storage source (not implemented) -> The choice
 * is transparent to calling class
 */
public enum Communication {

    INSTANCE;

    private NetworkCommunication netCom;
    private boolean isInit = false;

    private Communication() {
        netCom = new NetworkCommunication();
    }

    /**
     * init() method Initialize networkCommunication and localStorage. Must be
     * called first
     */
    public void init(RequestHandler h) {
        // TODO: Create LocalStorage class to retrieve data
        netCom.connect(h);
        isInit = true;
    }

    public boolean isInit() {
        return isInit;
    }

    public boolean isNetworkSessionValid() {
        return this.netCom.isSessionValid();
    }

    /**
     * Below are all the possible commands Each choose between network or
     * storage data on its own
     *
     * @param handler
     * @param params
     */
    public void getModulesList(RequestHandler handler) {
        // No storage data here (Implementation choice)
        netCom.startCommand(NetworkCommunication.CMD_GetModules, handler);
    }

    public void getProfilesList(RequestHandler handler) {
        netCom.startCommand(NetworkCommunication.CMD_GetProfiles, handler);
    }

    public void getInternalProfile(int iProfileId, RequestHandler handler) {
        try {
            JSONObject params = new JSONObject();
            params.put("id", iProfileId);
            netCom.startCommand(NetworkCommunication.CMD_GetInternalProfile, handler, params);
        } catch (JSONException ex) {
            Logger.getLogger(Communication.class.getName()).log(Level.SEVERE, null, ex);
            handler.onError("getInternalProfile(): error - JSONException", ex);
        }
    }

    public void deleteProfile(int id, RequestHandler handler) {
        try {
            JSONObject params = new JSONObject();
            params.put("id", id);
            netCom.startCommand(NetworkCommunication.CMD_DeleteProfile, handler, params);
        } catch (JSONException ex) {
            Logger.getLogger(Communication.class.getName()).log(Level.SEVERE, null, ex);
            handler.onError("deleteProfile(): error - JSONException", ex);
        }
    }

    public void login(String email, String password, RequestHandler handler) {
        try {
            JSONObject params = new JSONObject();
            params.put("email", email);
            params.put("password", password);
            netCom.startCommand(NetworkCommunication.CMD_Login, handler, params);
        } catch (JSONException ex) {
            Logger.getLogger(Communication.class.getName()).log(Level.SEVERE, null, ex);
            handler.onError("login(): error - JSONException", ex);
        }
    }

    public void toggleModuleState(int id, boolean status, RequestHandler handler) {
        try {
            JSONObject params = new JSONObject();
            params.put("id", id);
            params.put("status", status);
            netCom.startCommand(NetworkCommunication.CMD_TurnOnOff, handler, params);
        } catch (JSONException ex) {
            Logger.getLogger(Communication.class.getName()).log(Level.SEVERE, null, ex);
            handler.onError("toggleModuleState() error - JSONException", ex);
        }
    }

    public void renameModule(int id, String name, RequestHandler handler) {
        try {
            JSONObject params = new JSONObject();
            params.put("id", id);
            params.put("name", name);
            netCom.startCommand(NetworkCommunication.CMD_RenameModule, handler, params);
        } catch (JSONException ex) {
            Logger.getLogger(Communication.class.getName()).log(Level.SEVERE, null, ex);
            handler.onError("renameModule() error - JSONException", ex);
        }
    }

    public void updateModuleDefaultProfile(int moduleId, int profileId, RequestHandler handler) {
        try {
            JSONObject params = new JSONObject();
            params.put("id", moduleId);
            params.put("defaultProfileId", profileId != 0 ? profileId : null);
            netCom.startCommand(NetworkCommunication.CMD_UpdateModuleDefaultProfile, handler, params);
        } catch (JSONException ex) {
            Logger.getLogger(Communication.class.getName()).log(Level.SEVERE, null, ex);
            handler.onError("updateModuleDefaultProfile() error - JSONException", ex);
        }
    }

    public void getProfile(int profileId, RequestHandler handler) {
        try {
            JSONObject params = new JSONObject();
            params.put("id", profileId);
            netCom.startCommand(NetworkCommunication.CMD_GetProfile, handler, params);
        } catch (JSONException ex) {
            Logger.getLogger(Communication.class.getName()).log(Level.SEVERE, null, ex);
            handler.onError("getProfile() error - JSONException", ex);
        }
    }
    
    public void addTimeSlot(int profileId, JSONObject beg, JSONObject end, RequestHandler handler){
        try {
            JSONObject params = new JSONObject();
            params.put("profileId", profileId);
            params.put("beg", beg);
            params.put("end", end);
            netCom.startCommand(NetworkCommunication.CMD_AddTimeSlot, handler, params);
        } catch (JSONException ex) {
            Logger.getLogger(Communication.class.getName()).log(Level.SEVERE, null, ex);
            handler.onError("JSONException", ex);
        }        
    }
    
    public void updateTimeSlot(int slotId, JSONObject beg, JSONObject end, RequestHandler handler){
        try {
            JSONObject params = new JSONObject();
            params.put("id", slotId);
            params.put("beg", beg);
            params.put("end", end);
            netCom.startCommand(NetworkCommunication.CMD_UpdateTimeSlot, handler, params);
        } catch (JSONException ex) {
            Logger.getLogger(Communication.class.getName()).log(Level.SEVERE, null, ex);
            handler.onError("JSONException", ex);
        }
    }

    public void deleteTimeSlot(int slotId, RequestHandler handler){
        try {
            JSONObject params = new JSONObject();
            params.put("id", slotId);
            netCom.startCommand(NetworkCommunication.CMD_DeleteTimeSlot, handler, params);
        } catch (JSONException ex) {
            Logger.getLogger(Communication.class.getName()).log(Level.SEVERE, null, ex);
            handler.onError("JSONException", ex);
        }
    }
    
    public void addAlert(int profileId, int unitId, double value, RequestHandler handler){
        try {
            JSONObject params = new JSONObject();
            params.put("profileId", profileId);
            params.put("unitId", unitId);
            params.put("value", value);
            netCom.startCommand(NetworkCommunication.CMD_AddAlert, handler, params);
        } catch (JSONException ex) {
            Logger.getLogger(Communication.class.getName()).log(Level.SEVERE, null, ex);
            handler.onError("JSONException", ex);        
        }
    }
    public void updateAlert(int alertId, int unitId, double value, RequestHandler handler){
        try {
            JSONObject params = new JSONObject();
            params.put("id", alertId);
            params.put("unitId", unitId);
            params.put("value", value);
            netCom.startCommand(NetworkCommunication.CMD_UpdateAlert, handler, params);
        } catch (JSONException ex) {
            Logger.getLogger(Communication.class.getName()).log(Level.SEVERE, null, ex);
            handler.onError("JSONException", ex);        
        }
    }
    public void deleteAlert(int alertId, RequestHandler handler){
        try {
            JSONObject params = new JSONObject();
            params.put("id", alertId);
            netCom.startCommand(NetworkCommunication.CMD_DeleteAlert, handler, params);
        } catch (JSONException ex) {
            Logger.getLogger(Communication.class.getName()).log(Level.SEVERE, null, ex);
            handler.onError("JSONException", ex);        
        }
    }
    public void addProfile(String name, int polling, RequestHandler handler){
        try {
            JSONObject params = new JSONObject();
            params.put("name", name);
            params.put("polling", polling);
            netCom.startCommand(NetworkCommunication.CMD_AddProfile, handler, params);
        } catch (JSONException ex) {
            Logger.getLogger(Communication.class.getName()).log(Level.SEVERE, null, ex);
            handler.onError("JSONException", ex);        
        }
    }


}
