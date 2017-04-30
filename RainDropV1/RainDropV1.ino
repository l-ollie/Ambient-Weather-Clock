#include <Adafruit_NeoPixel.h>

#define PIN 6
#define Pixels 36

Adafruit_NeoPixel strip = Adafruit_NeoPixel(Pixels, PIN, NEO_GRB + NEO_KHZ800);

float dimForce = 0.05;
uint16_t rainMax = 100;
uint16_t rainIntensity = 1;

uint16_t halfPixels = Pixels * 0.5;
//rainDropEdgeBegin 0  -
uint16_t rainDropEdgeBegin = 9;
uint16_t rainDropEdgeEnd = halfPixels;

uint16_t sun[3] = {252, 236, 60};
uint16_t night[3] = {30, 30, 180};
uint16_t day[3] = {110, 110, 255};

// Exist out of the temparature / day and night cicle
uint16_t layer1RGB[Pixels][3];
// Exist out  dim force
float layer2RGB[Pixels];
float initialDimForce = 0.2;
float fadeRate = 0.0009;

// windSpeed 0-9
uint16_t windSpeed = 0;

float redStates[Pixels];
float blueStates[Pixels];
float greenStates[Pixels];

void setup() {
  strip.begin();
  strip.setBrightness(255);
  
  // Initialize layer2RGB
  for (uint16_t l = 0; l < Pixels; l++) {
    layer2RGB[l] = 1.0;
  }

  strip.show();
}

void loop () {
  // define first layer
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
  rainDropEdgeBegin += _windSpeed;
  rainDropEdgeEnd += _windSpeed;
  uint16_t margin = 40;

  if (random(rainMax) <= rainIntensity) {
    uint16_t i = random(halfPixels);
    if (i >= rainDropEdgeBegin && i <= rainDropEdgeEnd)
      i += halfPixels ;

    if (layer2RGB[i] >= 1) {
      layer2RGB[i] = initialDimForce;
    }
  }

  for (uint16_t l = 0; l < Pixels; l++) {
    if (layer2RGB[l] < 1) {
    layer1RGB[l][0] *= layer2RGB[l];
    layer1RGB[l][1] *= layer2RGB[l];
    layer1RGB[l][2] *= layer2RGB[l];
    
    layer2RGB[l] += (layer2RGB[l] * 0.00001) + fadeRate;
    
      strip.setPixelColor(l, layer1RGB[l][0], layer1RGB[l][1], layer1RGB[l][2]);
    }
  }
}
