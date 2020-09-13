/*
  Note: This example currently has very low performance on large displays (~38FPS refresh rate on 64x64)
  The Scrolling Layer refresh code is optimized if you use the new "GFX" Adafruit_GFX compatible layers instead.

  To update a SmartMatrix Library sketch to use Adafruit_GFX compatible layers:

  - Make sure you have the Adafruit_GFX Library installed in Arduino (you can use Arduino Library Manager)
  - add `#define SUPPORT_ADAFRUIT_GFX_LIBRARY` below (this is needed for any sketch to tell SmartMatrix Library that Adafruit_GFX is present, not just this sketch)
  - change the name of the ALLOCATE layer macros, adding "GFX_" before "LAYER":
    - change SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER() to SMARTMATRIX_ALLOCATE_BACKGROUND_GFX_LAYER()
    - change SMARTMATRIX_ALLOCATE_SCROLLING_LAYER() to SMARTMATRIX_ALLOCATE_SCROLLING_GFX_LAYER()
    - change SMARTMATRIX_ALLOCATE_INDEXED_LAYER() to SMARTMATRIX_ALLOCATE_INDEXED_GFX_LAYER()

  With the "GFX" layers you're no longer limited to the fonts built into the SmartMatrix Library.  You can use any of the
    fonts included in Adafruit_GFX, or add custom fonts
*/

//#define SUPPORT_ADAFRUIT_GFX_LIBRARY

// uncomment one line to select your MatrixHardware configuration - configuration header needs to be included before <SmartMatrix3.h>
//#include <MatrixHardware_ESP32_V0.h>    // This file contains multiple ESP32 hardware configurations, edit the file to define GPIOPINOUT (or add #define GPIOPINOUT with a hardcoded number before this #include)
//#include <MatrixHardware_KitV1.h>       // SmartMatrix Shield for Teensy 3 V1-V3
//#include <MatrixHardware_KitV4.h>       // SmartLED Shield for Teensy 3 V4
//#include <MatrixHardware_KitV4T4.h>     // Teensy 4 Wired to SmartLED Shield for Teensy 3 V4
//#include <MatrixHardware_T4Adapter.h>   // Teensy 4 Adapter attached to SmartLED Shield for Teensy 3 V4
//#include "MatrixHardware_Custom.h"      // Copy an existing MatrixHardware file to your Sketch directory, rename, customize, and you can include it like this
#include <SmartMatrix3.h>

#define COLOR_DEPTH 24                  // known working: 24, 48 - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24
const uint16_t kMatrixWidth = 32;        // known working: 32, 64, 96, 128, 256
const uint16_t kMatrixHeight = 32;       // known working: 16, 32, 48, 64, 128
const uint8_t kRefreshDepth = 36;       // known working: 24, 36, 48 (on Teensy 4.x: 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48)
const uint8_t kDmaBufferRows = 4;       // known working: 2-4, use 2 to save memory, more to keep from dropping frames and automatically lowering refresh rate
const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN;   // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels
const uint8_t kMatrixOptions = (SMARTMATRIX_OPTIONS_NONE);      // see http://docs.pixelmatix.com/SmartMatrix for options

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);

#ifdef SUPPORT_ADAFRUIT_GFX_LIBRARY
  const uint8_t kScrollingLayerOptions = (SM_GFX_MONO_OPTIONS_NONE);
  SMARTMATRIX_ALLOCATE_SCROLLING_GFX_LAYER(scrollingLayer1, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
  SMARTMATRIX_ALLOCATE_SCROLLING_GFX_LAYER(scrollingLayer2, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
  SMARTMATRIX_ALLOCATE_SCROLLING_GFX_LAYER(scrollingLayer3, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
  SMARTMATRIX_ALLOCATE_SCROLLING_GFX_LAYER(scrollingLayer4, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
  SMARTMATRIX_ALLOCATE_SCROLLING_GFX_LAYER(scrollingLayer5, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
#else
  const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);
  SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(scrollingLayer1, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
  SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(scrollingLayer2, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
  SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(scrollingLayer3, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
  SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(scrollingLayer4, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
  SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(scrollingLayer5, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
#endif

void setup() {
  matrix.addLayer(&scrollingLayer1); 
  matrix.addLayer(&scrollingLayer2); 
  matrix.addLayer(&scrollingLayer3); 
  matrix.addLayer(&scrollingLayer4); 
  matrix.addLayer(&scrollingLayer5); 
  matrix.begin();

  scrollingLayer1.setMode(wrapForward);
  scrollingLayer2.setMode(bounceForward);
  scrollingLayer3.setMode(bounceReverse);
  scrollingLayer4.setMode(wrapForward);
  scrollingLayer5.setMode(bounceForward);

  scrollingLayer1.setColor({0xff, 0xff, 0xff});
  scrollingLayer2.setColor({0xff, 0x00, 0xff});
  scrollingLayer3.setColor({0xff, 0xff, 0x00});
  scrollingLayer4.setColor({0x00, 0x00, 0xff});
  scrollingLayer5.setColor({0xff, 0x00, 0x00});

  scrollingLayer1.setSpeed(10);
  scrollingLayer2.setSpeed(20);
  scrollingLayer3.setSpeed(40);
  scrollingLayer4.setSpeed(80);
  scrollingLayer5.setSpeed(120);

  scrollingLayer1.setFont(gohufont11b);
  scrollingLayer2.setFont(gohufont11);
  scrollingLayer3.setFont(font8x13);
  scrollingLayer4.setFont(font6x10);
  scrollingLayer5.setFont(font5x7);

  scrollingLayer4.setRotation(rotation270);
  scrollingLayer5.setRotation(rotation90);

  scrollingLayer1.setOffsetFromTop((kMatrixHeight/2) - 5);
  scrollingLayer2.setOffsetFromTop((kMatrixHeight/4) - 5);
  scrollingLayer3.setOffsetFromTop((kMatrixHeight/2 + kMatrixHeight/4) - 5);
  scrollingLayer4.setOffsetFromTop((kMatrixWidth/2 + kMatrixWidth/4) - 5);
  scrollingLayer5.setOffsetFromTop((kMatrixWidth/2 + kMatrixWidth/4) - 5);

  scrollingLayer1.start("Layer 1", -1);
  scrollingLayer2.start("Layer 2", -1);
  scrollingLayer3.start("Layer 3", -1);
  scrollingLayer4.start("Layer 4", -1);
  scrollingLayer5.start("Layer 5", -1);
}

void loop() {
  Serial.print("Refresh Rate: ");
  Serial.println(matrix.getRefreshRate());
  delay(1000);
}
