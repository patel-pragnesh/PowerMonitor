using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Model
{
    public class Alert
    {
        [JsonProperty("id")]
        public UInt64 Id { get; private set; }
        [JsonProperty("unitId")]
        public UInt64 UnitId { get; private set; }
        [JsonProperty("value")]
        public int Value { get; private set; }

        public Alert(UInt64 id = 0, UInt64 unitId = 0, int value = 0)
        {
            Id = id;
            UnitId = unitId;
            Value = value;
        }
    }
}
