#include "Servo.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 

int irSensor1=13;
int irSensor2=12;
int irSensor3=11;
int irSensor4=10;
int irSensorEntree=9;
int irSensorSortie=8;
int irSensor; // total sensor values

/////////////////////////

int LED1 = 22;//red led of position 1
int LED1G = 23;//green led of position 1
int LED2 = 26;
int LED2G = 27;
int LED3 = 30;
int LED3G = 31;
int LED4 = 34;
int LED4G = 35;
int ledstop1 = 38;//red led of entrance
int ledgo1 = 39;//green led of entrance
int ledstop2 = 42;
int ledgo2 = 43;
int pinfire=2;

////////////

int buzzer = 5;
int MQSensor = A0;
int sensorThreshold = 800;

/////////////
unsigned long CarDetectedEntreeMillis;  // when car is detected in entrance
unsigned long Servo1UpAt;  // when servo1 was up
unsigned long CarDetectedSortieMillis;  // when car is detected in exit
unsigned long Servo2UpAt;  // when servo2 was up

unsigned long ServoDownDelay = 1000; // servo goes down after this time
bool Servo1Ready = true; // flag for when servo1 is down
bool Servo1State = true; // for servo1 is up or not.
bool Servo2Ready = true; // fflag for when servo2 is down
bool Servo2State = true; // for servo2 is up or not.

const long onDuration = 1000;// ON time for buzzer and LED
const long offDuration = 700;// OFF time for buzzer and LED
int warningState =HIGH;// initial state

long rememberTime = 0;

///////////////

int total_car;
int freeSlot;
const int totalSlot = 4;

//////////////

Servo Servomoteur1;//moteur d'entree
Servo Servomoteur2;//moteur dsortie


void setup() {
 pinMode(LED1, OUTPUT);
 pinMode(LED1G, OUTPUT);
 pinMode(LED2, OUTPUT);
 pinMode(LED2G, OUTPUT);
 pinMode(LED3, OUTPUT);
 pinMode(LED3G, OUTPUT);
 pinMode(LED4, OUTPUT);
 pinMode(LED4G, OUTPUT);
 pinMode(ledgo1, OUTPUT);
 pinMode(ledstop1, OUTPUT);
 pinMode(ledgo2, OUTPUT);
 pinMode(ledstop2, OUTPUT);
 pinMode(pinfire, OUTPUT);
 pinMode(irSensor1, INPUT);
 pinMode(irSensor2, INPUT);
 pinMode(irSensor3, INPUT);
 pinMode(irSensor4, INPUT);
 pinMode(irSensorEntree, INPUT);
 pinMode(irSensorSortie, INPUT);
 pinMode(buzzer, OUTPUT);//buzzer
 pinMode(MQSensor, INPUT);//MQ Sensor gaz
 Servomoteur1.attach(3);//pin of moteur d'entree is 3
 Servomoteur2.attach(4);//pin of moteur de sortie is 4
 Serial.begin(9600);
lcd.init();
lcd.backlight();
}

