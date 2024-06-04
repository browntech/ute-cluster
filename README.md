# ute-cluster

# Description
The goal of this repository is to compile an Arduino sketch (or maybe Raspberry Pi program?) that can be used to translate CANBus signals from a 2004 Accord ECU and drive a 2002 MK4 Golf cluster.

# Goals
- Real time tachometer
- Real time speedometer
- Accurate engine temperatures
- Disable lights that aren't needed

# Gauge list
| Gauge | Input | Output | Notes |
| Speedometer | Accord CANBus TBD | VSS Pulsed output from Arduino | n/a |
| Tachometer  | Accord CANBus | VW CanBus from Arduino | n/a |
| Temp Gauge  | Accord CANBus | Some kind of variable resistor setup TBD | n/a |
| Coolant Level | n/a | Blue connector PIN 22 Jumper to ground | n/a |
| Oil Level | C251 Pin 9 Yel/Red | Blue connector PIN 10 | n/a |

## Speedometer
I need a better equation to convert speed to a reading on the gauge cluster

## Tachometer
See tachometer_test_data.txt for CANBus examples.

## Temp Gauge
Maybe this?  It has been 15 years since I took an electronics class.
http://lithiumate.elithion.com/php/system_wiring.php#Fuel_gauges

## Coolant Level
I don't have a coolant expansion tank.  Maybe later eh?

## Oil Level
Need to find out what Pin 9 puts out, open or ground.