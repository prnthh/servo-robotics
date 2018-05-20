// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
int xpos=180, ypos=0, zpos=0, xto=90, yto=90, zto=90;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;
String freetime="";
Servo myservo[3];  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
int aspeed=100;

void animate(int x, int y, int z, int sp=100);

void setup() 
{ 
  Serial.begin(9600);
  Serial.println("LOLOLOLOLOL");
  inputString.reserve(200);
  myservo[0].attach(8);
  myservo[1].attach(9);
  myservo[2].attach(10);// attaches the servo on pin 9 to the servo object 
} 
 
 
void loop()
{  
   if(xpos != xto || ypos!=yto || zpos!=zto){
     if(xpos<xto)xpos++;else xpos--;
     if(ypos<yto)ypos++;else ypos--;
     if(zpos<zto)zpos++;else zpos--;
     delay(500/aspeed);
     myservo[0].write(xpos);
     myservo[1].write(ypos);
     myservo[2].write(zpos);
   }else{
     if(freetime=="dance"){
       if(xpos==80 && ypos==90 && zpos==80)animate(90,80,90,20);
       else if(xpos==90 && ypos==80 && zpos==90)animate(80,90,80,20);
       else animate(80,90,80,20);
     }
     if(freetime=="strike"){
       if(xpos==90 && ypos==180 && zpos==90)animate(50,180,90,120);
       else if(xpos==50 && ypos==180 && zpos==90)animate(50,180,40,120);
       else if(xpos==50 && ypos==180 && zpos==40)animate(90,180,90,20);
       else animate(90,180,90,70);
     }
     if(freetime=="walk"){
       if(xpos==20 && ypos==180 && zpos==90)animate(0,180,90,120);
       else if(xpos==0 && ypos==180 && zpos==90)animate(0,180,180,120);
       else if(xpos==0 && ypos==180 && zpos==180)animate(20,180,90,20);
       else animate(20,180,90,70);
     }
     if(freetime=="walks"){
       if(xpos==20 && ypos==180 && zpos==90)animate(0,180,90,120);
       else if(xpos==0 && ypos==180 && zpos==90)animate(0,180,180,120);
        
       else animate(20,180,90,70);
     }
   }
   
   if (stringComplete) {
     if(inputString=="dance")freetime="dance";
     else if(inputString=="strike")freetime="strike";
     else if(inputString=="walk")freetime="walk";
     else{freetime="";}
     
   if(inputString=="stop")animate(180, 0, 0);
   else if(inputString=="start")animate(90, 90, 90);
   else if(inputString=="point")animate(90, 180, 180);
   else if(inputString=="front")animate(90, 180, 90);
   Serial.println(inputString);
   inputString = "";
   stringComplete = false;
  }  
} 

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      inputString.replace('\n', '\0');
    } 
  }
}

void animate(int x, int y, int z, int sp){
  xto = x;
  yto = y;
  zto = z;
  aspeed = sp;  
}

