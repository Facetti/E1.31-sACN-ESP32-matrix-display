
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include <ESPAsyncE131.h>

#define PANEL_WIDTH 64
#define PANEL_HEIGHT 64  // Panel height of 64 will required PIN_E to be defined.
#define PANELS_NUMBER 2  // Number of chained panels, if just a single panel, obviously set to 1

#define PIN_R1 32
#define PIN_B1 33
#define PIN_R2 25
#define PIN_B2 26
#define PIN_A 27
#define PIN_C 14
#define PIN_CLK 12
#define PIN_OE 13

#define PIN_G1 19
//GND
#define PIN_G2 5
#define PIN_E 17
#define PIN_B 16
#define PIN_D 4
#define PIN_LAT 2
//GND

#define PANE_WIDTH ((PANEL_WIDTH) * (PANELS_NUMBER))
#define PANE_HEIGHT PANEL_HEIGHT

#define UNIVERSE 1                   // First DMX Universe to listen for
#define UNIVERSE_COUNT PANE_HEIGHT  // Total number of Universes to listen for, starting at UNIVERSE

// Wifi credentials
const char ssid[] = "SSID";            // Replace with your SSID
const char passphrase[] = "PASSWORD";  // Replace with your WPA2 passphrase

// placeholder for the matrix object
MatrixPanel_I2S_DMA *display = nullptr;

// ESPAsyncE131 instance with UNIVERSE_COUNT buffer slots
ESPAsyncE131 e131(UNIVERSE_COUNT);

void setup() {
  Serial.begin(115200);
  delay(5000);
  Serial.print(F("\nStarting (\n"));


  // Setup WiFi
  WiFi.mode(WIFI_STA);

  Serial.println("");
  Serial.print(F("Connecting to "));
  Serial.print(ssid);

  if (passphrase != NULL)
    WiFi.begin(ssid, passphrase);
  else
    WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print(F("Connected with IP: "));
  Serial.println(WiFi.localIP());

  // Setup e131
  //if (e131.begin(E131_UNICAST))                               // Listen via Unicast
  if (e131.begin(E131_MULTICAST, UNIVERSE, UNIVERSE_COUNT))  // Listen via Multicast
    Serial.println(F("Listening for e131 data..."));
  else
    Serial.println(F("*** e131.begin failed ***"));

  // Setup display
  HUB75_I2S_CFG mxconfig;
  mxconfig.mx_width = PANEL_WIDTH;
  mxconfig.mx_height = PANEL_HEIGHT;
  mxconfig.chain_length = PANELS_NUMBER;

  mxconfig.gpio.r1 = PIN_R1;  //left row
  mxconfig.gpio.b1 = PIN_B1;
  mxconfig.gpio.r2 = PIN_R2;
  mxconfig.gpio.b2 = PIN_B2;
  mxconfig.gpio.a = PIN_A;
  mxconfig.gpio.c = PIN_C;
  mxconfig.gpio.clk = PIN_CLK;
  mxconfig.gpio.oe = PIN_OE;

  mxconfig.gpio.g1 = PIN_G1;  //right row
  // GND
  mxconfig.gpio.g2 = PIN_G2;
  mxconfig.gpio.e = PIN_E;
  mxconfig.gpio.b = PIN_B;
  mxconfig.gpio.d = PIN_D;
  mxconfig.gpio.lat = PIN_LAT;
  // GND

  // OK, now we can create our matrix object
  display = new MatrixPanel_I2S_DMA(mxconfig);
  if (not display->begin())
    Serial.println("*** display memory allocation failed ***");
  display->clearScreen();
  display->setBrightness8(192);  // range is 0-255, 0 - 0%, 255 - 100%
  Serial.println(") Start finished. ");
}


void loop() {
  e131_packet_t packet;
  
  if (!e131.isEmpty()) {
    e131.pull(&packet);  // Pull packet from ring buffer
    for (int x = 0; x < PANE_WIDTH; x++)
      display->drawPixelRGB888(x, htons(packet.universe, packet.property_values[1 + 3 * x], packet.property_values[2 + 3 * x], packet.property_values[3 + 3 * x]);
  }
}
