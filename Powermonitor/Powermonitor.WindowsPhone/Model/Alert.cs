using Newtonsoft.Json;
using Powermonitor.Common;
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
        public double Value { get; private set; }
        [JsonIgnore]
        public string UnitName
        {
            get
            {
                return Units.units.ElementAt((int)this.UnitId - 1);
            }
        }

        public Alert(UInt64 id = 0, UInt64 unitId = 0, double value = 0)
        {
            Id = id;
            UnitId = unitId;
            Value = value;
        }
    }
}
