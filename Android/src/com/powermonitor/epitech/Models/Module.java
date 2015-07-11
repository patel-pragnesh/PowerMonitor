/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech.Models;

import android.content.Context;
import android.widget.Toast;
import com.github.mikephil.charting.data.Entry;
import java.util.ArrayList;

/**
 *
 * @author jourda_c
 */
public class Module {

    private String name = "Toto";
    private Profile.Small profil;
    private boolean status;
    public int id;

    public Module(int i) {
        status = true;
        this.id = i;
    }

    public Module(int i, String name, Profile.Small profile, boolean status) {
        this.status = status;
        this.id = i;
        this.name = name;
        this.profil = profile;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String n) {
        // Call network name change
        this.name = n;
    }

    public boolean getStatus() {
        return this.status;
    }

    ;
    public void setStatus(boolean s) {
        // Call network status change
        this.status = s;
    }

    ;
    
    public Profile.Small getProfil() {
        return this.profil;
    }

    ;
    
    public ArrayList<Entry> getDataList() {
        // Get data from storage or network, will do it later
        // Temp dat here
        ArrayList<Entry> dataList = new ArrayList<Entry>();
        dataList.add(new Entry(10, 0));
        dataList.add(new Entry(20, 1));
        dataList.add(new Entry(21, 2));
        dataList.add(new Entry(12, 3));
        dataList.add(new Entry(15, 4));
        dataList.add(new Entry(3, 5));
        dataList.add(new Entry(10, 6));
        dataList.add(new Entry(21, 7));
        return dataList;
    }
}
