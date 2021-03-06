#include <FastLED.h>
#include <Chrono.h>
#include "player.h"

#define NUM_LEDS 144 // all leds
#define LED_PIN 14   // place the led

const int ledLength = 8;     // later long of car
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
int MAX_BRIGHTNESS =  60;
const int fps = 100;

#define ctsPin 19  // place the sensor

int playerOneFireFirst = 0;  // how strong the first fire for 1st player
int playerTwoFireFirst = 0;  // how strong the first fire for 2nd player

int playerOneFireSecond = 0;  // how strong the second fire for 1st player
int playerTwoFireSecond = 0;  // how strong the second fire for 2nd player

int playerOneFirePosition = 1;  // where is the player1
int playerTwoFirePosition = 142;  // where is the player2

int fireCase1 = 0;
int fireCase2 = 0;

int defenceCountOne = 0;
int defenceCountTwo = 0;

boolean defenceOne = false;
boolean defenceTwo = false;

boolean defenceOneShow = false;
boolean defenceTwoShow = false;




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

int j = 60;

int i = 0;
int k = 142;

Player player1(0, 0, 0); // first car
Player player2(140, 0, 0); // first car

void setup() {

  FastLED.addLeds<NEOPIXEL, LED_PIN>(led, NUM_LEDS);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(led, NUM_LEDS);
  FastLED.setCorrection(TypicalLEDStrip); //LEDS.setCorrection(Candle); or (Tungsten40W)

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
  Chrono bright;
  Chrono defence2;
  Chrono defence1;

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

    player2.playShow(sensorWertC, led, NUM_LEDS, sensorWertD, playerTwoFireFirst, fireCase2);
    player1.playShow(sensorWertA, led, NUM_LEDS, sensorWertB, playerOneFireFirst, fireCase1);
    if (playerOneFireFirst > 199 && fireCase1 == 0) {
      player1.playShow(sensorWertA, led, NUM_LEDS, sensorWertB, playerOneFireSecond, fireCase1);
    }
    if (playerTwoFireFirst > 199 && fireCase2 == 0) {
      player2.playShow(sensorWertC, led, NUM_LEDS, sensorWertD, playerTwoFireSecond, fireCase2);
    }

    if (i > 130) {
      defenceTwo = player2.defenceTest(sensorWertC, sensorWertD);
    }
    if (k < 9) {
      defenceOne = player1.defenceTest(sensorWertA, sensorWertB);
    }
    if (sensorWertA > 7 && sensorWertB < 7) {
      defenceOneShow = true;
    }
    if (sensorWertB > 7 && sensorWertD < 7) {
      defenceTwoShow = true;
    }
  }
  //DRAW FRAME
  if (cNextFrame.hasPassed((1000 * 1000) / fps) ) { //milliseconds chrono -> triggers on every frame...
    cNextFrame.restart();
    FastLED.clear();



    led[143].setRGB(0, 0, 102);
    led[0].setRGB(102, 0, 0);

    if (defenceTwoShow == true) {
      if (defence2.hasPassed(1)) {
        if (defenceCountTwo > 2) {
          led[138].setRGB( 50, 0, 0);
          led[139].setRGB( 50, 00, 0);
          FastLED.show();
        } else {
          led[138].setRGB( 220, 220, 0);
          led[139].setRGB( 220, 220, 0);
          FastLED.show();
        }

        defenceTwoShow = false;
      }
    }
    if (defenceOneShow == true) {
      if (defence1.hasPassed(1)) {
        if (defenceCountOne > 2) {
          led[3].setRGB( 50, 0, 0);
          led[4].setRGB( 50, 0, 0);
        } else {
          led[3].setRGB( 220, 220, 0);
          led[4].setRGB( 220, 220, 0);
          FastLED.show();
        }
        defenceOneShow = false;
      }
    }
    // start
    if (fireCase1 == 0 && fireCase2 == 0) {
      led[playerOneFirePosition].setRGB( playerOneFireFirst, 0, 0);
      led[playerTwoFirePosition].setRGB( 0 , 0, playerTwoFireFirst);
      led[playerTwoFirePosition - 1].setRGB( 0, 0, playerTwoFireSecond);
      led[playerOneFirePosition + 1].setRGB( playerOneFireSecond, 0, 0);
      // 1 start   ___ 2 not yet
    } else if (fireCase1 != 0 && fireCase2 == 0) {
      led[playerTwoFirePosition].setRGB( 0, 0, playerTwoFireFirst);
      led[playerTwoFirePosition - 1].setRGB( 0, 0, playerTwoFireSecond);
      if (bright.hasPassed(1)) {
        bright.restart();
        led[i].setRGB( playerOneFireSecond, 0, 0);
        led[i + 1].setRGB( playerOneFireSecond, 0, 0);
        FastLED.show();
        if (i <= 140) {
          i++;
        }
        if (i == 141 && defenceTwo == false) {
          for (int i = 0; i < NUM_LEDS; i++) {
            led[i].setRGB( 220, 0, 0);
            FastLED.show();
            delay(10);
          }
          playerTwoFireSecond = 0;
          playerOneFireSecond = 0;
          playerOneFireFirst = 0;
          playerTwoFireFirst = 0;
          fireCase2 = 0;
          fireCase1 = 0;
          k = 142;
          i = 0;
          defenceCountTwo = 0;
          defenceCountOne = 0;
        } else if (defenceTwo == true && defenceCountTwo < 2) {
          defenceCountTwo++;
          i = 0;
          player1.resetPlayer(playerOneFireSecond, playerOneFireFirst, fireCase1, defenceTwo, defenceTwoShow);
        }
      }
      // 2 start   ___ 1 not yet
    }  else if (fireCase2 != 0 && fireCase1 == 0) {
      led[playerOneFirePosition].setRGB( playerOneFireFirst, 0, 0);
      led[playerOneFirePosition + 1].setRGB( playerOneFireSecond, 0, 0);
      if (bright.hasPassed(1)) {
        bright.restart();
        led[k].setRGB( 0, 0, playerTwoFireSecond);
        led[k - 1].setRGB( 0, 0, playerTwoFireSecond);
        FastLED.show();
        if (k > 2) {
          k--;
        }
        if (k == 2 && defenceOne == false) {
          led[k].setRGB( 0, 0, playerTwoFireSecond);
          led[k - 1].setRGB( 0, 0, playerTwoFireSecond);
          for (int i = 0; i < NUM_LEDS; i++) {
            led[i].setRGB( 0, 0, 220);
            FastLED.show();
            delay(10);
          }
          playerTwoFireSecond = 0;
          playerOneFireSecond = 0;
          playerOneFireFirst = 0;
          playerTwoFireFirst = 0;
          fireCase2 = 0;
          fireCase1 = 0;
          k = 142;
          i = 0;
          defenceCountTwo = 0;
          defenceCountOne = 0;
        } else if (defenceOne == true && defenceCountOne < 2) {
          defenceCountOne ++;
          k = 142;
          player2.resetPlayer(playerTwoFireSecond, playerTwoFireFirst, fireCase2, defenceOne, defenceOneShow);
        }
      }
    }
    // both start already
    else if (fireCase2 != 0 && fireCase1 != 0) {
      if (bright.hasPassed(1)) {
        bright.restart();
        led[k].setRGB( 0, 0, playerTwoFireSecond);
        led[k - 1].setRGB( 0, 0, playerTwoFireSecond);
        led[i].setRGB( playerOneFireSecond, 0, 0);
        led[i + 1].setRGB( playerOneFireSecond, 0, 0);
        FastLED.show();
        if (k >= 3) {
          k--;
        }
        if (i <= 140) {
          i++;
        }
      }
      if (k == i || k == i - 1 || k == i + 1) {
        if (playerOneFireSecond == playerTwoFireSecond) {
          for (int jjj = 200; jjj > 0; jjj--) {
            led[i].setRGB( jjj, 0, 0);
            led[i + 1].setRGB( jjj, 0, 0);
            led[i + 2].setRGB( 0, 0, jjj);
            led[k + 3].setRGB( 0, 0, jjj);
            FastLED.show();
            delay(5);
          }
          playerTwoFireSecond = 0;
          playerOneFireSecond = 0;
          playerOneFireFirst = 0;
          playerTwoFireFirst = 0;
          fireCase2 = 0;
          fireCase1 = 0;
          k = 142;
          i = 0;
        }
        else if (playerOneFireSecond < playerTwoFireSecond) {
          for (int jjj = 200; jjj > 0; jjj--) {
            led[i].setRGB( jjj, 0, 0);
            led[i + 1].setRGB( jjj, 0, 0);
            led[i + 2].setRGB( jjj, 0, 0);
            led[i + 3].setRGB( jjj, 0, 0);
            FastLED.show();
            delay(5);
          }
          i = 0;
          player1.resetPlayer(playerOneFireSecond, playerOneFireFirst, fireCase1, defenceTwo, defenceTwoShow);
        }
        else if (playerOneFireSecond > playerTwoFireSecond) {
          for (int jjj = 200; jjj > 0; jjj--) {
            led[k].setRGB( 0, 0, jjj);
            led[k + 1].setRGB( 0, 0, jjj);
            led[k - 1].setRGB( 0, 0, jjj);
            led[k - 2].setRGB( 0, 0, jjj);
            FastLED.show();
            delay(5);
          }
          k = 142;
          player2.resetPlayer(playerTwoFireSecond, playerTwoFireFirst, fireCase2, defenceOne, defenceOneShow);
        }

      }
      if (defenceOne == true && defenceCountOne < 2) {
        defenceCountOne++;
        k = 142;
        player2.resetPlayer(playerTwoFireSecond, playerTwoFireFirst, fireCase2, defenceOne, defenceOneShow);
      }
      if (defenceTwo == true && defenceCountTwo < 2) {
        defenceCountTwo++;
        i = 0;
        player1.resetPlayer(playerOneFireSecond, playerOneFireFirst, fireCase1, defenceTwo, defenceTwoShow);
      }
    }
    FastLED.show();
  }
}// end loop

float filter(float rawValue, float weight, float lastValue)
{
  float result = weight * rawValue + (1.0 - weight) * lastValue;
  return result;
}
