
## toolchain 

- Arduino
    - Prefs -> [x] use external editor
    - Prefs -> http://arduino.esp8266.com/stable/package_esp8266com_index.json
    - Tools -> Board -> Boards manager -> "esp" -> install
    - Tools -> Board -> NodeMCU 1.0
    
- CLion
    - Plugins -> Arduino

Library installation
- Arduino -> Sketch -> Include Library -> Manage Libraries
  - DHT sensor library
  - Adafruit Unified Sensor
  - ArduinoHttpClient
  - ArduinoJson

- Look for & remove duplicates under ~/Library/Arduino15/packages/esp8266/hardware/esp8266/

Win/Mac Drivers for the CH340G / CH341G serial chip
- https://kig.re/2014/12/31/how-to-use-arduino-nano-mini-pro-with-CH340G-on-mac-osx-yosemite.html
- http://www.wch.cn/download/CH341SER_MAC_ZIP.html

## docs
  - https://github.com/arduino-libraries/ArduinoHttpClient
  - https://github.com/adafruit/Adafruit_Sensor
  - https://github.com/adafruit/DHT-sensor-library



## Pinout
- https://learn.adafruit.com/dht/using-a-dhtxx-sensor
- https://www.teachmemicro.com/nodemcu-pinout/

## Power consumption:
- MAIN_INTERVAL = 5000
- 3.29V / 0.016A (idle)
- 3.29V / 0.075A (peak during work cycle)
- Visual readings from power supply
- Same with 2.99V and 2.79V
- Average ~~ (0.016 * 75 + 0.075 * 25)/100 = 0.023A = 23 mA
- With two 2200 mAh cells: 2200 mAh / 23 mA ~~ 96h = 4d

