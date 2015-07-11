/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech.Models;

import java.util.ArrayList;

/**
 *
 * @author jourda_c
 */
public class Profile {

    private int id = -1;
    private String name = "[ProfileName?]";
    private int polling = 0;
    private ArrayList<Alert> alerts;
    private ArrayList<TimeSlot> timeSlots;

    public Profile(int id_, String name_, int polling_) {
        this.id = id_;
        this.name = name_;
        this.polling = polling_;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getPolling() {
        return polling;
    }

    public void setPolling(int polling) {
        this.polling = polling;
    }

    public static class Small {
        private String name;
        private int id;
        public Small(int id, String name){
            this.name = name;
            this.id = id;
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }

        public int getId() {
            return id;
        }

        public void setId(int id) {
            this.id = id;
        }
        
    }
    
}
