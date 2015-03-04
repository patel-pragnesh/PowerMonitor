using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Common
{
    public static class Errors
    {
        private static readonly Dictionary<UInt64, string> _errors = new Dictionary<UInt64, string>()
        {
            { 404, "Id incorrect" },
            { 1, "Ce profil est associé à un module esclave"}
        };

        public static string GetErrorMessage(UInt64 code)
        {
            if (_errors.ContainsKey(code))
                return _errors[code];
            return "";
        }
    }
}
