using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlaneControl : MonoBehaviour {

	public float height { get; set; }
	private Material collide;
	private Material noCollide;

	// Use this for initialization
	void Start () {
		collide = new Material (Shader.Find ("Standard"));
		collide.color = new Color(1f,.6f,.6f);
		noCollide = GetComponent<Renderer> ().material;
	}
	
	// Update is called once per frame
	void Update () {
		gameObject.transform.position = new Vector3 (-2.4f, -4f + height, 0f);
	}

	void OnCollisionEnter(Collision c) {
		GetComponent<Renderer> ().material = collide;

	}

	void OnCollisionExit(Collision c) {
		GetComponent<Renderer> ().material = noCollide;
	}
}
