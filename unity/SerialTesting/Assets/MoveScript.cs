using UnityEngine;
using System.Collections;


public class MoveScript : MonoBehaviour {
	public float pos { get; set; }
	public float val1 { get; set; }
	public float val2 { get; set; }
    private GloveSerial port;
	// Use this for initialization
	void Start () {
        port = new GloveSerial();
	}

	// Update is called once per frame
	void Update () {
        port.Check();
        val1 = port.Get(0);
        val2 = port.Get(1);
		//gameObject.transform.position = new Vector3(x * 20 - 10, 0, y * 20 - 10);
		port.SlideSend (pos);
	}
}
