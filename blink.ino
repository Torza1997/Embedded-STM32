#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

int Value;
char auth[] = "7df071e725614ff184bf63c0135e6037";
// Your WiFi credentials
// Set password to "" for open networks.
char ssid[] = "ssss";
char pass[] = "torza35120";
void setup()
{
  
  pinMode(D5,INPUT);
  pinMode(D6,INPUT);
  pinMode(D7,INPUT);
  pinMode(D8,INPUT);
  pinMode(D9,INPUT);
  pinMode(D10,INPUT);
  pinMode(A0,INPUT);

  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{ 
  
 Blynk.run();
 sends(D6,D1);
 sends(D7,D2);
 sends(D8,D3);
 sends(D9,D4);
 sends(D5,9);
 sends(D10,10);
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading: 
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
void sends(const int pinIN,const int pinOUT){
  Value = digitalRead(pinIN);
  digitalWrite(pinOUT,Value); 
  delay(5);  
}
