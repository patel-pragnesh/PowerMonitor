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
            { 101, "La requête n'est pas bien formatée" },
            { 102, "La commande n'a pas été trouvée" },
            { 201, "Accès refusé" },
            { 202, "L'utilisateur n'a pas été trouvé" },
            { 203, "Le mot de passe est incorrect" },
            { 401, "Le profil est utilisé autre part" },
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
