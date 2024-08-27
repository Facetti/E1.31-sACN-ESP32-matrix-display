# ESP32 with matrix display receiving E.131/sACN data via WiFi 
This project shows how to play a video on a Windows PC, sending the data traffic in E1.31 sACN (DMX over Ethernet) protocol and receive it via WLAN on a ESP32 to display it on two chained 64x64 LED matrix displays (= heigh/rows/lines 64, width/columns 128).

In E1.31 there is a concept of Universes, which is a data block with max 512 bytes called Channels.
To keep it simple, we use one universe per row/line of the matrix display. 
Because we have three bytes (RGB) per pixel, we can have max 170 (512/3) LEDs horizontally. This is sufficient for two chained 64x64 matrixes (2 * 64 = 128 columns; 128 * 3 = 384 bytes).

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
* Depending on your video format it could be that you must install additiona codecs https://live-leds.de/faqs/my-avi-files-wont-play-and-jinx-says-maybe-an-unsupported-codec/
## Setup ESP32
* Wire the display according the PIN definition in the source code or change the definition.
* Set the ssid and the passphrase 
* Compile and download the E131_to_Matrix.ino
## Running Jinx
### Setup
#### Matrix Options
width 128, heigh 64, tick Use Patch State for Pixel drawing. 
#### Output Devices
64 entries needed, because one device per universe/line/row, each with 384 Channels. Because we use Multicast and we like to keep it simple we use the IP Addresses are 239.255.0.x with x = universe number.
#### Output Patch
Select the first cell in each line and use Fast Patch
* Dimension: x=128, y=1
* Patch Mode: Linewise starting Top-Left
* Pixel Order: RGB
* First Channel: 0 (check it! - if your universe has more channels defined than the x-dimension, this value will automatically be changed to the first 'unused' channel number)
* Patch Device: eACN/E1.31 239.255.0.x \[x\] (where is is the univers/line number)
###
