#include <FastLED.h>
// #include <JFA.hpp>
#include <Test.h>
// #include <String.hpp>

#define BAUD_RATE 115200
#define LED_PIN 13
#define NUM_LEDS 121
#define BRIGHTNESS 20
#define FRAMES_PER_SECOND 20
#define BPM 50
#define WAVE_LEN 10
#define BYTE_COUNT 3
#define MAX_INPUT 100

CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;

char serialString[MAX_INPUT] = "";
bool halt = false;

void setup()
{
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  // Set up palette for meteor effect
  currentPalette = CRGBPalette16(CRGB::Blue, CRGB::Black);
  fill_palette(leds, NUM_LEDS, 0, 255 / WAVE_LEN, currentPalette);

  Serial.begin(BAUD_RATE);
  Serial.setTimeout(10000);
}

void loop()
{
  if (Serial.available())
  {
    processSerialData();
  }

  if (!halt)
  {
    FastLED.show();
  }
}

void processSerialData()
{
  while (Serial.available() > 0)
  {
    char inChar = (char)Serial.read();
    if (inChar == '\n')
    {
      setEffects(serialString);
      serialString[0] = '\0';
    }
    else
    {
      strncat(serialString, &inChar, 1);
    }
  }
}

void setEffects(const char *config)
{
  //   // halt FastLED operations while
  //   // processing serial data
  //   if (strCompare(config, "H"))
  //   {
  //     halt = true;
  //     Serial.write("H");
  //     return;
  //   }

  //   Parser parser(config);
  //   JSONObject obj = parser.parseObject();
  //   JSONValue effect = obj.get("effect");
  //   JSONValue color = obj.get("color");

  //   halt = false;
  //   Serial.write(effect.string.str);
  //   Serial.write(color.string.str);
}

// Logic for meteor effect below

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