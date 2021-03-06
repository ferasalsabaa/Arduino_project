#include <FastLED.h>
#include <Chrono.h>
#include "Car_class.h"

#define NUM_LEDS 144 // all leds
#define LED_PIN 14   // place the led

const int ledLength = 8;     // later long of car
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define MAX_BRIGHTNESS  60
const int fps = 100;

int carOnePosition = 0;  // where is the car
int carTwoPosition = 0;  // where is the car

int carOneCount = 0;  // bouns
int carTwoCount = 0;  // bouns

#define ctsPin 19  // place the sensor

//VARIABLEN ERZEUGEN
int sensorPinA = 15;    //hier ist die nummer des analogen pins gespeichert an dem unser sensor angeschlossen ist, ggf. anpassen! (z.b. 16, 17, 20, oder 21)
int sensorPinB = 16;
int sensorPinC = 17;
int sensorPinD = 18;
int sensorWertA = 0;    //in dieser variable wird unser sensorwert, d.h. der Rückgabewert der Funktion analogRead(); oder touchRead(); gespeichert.
int sensorWertB = 0;
int sensorWertC = 0;
int sensorWertD = 0;
int sensorValueTest = 0;


//create chrono objects for timed actions:
Chrono cNextFrame(Chrono::MICROS);
Chrono cCheckInput;


CRGB led [NUM_LEDS];

Car_class car1; // first car
Car_class car2; // first car

void setup() {

  FastLED.addLeds<NEOPIXEL, LED_PIN>(led, NUM_LEDS);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(led, NUM_LEDS);
  FastLED.setCorrection(TypicalLEDStrip); //LEDS.setCorrection(Candle); or (Tungsten40W)
  FastLED.setBrightness(MAX_BRIGHTNESS);

  Serial.begin(115200); //serielle datenverbindung zum computer herstellen damit wir mit Serial.print(); oder Serial.println(); daten senden können
  //pinMode(sensorValue, OUTPUT);
  //pinMode(ctsPin, INPUT);

  pinMode(sensorPinA, INPUT_PULLUP);  //declare pin as input AND enable internal 33kohm pullup resistor (that is: a 33k resistor between the analog input pin and 3.3 volts)
  pinMode(sensorPinB, INPUT_PULLUP);
  pinMode(sensorPinC, INPUT_PULLUP);
  pinMode(sensorPinD, INPUT_PULLUP);
}

void loop()
{
  sensorWertA = filter(analogRead(sensorPinA), 0.25, sensorWertA);
  sensorWertB = filter(analogRead(sensorPinB), 0.25, sensorWertB);
  sensorWertC = filter(analogRead(sensorPinC), 0.25, sensorWertC);
  sensorWertD = filter(analogRead(sensorPinD), 0.25, sensorWertD);
  sensorWertA = map(sensorWertA, 0, 1023, 0, 100);
  sensorWertB = map(sensorWertB, 0, 1023, 0, 100);
  sensorWertC = map(sensorWertC, 0, 1023, 0, 100);
  sensorWertD = map(sensorWertD, 0, 1023, 0, 100);
  Serial.println(sensorWertA);               //send debug data to the Arduino Serial Monitor


  //INTERACTIVITY: work with sensor data every X ms
  if (cCheckInput.hasPassed(1)) {
    cCheckInput.restart();
    if (carOnePosition < carTwoPosition) {
      car1.blocks(sensorWertA, carOnePosition, led, NUM_LEDS, sensorWertB, carOneCount, 2);
      car2.blocks(sensorWertC, carTwoPosition, led, NUM_LEDS, sensorWertD, carTwoCount, 1);
    } else if (carOnePosition > carTwoPosition) {
      car2.blocks(sensorWertC, carTwoPosition, led, NUM_LEDS, sensorWertD, carTwoCount, 2);
      car1.blocks(sensorWertA, carOnePosition, led, NUM_LEDS, sensorWertB, carOneCount, 1);
    } else {
      if(carTwoPosition == 0 && carOnePosition == 0){
        car1.blocks(sensorWertA, carOnePosition, led, NUM_LEDS, sensorWertB, carOneCount, 1);
        car2.blocks(sensorWertC, carTwoPosition, led, NUM_LEDS, sensorWertD, carTwoCount, 1);
        }
       else if (sensorWertA < sensorWertC) {
        carTwoPosition --;
        car1.blocks(sensorWertA, carOnePosition, led, NUM_LEDS, sensorWertB, carOneCount, 2);
        car2.blocks(sensorWertC, carTwoPosition, led, NUM_LEDS, sensorWertD, carTwoCount, 1);
      } else{
        carOnePosition --;
        car2.blocks(sensorWertC, carTwoPosition, led, NUM_LEDS, sensorWertD, carTwoCount, 2);
        car1.blocks(sensorWertA, carOnePosition, led, NUM_LEDS, sensorWertB, carOneCount, 1);
      }
    }
  }
  //DRAW FRAME
  if (cNextFrame.hasPassed((1000 * 1000) / fps) ) { //milliseconds chrono -> triggers on every frame...

    cNextFrame.restart();
    FastLED.clear();
    //first one:
    led[20].setRGB(220, 0, 0);
    led[21].setRGB(220, 0, 0);
    led[22].setRGB(220, 0, 0);
    led[23].setRGB(220, 0, 0);
    led[24].setRGB(220, 0, 0);
    led[25].setRGB(220, 0, 0);
    //second one:
    led[90].setRGB(0, 0, 220);
    led[91].setRGB(0, 0, 220);
    led[92].setRGB(0, 0, 220);
    led[93].setRGB(0, 0, 220);
    led[94].setRGB(0, 0, 220);
    led[95].setRGB(0, 0, 220);
    led[96].setRGB(0, 0, 220);
    led[97].setRGB(0, 0, 220);
    led[98].setRGB(0, 0, 220);
    led[99].setRGB(0, 0, 220);
    led[100].setRGB(0, 0, 220);
    led[101].setRGB(0, 0, 220);
    //third one(counter):
    led[70].setRGB(0, 220, 0);
    led[42].setRGB(0, 220, 0);
    led[40].setRGB(0, 220, 0);
    //third blocks
    led[110].setRGB(248, 255, 10);
    led[111].setRGB(248, 255, 10);


    if (carOnePosition == carTwoPosition) {
      led[carOnePosition].setRGB(255, 51, 51);
      led[carTwoPosition].setRGB(255, 51, 51);

    } else if (carOnePosition == 144) {
      carOnePosition = 0;
      carTwoPosition = 0;
      carOneCount = 0;  // bouns
      carTwoCount = 0;  // bouns
      for (int i = 0; i < NUM_LEDS; i++) {
        led[i].setRGB(102, 0, 102);
        FastLED.show();
        delay(10);
      }
    } else if (carTwoPosition == 144) {
      carOnePosition = 0;
      carTwoPosition = 0;
      carOneCount = 0;  // bouns
      carTwoCount = 0;  // bouns
      for (int i = 0; i < NUM_LEDS; i++) {
        led[i].setRGB(255, 255, 102);
        FastLED.show();
        delay(10);
      }
    }
    else {
      led[carOnePosition].setRGB(102, 0, 102);
      led[carTwoPosition].setRGB(255, 255, 102);
    }
    FastLED.show();
  }

} // end loop

float filter(float rawValue, float weight, float lastValue)
{
  float result = weight * rawValue + (1.0 - weight) * lastValue;
  return result;
}
