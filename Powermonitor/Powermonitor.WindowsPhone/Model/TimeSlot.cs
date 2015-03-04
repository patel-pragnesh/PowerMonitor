using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Model
{
    public class TimeSlot
    {
        public enum Time
        {
            BEGINNING,
            END
        }

        public DateTime DateBeginning { get; private set; }
        public DateTime DateEnd { get; private set; }

        #region beginning
        private long _beginning;
        public long beginning
        {
            get
            {
                return _beginning;
            }
            set
            {
                if (_beginning != value)
                {
                    _beginning = value;
                    DateBeginning = new DateTime(value);
                }
            }
        }
        #endregion
        #region end
        private long _end;
        public long end
        {
            get
            {
                return _end;
            }
            set
            {
                if (_end!= value)
                {
                    _end = value;
                    DateEnd = new DateTime(value);
                }
            }
        }
        #endregion

        public TimeSlot(long b = 0, long e = 0)
        {
            beginning = b;
            end = e;
        }

        public DayOfWeek GetDayOfWeek(Time time)
        {
            if (time == Time.BEGINNING)
                return DateBeginning.DayOfWeek;
            return DateEnd.DayOfWeek;
        }

        public int GetHour(Time time)
        {
            if (time == Time.BEGINNING)
                return DateBeginning.Hour;
            return DateEnd.Hour;
        }

        public int GetMinute(Time time)
        {
            if (time == Time.BEGINNING)
                return DateBeginning.Minute;
            return DateEnd.Minute;
        }
    }
}
