/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.ContextMenu;
import android.view.ContextMenu.ContextMenuInfo;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;
import com.powermonitor.epitech.Dialogs.ErrorDialog;
import com.powermonitor.epitech.Dialogs.StringListViewDialog;
import com.powermonitor.epitech.ListRows.ModuleListAdapter;
import com.powermonitor.epitech.Models.Module;
import com.powermonitor.epitech.Models.Profile;
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
public class ConfigModules extends Fragment {

    private ListView listView;
    private List<Module> dataList = new ArrayList<Module>();
    private ModuleListAdapter adapter;
    private int _selectionPos;
    private JSONObject modulesList;

    public ConfigModules(JSONObject list) {
        super();
        this.modulesList = list;
    }

    @Override
    public void onCreate(Bundle saveInstance) {
        super.onCreate(saveInstance);
    }

    @Override
    public void setUserVisibleHint(boolean isVisible) {
        if (isVisible && getActivity() != null) {
            getActivity().setTitle("Modules");
        }
        super.setUserVisibleHint(isVisible);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstance) {

        View v = inflater.inflate(R.layout.configmodules, container, false);
        getActivity().setTitle("Modules");
        // Create list view
        this.listView = (ListView) v.findViewById(R.ConfigModules.modulesListView);
        this.adapter = new ModuleListAdapter(v.getContext(), R.layout.modulerow, dataList);
        this.adapter.setToggleVisibility(true);
        this.listView.setAdapter(adapter);
        registerForContextMenu(this.listView);

        try {
            JSONArray list = modulesList.getJSONArray("modules");
            for (int i = 0; i < list.length(); i++) {
                JSONObject o = list.getJSONObject(i);
                JSONObject defaultProfile = o.optJSONObject("defaultProfile");
                Profile.Small defProfile;
                if (defaultProfile == null) {
                    defProfile = new Profile.Small(0, "");
                } else {
                    defProfile = new Profile.Small(defaultProfile.getInt("id"), defaultProfile.getString("name"));
                }
                dataList.add(new Module(o.getInt("id"), o.getString("name"), defProfile, o.getBoolean("status")));
            }
        } catch (JSONException ex) {
            Logger.getLogger(Communication.class.getName()).log(Level.SEVERE, null, ex);
        }

        return v;
    }

    @Override
    public void onCreateContextMenu(ContextMenu menu, View v, ContextMenuInfo info) {
        super.onCreateContextMenu(menu, v, info);
        AdapterView.AdapterContextMenuInfo minfo = (AdapterView.AdapterContextMenuInfo) info;
        Module r = adapter.getItem(minfo.position);
        _selectionPos = minfo.position;
        menu.setHeaderTitle(r.getName());
        menu.add(0, 0, 0, "Renommer");
        menu.add(0, 1, 0, "Changer le profil");
        menu.add(0, 2, 0, "Changer le profil interne");
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {
        if (item.getGroupId() != 0) {
            return false;
        }
        if (item.getItemId() == 0) {
            onbRenameClicked();
        }
        if (item.getItemId() == 1) {
            onChangeProfileClicked();
        }
        return true;
    }

    private void onChangeProfileClicked() {

        Communication.INSTANCE.getProfilesList(new RequestHandler(ConfigModules.this.getActivity()) {
            @Override
            public void onResult(JSONObject result, JSONObject params) {
                final JSONObject profilesList = result;
                try {
                    StringListViewDialog dialog = new StringListViewDialog(ConfigModules.this.getActivity()) {
                        @Override
                        public void onItemClick(Object data) {
                            changeProfile((JSONObject) data);
                            super.onItemClick(data);
                        }
                    };
                    dialog.setTitle("Profils");
                    dialog.addRow("<Aucun>", null);
                    JSONArray list = profilesList.getJSONArray("profiles");
                    for (int i = 0; i < list.length(); i++) {
                        JSONObject item = list.getJSONObject(i);
                        dialog.addRow(item.getString("name"), item);
                    }
                    dialog.show();
                } catch (JSONException ex) {
                    Logger.getLogger(ConfigModules.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        });
    }

    private void changeProfile(JSONObject profileData) {
        if (_selectionPos >= 0 && this.listView.getItemAtPosition(_selectionPos) != null) {
            try {
                final String name = profileData != null ? profileData.getString("name") : "";
                final int newId = profileData != null ? profileData.getInt("id") : 0;
                final Module module = ((Module) this.listView.getItemAtPosition(_selectionPos));
                Communication.INSTANCE.updateModuleDefaultProfile(module.id, newId, new RequestHandler(ConfigModules.this.getActivity()) {

                    @Override
                    public void onResult(JSONObject result, JSONObject params) {
                        if (super.hasError(result)) {
                            return;
                        }
                        module.getProfil().setId(newId);
                        module.getProfil().setName(name);
                        adapter.notifyDataSetChanged();
                    }
                });
            } catch (JSONException ex) {
                Logger.getLogger(ConfigModules.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    public void onbRenameClicked() {
        final EditText input = new EditText(getActivity());
        new AlertDialog.Builder(getActivity())
                .setTitle("Nouveau nom")
                .setMessage("Entrez le nouveau nom")
                .setView(input)
                .setPositiveButton("Ok", new DialogInterface.OnClickListener() {

                    public void onClick(DialogInterface dialog, int which) {
                        doRename(input.getText().toString());
                    }
                })
                .setNegativeButton("Anuler", new DialogInterface.OnClickListener() {

                    public void onClick(DialogInterface dialog, int which) {
                    }
                }).show();
    }

    public void doRename(final String name) {
        if (_selectionPos >= 0 && this.listView.getItemAtPosition(_selectionPos) != null) {
            final Module module = ((Module) this.listView.getItemAtPosition(_selectionPos));

            Communication.INSTANCE.renameModule(module.id, name, new RequestHandler(ConfigModules.this.getActivity()) {

                @Override
                public void onResult(JSONObject result, JSONObject params) {
                    try {
                        int resultCode = result.getInt("returnCode");
                        if (resultCode != 0) {
                            ErrorDialog e = new ErrorDialog(ConfigModules.this.getActivity(), ErrorCodes.getMsg(resultCode), null);
                            e.show();
                        } else {
                            module.setName(name);
                            adapter.notifyDataSetChanged();
                        }
                    } catch (JSONException ex) {
                        Logger.getLogger(ConfigModules.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            });
        }
    }
}
