Dobsonometer
============

Code and documentation for an Arduino-based Dobson meter and sun photometer.

NOTE: This project is in early development, and the code is released as-is.  It should be cleaned up and leaned up.

The instrument uses an Adafruit TCS34725 RGB color sensor to measure aerosol optical thickness (AOT) and Adafruit GUVA-S12SD UV sensors to measure column ozone thickness.  Both sensors are connected to an Arduino, which is controlled by issuing commands via the serial port.

This code requires the [TCS34725 library](https://github.com/adafruit/Adafruit_TCS34725) from Adafruit.

# Serial Commands #

Serial commands can be an action or query command.  Query commands are distinguished by a question mark ("?") at the end, while action commands contain a period at the end followed by command options.  To issue a command, type the command followed by the new line character ("\n").

## Action Commands ##

1. `displayMeas`: reads saved measurements from memory locations `0` through `addr` and prints to serial port.
2. `echo.X`: specifies whether or not the sensor should return a messeage after completing a command.  When `X = 1` echo is turned on; when `X = 0` it is off.
1. `getMeas.X`: averages `X` readings and saves average to memory at memory locations `addr` through `addr + 24`.
1. `intTime.X`: sets the integration time of the TCS34725 RGB sensor.  `X` is the integration time in milliseconds.  Available options are:
	*  `2.5`, actual time = 2.4 ms, 1 cycle, max count = 1024
	*  `25`, actual time = 24 ms, 10 cycles, max count = 10240 
	*  `50`, actual time = 50 ms, 20 cycles, max count = 20480
	*  `100`, actual time = 101 ms, 42 cycles, max count = 43008
	*  `150`, actual time = 154 ms, 64 cycles, max count = 65535
	*  `700`, actual time = 700 ms, 256 cycles, max count = 65535

	For more information, see the Adafruit [library reference](https://learn.adafruit.com/adafruit-color-sensors/program-it).

1. `memAddr.X`: sets the current save location to EEPROM address `X`. Address `0` is reserved; available options are `1` -- `487` (because 24 bytes are needed to save one measurement).

## Query Commands ##

1. `*IDN?`: returns the identification string of the sensor.
1. `intTime?`: Returns the integration time of the TCS34725 RGB sensor in milliseconds.
2. `memAddr?`: Returns the current EEPROM save location.

