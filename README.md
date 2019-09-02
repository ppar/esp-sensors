
Library installation

- Sketch -> Include Library -> Manage Libraries
  - DHT sensor library
  - Adafruit Unified Sensor
  - ArduinoHttpClient
    - https://github.com/arduino-libraries/ArduinoHttpClient
  - ArduinoJson
- See
  - https://github.com/adafruit/Adafruit_Sensor
  - https://github.com/adafruit/DHT-sensor-library

Pinout
- https://learn.adafruit.com/dht/using-a-dhtxx-sensor
- https://www.teachmemicro.com/nodemcu-pinout/

Power consumption:
- MAIN_INTERVAL = 5000
- 3.29V / 0.016A (idle)
- 3.29V / 0.075A (peak during work cycle)
- Visual readings from power supply
- Same with 2.99V and 2.79V
- Average ~~ (0.016 * 75 + 0.075 * 25)/100 = 0.023A = 23 mA
- With two 2200 mAh cells: 2200 mAh / 23 mA ~~ 96h = 4d

