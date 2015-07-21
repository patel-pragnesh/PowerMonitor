using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Model
{
    public class Time
    {
        [JsonProperty("day")]
        public DayOfWeek Day { get; private set; }
        [JsonProperty("minute")]
        public int Minute { get; private set; }

        public Time(DayOfWeek day = 0, int minutes = 0)
        {
            Day = day;
            Minute = minutes;
        }

        public int AsHours()
        {
            return Minute / 60;
        }

        // Returns the rest of minutes in the hour. e.g returns 15 of 14h15
        public int MinutesInHour()
        {
            return Minute % 60;
        }
    }
}
