using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Powermonitor.Common
{
    /*public partial class Singleton<T> where T : class, new()
    {
        private static T instance;

        protected Singleton() { }

        public static T getInstance()
        {
            if (instance == null)
            {
                instance = new T();
            }
            return instance;
        }
    }*/
    public abstract class Singleton<T> where T : class
    {
        private static readonly Lazy<T> sInstance = new Lazy<T>(() => CreateInstanceOfT());

        public static T getInstance { get { return sInstance.Value; } }

        private static T CreateInstanceOfT()
        {
            return Activator.CreateInstance(typeof(T)) as T;
        }
    }
}
