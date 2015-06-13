# Senior-2-AlarmSystem
Code for senior 2 project. Alarm system for deaf/hearing impaired.

This is still work on progress!! Not finished code!

See FinalReport.pdf for more information about the project

The entire project is made using Atmel Visual Studio with Visual Micro plugin.
The Arduino libraries are used to make things simple.

Folder Structures:

Alarm_Light: It is a modified fire alarm with Xenon strobe and a speaker
AlarmPad: The base station alarm pad
BedShaker: Motorized bedshaker that shakes the bed
TX_Sensors: The window and door sensors

Schematics: Files for Multisim and Ultiboard.
	Note: Eagle Cad was not used since it was causing problems. The custom user database
	 is located at Useful Codes -> MultiSim User parts database -> UsrComp_S_Tahsin.usr

Useful Codes: Contains all the things that has been used. eg. Libraries, MCU core files, Custom user
			database used for the schematic.


Resources:

	MCU Core:
		ATtiny-core for Arduino: http://www.leonardomiliani.com/en/arduino/
		
	Libraries:
		RCSwitch library: http://code.google.com/p/rc-switch/
		AnalogComparator library: https://github.com/leomil72/analogComp
		Keypad library: http://playground.arduino.cc/Code/Keypad
		
Ignore things in the "Visual Micro" folder 
