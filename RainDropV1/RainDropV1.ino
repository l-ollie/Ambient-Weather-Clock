#include <Adafruit_NeoPixel.h>

#define PIN 6
#define Pixels 36

Adafruit_NeoPixel strip = Adafruit_NeoPixel(Pixels, PIN, NEO_GRB + NEO_KHZ800);

float dimForce = 0.05;
const uint16_t rainMax = 300;
// rainIntensity 0 - 50
uint16_t rainIntensity = 50;

const uint16_t halfPixels = Pixels * 0.5;

uint16_t rainDropEdgeBegin = 9;
uint16_t rainDropEdgeEnd = halfPixels;

const uint16_t sun[3] = {252, 236, 60};
const uint16_t night[3] = {30, 30, 180};
const uint16_t day[3] = {110, 110, 255};

// Exist out of the temparature / day and night cicle
uint16_t layer1RGB[Pixels][3];
// Exist out  dim force
float layer2RGB[Pixels];
const float initialDimForce = 0.2;
const float fadeRate = 0.0009;

// windSpeed 0-9
uint16_t windSpeed = 0;

void setup() {
  strip.begin();
  strip.setBrightness(55);

  // Initialize layer2RGB
  for (uint16_t l = 0; l < Pixels; l++) {
    layer2RGB[l] = 1.0;
  }

  strip.show();
}

void loop () {
  //define first layer
  for (uint16_t l = 0; l < Pixels; l++) {
    layer1RGB[l][0] = day[0];
    layer1RGB[l][1] = day[1];
    layer1RGB[l][2] = day[2];
    strip.setPixelColor(l, layer1RGB[l][0], layer1RGB[l][1], layer1RGB[l][2]);
  }

  updateRain(windSpeed);
  strip.show();
}

void updateRain(uint16_t _windSpeed) {
  //calculate the edge for the raindrops
  rainDropEdgeBegin += _windSpeed;
  rainDropEdgeEnd += _windSpeed;

  //make a raindrop
  if (random(rainMax) <= rainIntensity) {
    uint16_t i = random(halfPixels);
    if (i >= rainDropEdgeBegin && i <= rainDropEdgeEnd)
      i += halfPixels ;
    //if no drop is fading, add raindrop
    if (layer2RGB[i] >= 1) {
      layer2RGB[i] = initialDimForce;
    }
  }

  for (uint16_t l = 0; l < Pixels; l++) {
    if (layer2RGB[l] < 1) {
      //apply fading to led
      layer1RGB[l][0] *= layer2RGB[l];
      layer1RGB[l][1] *= layer2RGB[l];
      layer1RGB[l][2] *= layer2RGB[l];

      //substract fadingforce exponantial
      layer2RGB[l] += (layer2RGB[l] * 0.00001) + fadeRate;
      strip.setPixelColor(l, layer1RGB[l][0], layer1RGB[l][1], layer1RGB[l][2]);
    }
  }
}

void defineLayer1RGB(){


}

