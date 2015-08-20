/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech.ListRows;

import com.powermonitor.epitech.Models.Profile;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;
import java.util.List;
import com.powermonitor.epitech.R;

/**
 *
 * @author jourda_c
 */
public class ProfileListAdapter extends ArrayAdapter<Profile> {

    private int rowResourceId;
    
    public ProfileListAdapter(Context context, int viewResourceId, List<Profile> objects) {
        super(context, viewResourceId, objects);
        rowResourceId = viewResourceId;
    }

    @Override
    public View getView(int pos, View convertView, ViewGroup parent) {
        View v = convertView;
        if (v == null) {
            LayoutInflater inf = LayoutInflater.from(getContext());
            v = inf.inflate(this.rowResourceId, null);
            ViewHolder vh = new ViewHolder();
            vh.name = (TextView) v.findViewById(R.ProfileRow.name);
            v.setTag(vh);
        }
        ViewHolder vh = (ViewHolder) v.getTag();
        Profile item = getItem(pos);
        vh.name.setText(item.getName());
        return v;
    }

    private class ViewHolder {
        public TextView name;
    }
}
