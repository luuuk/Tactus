using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FingerController : MonoBehaviour {

    public GameObject knuckle;
    public GameObject f0;
    public GameObject f1;
    public GameObject f2;
    public GameObject[] segments;
    public float fingerPos { get; set; }
    public float knucklePos { get; set; }
	//private GloveSerial port;



	// Use this for initialization
	void Start () {
		//port = new GloveSerial();
        segments = new GameObject[3];
        segments[0] = f0;
        segments[1] = f1;
        segments[2] = f2;
        knucklePos = 20;	
	}

	// Update is called once per frame
	void Update () {
		//serial updates
		//port.Check();
		//fingerPos = port.Get(0);
		//knucklePos = port.Get(1);
		//position updates
		updatePos();
	}

    void updatePos()
    {
        HingeJoint knuckleJoint = knuckle.GetComponent<HingeJoint>();
        HingeJoint hingeJoint = f0.GetComponent<HingeJoint>();
        HingeJoint hingeJoint1 = f1.GetComponent<HingeJoint>();
        JointSpring kSpring = knuckleJoint.spring;
        JointSpring spring = hingeJoint.spring;
        JointSpring spring1 = hingeJoint1.spring;
        kSpring.targetPosition = -knucklePos + 20;
        spring.targetPosition = -fingerPos;
        spring1.targetPosition = -fingerPos;
        knuckleJoint.spring = kSpring;
        hingeJoint.spring = spring;
        hingeJoint1.spring = spring1;
    }
}
