#include <Adafruit_NeoPixel.h>

/* Define pin number constants (use #define to save program space, as these will be filled in at compile time) */
#define potPin 10
#define photoPin A9
#define neopixelPin 12
#define buzzerPin 2

#define brightnessRawMin 25 // Minimum brightness value to read (before constraining)
#define brightnessRawMax 821 // Maximum brightness value to read (before constraining)

#define numPixels 3 // How many neopixels are in the chain

#define potRawMin 4 // Minimum potentiometer value to read (before constraining)
#define potRawMax 1018 // Maximum potentiometer value to read (before constraining)


uint8_t potValue, ambientLight;

Adafruit_NeoPixel pixels(numPixels, neopixelPin, NEO_GRB + NEO_KHZ800);
uint8_t R, G, B;
bool lastOn;

void setup()
{
  pinMode(potPin, INPUT);
  pinMode(photoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  lastOn = true;

  pixels.begin();
}

void loop()
{
  /* Get sensor values */
  readPot();
  readPhoto();

  generateRGB();

  /* Set neopixel color based on input */
  pixels.clear();
  Serial.print("Ambient light");
  Serial.println(ambientLight);
  Serial.print("raw light");
  Serial.println(analogRead(photoPin));
  if (ambientLight < 100) { // Turn neopixels on
    for (int i = 0; i < numPixels; i++) {
      pixels.setPixelColor(i, R/2, G/2, B/2);
    }
    if (lastOn == false) {
      tone(buzzerPin, 1000, 1000);
      lastOn = true;
    }

  }

      if (lastOn == true && ambientLight >=100) {
      tone(buzzerPin, 1000, 1000);
      lastOn = false;
    }

  pixels.show(); // Update the neopixel
  delay(1000);
}


/* Read potentiometer value. Maps raw data to an 8-bit unsigned integer, then constrains any outliers to that same range */
void readPot()
{
  int rawPotValue = analogRead(potPin);
  potValue = constrain(map(rawPotValue, potRawMin, potRawMax, 0, 255), 0, 255);
}

/* Read Photoresistor value. Constrains the raw input to specified maximums and minimums, then maps to an 8-bit integer. */
void readPhoto()
{
  int rawBrightness = analogRead(photoPin);
  rawBrightness = constrain(rawBrightness, brightnessRawMin, brightnessRawMax);
  ambientLight = map(rawBrightness, brightnessRawMin, brightnessRawMax, 0, 255);
}

/* Generate an RGB value based on potentiometer value. As the G value increases, the B value decreases. (Yellow to magenta gradient)*/
void generateRGB()
{
  R = 255;
  G = potValue;
  B = 255 - potValue;
}

