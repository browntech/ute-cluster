# ute-cluster

# Description
The goal of this repository is to compile an Arduino sketch (or maybe Raspberry Pi program?) that can be used to translate CANBus signals from a 2004 Accord ECU and drive a 2002 MK4 Golf cluster.

# Goals
- Real time tachometer
- Real time speedometer
- Accurate engine temperatures
- Disable lights that aren't needed

# Gauge list
| Gauge | Input | Output |
| ----------- | ----------------- | ------------------------------ |
| Speedometer | Accord CANBus TBD | VSS Pulsed output from Arduino |
| Tachometer  | Accord CANBus | VW CanBus from Arduino |
| Temp Gauge  | Accord CANBus | Some kind of variable resistor setup TBD |
| Coolant Level | n/a | Blue connector PIN 22 Jumper to ground |
| Oil Level | Accord C251 Pin 9 Yel/Red | Blue connector PIN 10 |

## Speedometer
I need a better equation to convert speed to a reading on the gauge cluster

## Tachometer
See tachometer_test_data.txt for CANBus examples.

## Temp Gauge
Maybe this?  It has been 15 years since I took an electronics class.
http://lithiumate.elithion.com/php/system_wiring.php#Fuel_gauges

## Coolant Level
Blue connector, Pin 22. I don't have a coolant expansion tank.  Maybe later eh?  Run this to ground.  If open you'll get a flashing coolant level light.

## Oil Level
BLue connector, Pin 10.  If you run this through a 40 ohm resistor to ground you get no oil light.

Weirdly enough, pin 18 on the Green connector is listed as oil temperature and oil level warning signals. The motor I pulled this gauge from didn't come with an oil level sensor so thats probably nothing.

## Brake pad wear light
I have the original break pad circuits still but this comes from pin 7 on the green connector.  Attach this to ground to make it go away.

### Notes
https://www.facebook.com/VWMKSTREETTUNISIE/posts/how-to-check-yhe-oil-level-sensor-test-conditionsl-oil-temperature-at-least-70-c/1310318436115344/