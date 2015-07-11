/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech.Dialogs;

import com.powermonitor.epitech.R;
import android.R.layout;
import android.app.Dialog;
import android.content.Context;
import android.view.View;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import java.util.ArrayList;

/**
 *
 * @author jourda_c
 */
public class StringListViewDialog extends Dialog implements AdapterView.OnItemClickListener {
    
    private ListView listView;
    private ArrayAdapter<Row> adapter;
    private final ArrayList<Row> data = new ArrayList<Row>();

    public StringListViewDialog(Context context, boolean title) {
        super(context);
        if (!title)
            requestWindowFeature(Window.FEATURE_NO_TITLE);
        init();
    }
    public StringListViewDialog(Context context) {
        super(context);
        init();
    }

    public StringListViewDialog(Context context, int theme) {
        super(context, theme);
        init();
    }
    
    public final void init(){
        setContentView(R.layout.stringlistviewdialog);
        listView = (ListView) findViewById(R.StringListViewDialog.listView);
        adapter = new ArrayAdapter<Row>(getContext(), android.R.layout.simple_list_item_1, data);
        listView.setAdapter(adapter);
        listView.setOnItemClickListener(this);
    }
    
    public void addRow(String item, Object data){
        this.data.add(new Row(item, data));
        adapter.notifyDataSetChanged();
    }

    public final void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        onItemClick(adapter.getItem(position).data);
    }
    
    public void onItemClick(Object data){
        // Must overrode this one
        dismiss();
    }
    
    private class Row {
        String item;
        Object data;
        public Row(String item, Object data){
            this.item = item;
            this.data = data;
        }
        
        @Override
        public String toString(){
            return this.item;
        }
    }
}
