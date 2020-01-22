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


float speedPlayer1 = 0;
float speedPlayer2 = 0;
float gravity = 0.009;

float color50 = 90;
float color20 = 60;

float fade = 0.0;


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
// ---------------------------------player 1------------------------------------------
int OnePlayerPosition = 6;

float OneFireFirstPosition = 7;
float OneFireSecondPosition = 8;

float OnePlayerFireFirst = 0.0;
float OnePlayerFireSecond = 0.0;

int OneEnergyPlayer = 5;

bool OnefireCase = false;


Player player1(OnePlayerPosition, OneFireFirstPosition, OneFireSecondPosition, OnePlayerFireFirst, OnePlayerFireSecond, OneEnergyPlayer);

// ---------------------------------player 2------------------------------------------
int TwoPlayerPosition = 137;

float TwoFireFirstPosition = 136;
float TwoFireSecondPosition = 135;

float TwoPlayerFireFirst = 0.0;
float TwoPlayerFireSecond = 0.0;

int TwoEnergyPlayer = 5;


Player player2(TwoPlayerPosition, TwoFireFirstPosition, TwoFireSecondPosition, TwoPlayerFireFirst, TwoPlayerFireSecond, TwoEnergyPlayer);




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

    if (color50 < 90 && color20 < 60) {
      color50 += 0.4;
      color20 += 0.2;
    } else {
      color50 = 0;
      color20 = 0;
    }

    if (player1.effect3 == true) {
      if (player2.playerFireSecondC < 180 || player2.playerFireSecondC > 190) {
        player2.energyPlayerC = player2.energyPlayerC - 1;
        player1.resetPlayer();
    //    fade = 0.0;
        meteorRain(0xff,0,0,10, 64, true, 10, 1);
      } else if (player1.fireFirstPositionC > 140 && player2.playerFireSecondC > 180 && player2.playerFireSecondC < 190) {

        player1.resetPlayer();
        player2.effect3 = true;
      }
    } else if (player2.effect3 == true) {
   //   player2.fireFirstPositionC = player2.fireFirstPositionC - player2.speedC;
  //    player2.speedC = player2.speedC + gravity;
      if (player1.playerFireSecondC < 180 || player1.playerFireSecondC > 190) {
        player1.energyPlayerC = player1.energyPlayerC - 1;
        player2.resetPlayer();
   //     fade = 0.0;
        meteorRain(0,0,0xff,10, 64, true, 10, 2);
      } else if ( player2.fireFirstPositionC < 4 && player1.playerFireSecondC > 180 && player1.playerFireSecondC < 190) {
        player2.resetPlayer();
        player1.effect3 = true;
      }
    } else {
      player1.playShow(sensorWertA, sensorWertB);
      player2.playShow(sensorWertC, sensorWertD);
    }
  }
  //DRAW FRAME
  if (cNextFrame.hasPassed((1000 * 1000) / fps)  ) { //milliseconds chrono -> triggers on every frame...
    cNextFrame.restart();
    FastLED.clear();

    int onePos = (int) player1.fireFirstPositionC;
    int twoPos = (int) player2.fireFirstPositionC;


    led[onePos].setRGB(player1.playerFireFirstC, 0, 0);
    led[onePos + 1].setRGB(player1.playerFireSecondC, 0, 0);
    led[twoPos].setRGB(0, 0, player2.playerFireFirstC);
    led[twoPos - 1].setRGB(0, 0, player2.playerFireSecondC);
    if(player2.effect3 == true){
     led[twoPos + 1].setRGB(0, 0, 150 * fade);
      led[twoPos + 2].setRGB(0, 0, 120 * fade);
       led[twoPos + 3].setRGB(0, 0, 100 * fade);
          led[twoPos + 4].setRGB(0, 0, 80 * fade);
      led[twoPos + 5].setRGB(0, 0, 60 * fade);
       led[twoPos + 6].setRGB(0, 0, 20 * fade);
      }

          if(player1.effect3 == true){
     led[onePos - 1].setRGB(150 * fade, 0, 0);
      led[onePos - 2].setRGB(120 * fade, 0, 0);
       led[onePos - 3].setRGB(100 * fade, 0, 0);
          led[onePos - 4].setRGB(80 * fade, 0,0);
      led[onePos - 5].setRGB(60 * fade, 0,0);
       led[onePos - 6].setRGB(20 * fade, 0,0);
      }

    switch (player1.energyPlayerC) {
      case 5:
        led[0].setRGB( color50, 0, 0);
        led[1].setRGB( color50, color20, 0);
        led[2].setRGB( color50, color50, 0);
        led[3].setRGB( color20 , color50, 0);
        led[4].setRGB( 0, color50, 0);

        break;
      case 4:
        led[0].setRGB( color50, 0, 0);
        led[1].setRGB( color50, color20, 0);
        led[2].setRGB( color50, color50, 0);
        led[3].setRGB( color20 , color50, 0);
        break;
      case 3:
        led[0].setRGB( color50, 0, 0);
        led[1].setRGB( color50, color20, 0);
        led[2].setRGB( color50, color50, 0);
        break;
      case 2:
        led[0].setRGB( color50, 0, 0);
        led[1].setRGB( color50, color20, 0);
        break;
      case 1:
        led[0].setRGB( color20, 0, 0);
        break;
      case 0:
        for (int i = 0; i < 200; i++) {
          fill_solid( led, NUM_LEDS, CRGB(0, 0, i));
          FastLED.show();
          delay(10);
        }
        for (int i = 0; i < NUM_LEDS; i++) {
          fill_rainbow(led, i, 0, 5);
          FastLED.show();
          delay(10);
        }
        player2.resetPlayerNewGame();
        player1.resetPlayerNewGame();
        break;
    }
    switch (player2.energyPlayerC) {
      case 5:
        led[143].setRGB( color50, 0, 0);
        led[142].setRGB( color50, color20, 0);
        led[141].setRGB( color50, color50, 0);
        led[140].setRGB( color20 , color50, 0);
        led[139].setRGB( 0, color50, 0);

        break;
      case 4:
        led[143].setRGB( color50, 0, 0);
        led[142].setRGB( color50, color20, 0);
        led[141].setRGB( color50, color50, 0);
        led[140].setRGB( color20 , color50, 0);
        break;
      case 3:
        led[143].setRGB( color50, 0, 0);
        led[142].setRGB( color50, color20, 0);
        led[141].setRGB( color50, color50, 0);
        break;
      case 2:
        led[143].setRGB( color50, 0, 0);
        led[142].setRGB( color50, color20, 0);
        break;
      case 1:
        led[143].setRGB( color50, 0, 0);
        break;
      case 0:
        for (int i = 0; i < 200; i++) {
          fill_solid( led, NUM_LEDS, CRGB(i, 0, 0));
          FastLED.show();
          delay(10);
        }
        for (int i = 0; i < NUM_LEDS; i++) {
          fill_rainbow(led, i, 0, 5);
          FastLED.show();
          delay(10);
        }
        player2.resetPlayerNewGame();
        player1.resetPlayerNewGame();
        break;
    }

    FastLED.show();
  }
}// end loop

float filter(float rawValue, float weight, float lastValue)
{
  float result = weight * rawValue + (1.0 - weight) * lastValue;
  return result;
}

void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   led[Pixel].r = red;
   led[Pixel].g = green;
   led[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay, int player) {  
  setAll(0,0,0);

  if(player == 1){
      for(int i = 0; i < NUM_LEDS; i++) {
   
   
    // fade brightness all LEDs one step
    for(int j=0; j<NUM_LEDS; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
   
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      }
    }
   
    showStrip();
    delay(SpeedDelay);
  }
    } else{
        for(int i = NUM_LEDS; i > 1; i--) {
   
   
    // fade brightness all LEDs one step
    for(int j=0; j<NUM_LEDS; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
   
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      }
    }
   
    showStrip();
    delay(SpeedDelay);
  }
      }
}

void fadeToBlack(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
   
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
   
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   led[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}
// -------------------------------Fire -----------------------------------------------
void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[NUM_LEDS];
  int cooldown;
 
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);
   
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
 
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
   
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  showStrip();
  delay(SpeedDelay);
}

void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    setPixel(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    setPixel(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}
