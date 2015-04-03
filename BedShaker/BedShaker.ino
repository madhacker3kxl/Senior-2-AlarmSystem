//Function of the system:
//The system is based on 433MHz ASK RF
//The unit called the Bed Shaker. It receives three different codes.
//One for doorbell, one for panic alert, one for notifications.
//Patterns in dot-dash.
//Doorbell: .-.-.-.-
//Panic: ON
//Notifications: ..

#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/wdt.h> //Needed to enable/disable watch dog timer
#include <RCSwitch/RCSwitch.h>

//Pins going to use
#define RX   INT0       //RX Pin
#define OUT  PINB3		//Output Pin

//Receive codes
const int N_Code     = 8080; //Notification code
const int D_Code     = 8180; //Doorbell code 
const int P_Code_On  = 9198; //Panic mode on code
const int P_Code_Off = 9098; //Panic mode off code

RCSwitch mySwitch = RCSwitch();

void setup() {
	//Power off not needed stuff
	ADCSRA &= ~(1<<ADEN);	//Disable ADC
	ACSR   &= ~(1<<ACD);	//Disable Analog Comparator
	MCUCR  &= ~(1<<BODS);   //Disable Brownout Stuff
	sleep_bod_disable();    //Disable Brownout detect on sleep

	power_all_disable();    //Turn all the peripherals clock off
	power_timer0_enable();  //Turn on timer0 clock on
	power_timer1_enable();  //Turn on timer1 clock on

	//Setup needed pins
	DDRB  |= (1 << OUT);	//Set Out pin as output
	PORTB &= ~(1 << OUT);   //Set the pin as low just in case

	mySwitch.enableReceive(0);     //Enable receive on pin RX

	//Notify the user mcu has loaded fine
	notify();
}

void loop(){
	if (mySwitch.available()) {
		
		int value = mySwitch.getReceivedValue();
		
		if (value == N_Code){
			notify();
		}
		
		if (value == D_Code)
		{
			doorbell();
		}
		if (value == P_Code_On)
		{
			panic_on();
		}
		if (value == P_Code_Off)
		{
			panic_off();
		}
		mySwitch.resetAvailable();			
	}
}

void notify(){ //Notifications: ..
	PORTB |= (1 << OUT);
	delay(200);
	PORTB &= ~(1 << OUT);
	delay(300);
	PORTB |= (1 << OUT);
	delay(200);
	PORTB &= ~(1 << OUT);
	delay(300);
}

void doorbell(){ //Doorbell: .-.-
	PORTB |= (1 << OUT); //.
	delay(200);
	PORTB &= ~(1 << OUT);
	delay(300);
	PORTB |= (1 << OUT); //-
	delay(600);
	PORTB &= ~(1 << OUT);
	delay(300);
	PORTB |= (1 << OUT); //.
	delay(200);
	PORTB &= ~(1 << OUT);
	delay(300);
	PORTB |= (1 << OUT); //-
	delay(600);
	PORTB &= ~(1 << OUT);
	delay(300);
}

void panic_on(){
	PORTB |= (1 << OUT);
}

void panic_off(){
	PORTB &= ~(1 << OUT);
}