using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Model
{
    public class TimeSlot
    {
        public UInt64 Id { get; private set; }
        public Time Beg { get; private set; }
        public Time End { get; private set; }

        public TimeSlot(UInt64 id = 0, Time beg = null, Time end = null)
        {
            Id = id;
            Beg = beg;
            End = end;
        }
    }
}
