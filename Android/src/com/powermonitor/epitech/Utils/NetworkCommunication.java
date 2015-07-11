/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech.Utils;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Handler;
import android.os.Message;
import android.os.SystemClock;
import com.powermonitor.epitech.Login;
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.json.JSONException;
import org.json.JSONObject;

public class NetworkCommunication {

    private Socket socket;
    private DataInputStream diStream;
    private DataOutputStream doStream;
    private BufferedOutputStream boStream;
    private int currentStructSize = -1;
    private boolean cmdEnded = true;
    private boolean connected = false;
    private final Queue<Command> queue;
    private final Session session;

    public final static int SOCKET_TIMEOUT = 10000; // Socket read timeout : 10sec

    public final static String SERVER_IP = "62.4.24.188";

    public final static String CMD_GetModules = "getModules";
    public final static String CMD_GetProfiles = "getProfiles";
    public final static String CMD_GetInternalProfile = "getInternalProfile";
    public final static String CMD_DeleteProfile = "deleteProfile";
    public final static String CMD_Login = "login";
    public final static String CMD_TurnOnOff = "turnOnOff";
    public final static String CMD_RenameModule = "renameModule";
    public final static String CMD_UpdateModuleDefaultProfile = "updateModuleDefaultProfile";
    public final static String CMD_GetProfile = "getProfile";
    public final static String CMD_AddTimeSlot = "addTimeSlot";
    public final static String CMD_UpdateTimeSlot = "updateTimeSlot";
    public final static String CMD_DeleteTimeSlot = "deleteTimeSlot";
    public final static String CMD_AddAlert = "addAlert";
    public final static String CMD_UpdateAlert = "updateAlert";
    public final static String CMD_DeleteAlert = "deleteAlert";
    public final static String CMD_AddProfile = "addProfile";
    
    public NetworkCommunication() {
        queue = new LinkedList<Command>();
        session = new Session();
        Storage.INSTANCE.prefs.getSession(session);
    }

    public boolean isSessionValid() {
        return this.session.isValid();
    }

    public void connect(RequestHandler h) {

        System.out.println("Trying to connect ...");
        this.cmdEnded = true;
        Command c = new ConnectCmd();
        c.setRequestHandler(h);
        new Thread(c).start();
    }

    public void startCommand(String cmd, RequestHandler r) {
        this.startCommand(cmd, r, null);
    }

    /**
     * startCommand gets the command from the cmdMap and execute it. The command
     * is run in a new thread Returned data are passed to the main thread using
     * ReturnHandler class (extends Handler)
     *
     * @param cmd
     * @param r
     * @param params
     */
    public void startCommand(String cmd, RequestHandler r, JSONObject params) {
        while (!connected) {
            SystemClock.sleep(10); // Avoid a heavy loop
        }        //TODO: Check if internet in login page
        final Command c = new Command(cmd);
        c.setRequestHandler(r);
        c.setParams(params);
        this.queue.add(c);
        if (cmdEnded) {
            nextCommand();
        }
    }

    private void nextCommand() {
        cmdEnded = false;
        if (this.queue.size() > 0) {
            final Command c = queue.remove();
            c.setSession(this.session);
            new Thread(c).start();
        } else {
            cmdEnded = true;
        }
    }

    private class Command implements Runnable {

        private RequestHandler handler;
        private JSONObject params;
        protected ReturnHandler retHandler = new ReturnHandler();

        public Command(String cmd) {
            this.params = new JSONObject();
            try {
                this.params.put("cmd", cmd);
            } catch (JSONException ex) {
                Logger.getLogger(NetworkCommunication.class.getName()).log(Level.SEVERE, null, ex);
            }
        }

        public void setRequestHandler(RequestHandler r) {
            this.handler = r;
        }

