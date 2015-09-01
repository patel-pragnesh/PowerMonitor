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
            { 0x101, "La requête n'est pas bien formatée" },
            { 0x102, "La commande n'a pas été trouvée" },
            { 0x103, "La session n'est pas valide" },
            { 0x104, "La session est expirée" },
            { 0x201, "Le mot de passe est incorrect" },
            { 0x301, "L'utilisateur n'a pas été trouvé" },
            { 0x401, "Le module n'a pas été trouvé" },
            { 0x402, "Impossible de modifier l'état du module" },
            { 0x403, "Le module est déjà dans cet état" },
            { 0x501, "Le profil n'a pas été trouvé" },
            { 0x502, "Le profil est en encore utilisé" },
            { 0x503, "Un profil avec ce nom existe déjà" },
            { 0x601, "L'alerte n'a pas été trouvée" },
            { 0x701, "La plage n'a pas été trouvée" },
            { 0x801, "L'unité n'a pas été trouvée" },
        };

        public static string GetErrorMessage(UInt64 code)
        {
            if (_errors.ContainsKey(code))
                return _errors[code];
            return "";
        }
    }

    public class Error
    {
        public UInt64 Code;
        public string Text;

        public Error(UInt64 code, string text)
        {
            Code = code;
            Text = text;
        }
    }
}
