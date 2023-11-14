#include <FastLED.h>
#include <jfa.h>

#define BAUD_RATE 115200
#define LED_PIN 13
#define NUM_LEDS 121
#define BRIGHTNESS 20
#define DEFAULT_FPS 20
#define BPM 50
#define WAVE_LEN 10
#define BYTE_COUNT 3
#define MAX_INPUT 100

CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
char serialString[MAX_INPUT] = "";
bool halted = false;

char currentEffect[MAX_INPUT] = "meteor";
int framesPerSecond = DEFAULT_FPS;

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

  if (!halted)
  {
    int lowest = 50;
    int highest = 200;
    int position = beatsin16(BPM, lowest, highest);

    if (strCompare(currentEffect, "meteor"))
    {
      // Meteor effect
      for (int i = 0; i < NUM_LEDS; i++)
      {
        int lastLED = NUM_LEDS - 1;
        if (i == 0)
        {
          leds[lastLED] = leds[0];
        }
        else
        {
          leds[i - 1] = leds[i];
        }
      }

      FastLED.delay(1000 / framesPerSecond);
      FastLED.show();
    }
  } 
}

void processSerialData()
{
  while (Serial.available() > 0)
  {
    char inChar = (char)Serial.read();
    if (inChar == '\n')
    {
      processString(serialString);
      serialString[0] = '\0';
    }
    else
    {
      strncat(serialString, &inChar, 1);
    }
  }
}

void processString(char *str)
{
  // halt FastLED operations
  if (!halted)
  {
    halted = true;
    Serial.write("H");
    return;
  }

  setEffects(str);
}

void setEffects(const char *config)
{
  Parser parser(config);
  JSONObject obj = parser.parseObject();
  JSONValue effect = obj.get("effect");

  // This breaks. JFA probably isn't handling cases where the
  // value doesn't exist appropriately.
  //
  // JSONValue fps = obj.get("fps");
  // framesPerSecond = parseInt(fps.string.str);

  Serial.write("F");

  strcpy(currentEffect, effect.string.str);
  halted = false;

  Serial.write("E");
}

int parseInt(const char *str)
{
  int result = 0;
  int len = strlen(str);
  for (int i = 0; i < len; i++)
  {
    result = result * 10 + (str[i] - '0');
  }

  return result;
}