/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech.Utils;

import android.util.SparseArray;
import java.util.HashMap;
import java.util.Map;

/**
 *
 * @author jourda_c
 */
public class ErrorCodes {
    public static final SparseArray<Error> errorMap;

    /**
     * Internal
     */
    public static final int NO_CONNECTION = 0xFFFFFF;

    /**
     * Generics
     */
    public static final int GEN_INCORRECT_REQUEST = 0x101;
    public static final int GEN_COMMAND_NOT_FOUND = 0x102;
    public static final int GEN_INVALID_SESSION = 0x103;
    public static final int GEN_SESSION_EXPIRED = 0x104;

    /**
     * Authentication
     */
    public static final int AUT_INCORRECT_PASSWORD = 0x201;
    
    /**
     * Entities
     */
    public static final int ENT_NOT_FOUND = 0x301;
    public static final int ENT_INVALID_NAME = 0x302;
    
    /**
     * Modules
     */
    public static final int MOD_UPDATE_STATE = 0x401; // When the state cannot be updated
    public static final int MOD_STATE_ALREADY_SET = 0x402; // When a state is sent but the module already has this state
    public static final int MOD_NO_SUCH_PROFILE = 0x403; // A wrong profile ID is sent
    
    /**
     * Profiles
     */
    public static final int PRO_DELETE_IN_USE = 0x501;
    
    static {
        SparseArray<Error> m = new SparseArray<Error>();
        m.put(NO_CONNECTION, new Error("Le serveur est introuvable. Veuillez contacter le support", true));
        m.put(GEN_INCORRECT_REQUEST, new Error("Requete incorrect. Veuillez reporter l'erreur dès que possible", false));
        m.put(GEN_COMMAND_NOT_FOUND, new Error("Commande introuvable. Veuillez reporter l'erreur dès que possible", false));
        m.put(GEN_INVALID_SESSION, new Error("Session invalide. Veuillez vous reconnecter", true));
        m.put(GEN_SESSION_EXPIRED, new Error("La session a expriré. Veuillez vous reconnecter", true));
        m.put(AUT_INCORRECT_PASSWORD, new Error("Mot de passe incorrect", true));
        m.put(ENT_NOT_FOUND, new Error("Entité introuvable. Veuillez reporter l'erreur dès que possible", false));
        m.put(ENT_INVALID_NAME, new Error("Nom d'entité invalide", false));
        m.put(MOD_UPDATE_STATE, new Error("Impossible de mettre à jour l'état du module", true));
        m.put(MOD_STATE_ALREADY_SET, new Error("Le module possède déjà cet état", true));
        m.put(MOD_NO_SUCH_PROFILE, new Error("Ce profil est introuvable", true));
        m.put(PRO_DELETE_IN_USE, new Error("Impossible de supprimer un profil associé à un module", true));
        errorMap = m;
    }
    public static Error getMsg(int errCode){
        return errorMap.get(errCode);
    }
    
    public static class Error {
        public String text;
        public boolean show;
        public Error(String err, boolean show){
            this.text = err;
            this.show = show;
        }
    }
}
