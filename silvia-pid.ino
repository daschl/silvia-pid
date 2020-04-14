#include <Adafruit_GFX.h>
#include <SPI.h>

#include "Adafruit_SSD1351.h"
#include "bitmaps.h"

// ------------------------
// --- Global Constants ---
// ------------------------

#define DEBUG             1
#define SERIAL_BAUD  115200

#define MAJOR_VERSION     0
#define MINOR_VERSION     0
#define PATCH_VERSION     1

// ------------------------------
// --- Display Initialization ---
// ------------------------------

#define DISPLAY_DC_PIN    4
#define DISPLAY_CS_PIN    2
#define DISPLAY_RST_PIN   5

#define DISPLAY_WIDTH   128
#define DISPLAY_HEIGHT  128

Adafruit_SSD1351 display = Adafruit_SSD1351(
  DISPLAY_WIDTH, 
  DISPLAY_HEIGHT, 
  &SPI, 
  DISPLAY_CS_PIN, 
  DISPLAY_DC_PIN, 
  DISPLAY_RST_PIN
);

// -------------
// --- Setup ---
// -------------

void setup() {
  logInit();
  displayInit();
  renderBootLogo();
}

// ---------------------
// --- Main Run Loop ---
// ---------------------

void loop() {

}

// -------------------------
// --- Display Functions ---
// -------------------------

// Initializes the display
void displayInit() {
  display.begin();
}

// Renders the boot logo with version
void renderBootLogo() {
  display.fillScreen(0xFFFF);
  display.drawRGBBitmap(17,17, bootLogo, 94, 94);
}

// -----------------------
// --- Debug Functions ---
// -----------------------
void logInit() {
  #ifdef DEBUG
  Serial.begin(SERIAL_BAUD);
  Serial.println("Starting Siliva PID");
  #endif
}
