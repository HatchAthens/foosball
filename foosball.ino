#include <Adafruit_NeoPixel.h>
#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define SENSOR1 6
#define SENSOR2 7
#define ST1 4
#define ST2 5

int sensorState1 = 0, lastState1=0;
int sensorState2 = 0, lastState2=0;
int Score1=-1;
int Score2=-1;

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(10, ST1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(10, ST2, NEO_GRB + NEO_KHZ800);

TMRpcm tmrpcm;

const int SD_ChipSelectPin = 10;

void setup() {

  strip2.begin();
  strip2.show(); // Initialize all pixels to 'off'
  strip1.begin();
  strip1.show(); // Initialize all pixels to 'off'

pinMode(SENSOR1, INPUT);     
digitalWrite(SENSOR1, HIGH); // turn on the pullup
pinMode(SENSOR2, INPUT);     
digitalWrite(SENSOR2, HIGH); // turn on the pullup

 Serial.begin(9600);

 if (!SD.begin(SD_ChipSelectPin)) { // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;                          // don't do anything more if not
  }else{   
    Serial.println("SD ok");   
  } 
tmrpcm.setVolume(0);
tmrpcm.speakerPin = 9;



colorWipe(strip1.Color(30, 0, 30), 50); // Purple


delay(5000);
colorWipe(strip1.Color(0, 0, 0), 50); // Off

strip1.setPixelColor(0,0,0,30);
strip1.show();
delay(50);
strip2.setPixelColor(0,0,0,30);
strip2.show();
delay(50);




}
void loop() {

sensorState1 = digitalRead(SENSOR1);
 
  // check if the sensor beam is broken
  // if it is, the sensorState is LOW:
  
  if (sensorState1 && !lastState1) {
    Serial.println("Unbroken1");
    
    Score1=Score1+1;
    Serial.println(Score1);
    for(uint16_t i=0; i<=Score1; i++) {
    strip1.setPixelColor(i,0,0,30);
    strip1.show();
 
  }

    
    
    if (Score1>=10) {
     Win1();
     delay(5000000); 
    }
  } 
  if (!sensorState1 && lastState1) {
    Serial.println("Broken1");
  }

//Serial.println(sensorState1);
lastState1 = sensorState1;

sensorState2= digitalRead(SENSOR2);
 
  // check if the sensor beam is broken
  // if it is, the sensorState is LOW:
  
  if (sensorState2 && !lastState2) {
    Serial.println("Unbroken2");
    
    Score2=Score2+1;
    Serial.println(Score2);
    for(uint16_t i=0; i<=Score2; i++) {
    strip2.setPixelColor(i,0,0,30);
    strip2.show();
    
    if (Score2>=10) {
     Win2();
     delay(5000000); 
    }
  } 
  if (!sensorState2 && lastState2) {
    Serial.println("Broken2");
  }
  }
//Serial.println(sensorState2);
lastState2 = sensorState2;










}

//SUBROUTINES START HERE



// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
    strip1.setPixelColor(i, c);
    strip1.show();
    strip2.setPixelColor(i, c);
    strip2.show();
    delay(wait);
  }

}
void Win1() {
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
    strip1.setPixelColor(i, 0,30,0);
    strip1.show();
    strip2.setPixelColor(i, 30,0,0);
    strip2.show();
  }
tmrpcm.setVolume(5);
tmrpcm.play("GL.WAV");
delay(3000);

}
void Win2() {
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
    strip1.setPixelColor(i, 30,0,0);
    strip1.show();
    strip2.setPixelColor(i, 0,30,0);
    strip2.show();
  }
tmrpcm.setVolume(5);
tmrpcm.play("GL.WAV");
delay(3000);

}

