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

        public GloveSerial()
        {
            port = new SerialPort(portName);
            port.BaudRate = 9600;
            port.Open();
        }

        public void Check()
        {
            string newline;
            while (port.BytesToRead > 0)
            {
                newline = port.ReadLine();
                string[] words = newline.Split(' ');
                for (int i = 0; i < words.Length; i += 2)
                {
                    map[words[i]] = int.Parse(words[i + 1]);
                }
            }
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
