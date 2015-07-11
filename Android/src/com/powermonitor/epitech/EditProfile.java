package com.powermonitor.epitech;

import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Spinner;
import android.widget.TextView;
import com.powermonitor.epitech.Dialogs.StringListViewDialog;
import com.powermonitor.epitech.Utils.Communication;
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
public class EditProfile extends Activity {

    private EditText name;
    private EditText polling;
    private Button editSlotsButton;
    private int id;
    private ProfileInfo profileInfo;
    private AlertListAdapter alertListAdapter;
    private ListView alertList;

    @Override
    public void onCreate(Bundle savedInstance) {
        super.onCreate(savedInstance);
        setContentView(R.layout.editprofile);
        setTitle("Profil");
        alertListAdapter = new AlertListAdapter(this);
        alertList = (ListView) findViewById(R.EditProfile.alertList);
        alertList.setAdapter(alertListAdapter);
        id = getIntent().getIntExtra(ConfigProfiles.EXTRA_PROFILE_ID, -1);
        name = (EditText) findViewById(R.EditProfile.name);
        polling = (EditText) findViewById(R.EditProfile.polling);
        editSlotsButton = (Button) findViewById(R.EditProfile.slotsButton);
        editSlotsButton.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v) {
                Intent i = new Intent(EditProfile.this, EditProfileSlots.class);
                i.putExtra(ConfigProfiles.EXTRA_PROFILE_ID, id);
                startActivity(i);
            }
        });
        Communication.INSTANCE.getProfile(id, onGetProfile);
    }

    private void initDataLoaded() {
        name.setText(profileInfo.name);
        for (ProfileAlert alert : profileInfo.alertList) {
            alertListAdapter.add(alert);
        }
        polling.setText(profileInfo.polling + "");
    }

    public void onAddAlertClick(View v) {
        AlertCreateDialog ac = new AlertCreateDialog(this) {

            @Override
            public void onValidate(int uid, double value) {
                Communication.INSTANCE.addAlert(id, uid, value, onAddAlert);
            }
        };
        ac.show();
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
    private final RequestHandler onAddAlert = new RequestHandler(this) {
        @Override
        public void onResult(JSONObject result, JSONObject params) {
            try {
                ProfileAlert alert = new ProfileAlert(result.getInt("id"), params.getInt("unitId"), params.getDouble("value"));
                alertListAdapter.add(alert);
            } catch (JSONException ex) {
                Logger.getLogger(EditProfile.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    };

    private final RequestHandler onUpdateAlert = new RequestHandler(this) {

        @Override
        public void onResult(JSONObject result, JSONObject params) {
            try {
                int res = result.getInt("returnCode");
                if (res == 0) {
                    alertListAdapter.selectedItem.unitId = params.getInt("unitId");
                    alertListAdapter.selectedItem.value = params.getDouble("value");
                    alertListAdapter.selectedItem = null;
                    alertListAdapter.notifyDataSetChanged();
                }
            } catch (JSONException ex) {
                Logger.getLogger(EditProfile.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    };

    private final RequestHandler onDeleteAlert = new RequestHandler(this) {

        @Override
        public void onResult(JSONObject result, JSONObject params) {
            try {
                int res = result.getInt("returnCode");
                if (res == 0) {
                    alertListAdapter.remove(alertListAdapter.selectedItem);
                    alertListAdapter.selectedItem = null;
                    alertListAdapter.notifyDataSetChanged();
                }
            } catch (JSONException ex) {
                Logger.getLogger(EditProfile.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    };
    
    public void onSaveClick(View v){
        
    }

    public static class ProfileInfo {

        public final int id, polling;
        public final String name;
        public final ArrayList<ProfileAlert> alertList;
        public final ArrayList<ProfileTimeSlot> timeslotList;

        public ProfileInfo(JSONObject o) throws JSONException {
            this.id = o.getInt("id");
            this.name = o.getString("name");
            this.polling = o.getInt("polling");
            JSONArray alerts = o.getJSONArray("alerts");
            alertList = new ArrayList<ProfileAlert>();
            if (alerts.length() > 0) {
                for (int i = 0; i < alerts.length(); i++) {
                    alertList.add(new ProfileAlert(alerts.getJSONObject(i)));
                }
            }
            JSONArray timeSlots = o.getJSONArray("timeSlots");
            timeslotList = new ArrayList<ProfileTimeSlot>();
            if (timeSlots.length() > 0) {
                for (int i = 0; i < timeSlots.length(); i++) {
                    timeslotList.add(new ProfileTimeSlot(timeSlots.getJSONObject(i)));
                }
            }
        }
    }

    public static class ProfileAlert {

        public int id, unitId;
        public double value;

        ProfileAlert(int id, int uid, double v) {
            this.id = id;
            this.unitId = uid;
            this.value = v;
        }

        ProfileAlert(JSONObject o) throws JSONException {
            this.id = o.getInt("id");
            this.unitId = o.getInt("unitId");
            this.value = o.getDouble("value");
        }
    }

    public class AlertListAdapter extends ArrayAdapter<ProfileAlert> {

        private int resId;
        private ArrayList<String> units;
        public ProfileAlert selectedItem;

        public AlertListAdapter(Context context) {
            super(context, R.layout.alert_list_row, new ArrayList<ProfileAlert>());
            resId = R.layout.alert_list_row;
            units = new ArrayList<String>();
            units.add("Puissance");
            units.add("Intensité");
            units.add("Voltage");
        }

        @Override
        public View getView(final int position, View old, ViewGroup parent) {
            View v = old;
            ViewHolder vh;
            if (v == null) {
                v = getLayoutInflater().inflate(resId, parent, false);
                vh = new ViewHolder();
                vh.type = (TextView) v.findViewById(R.AlertListRow.type);
                vh.value = (TextView) v.findViewById(R.AlertListRow.value);
                v.setTag(vh);
            } else {
                vh = (ViewHolder) v.getTag();
            }
            final ProfileAlert item = getItem(position);
            if (item != null) {
                vh.type.setText("type: " + units.get(item.unitId - 1));
                vh.value.setText("value: " + item.value);
                v.setOnClickListener(new View.OnClickListener() {

                    public void onClick(View v) {
                        selectedItem = getItem(position);
                        StringListViewDialog dg = new StringListViewDialog(EditProfile.this, false) {
                            @Override
                            public void onItemClick(Object data) {
                                int row = (Integer) data;
                                if (row == 0) {
                                    AlertCreateDialog ac = new AlertCreateDialog(getContext(), item.unitId, item.value) {
                                        @Override
                                        public void onValidate(int uid, double value) {
                                            Communication.INSTANCE.updateAlert(item.id, uid, value, onUpdateAlert);
                                        }
                                    };
                                    ac.setTitle("Modifier l'alerte");
                                    ac.show();
                                }
                                else if (row == 1) {
                                    Communication.INSTANCE.deleteAlert(item.id, onDeleteAlert);
                                }
                                this.dismiss();
                            }
                        };
                        dg.addRow("Modifier", 0);
                        dg.addRow("Supprimer", 1);
                        dg.show();
                    }
                });
            }
            return v;
        }

        private class ViewHolder {

            public TextView type;
            public TextView value;
        }

    }

    public static class ProfileTimeSlot {

        public final int id, begDay, begMin, endDay, endMin;

        public ProfileTimeSlot(JSONObject o) throws JSONException {
            this.id = o.getInt("id");
            JSONObject beg = o.getJSONObject("beg");
            JSONObject end = o.getJSONObject("end");
            this.begDay = beg.getInt("day");
            this.begMin = beg.getInt("minute");
            this.endDay = end.getInt("day");
            this.endMin = end.getInt("minute");
        }
    }

    public static abstract class AlertCreateDialog extends Dialog {

        private Button bOk;
        private EditText value;
        private Spinner unit;

        public AlertCreateDialog(Context context) {
            super(context);
            init();
        }

        public AlertCreateDialog(Context context, int uid, double val) {
            super(context);
            init();
            unit.setSelection(uid - 1);
            value.setText(String.valueOf(val));
        }

        private void init() {
            setContentView(R.layout.alert_create_dialog);
            setTitle("Ajouter une alerte");
            unit = (Spinner) findViewById(R.AlertCreateDialog.sType);
            bOk = (Button) findViewById(R.AlertCreateDialog.bOk);
            value = (EditText) findViewById(R.AlertCreateDialog.etValue);
            ArrayAdapter<CharSequence> adapter = new ArrayAdapter<CharSequence>(getContext(), android.R.layout.simple_spinner_item);
            adapter.add("Puissance");
            adapter.add("Intensité");
            adapter.add("Voltage");
            unit.setAdapter(adapter);
            bOk.setOnClickListener(new View.OnClickListener() {

                public void onClick(View v) {
                    onValidate(unit.getSelectedItemPosition() + 1, Double.parseDouble(value.getText().toString()));
                    dismiss();
                }
            });
        }

        public abstract void onValidate(int uid, double value);
    }

}
