using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Model
{
    public class TimeSlotsContainer
    {
        public List<TimeSlot> TimeSlots { get; private set; }
        public UInt64 ProfileId { get; private set; }
        public DayOfWeek DayOfWeek { get; private set; }

        public TimeSlotsContainer(UInt64 id, DayOfWeek day)
        {
            TimeSlots = new List<TimeSlot>();
            ProfileId = id;
            DayOfWeek = day;
        }
    }
}
