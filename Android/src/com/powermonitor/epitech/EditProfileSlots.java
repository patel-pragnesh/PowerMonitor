/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech;

import android.app.Activity;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.widget.EditText;
import android.widget.TextView;
import com.powermonitor.epitech.EditProfile.ProfileInfo;
import com.powermonitor.epitech.Utils.Communication;
import com.powermonitor.epitech.Utils.RequestHandler;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 *
 * @author jourda_c
 */
public class EditProfileSlots extends FragmentActivity {

    private ViewPager pager;
    private int id;
    private ProfileInfo profileInfo;

    @Override
    public void onCreate(Bundle savedInstance) {
        super.onCreate(savedInstance);
        setContentView(R.layout.editprofileslots);
        id = getIntent().getIntExtra(ConfigProfiles.EXTRA_PROFILE_ID, -1);
        Communication.INSTANCE.getProfile(id, onGetProfile);
        setTitle("Profil");
    }

    private final RequestHandler onGetProfile = new RequestHandler(this) {

        @Override
        public void onResult(JSONObject result, JSONObject params) {
            try {
                JSONObject obj = result.getJSONObject("profile");
                profileInfo = new ProfileInfo(obj);
                initDataLoaded();
            } catch (JSONException ex) {
                Logger.getLogger(EditProfileSlots.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    };

    private void initDataLoaded() {
        pager = (ViewPager) findViewById(R.EditProfileSlots.pager);
        pager.setAdapter(new MyAdapater(getSupportFragmentManager()));
    }

    private class MyAdapater extends FragmentPagerAdapter {

        public MyAdapater(FragmentManager fm) {
            super(fm);
        }

        @Override
        public Fragment getItem(int i) {
            switch (i) {
                case 0:
                    return new CalendarDayFragment(0, profileInfo.timeslotList, profileInfo.id);
                case 1:
                    return new CalendarDayFragment(1, profileInfo.timeslotList, profileInfo.id);
                case 2:
                    return new CalendarDayFragment(2, profileInfo.timeslotList, profileInfo.id);
                case 3:
                    return new CalendarDayFragment(3, profileInfo.timeslotList, profileInfo.id);
                case 4:
                    return new CalendarDayFragment(4, profileInfo.timeslotList, profileInfo.id);
                case 5:
                    return new CalendarDayFragment(5, profileInfo.timeslotList, profileInfo.id);
                case 6:
                    return new CalendarDayFragment(6, profileInfo.timeslotList, profileInfo.id);
                default:
                    return new CalendarDayFragment(0, profileInfo.timeslotList, profileInfo.id);
            }
        }

        @Override
        public int getCount() {
            return 7;
        }
    }
}
