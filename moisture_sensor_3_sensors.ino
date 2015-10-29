// **** INCLUDES *****

#include "LowPower.h"
#include <Adafruit_NeoPixel.h>
#define PIN 4
#define N_LEDS 1

Adafruit_NeoPixel strip = Adafruit_NeoPixel (N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
int m1 = A4;
int m2 = A1;
int m3 = A2;
int led = 13;
int pump = 2;

void setup() {
   // put your setup code here, to run once:
   pinMode(m1,INPUT);
   pinMode(m2,INPUT);
   pinMode(m3,INPUT);
   pinMode(led,OUTPUT);
   pinMode(pump,OUTPUT);
   Serial.begin(9600);
   strip.begin();
}

int check_sensor(int m){
   int r1 = analogRead(m);
   delay(50);
   int r2 = analogRead(m);
   delay(50);
   int r3 = analogRead(m);
   delay(50);
   int avg = ((r1+r2+r3)/3);
   Serial.print("sensor ");
   Serial.print(m);
   Serial.print(" average is ");
   Serial.println(avg);
   return avg;
}

bool average_all(){
   int s1 = check_sensor(m1);
   int s2 = check_sensor(m2);
   int s3 = check_sensor(m3);
   int avg = ((s1+s2+s3)/3);
 
    if (avg < 250) {
      strip.setPixelColor(0, strip.Color(255,0,0));
      strip.show();
    
      //turn on the motor
      turn_on_motor();
      delay(60000);
      turn_off_motor();
    }
    else if(avg > 650)
    {
      strip.setPixelColor(0, strip.Color(0,0,255));
      strip.show();
    }
    else
    {
      strip.setPixelColor(0, strip.Color(0,255,0));
      strip.show();
    } 
}

void turn_on_motor(){
  digitalWrite(pump,HIGH);
}
void turn_off_motor(){
  digitalWrite(pump,LOW);
}

void loop()
{
  
   // Enter power down state for 8 s with ADC and BOD module disabled
   LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  
   // Do something here
   // Example: Read sensor, data logging, data transmission.
   average_all();
  
}
