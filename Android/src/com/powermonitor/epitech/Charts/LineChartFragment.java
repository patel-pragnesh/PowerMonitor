/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech.Charts;

import com.powermonitor.epitech.Models.Module;
import com.powermonitor.epitech.R;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;
import java.util.ArrayList;
import java.util.List;


/**
 *
 * @author jourda_c
 */
public class LineChartFragment extends Fragment {

    private LineChart chart;
    private List<Module> dataList;
    
    @Override
    public void onCreate(Bundle savedInstanceBundle){
        super.onCreate(savedInstanceBundle);
    }
    
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstance) {
        View v = inflater.inflate(R.layout.linechart, container, false);
        this.chart = (LineChart)v.findViewById(R.Charts.LineChart);

                // Temp data from 1st module
        // Temp code for test purpose
        ArrayList<Entry> tmpData = new Module(0).getDataList();
        LineDataSet dataSet = new LineDataSet(tmpData, "Consommation");
        dataSet.setLineWidth(2);

        ArrayList<LineDataSet> sets = new ArrayList<LineDataSet>();
        sets.add(dataSet);
        
        ArrayList<String> xVals = new ArrayList<String>();
        /*xVals.add("1");
        xVals.add("2");
        xVals.add("3");
        xVals.add("4");
        xVals.add("5");
        xVals.add("6");
        xVals.add("7");*/
        for (Entry e : tmpData){
            xVals.add(Integer.toString(e.getXIndex()));
        }

        LineData data = new LineData(xVals, sets);
        this.chart.setData(data);
        
        return v;
    }    
}
