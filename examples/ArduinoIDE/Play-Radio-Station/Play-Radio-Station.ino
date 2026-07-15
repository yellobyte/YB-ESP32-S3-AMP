/*
  Play-Radio-Station

  Plays a radio station's audio stream over the two MAX98357A I2S amplifiers (left+right audio channels).
  Make sure you have library "ESP32-audioI2S" added to your project or ArduinoIDE. More info about this versatile lib
  are available on its homepage "https://github.com/schreibfaul1/ESP32-audioI2S".

  Solder bridge DAC_MUTE is open by default and both MAX98357A are active. Closing the solder bridge will connect pin
  GPIO47 (onboard LED IO47) with the amps SD_MODE pin. Setting GPIO47 to LOW (LED off) will shut down (mute) the amps
  and setting GPIO47 to HIGH (LED on) will activate the amps.

  Last updated 2026-07-15, ThJ <yellobyte@bluewin.ch>
*/

#include <Arduino.h>
#include <WiFi.h>
#include "Audio.h"

#define RADIO_STREAM "http://legacy.scahw.com.au/2classicrock_32"
//#define RADIO_STREAM "http://stream.srg-ssr.ch/m/rsp/mp3_128"
//#define RADIO_STREAM "http://www.radioeins.de/frankfurt/livemp3"
//#define RADIO_STREAM "http://vis.media-ice.musicradio.com/CapitalMP3"
//#define RADIO_STREAM "http://stream.laut.fm/oldies"

const char ssid[] = "MySSID";
const char pass[] = "MyPassword"; 

Audio audio;
 
void my_audio_info(Audio::msg_t m) {
    Serial.printf("%s: %s\n", m.s, m.msg);
}

void setup()
{
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("running example \"Play-Radio-Station\":");

  // connecting to local WiFi network
  Serial.printf("connecting to WiFi network \"%s\"\n", ssid);
  WiFi.begin(ssid, pass);
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(2000);
  }
  Serial.printf("\nconnected successfully to \"%s\". IP address: %s\n", ssid, WiFi.localIP().toString().c_str());
  digitalWrite(LED_BUILTIN, HIGH);      // status LED On
  
  audio.audio_info_callback = my_audio_info;
  audio.setPinout(I2S_BCLK, I2S_LRCLK, I2S_DOUT);
  audio.setVolume(10);                 // 0...21(max)
  audio.setConnectionTimeout(1200,0);  // needed for some stations esp. from around the globe
  audio.connecttohost(RADIO_STREAM);
}

void loop()
{
  audio.loop();                        // play audio stream
  vTaskDelay(1);                       // needed !
}



