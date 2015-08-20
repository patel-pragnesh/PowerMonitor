/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.Toast;
import com.powermonitor.epitech.CustomCalendar.Slot;
import com.powermonitor.epitech.Dialogs.DoubleTimePicker;
import com.powermonitor.epitech.Dialogs.DoubleTimePicker.Time;
import com.powermonitor.epitech.EditProfile.ProfileTimeSlot;
import com.powermonitor.epitech.Utils.Communication;
import com.powermonitor.epitech.Utils.RequestHandler;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.json.JSONException;
import org.json.JSONObject;

/**
 *
 * @author jourda_c
 */
public class CalendarDayFragment extends Fragment {

    private static final String[] days = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};
    private final int day; // Should pass int. Waiting for server for change
    public CustomCalendar calendar;
    private ArrayList<ProfileTimeSlot> list;
    private int profileId;

    public CalendarDayFragment(int day, ArrayList<ProfileTimeSlot> slots, int profileId) {
        this.day = day;
        this.list = slots;
        this.profileId = profileId;
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {
        if (!getUserVisibleHint()) {
            return super.onContextItemSelected(item);
        }
        if (item.getGroupId() == CustomCalendar.CONTEXT_MENU_GROUP) {
            CustomCalendar.SlotContextMenuInfo info = (CustomCalendar.SlotContextMenuInfo) item.getMenuInfo();
            switch (item.getItemId()) {
                case CustomCalendar.CONTEXT_MENU_ITEM_MODIFY:
                    calendar.updateSlot(info.slot, true);
                    return true;
                case CustomCalendar.CONTEXT_MENU_ITEM_DELETE:
                    onDeleteOptionSelected(info.slot);
                    return true;
            }
        }
        return super.onContextItemSelected(item);
    }

    private void onDeleteOptionSelected(final Slot s){
        Communication.INSTANCE.deleteTimeSlot(s.id, new RequestHandler(getActivity()) {
                        @Override
            public void onResult(JSONObject result, JSONObject params) {
                calendar.removeSlot(s);
            }
        });
    }
    
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstance) {
        View v = inflater.inflate(R.layout.calendarday, container, false);
        ((TextView) v.findViewById(R.CalendarDay.title)).setText(days[this.day]);
        calendar = (CustomCalendar) v.findViewById(R.EditProfileSlots.calendar);
        calendar.setOnSlotAddedListener(new CustomCalendar.OnSlotEventListener() {
            @Override
            public void onSlotAdded(DoubleTimePicker.Time beg, DoubleTimePicker.Time end) {
                JSONObject bo = new JSONObject();
                JSONObject eo = new JSONObject();
                try {
                    bo.put("day", day);
                    bo.put("minute", beg.hours * 60 + beg.minutes);
                    eo.put("day", day);
                    eo.put("minute", end.hours * 60 + end.minutes);
                    Communication.INSTANCE.addTimeSlot(profileId, bo, eo, onSlotAdded);
                } catch (JSONException ex) {
                    Logger.getLogger(CalendarDayFragment.class.getName()).log(Level.SEVERE, null, ex);
                }
            }

            @Override
            public void onSlotChanged(final Slot s, final DoubleTimePicker.Time beg, final DoubleTimePicker.Time end) {
                JSONObject bo = new JSONObject();
                JSONObject eo = new JSONObject();
                try {
                    bo.put("day", day);
                    bo.put("minute", beg.hours * 60 + beg.minutes);
                    eo.put("day", day);
                    eo.put("minute", end.hours * 60 + end.minutes);
                    Communication.INSTANCE.updateTimeSlot(s.id, bo, eo, new RequestHandler(getActivity()) {
                        @Override
                        public void onResult(JSONObject result, JSONObject params) {
                            s.beg.copy(beg);
                            s.end.copy(end);
                            calendar.invalidate();
                        }
                    });
                } catch (JSONException ex) {
                    Logger.getLogger(CalendarDayFragment.class.getName()).log(Level.SEVERE, null, ex);
                }
                s.beg.copy(beg);
                s.end.copy(end);
                calendar.invalidate();
            }
        });
        for (ProfileTimeSlot t : list) {
            addValidTimeSlot(t);
        }
        return v;
    }

    private final RequestHandler onSlotAdded = new RequestHandler(getActivity()) {

        @Override
        public void onResult(JSONObject result, JSONObject params) {
            try {
                int id = result.getInt("id");
                int minutesBeg = params.getJSONObject("beg").getInt("minute");
                int minutesEnd = params.getJSONObject("end").getInt("minute");
                calendar.addSlot(id, minutesBeg, minutesEnd);
            } catch (JSONException ex) {
                Logger.getLogger(CalendarDayFragment.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    };

    private void addValidTimeSlot(ProfileTimeSlot t) {
        if (t.begDay == this.day) {
            calendar.addSlot(t.id, t.begMin, t.endMin);
        }
    }
}
