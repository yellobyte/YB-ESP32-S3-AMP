## YB-ESP32-S3-AMP Development Board Overview:
The **YB-ESP32-S3-AMP** is a general purpose development board based on Espressif's ESP32-S3 MCU. It presently comes in two different variants and is available on sales platforms [eBay](https://www.ebay.de/sch/i.html?_nkw=yb-esp32-s3) and [Ricardo.ch](https://www.ricardo.ch/en/s/YB-ESP32-S3):
- with **ESP32-S3-WROOM-1-N8R2 module** (8MB Flash, 2MB PSRAM, WiFi PCB Antenna),
- without **ESP32-S3-WROOM-1 module** which allows you to solder on any ESP32-S3-WROOM module of your choice.

Apart from the **ESP32-S3** it provides a **microSD** card slot, two **MAX98357A I2S PCM Class D Amplifiers** (for left + right audio channels), **USB-C connector** for software upload, serial output, JTAG debugging and/or feeding power to the board, **CH334 USB-Hub** chip, **CH343 USB-UART bridge** chip, **two status LEDs** and lots of **GPIO pins** for free usage.

<p align="center"><img src="https://github.com/yellobyte/YB-ESP32-S3-AMP/raw/main/doc/YB-ESP32-S3-AMP_top_with_screw_terminals.jpg" height="160"/></p>

The onboard USB-Hub (USB high-speed HUB controller chip CH334) allows for **JTAG debugging and watching serial output simultaneously** without any problems. More info further down.

