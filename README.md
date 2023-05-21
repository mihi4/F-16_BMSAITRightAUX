# BMSAIT Right Aux Controller
* Microcontroller: Arduino Nano

## Hardware controlled
- PFD
- CAUTION PANEL
- COMPASS
- FUEL QTY Gauge
- HYD PRESS Gauges
- EPU FUEL Gauge
- CABIN PRESS Gauge
- ~~(LIQUID FUEL Gauge)~~
## Pinmapping
* PFD: 
  * Serial Display  
    (Old DED, 2 pins, softwareSerial) D2,D3
* CAUTION PANEL:
  * 1 MM5451  
    (2 pins) D4,D5
* HYD PRESS:
  * 2 Servos  
    (2 pins) D6,D7
* FUEL QTY:
  * 2 servos  
    (2 pins) D8,D9
  * MAX7219 5 digit 7seg display  
    (3 pins) D10,D11,D12
* AX1201728SG (7 pins), D13-A5
  * COMPASS: 1 X27  
    (2 pins)
  * CABIN PRESS: 1 X27  
    (2 pins)
  * EPU FUEL: 1 X27  
    (2 pins)  
* Input for compass seroizing sensor (1 pin) A6  
* Input for compass seroizing button (1 pin) A7

