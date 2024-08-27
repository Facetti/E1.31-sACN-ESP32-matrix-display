# ESP32 with matrix display receiving E.131/sACN data via WiFi 
This project shows how to play a video on a Windows PC, sending the data traffic in E1.31 sACN (DMX over Ethernet) protocol and receive it via WLAN on a ESP32 to display it on two chained 64x64 LED matrix displays (= heigh/rows/lines 64, width/columns 128). Because of the inefficient coding and protocol overhead don't expect high frame rates and don't be surprised if not all lines are updated. Anyway, this is a good starting point for your own optimizations.

In E1.31 there is a concept of Universes, which is a data block with max 512 bytes called Channels.
To keep it simple, we use one universe per row/line of the matrix display. 
Because we have three bytes (RGB) per pixel, we can have max 170 (512/3) LEDs horizontally. This is sufficient for two chained 64x64 matrixes (2 * 64 = 128 columns; 128 * 3 = 384 bytes).
Payload structure (bytes): start code (ignore) | Pixel 1 R | Pixel 1 G | Pixel 1 B | Pixel 2 R | Pixel 2 G | .... | Pixel 128 G | Pixel 128 R


## Requirements
### Hardware
* ESP32
* 64x64 LED matrix display connected to the ESP32
### Arduino IDE (2.3.2) with installed libraries
* FastLED - https://github.com/FastLED/FastLED
* ESP32 HUB75 LED MATRIX PANEL DMA - https://github.com/mrcodetastic/ESP32-HUB75-MatrixPanel-DMA
* ESP Async E1.31 https://github.com/forkineye/ESPAsyncE131
### Windows (10) PC
* Jinx LED Software https://live-leds.de/downloads/ 
* Depending on your video format it could be that you must install additiona codecs https://live-leds.de/faqs/my-avi-files-wont-play-and-jinx-says-maybe-an-unsupported-codec/
## Setup ESP32
* Wire the display according the PIN definition in the source code or change the definition.
* Set the ssid and the passphrase 
* Compile and download the E131_to_Matrix.ino
## Running Jinx
### Setup
#### Matrix Options
width 128, heigh 64, tick Use Patch State for Pixel drawing. 

<img width="239" alt="MatrixOptions" src="https://github.com/user-attachments/assets/7c05b5e7-9c3f-43fa-941f-6ba893a7d242">

#### Output Devices
64 entries needed, because one device per universe/line/row, each with 384 Channels. Because we use Multicast and we like to keep it simple we use the IP Addresses are 239.255.0.x with x = universe number.

<img width="459" alt="OutPutDevices1" src="https://github.com/user-attachments/assets/eaa6b5cf-9dbb-4bc0-b485-443c6fa98242">

<img width="165" alt="OutPutDevices2" src="https://github.com/user-attachments/assets/33019107-8402-42ad-ad5e-44aceac34047"><img width="165" alt="OutPutDevices3" src="https://github.com/user-attachments/assets/cc4fd4cc-50f4-4e4a-8fbb-cfd9bfab7ef0"> . . . <img width="165" alt="OutPutDevices4" src="https://github.com/user-attachments/assets/7eba059c-00da-4c7a-9bdd-b97fa814a513">

#### Output Patch
Select the first cell in each line and use Fast Patch
* Dimension: x=128, y=1
* Patch Mode: Linewise starting Top-Left
* Pixel Order: RGB
* First Channel: 0 (check it! - if your universe has more channels defined than the x-dimension, this value will automatically be changed to the first 'unused' channel number)
* Patch Device: eACN/E1.31 239.255.0.x \[x\] (where is is the univers/line number)
<img width="678" alt="OutPutPatch" src="https://github.com/user-attachments/assets/1b657869-da72-449a-9cbe-5ee7f8b59d10">

### Testing
* Set Channel 1 effect to Plasma and Setup->Start Output
<img width="346" alt="StartOutput" src="https://github.com/user-attachments/assets/b31b7b56-2822-4109-801a-5ca2e20a559b">

* Select Channel 1 AVI Player, Edit to select your Video and Setup->Start Output
<img width="491" alt="StartVideo" src="https://github.com/user-attachments/assets/ad6b1061-12fb-4f9e-a4c7-4a7cc7d93fb6">

and enjoy

https://github.com/user-attachments/assets/8d432cec-905c-44f5-84df-edc6e7b22868




