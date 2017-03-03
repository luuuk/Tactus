﻿using UnityEngine;
using System.Collections;
using HapticGlove;

public class MoveScript : MonoBehaviour {
    private GloveSerial port;
	// Use this for initialization
	void Start () {
        port = new GloveSerial();
	}

	// Update is called once per frame
	void Update () {
        port.Check();
        float x = (1.0f/700) * port.Get(0);
        float y = (1.0f/1023) * port.Get(1);
		gameObject.transform.position = new Vector3(x * 20 - 10, 0, y * 20 - 10);
	}
}
