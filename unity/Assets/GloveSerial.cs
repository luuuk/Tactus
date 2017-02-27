using UnityEngine;
using System.Collections;
using System.IO.Ports;
using System.Collections.Generic;

namespace HapticGlove
{
    public class GloveSerial
    {
        private const string portName = "COM1";
        private Dictionary<string, int> map;
        private SerialPort port;
        private string buffer;

        public GloveSerial()
        {
            port = new SerialPort(portName);
            port.BaudRate = 9600;
            port.Open();
            map = new Dictionary<string, int>();
            buffer = "";
        }

        public void Check()
        {
            string newline;
            while (port.BytesToRead > 0)
            {
                newline = port.ReadLine();
                string[] pairs = newline.Split('&');
                for (int i = 0; i < pairs.Length; i += 1)
                {
                    int colon = pairs[i].IndexOf(":");
                    string name = pairs[i].Substring(0, colon);
                    int val = int.Parse(pairs[i].Substring(colon + 1));
                    map[name] = val;
                }
            }
        }

        //adds a name-value pair to the buffer
        public void Set(string key, int val)
        {
            buffer += "&" + key + ":" + val;
        }
        
        //Must be called in the "Update" method of the object extending Monobehavior
        public void Send()
        {
            port.WriteLine(buffer);
            buffer = "";
        }

        public int Get(string key)
        {
            if (!map.ContainsKey(key))
            {
                Debug.LogError("Key does not exist");
                return -1;
            }
            return map[key];
        }
    }
}
