using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class CMain : MonoBehaviour {
	SocketIOClient.Client socket;
	public ParticleSystem baseDrumParticleEmitter;
	public ParticleSystem rightTamParticleEmitter;
	public ParticleSystem leftTamParticleEmitter;
	public ParticleSystem cymbalParticleEmitter;
	public int baseDrumIntensity;
	public int rightTamIntensity;
	public int leftTamIntensity;
	public int cymbalIntensity;

	// Use this for initialization
	void Start ()
	{

		Screen.SetResolution(1280, 1024, false);

		baseDrumIntensity = 0;
		rightTamIntensity = 0;
		leftTamIntensity = 0;
		cymbalIntensity = 0;

		GameObject rightTamObject = GameObject.Find("RightTamParticleSystem");
		rightTamParticleEmitter = rightTamObject.GetComponent<ParticleSystem> ();
		GameObject baseDrumObject = GameObject.Find("BassDrumParticleSystem");
		baseDrumParticleEmitter = baseDrumObject.GetComponent<ParticleSystem> ();
		GameObject leftTamObject = GameObject.Find("LeftTamParticleSystem");
		leftTamParticleEmitter = baseDrumObject.GetComponent<ParticleSystem> ();
		GameObject cymbalObject = GameObject.Find("CymbalParticleSystem");
		cymbalParticleEmitter = baseDrumObject.GetComponent<ParticleSystem> ();

		socket = new SocketIOClient.Client("http://127.0.0.1:8000");
		socket.On("connect", (fn) => {
			Debug.Log ("connect - socket");			
			Dictionary<string, string> args = new Dictionary<string, string>();
			args.Add("msg", "what's up?");
			socket.Emit("SEND", args);
		});

		socket.On("leftTam", (data) => {
			Debug.Log (data.Json.ToJsonString());
			int intensity = data.Json.GetFirstArgAs<int>();
			Debug.Log (intensity);
			leftTamIntensity  = intensity;
		});

		socket.On("rightTam", (data) => {
			Debug.Log (data.Json.ToJsonString());
			int intensity = data.Json.GetFirstArgAs<int>();
			Debug.Log (intensity);
			rightTamIntensity  = intensity;
		});
	
		socket.On("bassDrum", (data) => {
			Debug.Log (data.Json.ToJsonString());
			int intensity = data.Json.GetFirstArgAs<int>();
			Debug.Log (intensity);
			baseDrumIntensity  = intensity;
		});
		socket.Error += (sender, e) => {
			Debug.Log ("socket Error: " + e.Message.ToString ());
		};
		socket.Connect();
	}
	
	// Update is called once per frame
	void Update ()
	{ 
		if (baseDrumIntensity > 0) {
			baseDrumParticleEmitter.Emit ((baseDrumIntensity - 150) * 5);
			baseDrumIntensity = 0;
		} 
		if (rightTamIntensity > 0) {
			rightTamParticleEmitter.Emit ((rightTamIntensity - 150) * 5);
			rightTamIntensity = 0;
		} 
		if (leftTamIntensity > 0) {
			leftTamParticleEmitter.Emit ((leftTamIntensity - 150) * 5);
			leftTamIntensity = 0;
		} 
		if (cymbalIntensity > 0) {
			cymbalParticleEmitter.Emit ((cymbalIntensity - 150) * 5);
			cymbalIntensity = 0;
		} 

		
		//		if (GUI.Button (new Rect (20, 70, 150, 30), "SEND")) {
//			Debug.Log ("Sending");
//			Dictionary<string, string> args = new Dictionary<string, string>();
//			args.Add("msg", "hello!");
//			socket.Emit("SEND", args);
//		}
//		
//		if (GUI.Button (new Rect (20, 120, 150, 30), "Close Connection")) {
//			Debug.Log ("Closing");
//			
//			socket.Close();
//		}
	}
}
