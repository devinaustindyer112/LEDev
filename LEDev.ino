
#include <FastLED.h>
#include "./Parser.hpp"
#include "./JSONValue.hpp"
#include "./JSONObject.hpp"
#include "./String.hpp"
#include "./Utilities.hpp"

#define BAUD_RATE 19200
#define LED_PIN 13
#define NUM_LEDS 121
#define BRIGHTNESS 20
#define FRAMES_PER_SECOND 2
#define BPM 50
#define WAVE_LEN 10
#define BYTE_COUNT 3

#define MAX_INPUT 100

CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;

char serialString[100]; // Empty serial string variable
int stringIndex = 0;    // Index of serial string
bool stringComplete = false;

bool halt = false;

void setup()
{
  FastLED.clear();
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  // Sets up pallete for metor effect
  currentPalette = CRGBPalette16(CRGB::Blue, CRGB::Black);
  fill_palette(leds, NUM_LEDS, 0, 255 / WAVE_LEN, currentPalette);

  Serial.begin(BAUD_RATE);
  Serial.setTimeout(10000);
}

void loop()
{
  // The serial string has been parsed
  if (stringComplete)
  {
    // Process here
    Serial.print(serialString);

    // Serial.write(serialString);
    if(strcmp(serialString, "H") == 0){
      Serial.print("H");
      halt = true;
    } 
    else if(strcmp(serialString, "R") == 0) {
      Serial.print("R");
      halt = false;
    }

    serialString[0] = '\0';
    stringIndex = 0;
    stringComplete = false;
  }

  if (!halt)
  {
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    FastLED.show();
  }

  // https://docs.arduino.cc/built-in-examples/communication/SerialEvent
}

void serialEvent()
{
  while (Serial.available())
  {
    char inChar = (char)Serial.read();
    if (inChar == '\n')
    {
      stringComplete = true;
      serialString[stringIndex] = '\0';
    } else {
      serialString[stringIndex] = inChar;
    }
    stringIndex++;
  }
}

// // Serial communication
// if (Serial.available() > 0)
// {

//   byte data[BYTE_COUNT] = {};
//   Serial.readBytes(data, BYTE_COUNT);
//   unsigned long result = ((unsigned long)data[0] << 16) | ((unsigned long)data[1] << 8) | data[2]; // concatenate AA, BB, and CC to obtain the 24-bit value

//   delay(1000);

//   currentPalette = CRGBPalette16(result, CRGB::Black);
//   fill_palette(leds, NUM_LEDS, 0, 255 / WAVE_LEN, currentPalette);
// }

// // Setup sine wave
// int lowest = 50;
// int highest = 200;
// int position = beatsin16(BPM, lowest, highest);

// // Meteor effect
// for (int i = 0; i < NUM_LEDS; i++)
// {
//   int lastLED = NUM_LEDS - 1;
//   if (i == 0)
//   {
//     leds[lastLED] = leds[0];
//   }
//   else
//   {
//     leds[i - 1] = leds[i];
//   }
// }