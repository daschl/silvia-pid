#include <Adafruit_GFX.h>
#include <SPI.h>

#include "TSIC.h"
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

// ----------------------------------
// --- Temp Sensor Initialization ---
// ----------------------------------

#define TEMP_SIGNAL_PIN 16
TSIC TempSensor(TEMP_SIGNAL_PIN);

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
  delay(1000);
  display.fillScreen(0xFFFF);
}

// ---------------------
// --- Main Run Loop ---
// ---------------------

void loop() {
  float currentTemp = currentSensorTemp();
  renderOverview(currentTemp);
  delay(1000);
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

void renderOverview(float currentTemp) {
  display.setCursor(0, 0);
  display.setTextColor(0x0000, 0xFFFF);
  display.setTextSize(1);
  display.print("Temp: ");
  display.print(currentTemp);
}

// -----------------------------
// --- Temp Sensor Functions ---
// -----------------------------
float currentSensorTemp() {
  uint16_t tempRaw = 0;
  TempSensor.getTemperature(&tempRaw);
  float tempCelsius = TempSensor.calc_Celsius(&tempRaw);

  #ifdef DEBUG
  Serial.print("Current Sensor Temp: Raw=");
  Serial.print(tempRaw);
  Serial.print(", Celsius=");
  Serial.println(tempCelsius);
  #endif

  return tempCelsius;
}

// -----------------------
// --- Debug Functions ---
// -----------------------
void logInit() {
  #ifdef DEBUG
  Serial.begin(SERIAL_BAUD);
  Serial.println("");
  Serial.println("Starting Siliva PID");
  #endif
}
