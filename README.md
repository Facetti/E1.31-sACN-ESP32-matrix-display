# ESP32 with matrix display receiving E.131/sACN data via WiFi 
This project shows how to play a video on a Windows PC, sending the data traffic in E1.31 sACN (DMX over Ethernet) protocol and receive it via WLAN on a ESP32 to display it on two chained 64x64 LED matrix displays.

In E1.31 there is a concept of universes, which is a data block with max 512 bytes.
To keep it simple, we use one univers is used per line of the matrix display. 
Because we have three bytes (RGB) per pixel, we can have max 170 (512/3) LEDs horizontally. This is sufficient for two chained 64x64 matrixes (2 * 64 = 128; 128 * 3 = 384 bytes).

## Requirements
### Hardware
* ESP32
* 64x64 LED matrix display connected to the ESP32
### Arduino IDE (2.3.2) with installed libraries
* FastLED - https://github.com/FastLED/FastLED
* ESP32 HUB75 LED MATRIX PAMDEL DMA - https://github.com/mrcodetastic/ESP32-HUB75-MatrixPanel-DMA
* ESP Async E1.31 https://github.com/forkineye/ESPAsyncE131
### Windows (10) PC with
* Jinx LED Software https://live-leds.de/downloads/ installed
## Setup ESP32
* Wire the display according the PIN definition in the source code or change the definition.
* Set the ssid and the passphrase 
* Compile and download the E131_to_Matrix.ino
## Setup Jinx