        public void setParams(JSONObject p) {
            if (p == null) {
                return;
            }
            Iterator it = p.keys();
            while (it.hasNext()) {
                String key = (String) it.next();
                try {
                    this.params.put(key, p.get(key));
                } catch (JSONException ex) {
                    Logger.getLogger(NetworkCommunication.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }

        public void setSession(Session session_) {
            if (!session_.isValid()) {
                return;
            }
            try {
                this.params.put("session", session_.getSession());
            } catch (JSONException ex) {
                Logger.getLogger(NetworkCommunication.class.getName()).log(Level.SEVERE, null, ex);
            }
        }

        @Override
        public void run() {
            try {
                System.out.println("SOCKET?:" + socket.isConnected());
                System.out.println("Input?" + socket.isInputShutdown());
                System.out.println("Ouput?" + socket.isOutputShutdown());
                // JSON string to send. Created by param (cmd attribute is in ctor)
                String str = this.params.toString();
                int cRead = 0;

                // Send cmd lenght and send cmd data
                ByteBuffer b = ByteBuffer.allocate(4);
                b.putInt(str.length());
                //boStream.write(b.array(), 0, 4);
                //doStream.writeInt(str.length());
                //doStream.write(str.getBytes());
                socket.getOutputStream().write(b.array());
                socket.getOutputStream().write(str.getBytes());
                //boStream.flush();
                System.out.println("Wrote: " + str);

                // get header value
                diStream = new DataInputStream(socket.getInputStream());
                currentStructSize = diStream.readInt();

                System.out.println("Will read: " + currentStructSize);

                // read of header size max
                byte[] buffer = new byte[currentStructSize];
                do {
                    cRead += diStream.read(buffer, cRead, currentStructSize - cRead);
                } while (cRead < currentStructSize);

                System.out.println("Read: " + new String(buffer, "UTF-8"));
                // Transform raw bytes to raw string and transfrom raw json string to JSONObject
                JSONObject jObj = new JSONObject(new String(buffer, "UTF-8"));

                // Call result handler back into main thread
                // Use retHandler to pass data to mainThread, else callback is still in this thread
                Message m = new Message();
                m.obj = jObj;
                m.what = ReturnHandler.MSG_CMDEND;
                retHandler.sendMessage(m);

            } catch (SocketTimeoutException ex) {
                // TODO: handle timeout here
                // Maybe pass a generic timeout handler, that will popup a messagebox
            } catch (IOException ex) {
                Logger.getLogger(NetworkCommunication.class.getName()).log(Level.SEVERE, null, ex);
            } catch (JSONException ex) {
                Logger.getLogger(NetworkCommunication.class.getName()).log(Level.SEVERE, null, ex);
            }
        }

        public class ReturnHandler extends Handler {

            public static final int MSG_CONNECTED = 0;
            public static final int MSG_CMDEND = 1;

            @Override
            public void handleMessage(Message msg) {
                if (msg.what == MSG_CMDEND) {
                    JSONObject ret;
                    JSONObject sess;
                    try {
                        ret = (JSONObject) msg.obj;
                        if (ret.getInt("returnCode") == ErrorCodes.GEN_INVALID_SESSION) {
                            handler.onInvalidToken();
                            return;
                        }
                        sess = ret.getJSONObject("session");
                        session.setSessionToken(sess.getString("token"));
                        session.setUserId(sess.getInt("userId"));
                        Storage.INSTANCE.prefs.saveSession(session);
                        handler.onResult(ret, params);
                    } catch (JSONException ex) {
                        Logger.getLogger(NetworkCommunication.class.getName()).log(Level.SEVERE, null, ex);
                    } finally {
                        nextCommand();
                    }
                } else if (msg.what == MSG_CONNECTED) {
                    connected = true;
                    handler.onResult(null, null);
                }
            }
        }
    }

    public class ConnectCmd extends Command {

        public ConnectCmd() {
            super("");
        }

        @Override
        public void run() {
            try {
                InetAddress servAddr = InetAddress.getByName(SERVER_IP);
                socket = new Socket(servAddr, 4242);

                diStream = new DataInputStream(socket.getInputStream());
                doStream = new DataOutputStream(socket.getOutputStream());

                boStream = new BufferedOutputStream(socket.getOutputStream());

                socket.setSoTimeout(SOCKET_TIMEOUT);

                Message m = new Message();
                m.what = Command.ReturnHandler.MSG_CONNECTED;
                retHandler.sendMessage(m);

                System.out.println("NetworkCommunication ready");
            } catch (UnknownHostException ex) {
                Logger.getLogger(NetworkCommunication.class.getName()).log(Level.SEVERE, null, ex);
            } catch (IOException ex) {
                Logger.getLogger(NetworkCommunication.class.getName()).log(Level.SEVERE, null, ex);
            }

        }
    }

    public class Session {

        private final JSONObject jSession = new JSONObject();

        private Object _get(String s) {
            try {
                return jSession.get(s);
            } catch (JSONException ex) {
                Logger.getLogger(NetworkCommunication.class.getName()).log(Level.SEVERE, null, ex);
            }
            return null;
        }

        private void _set(String s, Object o) {
            try {
                this.jSession.put(s, o);
            } catch (JSONException ex) {
                Logger.getLogger(NetworkCommunication.class.getName()).log(Level.SEVERE, null, ex);
            }
        }

        public String getSessionToken() {
            return (String) this._get("token");
        }

        public void setSessionToken(String sessionToken) {
            this._set("token", sessionToken);
        }

        public int getUserId() {
            return (Integer) this._get("userId");
        }

        public void setUserId(int userId) {
            this._set("userId", userId);
        }

        public JSONObject getSession() {
            return this.jSession;
        }

        public boolean isValid() {
            return !this.getSessionToken().equals("") && this.getUserId() >= 0;
        }
    }
}
