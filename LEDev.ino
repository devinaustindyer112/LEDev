
#include <FastLED.h>
#include "./String.hpp"

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
int stringIndex = 0;

void setup()
{
  FastLED.clear();
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  // Sets up pallete for metor effect
  currentPalette = CRGBPalette16(CRGB::Blue, CRGB::Black);
  fill_palette(leds, NUM_LEDS, 0, 255 / WAVE_LEN, currentPalette);

  Serial.begin(9600);
  Serial.setTimeout(100);
}

void loop()
{
  if (Serial.available() > 0)
  {
    while (Serial.available() > 0)
    {
      const byte inByte = Serial.read();
      Serial.print(inByte);
      processIncomingByte(inByte);
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

  // // Set delay and show
  // FastLED.delay(1000 / FRAMES_PER_SECOND);
  // FastLED.show();
}

void processIncomingByte(const byte inByte)
{
  static char input_line[MAX_INPUT];
  static unsigned int input_pos = 0;

  if (inByte == '\n')
  {
    input_line[input_pos] = '\0';
    input_pos = 0;
    return;
  }

  if (input_pos < (MAX_INPUT - 1))
  {
    input_line[input_pos++] = inByte;
  }
}