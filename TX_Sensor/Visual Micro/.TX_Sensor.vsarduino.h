/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: ATtiny x5 w/ ATtiny85 @ 8 MHz  (internal oscillator; BOD disabled), Platform=avr, Package=attiny 1.5.8-2
*/

#define __AVR_ATtiny85__
#define __AVR_ATTINY85__
#define ARDUINO 160
#define ARDUINO_MAIN
#define F_CPU 8000000L
#define __AVR__
extern "C" void __cxa_pure_virtual() {;}

//
//
void sleep();
void beep();
void enable_batt_check();
void check_battery();
void setup_watchdog(int timerPrescaler);
void battStatus();
void wakeup();
void send_data(int data);
void LED_on();
void LED_off();

#include "C:\Users\Tahsin\Documents\Arduino\hardware\attiny 1.5.8-2\avr\cores\tiny\arduino.h"
#include <TX_Sensor.ino>
