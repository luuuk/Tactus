using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FingerController : MonoBehaviour {

    public int ARDUINO_MAX_VALUE;
    public GameObject knuckle;
    public GameObject f0;
    public GameObject f1;
    public GameObject f2;
    public GameObject[] segments;
    private GloveSerial port;
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
        //port = new GloveSerial();
	}

	// Update is called once per frame
	void Update () {
        //serial updates
        //port.Check();
        //fingerPos = port.Get(0);
        //knucklePos = port.Get(1);
        //position updates
        //servoPos();
		updatePos();
        float torque = f1.GetComponent<HingeJoint>().currentTorque.magnitude;
        if(torque != 0)
        {
            Debug.Log(torque*1000000);
            int valToSend = (int)Mathf.Round(map(torque * 1000000, 0, 25, 0, ARDUINO_MAX_VALUE));
            //uncomment the following to send torque data to the serial port (make sure to uncomment all other lines involving the object "port" as well)
            //port.Set(0, valToSend);
            //port.Send();
        }
	}

    void servoPos()
    {
        port.Check();
        int servopos = port.Get(0);
        setFingerPos(map(servopos, 0, 180, 0, 110));
    }

    static float map(float val, float min1, float max1, float min2, float max2)
    {
        return (val - min1) * ((max2 - min2) / (max1 - min1)) + min2;
    }

    void updatePos()
    {
        setFingerPos(fingerPos);
        setKnucklePos(knucklePos);
    }

    void setFingerPos(float val)
    {
        HingeJoint hingeJoint = f0.GetComponent<HingeJoint>();
        HingeJoint hingeJoint1 = f1.GetComponent<HingeJoint>();
        JointSpring spring = hingeJoint.spring;
        JointSpring spring1 = hingeJoint1.spring;
        spring.targetPosition = -val;
        spring1.targetPosition = -val;
        hingeJoint.spring = spring;
        hingeJoint1.spring = spring1;
    }

    void setKnucklePos(float val)
    {
        HingeJoint knuckleJoint = knuckle.GetComponent<HingeJoint>();
        JointSpring kSpring = knuckleJoint.spring;
        kSpring.targetPosition = -val + 20;
        knuckleJoint.spring = kSpring;
    }
}
