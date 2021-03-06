# thinx-esp8266-firmware

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/391e02d431bc45b5a1c7a59e48b109a6)](https://www.codacy.com/app/suculent/thinx-firmware-esp8266-pio?utm_source=github.com&utm_medium=referral&utm_content=suculent/thinx-firmware-esp8266-pio&utm_campaign=badger)

Firmware for automatic device registration and OTA updates.

Provides example implementations in Arduino C, Lua and Micropython.

* This is a work in progress.
* 100% functionality is not guaranteed for all the time.

# Requirements

### Arduino C development

- Arduino IDE or Platform.io
- Included librearies: ArduinoJSON, WiFiManager
- Arduino libraries: ESP8266httpUpdate (to be replaced)
- Open this folder using Atom with installed Platform.io or thinx-firmware-esp8266/thinx-firmware-esp8266.ino using Arduino IDE.
- Run prerelease.sh to bake your commit ID into the Thinx.h file.

### Micropython/Lua development

- ESPlorer
- ESPTool

## Arduino C / Platform.io

**RobotDyn MEGA WiFi Notes**

1. To Upload firmware to ESP8266, set DIP switches to:

| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|:----|:----|:----|:----|:----|:----|:----|:----|
| OFF | OFF | OFF | OFF | *ON* | *ON* | *ON* | - |

2. To debug firmware on ESP8266, set DIP switches to:

| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|:----|:----|:----|:----|:----|:----|:----|:----|
| OFF | OFF | OFF | OFF | *ON* | *ON* | OFF | - |


## Micropython

## Lua

Requires following modules: wifi,websocket,uart,tmr,node,net,mqtt,http,file,cjson

### Manual installation

• Edit config.lua, set your WiFi SSID and password
• Upload config.lua, thinx.lua and init.lua
• Reboot


### Forced Update

• Not yet implemented, will be possible in future.

Tested with:

    NodeMCU custom build by frightanic.com
    	branch: master
    	commit: ec265a6c21db22640795f190bdcb8a4f014cdced
    	SSL: false
    	modules: adc,bit,cjson,coap,crypto,dht,enduser_setup,file,gpio,http,i2c,mdns,mqtt,net,node,ow,pcm,pwm,struct,tmr,u8g,uart,websocket,wifi
     build 	built on: 2016-12-04 22:54
     powered by Lua 5.1.4 on SDK 1.5.4.1(39cb9a32)

# Usage

1. Create account on the [http://rtm.thinx.cloud/](http://rtm.thinx.cloud/) site
2. Create an API Key
3. Clone [vanilla NodeMCU app repository](https://github.com/suculent/thinx-firmware-esp8266)
4. Run the bash ./prerelease.sh to create Thinx.h file; you can edit this with your custom information but the file will be overwritten when building on the server
5. You can store Owner ID and API Key in Thinx.h file in case your project is not stored in public repository.
6. Build and upload the code to your device.
7. After restart, connect with some device to WiFi AP 'AP-THiNX' and copy-paste the API Key and Owner ID, if you haven't hardcoded it in step 4
8. Device will connect to WiFi and register itself. Check your thinx.cloud dashboard for new device.

... Then you can add own git source, add ssh-keys to access those sources if not public, attach the source to device to dashboard and click the last icon in row to build/update the device.

Note: In case you'll build/upload your project (e.g. the library) using thinx.cloud, API key will be injected automatically and you should not need to set it up anymore.

# Security

Because all the traffic from ESP8266 is usually HTTP-only and not all devices can handle SSL, you can install our side-kick project [THiNX-Connect](https://github.com/suculent/thinx-connect). Install this proxy to your home environment and it will encrypt HTTP traffic to HTTPS and will tunnell your device communication directly to thinx.cloud.
