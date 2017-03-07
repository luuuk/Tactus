using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FingerController : MonoBehaviour {

    public GameObject f0;
    public GameObject f1;
    public GameObject f2;
    public GameObject[] segments;
    public float pos { get; set; }


	// Use this for initialization
	void Start () {
        segments = new GameObject[3];
        segments[0] = f0;
        segments[1] = f1;
        segments[2] = f2;		
	}
	
	// Update is called once per frame
	void Update () {
        updatePos();
	}

    void updatePos()
    {
        HingeJoint hingeJoint = f0.GetComponent<HingeJoint>();
        HingeJoint hingeJoint1 = f1.GetComponent<HingeJoint>();
        JointSpring spring = hingeJoint.spring;
        JointSpring spring1 = hingeJoint1.spring;
        spring.targetPosition = -100 * pos;
        spring1.targetPosition = -110 * pos;
        hingeJoint.spring = spring;
        hingeJoint1.spring = spring1;
    }
}
