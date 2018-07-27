/*this sample runs on a NodeMCU with one Servo motor attached
*/

#include <Servo.h> 
#include <ESP8266WiFi.h>

const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";

WiFiServer server(80);
Servo myservo;  

void setup() 
{ 
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
  
  closeDoor();
} 
 
void loop() 
{ 
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  int val;
  if (req.indexOf("/door/0") != -1)
    val = 0;
  else if (req.indexOf("/door/1") != -1)
    val = 1;
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  // Set GPIO2 according to the request
  if(val==0)closeDoor();
  else openDoor();
  
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val)?"high":"low";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

void openDoor(){
   myservo.attach(0);  // attaches the servo on GIO2 to the servo object 
  int pos;
  for(pos = 0; pos <= 90; pos += 1) // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    }
    myservo.detach();
  }

void closeDoor(){
    myservo.attach(0);  // attaches the servo on GIO2 to the servo object 
    int pos;
    for(pos = 90; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
    {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    }
    myservo.detach();
  }

