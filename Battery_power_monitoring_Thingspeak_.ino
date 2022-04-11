#include <DHT.h>  // Including library for dht11
#include <ESP8266WiFi.h>
String apiKey = "4ILBGXTCN7JETLVC";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "ICE Innovation Lab";     //  wifi ssid 
const char *pass =  "beinnovative#";    // wifi password
const char* server = "api.thingspeak.com";

WiFiClient client;


#define DHTPIN 0       //pin where the dht11 is connected
DHT dht(DHTPIN, DHT11);


#define analoginput A0
#define f D0
#define e D1
#define d D2
#define c D7
#define b D4
#define a D5
//int s=13;

float vout = 0.0;
float vin = 0.0;
float R1 = 100000;
float r2 = 10000;
int value = 0;


void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.print("Connecting to: ");
  Serial.println(ssid);

      WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");


      
  pinMode(analoginput,INPUT);
  //  pinMode(s,OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);


  //  digitalWrite(s,LOW);
  digitalWrite(a, HIGH);
  delay(500);
  digitalWrite(b, HIGH);
  delay(500);
  digitalWrite(c, HIGH);
  delay(500);
  digitalWrite(d, HIGH);
  delay(500);
  digitalWrite(e, HIGH);
  delay(500);
  digitalWrite(f, HIGH);
  delay(500);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);




}

void loop() {
  value = analogRead(analoginput);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("Temperature:");
  Serial.println(t);
  Serial.print("Humidity:");
  Serial.println(h);
  
      
  Serial.print("Pin value: ");
  Serial.println(value);
  vout = (value * 5) / 1024;
  vin = vout / ( (R1 / (R1 + R1)));
  Serial.print("Input voltage = ");
  Serial.println(vin);

  if (vin > 7) {
    digitalWrite(a, HIGH);
  }
  else {
    digitalWrite(a, LOW);
  }
  if (vin <= 7 && vin > 6) {
    digitalWrite(b, HIGH);
  }
  else {
    digitalWrite(b, LOW);
  }
  if (vin <= 6 && vin > 5) {
    digitalWrite(c, HIGH);
  }
  else {
    digitalWrite(c, LOW);
  }
  if (vin <= 5 && vin > 4) {
    digitalWrite(d, HIGH);
  }
  else {
    digitalWrite(d, LOW);
  }
  if (vin <= 4 && vin > 3) {
    digitalWrite(e, HIGH);
  }
  else {
    digitalWrite(e, LOW);
  }
  if (vin <= 3) {
    digitalWrite(f, HIGH);
  }
  else {
    digitalWrite(f, LOW);
  }
  delay(2000);


  
    if (isnan(h) || isnan(t) || isnan(vin)) 
                 {
                     Serial.println("Failed to read Voltage!");
                      return;
                 }

                 

                         if (client.connect(server,80))   // establishing the connection with thingspeak server
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(vin);
                             postStr +="&field2=";
                             postStr += String(t);
                             postStr +="&field3=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Volatge and sensor signal: ");
                             Serial.print(vin);
                            
                             Serial.println(" Send to Thingspeak.");
                        }

                                  client.stop();
 
          Serial.println("Waiting...");
  
  
  delay(500);  // dealy half second and regenerate the temperature and send it to the thingspeak


}
