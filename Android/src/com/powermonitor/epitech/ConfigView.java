/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.json.JSONException;
import org.json.JSONObject;

/**
 *
 * @author jourda_c
 */
public class ConfigView extends FragmentActivity {

    private MyAdapter mAdapter;
    private ViewPager mPager;
    private JSONObject modulesData;
    private JSONObject profilesData;

    @Override
    protected void onCreate(Bundle savedInstanceBundle) {
        super.onCreate(savedInstanceBundle);
        Intent i = getIntent();
        try {
            modulesData = new JSONObject(i.getStringExtra("modules"));
            profilesData = new JSONObject(i.getStringExtra("profiles"));
        } catch (JSONException ex) {
            Logger.getLogger(ConfigView.class.getName()).log(Level.SEVERE, null, ex);
        }
        setContentView(R.layout.configview);
        mAdapter = new MyAdapter(getSupportFragmentManager(), modulesData, profilesData);
        mPager = (ViewPager) findViewById(R.id.pager);
        mPager.setAdapter(mAdapter);
    }

    private class MyAdapter extends FragmentPagerAdapter {

        private Context ctx;
        private JSONObject modules;
        private JSONObject profiles;

        public MyAdapter(FragmentManager fragmentManager, JSONObject modules, JSONObject profiles) {
            super(fragmentManager);
            this.modules = modules;
            this.profiles = profiles;
        }

        @Override
        public int getCount() {
            return 2;
        }

        @Override
        public Fragment getItem(int position) {
            ConfigModules m = new ConfigModules(this.modules);
            ConfigProfiles p = new ConfigProfiles(this.profiles);
            switch (position) {
                case 0:
                    return m;
                case 1:
                    return p;
                default:
                    return m;
            }
        }
    }

    /*@Override
     public boolean onCreateOptionsMenu(Menu menu) {
     // Inflate the menu; this adds items to the action bar if it is present.
     getMenuInflater().inflate(R.menu.main, menu);
     return true;
     }*/
}
