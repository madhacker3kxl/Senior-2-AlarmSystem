******** analogComp.h  *******

analogComp

This little library can be used to set and manage the analog
comparator that is integrated in a wide variety of
Atmel microcontrollers

Written by Leonardo Miliani <leonardo AT leonardomiliani DOT com>


***********************
Version history

v. 1.2.1:  fixed a bug that let the ADC off after a comparison
v. 1.2.0:  fixed a bug into the conversion from analog to phisical pins
v. 1.1.1:  now it calls the correct interrupt vector for the MCU in use
v. 1.1.0:  fixed several issues with ATtinyx313 and ATtinyx5
v. 1.0.1:  fixed Atmega8/A support
v. 1.0.0:  new methods and bug fixing
v. 0.1.0:  the library can enable/disable an interrupt on AC
v. 0.0.1:  early release - prototype of the library


***********************
How to use it - Methods

Unpack the library and copy it into your /libraries folder, that usually
is in your sketchs' folder. Then include the library by adding the
following code at the top of your sketch:

#include "analogComp.h"


Now you can set what has to be connected to the inverting (AIN-) and
non-inverting (AIN+) inputs of the analog comparator. Usually, the
AIN+ is connected to external pin AIN0 and the AIN- is connected to
external pin AIN1. The AIN+ can be connected to the internal voltage
reference (usually 1V1), while the AIN- can be connected to any of the
analog input pins of the microcontroller. (see "Supported Microcontrollers"
for specific limitations)


To choose the analog comparator inputs use the method setOn():

analogComparator.setOn([AIN+, AIN-]);

For the AIN+ you can choose between the following:
AIN0: set the AIN0 pin as input
INTERNAL_REFERENCE: set the internal voltage reference as input

For the AIN- you can choose between the following:
AIN1: set the AIN1 pin as input
A0..Ax: set the Analog Input Channel (max number depends of the MCU)

AIN+ and AIN- are optionals, if not set, AIN0 and AIN1 will be used.

You can enable an interrupt routine to be executed when an event occurs:

analogComparator.enableInterrupt(myFunction[, event]);

myFunction is the name of the function to be called when the event
occurs. event can be:
CHANGE: when the comparation changes between AIN+>AIN- and AIN+<AIN-
RISING: when the voltage on AIN+ becomes greater than the voltage on AIN-
FALLING: when AIN+ becomes smaller than AIN-
event is optional, if not set CHANGE will be choosen.


You can disable the interrupt by calling this method:

analogComparator.disableInterrupt();


You can wait for a comparation to occur:

analogComparator.waitComp([timeout]);

timeout is optional and rapresents the number of milliseconds to wait
before to return (default is 5000).
This method will return false (0) if voltage on AIN- will remain
greater than the voltage on AIN+ for the whole interval specified by
timeout; it will return true (1) if AIN+ will become greater than
AIN- during the interval.

If the analog comparator won't be set up before to call the waitComp
method, by default the library will use AIN0 and AIN1 pins.


To switch off the analog comparator, call this method:

analogComparator.setOff();

It will switch off the analog comparator and will disable any enabled
interrupt.


***********************
How it works

The Analog Comparator is an operational amplifier (op-amp) integrated
into the microcontroller. An op-amp has 2 inputs: a non-inverting input,
AIN+, and an inverting input, AIN-. When the voltage that is present on
the non-inverting input is greater than the voltage that is present on
the inverting input, the op-amp will set to high its output. The signal
can be used to raise an interrupt to do an automatic operation.
Different combinations of inverting and non-inverting inputs can be
selected by manipulating the internal registers.


***********************
Supported microcontrollers

Actually the library works with a wide variety of Atmel microcontrollers
and Arduino boards:
- Attiny2313/4313*
- Attiny24/44/84
- Attiny25/45/85
- Atmega344/644/1284
- Atmega8
- Atmega48/88/168/328 (Arduino UNO)
- Atmega640/1280/1281/2560/2561 (Arduino MEGA)
- Atmega32U4** (Arduino Leonardo)

Specific limitations:
* Attiny2313/4313:
due to the fact that these MCUs don't have an integrated ADC, only AIN1
is allowed for AIN-.

** Atmega32U4:
the Atmega32U4 AIN- can only be connected to an analog input pin because
it has no AIN1 pin.

***********************
Licence

This library is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3.0 of the License, or (at your
option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


***********************
Document revision

7th revision: 2013/07/30
