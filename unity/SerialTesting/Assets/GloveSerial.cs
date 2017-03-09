using UnityEngine;
using UnityEngine.Events;
using System.Collections;
using System.IO.Ports;
using System.Collections.Generic;


public class GloveSerial : MonoBehaviour
{
    private const string portName = "/dev/cu.usbmodem1421";
    private Dictionary<int, int> map;
    private SerialPort port;
    private string buffer;
	public float uno { get; set; }
	public float dos { get; set; }

    public GloveSerial()
    {
        port = new SerialPort(portName);
        port.BaudRate = 9600;
        port.Open();
        map = new Dictionary<int, int>();
        buffer = "";
    }
     
    public void Check()
    {
        string newline;
		Debug.Log ("Checking");
        while (port.BytesToRead > 0)
        {
			Debug.Log ("Reading:");
            newline = port.ReadLine();
			Debug.Log (newline);
            string[] pairs = newline.Split('&');
            for (int i = 1; i < pairs.Length; i += 1)
            {
				Debug.Log (pairs [i]);
				int colon = pairs [i].IndexOf (":");
				int name = int.Parse (pairs [i].Substring (0, colon));
				Debug.Log ("Name: " + name);
				int val = int.Parse (pairs [i].Substring (colon + 1));
				Debug.Log ("Val " + val);
				map [name] = val;
            }
        }
		map [0] = uno;
		map [1] = dos;
    }

    //adds a name-value pair to the buffer
    public void Set(int key, int val)
    {
        buffer += "&" + key + ":" + val;
    }

	public void SlideSend(float val) {
		port.WriteLine ("&0:" + (int)val + "&1:1&2:5");
		Debug.Log ("Sending: " + "&0:" + val);
	}
    
    //Must be called in the "Update" method of the object extending Monobehavior
    public void Send()
    {
        port.WriteLine(buffer);
        buffer = "";
    }

    public int Get(int key)
    {
        if (!map.ContainsKey(key))
        {
            Debug.LogError("Key does not exist");
            return -1;
        }
        return map[key];
    }
}

