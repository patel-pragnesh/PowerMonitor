/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech;

import android.app.DatePickerDialog;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.view.View;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import com.powermonitor.epitech.Charts.LineChartFragment;
import com.powermonitor.epitech.ListRows.ModuleListAdapter;
import com.powermonitor.epitech.Models.Module;
import com.powermonitor.epitech.Utils.DatePickerFragment;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author jourda_c
 */
public class ViewModules extends FragmentActivity {

    private ListView list;
    private List<Module> dataList;
    private ModuleListAdapter adapter;
    private ChartViewAdapter chartViewAdapter;
    private ViewPager chartViewPager;

    @Override
    public void onCreate(Bundle saveInstance) {
        super.onCreate(saveInstance);
        setContentView(R.layout.viewmodules);
        ((TextView) findViewById(R.id.page_title)).setText("Consultation");

        // List view
        this.list = (ListView) findViewById(R.ViewModules.modulesListView);
        this.dataList = new ArrayList<Module>();
        //this.dataList.add(new Module(0));
        this.adapter = new ModuleListAdapter(this, R.layout.modulerow, this.dataList);
        this.list.setAdapter(this.adapter);

        // Date filter
        EditText dateFrom = (EditText) findViewById(R.ViewModules.dateFrom);
        EditText dateTo = (EditText) findViewById(R.ViewModules.dateTo);
        dateFrom.setOnClickListener(new OnDateClickListener());
        dateTo.setOnClickListener(new OnDateClickListener());
        
        // Chart
        this.chartViewAdapter = new ChartViewAdapter(getSupportFragmentManager());
        this.chartViewPager = (ViewPager) this.findViewById(R.ViewModules.pager);
        this.chartViewPager.setAdapter(this.chartViewAdapter);
        
        // Temp data from 1st module
        // Temp code for test purpose
        /*ArrayList<Entry> tmpData = this.dataList.get(0).getDataList();
        LineDataSet dataSet = new LineDataSet(tmpData, "Consommation");
        dataSet.setLineWidth(2);

        ArrayList<LineDataSet> sets = new ArrayList<LineDataSet>();
        sets.add(dataSet);
        
        ArrayList<String> xVals = new ArrayList<String>();
        xVals.add("1");
        xVals.add("2");
        xVals.add("3");
        xVals.add("4");
        xVals.add("5");
        xVals.add("6");
        xVals.add("7");

        LineData data = new LineData(xVals, sets);
        LineChart chart = (LineChart) findViewById(R.ViewModules.lineChart);
        chart.setData(data);*/
    }

    public class OnDateClickListener implements View.OnClickListener {

        public void onClick(View v) {
                final EditText clickedEdit = (EditText) v;
                DialogFragment dateFragment = new DatePickerFragment() {
                    @Override
                    public void onDateSet(DatePicker view, int y, int m, int d) {
                        clickedEdit.setText("" + d + "/" + m + "/" + y);
                    }
                };
                dateFragment.show(getSupportFragmentManager(), "datePicker");
        }

    }
    
    private class ChartViewAdapter extends FragmentPagerAdapter {
        
        private static final int ITEM_COUNT = 2 ;

        public ChartViewAdapter(FragmentManager fm) {
            super(fm);
        }

        @Override
        public Fragment getItem(int i) {
            switch (i){
                case 0: return new LineChartFragment();
                case 1: return new LineChartFragment();
                default: return new LineChartFragment();
            }
        }

        @Override
        public int getCount() {
            return ITEM_COUNT;
        }
        
    }

}