Of course you can **connect additional hardware** to the board, e.g. TFT displays, IR receivers or any other module that communicates via I2C/SPI, etc. The **I2S bus signals** (**D**ata, **L**eft/**R**ight (word) clock, **B**it clock) are accessible via **solder pads** on the bottom of the board for attaching external I2S components if needed.  

The densly populated YB-ESP32-S3-AMP board provides multiple GPIO pins (as shown below) and is still highly [**breadboard compatible**](https://github.com/yellobyte/YB-ESP32-S3-AMP/raw/main/doc/YB-ESP32-S3-AMP_on_breadboard.jpg) for it leaves one row of accessible breadboard contacts on either side of the board. All I/O ports (GPIOx) are clearly labeled on both sides of the board.  

Please have a look at the provided [examples](https://github.com/yellobyte/YB-ESP32-S3-AMP/tree/main/examples) for PlatformIO resp. ArduinoIDE.
Most of them use Schreibfaul1's awesome Arduino library [**ESP32-audioI2S**](https://github.com/schreibfaul1/ESP32-audioI2S) which is highly suitable for this board.

## Quickstart guide:
**All YB-ESP32-S3-AMP boards delivered have already been flashed with software example 'Play-All-MP3-Files-on-SD'.**
- Step 1) connect one or two 4Ω...8Ω loudspeaker(s) to the board
- Step 2) insert a microSD card (FAT32) holding some *.mp3 files
- Step 3) apply power (via USB or 5V pins)

That's it. The status LED will light up when the microSD card has been detected ok and the board will start playing all *.mp3 files found.

Carrying on you could build and upload one of the many provided ArduinoIDE/PlatformIO [examples](https://github.com/yellobyte/YB-ESP32-S3-AMP/tree/main/examples) and listen to internet radio stations, play an audio file from your NAS running a media server and much more.

## YB-ESP32-S3-AMP board features in detail:
 - **ESP32-S3-WROOM-1-N8R2** module with 8MB Flash, 2MB PSRAM, WiFi PCB antenna (when populated with WROOM module)
 - **2 x MAX98357A** I2S PCM Class D Amplifier (3.2W@4Ω) connected to the ESP32-S3 as follows:
   - *GPIO5 - BCLK* (bit clock)
   - *GPIO6 - LRCLK* (frame clock)
   - *GPIO7 - DIN* (digital audio signal)

    Note: GPIOs 5/6/7 are not wired to any board pin, they are exclusively used for the two MAX98357A.
 - **screw terminals** for connecting 2 loudspeakers (4...8Ω, left + right audio channel)
 - **microSD** card slot connected to the ESP32-S3 via fast SPI bus *FSPI*:
   - *GPIO10 - SCS* (SPI bus control, chip select, this control line is not needed for SD_MMC-lib and available for other usage when solder bridge *SD_CS* is open [default closed])
   - *GPIO11 - MOSI* (SPI bus data communication, SD_MMC calls it *CMD*)
   - *GPIO12 - SCK* (SPI bus clock signal)
   - *GPIO13 - MISO* (SPI bus data communication, SD_MMC calls it *D0*)

   Note: GPIOs 11/12/13 are not wired to any board pin, they are exclusively used for the microSD slot.
 - **control LEDs**. One LED labeled 'P' is connected to the 3.3V rail to indicate board power and the other LED labeled 'IO47' is connected to GPIO47 which can be used as status LED.
 If solder bridge *DAC_MUTE* is closed [default open] this pin can be used for muting the two audio amplifiers: active when GPIO47 is HIGH or muted when GPIO47 is LOW.
 - **USB-C** port connected to the onboard CH334 USB-Hub chip. This allows for simultaneous JTAG debugging and serial output as well as software upload (e.g. via ArduinoIDE, VSCode/PlatformIO etc). The ESP32-S3 contains an inbuild JTAG adapter hence [**debugging**](https://github.com/yellobyte/ESP32-DevBoards-Getting-Started/tree/main/debugging) becomes fairly easy.
 - **hardware logic** for *automatic* software uploads (supported by most Development IDEs) via USB-C port using the onboard CH343 USB-UART bridge chip.
 - **pushbuttons**. One is labeled 'R' and resets the ESP32-S3 (shorts EN pin to ground) and the other one is labeled 'B' and shorts GPIO0 to ground when pressed. The latter is sometimes needed to force the board into boot mode.
 - **lots of available GPIOs**, useful for connecting LEDs, buttons, additional modules via second SPI bus or I2C, e.g displays, rotary encoders, bluetooth, etc.

In summary, the board replaces a lot of separate modules & cables, saves space on the breadboard and might avoid the odd frustration to get it all running.

 ![](https://github.com/yellobyte/YB-ESP32-S3-AMP/raw/main/doc/YB-ESP32-S3-AMP_modules_replacement.jpg)

## Board Pin Layout:
 ![](https://github.com/yellobyte/YB-ESP32-S3-AMP/raw/main/doc/YB-ESP32-S3-AMP_pinlayout.jpg)

The boards **outline** and **schematic** files are all located in folder [doc](https://github.com/yellobyte/YB-ESP32-S3-AMP/raw/main/doc), together with data sheets for Espressif's MCU ESP32-S3 and the ESP32-S3-WROOM-1 module family.

## Powering the board:
There are two ways to provide power to the board:
  - through the USB-C port or
  - ~5VDC applied to the 5V pin

The board uses a LDO to drop the external supply voltage to 3.3Volt needed by the ESP32-S3. The two audio amplifiers MAX98357A though get their voltage directly from pin '5V'. They can operate up to 5.5V and their absolute maximum rating is 6V. Therefore **never supply more than ~5.5VDC to the '5V' power input pins** !!

Normal operating current of the idle board (all GPIOs unconnected, no audio output, WiFi disabled) is about 45mA. With WiFi active the board draws about 100mA (mainly depending on WiFi link). With WiFi active, a microSD in the slot and lower audio output power on both amp channels the current rises to ~160mA.

### Recommended wiring for max. audio output power:
Each audio channel can produce max. 3.2W output power at 4 Ohms. If your project requires more then just a few mW of audio output power it is recommended to use a capable power supply (5VDC/1.5A) and preferably an additional capacitor of min. 220uF or greater value across the 5V/GND pins of the board as shown below:

![](https://github.com/yellobyte/YB-ESP32-S3-AMP/raw/main/doc/YB-ESP32-S3-AMP_recommended_wiring.jpg)

## Application hints:
The board uses a WCH chip CH343P (USB-UART bridge). If you haven't done yet then you need to install the CH343 Driver on your Laptop/PC. For Windows go [here](https://www.wch-ic.com/search?t=all&q=ch343) and download and install the newest version of the driver. Linux provides CH34x drivers by default.

### Arduino IDE:
As of Arduino ESP32 Core V3.3.6 you open the board list, enter "yb" and then select "**Yellobyte YB-ESP32-S3-AMP**". Now choose the proper settings for COM port, debug level, etc. as shown below. Be aware, since the ESP32-S3 MCU is very versatile there are a lot of build options to play with. Espressif's homepage offers some help.

Correct **ArduinoIDE** settings for the **YB-ESP32-S3-AMP** board with 8MB Flash & 2MB PSRAM:
- Board: *YB-ESP32-S3-AMP*
- USB CDC On Boot: _Disabled_
- Flash Size: *8MB (64Mb)*
- Partition Scheme: *8MB with spiffs (...)*
- PSRAM: *QSPI PSRAM*

 ![](https://github.com/yellobyte/YB-ESP32-S3-AMP/raw/main/doc/YB-ESP32-S3-AMP_ArduinoIDE-Settings-N8R2.jpg)

For boards with different WROOM modules (e.g. -N8R8, -N16R8) you need to adjust the settings of course.

### PlatformIO:
Building with **PlatformIO** is easy as well. Starting with Arduino ESP32 Core v3.3.6 the VSCode/PlatformIO IDE holds all the necessary *.json board files that provide the correct board definitions & settings.

Just create a new project and give it a name, then go to board selection, enter "yb-" and choose your YB-ESP32-S3-AMP*** board from the list thats popping up.

 ![](https://github.com/yellobyte/YB-ESP32-S3-AMP/raw/main/doc/YB-ESP32-S3-AMP_PlatformIO_board_selection.jpg)

### Using the USB-C port:
With the board connected to your PC/Laptop you'll see 3 additional USB devices. Two COM ports: **Serial USB device** and **USB-Enhanced-Serial CH343** and one device: **USB JTAG/serial debug unit** (or similar, depending on your OS).

You can connect a serial monitor program on your PC/Laptop to device "USB-Enhanced-Serial CH343" and watch the serial output generated with e.g. Serial.print(). Important: This serial connection is **not** affected by any board reset.

Device "USB JTAG/serial debug unit" lets you simultaneously debug the board via the ESP32-S3 integrated JTAG debug circuitry. How to use the latter for debugging is explained in detail [**here**](https://github.com/yellobyte/ESP32-DevBoards-Getting-Started/tree/main/debugging).

**Please note:** The PlatformIO builder scripts (*.json) for modules containing ESP32-S3/C3 normally define the build flag _ARDUINO_USB_MODE=1_. This enables the USB-Serial-JTAG controller and disables the USB-OTG-Controller in the ESP32-S3. If you want to override it you can (re-)define it in your platformio.ini control file. Normally you don't have to worry about it.

### Software Upload to the board:
Uploading new software to boards with your IDE is a breeze. Select the correct COM port and upload the program. The integrated hardware logic will put the board into upload mode automatically.

However, at any time and if needed you can force the ESP32-S3 into upload mode *manually*. Keep the **'B'** button pressed, then press/release the **'R'** button and finally release the **'B'** button. The serial monitor output will subsequently confirm the boards readiness for getting flashed.

```
....
23:19:07.453 > ESP-ROM:esp32s3-20210327
23:19:07.453 > Build:Mar 27 2021
23:19:07.453 > rst:0x1 (POWERON),boot:0x0 (DOWNLOAD(USB/UART0))
23:19:07.459 > waiting for download
```

### Flash/RAM usage:
The -N8R2 module on the board should provide enough memory even for demanding projects. Building e.g. software example [Play-All-MP3-Files-on-SD](https://github.com/yellobyte/YB-ESP32-S3-AMP/tree/main/examples/PlatformIO/Play-All-MP3-Files-on-SD) shows the following Flash/RAM usage:
```
Executing task: C:\Users\tj\.platformio\penv\Scripts\platformio.exe run

Processing v2 (board: yb-esp32-s3-amp-v2; platform: espressif32; framework: arduino)
------------------------------------------------------------------------------------------------------------------------------------
Verbose mode can be enabled via `-v, --verbose` option
CONFIGURATION: https://docs.platformio.org/page/boards/espressif32/yb-esp32-s3-amp-v2.html
PLATFORM: Espressif 32 (6.9.0) > YB-ESP32-S3-AMP (8 MB QD FLASH, 2 MB PSRAM)
HARDWARE: ESP32S3 240MHz, 320KB RAM, 8MB Flash
DEBUG: Current (esp-builtin) On-board (esp-builtin) External (cmsis-dap, esp-bridge, esp-prog, iot-bus-jtag, jlink, minimodule, olimex-arm-usb-ocd, olimex-arm-usb-ocd-h, olimex-arm-usb-tiny-h, olimex-jtag-tiny, tumpa)
PACKAGES:
 - framework-arduinoespressif32 @ 3.20017.0 (2.0.17)
 - tool-esptoolpy @ 1.40501.0 (4.5.1)
 - toolchain-riscv32-esp @ 8.4.0+2021r2-patch5
 - toolchain-xtensa-esp32s3 @ 8.4.0+2021r2-patch5
LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
LDF Modes: Finder ~ chain, Compatibility ~ soft
Found 62 compatible libraries
Scanning dependencies...
Dependency Graph
|-- SD @ 2.0.0
|-- ESP32-audioI2S @ 2.0.0
|-- FS @ 2.0.0
|-- SPI @ 2.0.0
Building in release mode
Retrieving maximum program size .pio\build\v2\firmware.elf
Checking size .pio\build\v2\firmware.elf
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [=         ]   8.4% (used 27608 bytes from 327680 bytes)
Flash: [===       ]  28.5% (used 950957 bytes from 3342336 bytes)
```
### General notes:
1) In case you get left channel output on the right speaker and vice-versa (L + R channels are swapped) you need to build with a [newer ESP32-AudioI2S library version](https://github.com/schreibfaul1/ESP32-audioI2S/releases) with this error fixed.

2) The ESP32-S3 includes four SPI controllers: SPI0, SPI1, SPI2(Fast SPI) and SPI3. SPI0/1 are reserved for Flash and PSRAM (if available) and should be left alone. The remaining two are available for the public. In the Arduino universe SPI2 & SPI3 are named FSPI & HSPI. FSPI by default is assigned to GPIOs 10-15 and routed via IO MUX. However, both can get pinned to any available GPIO pin if needed but FSPI will be slower if routed through GPIO Matrix

3) The ESP32-S3-WROOM-1 module family comprises several [**versions**](https://github.com/yellobyte/ESP32-DevBoards-Getting-Started/raw/main/ESP32_specs_and_manuals/ESP32-S3-WROOM-1(U)_Variants.jpg). The **-1** versions come with embedded PCB antenna, the **-1U** versions with IPEX antenna socket instead. The extension -Nx(Ry) defines the amount of integrated FLASH/PSRAM, e.g. -N4 (4MB Flash, no PSRAM), -N4R2 (4 MB Flash, 2MB PSRAM), -N8R2 (8 MB Flash, 2MB PSRAM) etc.

### Integrating this board into your own PCB design projects:
Its easy. Folder [doc](https://github.com/yellobyte/YB-ESP32-S3-AMP/tree/main/doc) provides the Eagle library file **_yb-esp32-s3-amp.lbr_** containing both boards. Most other PCB design software (e.g. KiCad) are able to import and use Eagle lib files.

<p align="center"><img src="https://github.com/yellobyte/YB-ESP32-S3-AMP/raw/main/doc/Eagle_project_with_yb-esp32-s3-amp.jpg" height="250"/>&nbsp;<img src="https://github.com/yellobyte/YB-ESP32-S3-AMP/raw/main/doc/Eagle_project_with_yb-esp32-s3-amp2.jpg" height="250"/></p>

