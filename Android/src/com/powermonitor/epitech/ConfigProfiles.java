/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.ContextMenu;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import com.powermonitor.epitech.Dialogs.ErrorDialog;
import com.powermonitor.epitech.Models.Profile;
import com.powermonitor.epitech.ListRows.ProfileListAdapter;
import com.powermonitor.epitech.Utils.Communication;
import com.powermonitor.epitech.Utils.ErrorCodes;
import com.powermonitor.epitech.Utils.RequestHandler;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 *
 * @author jourda_c
 */
public class ConfigProfiles extends Fragment {

    public static final String EXTRA_PROFILE_ID = "extraProfileId";

    private ListView list;
    private ProfileListAdapter adapter;
    private List<Profile> dataList = new ArrayList<Profile>();
    private Profile selectedItem = null;
    private JSONObject profilesList;

    public ConfigProfiles(JSONObject list) {
        super();
        this.profilesList = list;
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        inflater.inflate(R.menu.profile_list_menu, menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_add_profile:
                AddProfileDialog dg = new AddProfileDialog(getActivity()) {
                    @Override
                    public void onValidate(String name, String polling) {
                        Communication.INSTANCE.addProfile(name, Integer.parseInt(polling), addRequestHandler);
                    }
                };
                dg.show();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    @Override
    public void onCreate(Bundle saveInstanceBundle) {
        super.onCreate(saveInstanceBundle);
        setHasOptionsMenu(true);
    }

    @Override
    public void setUserVisibleHint(boolean isVisible) {
        if (isVisible && getActivity() != null)
            getActivity().setTitle("Profils");
        super.setUserVisibleHint(isVisible);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstance) {

        View v = inflater.inflate(R.layout.configprofiles, container, false);

        // List view
        this.list = (ListView) v.findViewById(R.ConfigProfiles.profileListView);
        this.adapter = new ProfileListAdapter(v.getContext(), R.layout.profilerow, this.dataList);
        this.list.setAdapter(this.adapter);

        // ContextMenu
        registerForContextMenu(this.list);

        try {
            JSONArray profiles = this.profilesList.getJSONArray("profiles");
            for (int i = 0; i < profiles.length(); i++) {
                JSONObject o = profiles.getJSONObject(i);
                dataList.add(new Profile(o.getInt("id"), o.getString("name"), o.getInt("polling")));
            }
        } catch (JSONException ex) {
            Logger.getLogger(ConfigProfiles.class.getName()).log(Level.SEVERE, null, ex);
        }

        return v;
    }

    @Override
    public void onCreateContextMenu(ContextMenu menu, View v, ContextMenu.ContextMenuInfo info) {
        super.onCreateContextMenu(menu, v, info);
        AdapterView.AdapterContextMenuInfo minfo = (AdapterView.AdapterContextMenuInfo) info;
        Profile p = this.adapter.getItem(minfo.position);
        selectedItem = p;
        menu.setHeaderTitle(p.getName());
        menu.add(1, 0, 0, "Editer");
        menu.add(1, 1, 0, "Supprimer");
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {
        if (item.getGroupId() != 1) {
            return false;
        }
        if (item.getItemId() == 0) {
            Intent i = new Intent(this.getActivity(), EditProfile.class);
            i.putExtra(EXTRA_PROFILE_ID, selectedItem.getId());
            startActivity(i);
        } else if (item.getItemId() == 1) {
            Communication.INSTANCE.deleteProfile(selectedItem.getId(), this.deleteRequestHandler);
        }
        return true;
    }

    private final RequestHandler deleteRequestHandler = new RequestHandler(getActivity()) {

        @Override
        public void onResult(JSONObject result, JSONObject params) {
            try {
                int returnCode = result.getInt("returnCode");
                if (returnCode == 0) {
                    dataList.remove(selectedItem);
                    adapter.notifyDataSetChanged();
                } else {
                    ErrorDialog e = new ErrorDialog(ConfigProfiles.this.getActivity(), ErrorCodes.getMsg(returnCode).text, null);
                    e.show();
                }
            } catch (JSONException ex) {
                Logger.getLogger(ConfigProfiles.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    };

    private final RequestHandler addRequestHandler = new RequestHandler(getActivity()) {

        @Override
        public void onResult(JSONObject result, JSONObject params) {
            try {
                int returnCode = result.getInt("returnCode");
                if (returnCode == 0) {
                    Profile p = new Profile(result.getInt("profileId"), params.getString("name"), params.getInt("polling"));
                    dataList.add(p);
                    adapter.notifyDataSetChanged();
                } else {
                    ErrorDialog e = new ErrorDialog(ConfigProfiles.this.getActivity(), ErrorCodes.getMsg(returnCode).text, null);
                    e.show();
                }
            } catch (JSONException ex) {
                Logger.getLogger(ConfigProfiles.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    };
    public static abstract class AddProfileDialog extends Dialog {

        private Button bOk;
        private EditText name;
        private EditText polling;

        public AddProfileDialog(Context context) {
            super(context);
            setContentView(R.layout.add_profile_dialog);
            setTitle("Ajouter un profil");
            bOk = (Button) findViewById(R.AddProfileDialog.bOk);
            name = (EditText) findViewById(R.AddProfileDialog.etName);
            polling = (EditText) findViewById(R.AddProfileDialog.etPolling);
            bOk.setOnClickListener(new View.OnClickListener() {

                public void onClick(View v) {
                    onValidate(name.getText().toString(), polling.getText().toString());
                    dismiss();
                }
            });
        }
        
        public abstract void onValidate(String name, String polling);

    }
}
