#include <Adafruit_NeoPixel.h>

#define PIN 6
#define Pixels 36

Adafruit_NeoPixel strip = Adafruit_NeoPixel(Pixels, PIN, NEO_GRB + NEO_KHZ800);

float dimForce = 0.05;
uint16_t rainMax = 100;
uint16_t rainIntensity = 1;
float fadeRate = 1.005;

uint16_t halfPixels = Pixels * 0.5;
//rainDropEdgeBegin 0  -
uint16_t rainDropEdgeBegin = 9;
uint16_t rainDropEdgeEnd = halfPixels;

uint16_t sun[3] = {252, 236, 60};
uint16_t night[3] = {30, 30, 180};

uint16_t initialRed = night[0];
uint16_t initialGreen = night[1];
uint16_t initialBlue = night[2];

uint16_t targetRed = 1 + floor(initialRed * dimForce);
uint16_t targetGreen = 1 + floor(initialGreen * dimForce);
uint16_t targetBlue = 1 + floor(initialBlue * dimForce);


// windSpeed 0-9
uint16_t windSpeed = 0;

float redStates[Pixels];
float blueStates[Pixels];
float greenStates[Pixels];

void setup() {
  strip.begin();
  strip.setBrightness(255);
  // Initialize all pixels to 'off'
  for (uint16_t l = 0; l < Pixels; l++) {
    redStates[l] = initialRed;
    greenStates[l] = initialGreen;
    blueStates[l] = initialBlue;
  }

  strip.show();

}

void loop () {
  updateRain();
  strip.show();

}


void updateRain() {
  rainDropEdgeBegin += windSpeed;
  rainDropEdgeEnd += windSpeed;
  uint16_t margin = 40;
  
  if (random(rainMax) <= rainIntensity) {
    uint16_t i = random(halfPixels);
    if (i >= rainDropEdgeBegin && i <= rainDropEdgeEnd)
      i += halfPixels ;

    if (redStates[i] >= (initialRed - margin) && greenStates[i] >= (initialGreen - margin) && blueStates[i] >= (initialBlue - margin)) {
      redStates[i] = targetRed;
      greenStates[i] = targetGreen;
      blueStates[i] = targetBlue;
    }
  }

  for (uint16_t l = 0; l < Pixels; l++) {
    if (redStates[l] <= initialRed || greenStates[l] <= initialRed || blueStates[l] <= initialRed) {
      strip.setPixelColor(l, redStates[l], greenStates[l], blueStates[l]);

      if (redStates[l] < initialRed) {
        redStates[l] = redStates[l] * fadeRate ;
        if (redStates[l] > 255) {
          redStates[l] = 255;
        }
      } else {
        redStates[l] = initialRed;
      }

      if (greenStates[l] < initialGreen) {
        greenStates[l] =  greenStates[l] * fadeRate ;
        if (greenStates[l] > 255) {
          greenStates[l] = 255;
        }
      } else {
        greenStates[l] = initialGreen;
      }

      if (blueStates[l] < initialBlue) {
        blueStates[l] =  blueStates[l] * fadeRate ;
        if (blueStates[l] > 255) {
          blueStates[l] = 255;
        }
      } else {
        blueStates[l] = initialBlue;
      }

    } else {
      strip.setPixelColor(l, initialRed, initialGreen, initialBlue);
    }
  }
}