void loop() {


          
  int analogSensor = analogRead(MQSensor);
  Serial.println(analogSensor);
  if (analogSensor > sensorThreshold)
  {
    lcd.setCursor(1,0);
    lcd.print(" WARNING FIRE   ");
    lcd.setCursor(0,1);
    lcd.print("EXIT THE PARKING");
    digitalWrite(pinfire,HIGH);
    
    Servomoteur1.write(8); // la barrière entree se ferme
    Servomoteur2.write(110); // la barrière sortie s'ouvre
    digitalWrite(LED1G, LOW);
    digitalWrite(LED2G, LOW);
    digitalWrite(LED3G, LOW);
    digitalWrite(LED4G, LOW);
    warningState == HIGH;
         if( warningState == HIGH )
         {  tone(buzzer, 2000, 200);
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3, HIGH);
            digitalWrite(LED4, HIGH);
            digitalWrite(ledstop1, HIGH);
            digitalWrite(ledstop2, HIGH);
            if( (millis()- rememberTime) >= onDuration)
            {   
            warningState = LOW;
            rememberTime=millis();
            }
         }
         else
         {  noTone(buzzer);   
            digitalWrite(LED1, LOW);
            digitalWrite(LED2, LOW);
            digitalWrite(LED3, LOW);
            digitalWrite(LED4, LOW);
            digitalWrite(ledstop1, LOW);
            digitalWrite(ledstop2, LOW);
            
            if( (millis()- rememberTime) >= offDuration){ 
              
            warningState =HIGH;// change the state of warning
            rememberTime=millis();// remember Current millis() time
            }
         }
  }
  else
  {
        lcd.setCursor(1,0);
        lcd.print("SMART  PARKING");
        lcd.setCursor(0,1);
        lcd.print(freeSlot);
        lcd.setCursor(1,1);
        lcd.print(" PLACES  LIBRES");
        
        noTone(buzzer);
      // irsensor value read as analog, maximum value can be 1024
      // value depends on the distance of obstacle
      int statusSensor1 = digitalRead (irSensor1);
      int statusSensor2 = digitalRead (irSensor2);
      int statusSensor3 = digitalRead (irSensor3);
      int statusSensor4 = digitalRead (irSensor4);
      int statusSensorEntree = digitalRead (irSensorEntree);
      int statusSensorSortie = digitalRead (irSensorSortie);
      //control LED
      if (statusSensor1 == 1)
        {digitalWrite(LED1, LOW);// LED red LOW
        digitalWrite(LED1G, HIGH);}// LED green high
      else
        {digitalWrite(LED1, HIGH);//LED red HIGH
        digitalWrite(LED1G, LOW);}// LED green LOW
        
       if (statusSensor2 == 1)
        {digitalWrite(LED2, LOW);
        digitalWrite(LED2G, HIGH);}
      else
       {digitalWrite(LED2, HIGH);
        digitalWrite(LED2G, LOW);}
        
      if (statusSensor3 == 1)
        {digitalWrite(LED3, LOW); 
        digitalWrite(LED3G, HIGH);}
      else
        {digitalWrite(LED3, HIGH);
        digitalWrite(LED3G, LOW);}
        
      if (statusSensor4 == 1)
        {digitalWrite(LED4, LOW);
        digitalWrite(LED4G, HIGH);}
      else
        {digitalWrite(LED4, HIGH);
        digitalWrite(LED4G, LOW);}
      
      // all four sensors values are added here to take decision easily 
      irSensor = statusSensor1 + statusSensor2 + statusSensor3 + statusSensor4;
      if(irSensor == 4)
          total_car = 0;
      if(irSensor == 3)
          total_car = 1;
      if(irSensor == 2)
          total_car = 2;
      if(irSensor == 1)
          total_car = 3;
      if(irSensor == 0)
          total_car = 4;
      // total free slot can find from (total slotlot - total car)  
      freeSlot = totalSlot - total_car; 
      if(freeSlot!=0)
//Fonctionnement Servo1 
      {
            unsigned long currentMillis = millis(); 
            // check the entrance sensor
            if (statusSensorEntree == LOW) {
             // update the time when car is detected
             CarDetectedEntreeMillis = currentMillis;
             Servo1Ready = true;
            }
            
          
            if (Servo1Ready) {
              //this is typical millis code here:
             
                 // okay, enough time has passed since the button was let go.
                 Servomoteur1.write(110);
                 digitalWrite(ledgo1, HIGH);
                 digitalWrite(ledstop1, LOW);
                 // setup our next "state"
                 Servo1State = true;
                 // save when the servo was up
                 Servo1UpAt = currentMillis;
              
                 Servo1Ready = false;
                    }
            
               
                if (Servo1State) {
                  
                  if ((unsigned long)(currentMillis - Servo1UpAt) >= ServoDownDelay) {
                    Servo1State = false;
                    Servomoteur1.write(8);
                    digitalWrite(ledgo1, LOW);
                    digitalWrite(ledstop1, HIGH);
                  }
                }
         
      }
      else
      {
        Servomoteur1.write(8);
      }
//Fonctionnement Servo2                      
           unsigned long currentMillis = millis();
            
            if (statusSensorSortie == LOW) 
            {
             
             CarDetectedSortieMillis = currentMillis;
             Servo2Ready = true;
            }
            
            
            if (Servo2Ready) {
             
                 Servomoteur2.write(110);
                 digitalWrite(ledgo2, HIGH);
                 digitalWrite(ledstop2, LOW);
                 // setup our next "state"
                 Servo2State = true;
                 Servo2UpAt = currentMillis;
                 Servo2Ready = false;
                    }
            
                if (Servo2State) {
                  if ((unsigned long)(currentMillis - Servo2UpAt) >= ServoDownDelay) {
                    Servo2State = false;
                    Servomoteur2.write(8);
                    digitalWrite(ledgo2, LOW);
                    digitalWrite(ledstop2, HIGH);
                  }
                }
  }

  
}
