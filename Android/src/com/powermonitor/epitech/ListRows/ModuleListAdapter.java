/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech.ListRows;

import com.powermonitor.epitech.Models.Module;
import android.content.Context;
import android.graphics.Color;
import android.opengl.Visibility;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;
import com.powermonitor.epitech.ConfigModules;
import com.powermonitor.epitech.Dialogs.ErrorDialog;
import java.util.List;
import com.powermonitor.epitech.R;
import com.powermonitor.epitech.Utils.Communication;
import com.powermonitor.epitech.Utils.ErrorCodes;
import com.powermonitor.epitech.Utils.RequestHandler;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.json.JSONException;
import org.json.JSONObject;

/**
 *
 * @author jourda_c
 */
public class ModuleListAdapter extends ArrayAdapter<Module> {

    private int showToggle = View.INVISIBLE;

    public ModuleListAdapter(Context context, int viewResourceId, List<Module> objects) {
        super(context, viewResourceId, objects);
    }

    @Override
    public View getView(int pos, View convertView, ViewGroup parent) {
        View v = convertView;
        // Check if view had already been inflated
        if (v == null) {
            LayoutInflater vi = LayoutInflater.from(getContext());
            v = vi.inflate(R.layout.modulerow, null);
            ViewHolder vh = new ViewHolder();
            vh.name = (TextView) v.findViewById(R.id.name);
            vh.toggle = (ToggleButton) v.findViewById(R.ModuleRow.onOffButton);
            vh.profile = (TextView) v.findViewById(R.id.profil);
            vh.toggle.setVisibility(showToggle);
            v.setTag(vh);
        }
        // Set view data
        Module item = getItem(pos);
        if (item != null) {
            ViewHolder vh = (ViewHolder) v.getTag();
            vh.name.setText(item.getName());
            vh.toggle.setChecked(item.getStatus());
            vh.toggle.setTag(pos);
            vh.toggle.setOnClickListener(new View.OnClickListener() {

                public void onClick(View v) {
                    final Module item2 = getItem((Integer) v.getTag());
                    final ToggleButton b = ((ToggleButton) v);
                    Communication.INSTANCE.toggleModuleState(item2.id, b.isChecked(), new RequestHandler(getContext()) {

                        @Override
                        public void onResult(JSONObject result, JSONObject params) {
                            try {
                                int returnCode = result.getInt("returnCode");
                                if (returnCode != 0) {
                                    ErrorDialog e = new ErrorDialog(getContext(), ErrorCodes.getMsg(returnCode), null);
                                    e.show();
                                } else {
                                    item2.setStatus(b.isChecked());
                                    notifyDataSetChanged();
                                }
                            } catch (JSONException ex) {
                                Logger.getLogger(ConfigModules.class.getName()).log(Level.SEVERE, null, ex);
                            }

                        }
                    });

                }
            });
            vh.profile.setText(item.getProfil().getName());
        }
        return v;
    }

    public void setToggleVisibility(boolean v) {
        showToggle = v ? View.VISIBLE : View.INVISIBLE;
    }

    private class ViewHolder {

        public TextView name;
        public ToggleButton toggle;
        public TextView profile;
    }

}
