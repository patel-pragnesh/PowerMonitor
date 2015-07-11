/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech.Dialogs;

import android.app.DatePickerDialog;
import android.app.Dialog;
import android.app.TimePickerDialog;
import android.content.Context;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.FragmentActivity;
import android.view.View;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.TimePicker;
import com.powermonitor.epitech.R;
import com.powermonitor.epitech.Utils.DatePickerFragment;

/**
 *
 * @author jourda_c
 */
public abstract class DoubleTimePicker extends Dialog {

    private EditText beggining;
    private EditText end;
    private Button bOk;
    private Time defaultTime1;
    private Time defaultTime2;
    
    public DoubleTimePicker(Context context) {
        super(context);
        init();
    }

    public DoubleTimePicker(Context context, int theme) {
        super(context, theme);
        init();
    }
    
    public final void init(){
        setContentView(R.layout.doubletimepicker);
        this.setTitle("Entrez l'horraire");
        beggining = (EditText)findViewById(R.DoubleTimePicker.Beginning);
        beggining.setOnClickListener(new OnDateClickListener());
        end = (EditText)findViewById(R.DoubleTimePicker.End);
        end.setOnClickListener(new OnDateClickListener());
        bOk = (Button)findViewById(R.DoubleTimePicker.bOk);
        bOk.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v) {
                Time t1, t2;
                t1 = (Time) beggining.getTag();
                t2 = (Time) end.getTag();
                onTimesSet(t1, t2);
                dismiss();
            }
        });
    }

    public void setDefaultTime(Time t1, Time t2){
        beggining.setTag(t1);
        end.setTag(t2);
        beggining.setText(String.format("%02d:%02d", t1.hours, t1.minutes));
        end.setText(String.format("%02d:%02d", t2.hours, t2.minutes));
    }
    
    public abstract void onTimesSet(Time time1, Time time2);
    
    public class OnDateClickListener implements View.OnClickListener {

        public void onClick(View v) {
            final EditText clicked = (EditText)v;
            Time def = (Time)v.getTag();
            if (def == null)
                def = new Time(0,0);
            TimePickerDialog picker = new TimePickerDialog(getContext(), new TimePickerDialog.OnTimeSetListener (){

                public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
                    clicked.setTag(new Time(hourOfDay, minute));
                    clicked.setText(String.format("%02d:%02d", hourOfDay, minute));
                }
            },def.hours, def.minutes, true);
            picker.show();
        }
    }
    
    public static class Time{
        public int hours;
        public int minutes;
        public Time(int hh, int mm){
           this.hours = hh;
           this.minutes = mm;
        }
        public void copy(Time other){
            this.hours = other.hours;
            this.minutes = other.minutes;
        }
        
        public int cmp(Time o){
            float mt = this.hours + this.minutes / 60.0f;
            float yt = o.hours + o.minutes / 60.0f;
            if (mt < yt)
                return -1;
            if (mt == yt)
                return 0;
            return 1;
        }
    }
}
