# Arduino_Code_Smart_House
Smart House Arduino code

---
## Table of contents

- [Signals](#signals)
  * [Input signals](#input-signals:)
  * [Output signals](#output-signals:)
- [MQTT](#mqtt)
  * [About MQTT](#about-mqtt)
---

## Signals

### Inputs signals:

* Fire alarm - a switch that simulates fire (Values 1 and 0)
* Housebreaking alarm - house door (1 when closed, 0 when open) ← Bad naming
* Water leakage - a switch that simulates water leakage (Values 1 and 0)
* Temperature indoors - analog sensor LM35 (Outputs temp as double in format [dd.dd])
* Temperature outdoors - digital sensor SMT160-30 
(Outputs temp as int - will be converted to double value - not tested properly - maybe it gives the double value)
* Stove - a switch that simulates the stove (Values 1 and 0)
* Window - a switch that simulates window open/closed (Values 1 and 0)
* Electricity consumption - analog sensor (Outputs int value of the voltage)
* Twilight automatic system - Light-to-voltage sensor (not tested)
* Power cut - digital sensor (1 when power is present, 0 when not)

### Output signals:

(Taking MUX(Multiplexer) commands - one at a time)

* Timer T1 - a LED lamp marked T1 (can be used to show if alarm is armed)
* Timer T2 - a LED lamp marked T2 (can be used for something else)
* Indoor light - One lamp inside the house
* Outdoor light - One lamp outside the house
* Housebreaking alarm - a speaker
* Fan (not MUX) - a fan mounted on the house’s loft (possible speed 
control - not checked)
* Radiator - Four radiators mounted inside the house
* Heating element wind - mounted close to the fan (untested)

---
``` 
Values will (probably) be sent as Strings where 1 will be true and 
0 false. E.g. Topic:”house/lights/indoorLight” Message:”true”
```

``` 
Temperature data will be both sent as RAW data 
(just what the sensor gives) AND also 
human-readable correct temperature value 
in Celsius as a String with a double 
e.g. “23.05”
```

---

## MQTT

### About MQTT

MQTT is an open OASIS and ISO standard lightweight, publish-subscribe network protocol 
that transports messages between devices. The protocol usually runs over TCP/IP; 
however, any network protocol that provides ordered, lossless, bi-directional 
connections can support MQTT. [MQTT-Wiki](https://en.wikipedia.org/wiki/MQTT)


... to be continued.
