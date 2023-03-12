using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Vuforia;
using UnityEngine.Networking;

public class First : MonoBehaviour
{
    public VirtualButtonBehaviour Vb_on;
    public VirtualButtonBehaviour Vb_off;
    public string url_on;
    public string url_off;

    IEnumerator GetRequest(string uri)
    {
        using (UnityWebRequest webRequest = UnityWebRequest.Get(uri))
        {
            // Request and wait for the desired page.
            yield return webRequest.SendWebRequest();

        }
    }

    void Start()
    {
        Vb_on.RegisterOnButtonPressed(OnButtonPressed_on);

        Vb_off.RegisterOnButtonPressed(OnButtonPressed_off);
       
    }


    public void OnButtonPressed_on(VirtualButtonBehaviour Vb_on)
    {
        StartCoroutine(GetRequest(url_on));
        Debug.Log("LED IS ON");
    }

    public void OnButtonPressed_off(VirtualButtonBehaviour Vb_off)
    {
        StartCoroutine(GetRequest(url_off));
        Debug.Log("LED IS OFF");
    }

}
