/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.powermonitor.epitech;

import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.ContextMenu;
import android.view.MotionEvent;
import android.view.View;
import com.powermonitor.epitech.Dialogs.DoubleTimePicker;
import com.powermonitor.epitech.Dialogs.DoubleTimePicker.Time;
import com.powermonitor.epitech.Dialogs.ErrorDialog;
import java.util.ArrayList;

/**
 *
 * @author jourda_c
 */
public class CustomCalendar extends View {

    private final static int CELL_HEIGHT = 80;
    public final static int CONTEXT_MENU_GROUP = 0x145754f;
    public final static int CONTEXT_MENU_ITEM_MODIFY = 0;
    public final static int CONTEXT_MENU_ITEM_DELETE = 1;
    private Paint gray, white;
    private int width;
    private ArrayList<Slot> slots;
    private boolean ignoreEvent = false;
    private OnSlotEventListener onSlotAdded;
    private Slot selected;

    public CustomCalendar(Context context) {
        super(context);
        init();
    }

    public CustomCalendar(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public CustomCalendar(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        init();
    }

    public final void init() {
        setVerticalScrollBarEnabled(true);
        setOnCreateContextMenuListener(onContextMenu);
        gray = new Paint();
        white = new Paint();
        gray.setColor(Color.GRAY);
        white.setColor(Color.WHITE);
        gray.setTextSize(13);
        slots = new ArrayList<Slot>();
    }

    public void setOnSlotAddedListener(OnSlotEventListener listener) {
        this.onSlotAdded = listener;
    }

    public void addSlot(int id, int minutesBeg, int minutesEnd) {
        int mmb = minutesBeg % 60;
        int hhb = minutesBeg / 60;
        int mme = minutesEnd % 60;
        int hhe = minutesEnd / 60;
        slots.add(new Slot(id, new Time(hhb, mmb), new Time(hhe, mme)));
        this.invalidate();
    }

    public void addSlot(Slot s) {
        slots.add(s);
    }

    public void removeSlot(Slot s){
        slots.remove(s);
        this.invalidate();
    }
    
    @Override
    public void onDraw(Canvas c) {
        float sepPos = (float) (width * 0.2);
        for (int i = 0; i < 24; i++) {
            c.drawRect(0, i * CELL_HEIGHT, width, (i + 1) * CELL_HEIGHT, gray);
            c.drawRect(2, i == 0 ? i * CELL_HEIGHT + 2 : i * CELL_HEIGHT, width - 2, (i + 1) * CELL_HEIGHT - 2, white);
            c.drawText(i + ":00", sepPos * 0.3f, i * CELL_HEIGHT - 2 + CELL_HEIGHT * 0.6f, gray);
        }
        c.drawLine(width * 0.2f, 0, width * 0.2f, 24 * CELL_HEIGHT, gray);
        drawSlots(c, sepPos);
    }

    public void drawSlots(Canvas c, float sepPos) {
        for (Slot slot : slots) {
            c.drawRect(sepPos, (slot.beg.hours + slot.beg.minutes / 60.0f) * CELL_HEIGHT, width - 2, (slot.end.hours + slot.end.minutes / 60.0f) * CELL_HEIGHT - 2, gray);
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (event.getActionMasked() == MotionEvent.ACTION_DOWN) {
            ignoreEvent = false;
            return true;
        }
        if (event.getActionMasked() == MotionEvent.ACTION_MOVE) {
            ignoreEvent = true;
            return super.onTouchEvent(event);
        }
        if (event.getActionMasked() == MotionEvent.ACTION_UP && !ignoreEvent) {
            final boolean change;
            float x, y;
            x = event.getX();
            y = event.getY() / CELL_HEIGHT;
            Slot s = getExistingSlot(y);
            selected = s;
            if (s == null) {
                s = new Slot(0, new Time((int) y, 0), new Time((int) y + 1, 0));
                change = false;
                updateSlot(s, false);
            } else {
                change = true;
                showContextMenu();
            }
            return true;
        }
        return super.onTouchEvent(event);
    }

    public void updateSlot(final Slot s, final boolean change) {
        DoubleTimePicker picker = new DoubleTimePicker(this.getContext()) {
            @Override
            public void onTimesSet(Time beg, Time end) {
                if (isValid(s, beg, end)) {
                    if (!change) {
                        onSlotAdded.onSlotAdded(beg, end);
                    }
                    if (change) {
                        onSlotAdded.onSlotChanged(s, beg, end);
                    }
                } else {
                    ErrorDialog err = new ErrorDialog(getContext(), "Ce slot est invalide. Veuillez corriger", null);
                    err.show();
                }
            }
        };
        picker.setDefaultTime(s.beg, s.end);
        picker.show();
    }

    private boolean isValid(Slot current, Time beg, Time end) {
        if (end.cmp(beg) <= 0) {
            return false;
        }
        Slot n = new Slot(0, beg, end);
        for (Slot slot : slots) {
            if (current != slot && (slot.contains(beg) || slot.contains(end))) {
                return false;
            }
            if (current != slot && (n.contains(slot.beg) || n.contains(slot.end))) {
                return false;
            }
        }
        return true;
    }

    private Slot getExistingSlot(float y) {
        for (Slot slot : slots) {
            if (slot.beg.hours <= y && y <= slot.end.hours) {
                return slot;
            }
        }
        return null;
    }

    @Override
    public void onMeasure(int wspec, int hspec) {
        super.onMeasure(wspec, hspec);
        width = MeasureSpec.getSize(wspec);
        setMeasuredDimension(width, 24 * CELL_HEIGHT);
    }

    public static class Slot {

        public Time beg;
        public Time end;
        public int id;

        public Slot(int id, Time beg, Time end) {
            this.beg = beg;
            this.end = end;
            this.id = id;
        }

        public boolean contains(Time t) {
            return this.beg.cmp(t) <= 0 && this.end.cmp(t) >= 0;
        }
        
        @Override
        public int hashCode() {
            int hash = 7;
            hash = 83 * hash + this.id;
            return hash;
        }

        @Override
        public boolean equals(Object obj) {
            if (obj == null) {
                return false;
            }
            if (getClass() != obj.getClass()) {
                return false;
            }
            final Slot other = (Slot) obj;
            return this.id == other.id;
        }
    }

    public static abstract class OnSlotEventListener {

        public abstract void onSlotAdded(Time beg, Time end);

        public abstract void onSlotChanged(Slot s, Time beg, Time end);
        //public abstract void onEvent(Time beg, Time end);
    }

    private OnCreateContextMenuListener onContextMenu = new OnCreateContextMenuListener() {

        public void onCreateContextMenu(ContextMenu menu, View v, ContextMenu.ContextMenuInfo menuInfo) {
            menu.add(CONTEXT_MENU_GROUP, CONTEXT_MENU_ITEM_MODIFY, 0, "Modifier");
            menu.add(CONTEXT_MENU_GROUP, CONTEXT_MENU_ITEM_DELETE, 1, "Supprimer");
        }
    };

    @Override
    protected ContextMenu.ContextMenuInfo getContextMenuInfo() {
        SlotContextMenuInfo info = new SlotContextMenuInfo();
        info.slot = selected;
        return info;
    }

    public class SlotContextMenuInfo implements ContextMenu.ContextMenuInfo {

        public Slot slot;
    }
}
