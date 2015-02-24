#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/io.h>
#include <avr/wdt.h> //Needed to enable/disable watch dog timer
#include <RCSwitch/RCSwitch.h>
#include <analogComp-master/analogComp.h>

#define TX   PINB4      //TX Pin
#define LED  PINB0		//LED Pin
#define Sens PINB2      //Input pin
#define low_Batt_code    101010 //Code for low battery

RCSwitch mySwitch = RCSwitch();

boolean lowBattery = false; //used to check if the interrupt has raised low battery

void setup() {
    //Power off not needed stuff
    ADCSRA &= ~(1<<ADEN);	//Disable ADC
    ACSR   &= ~(1<<ACD);	//Disable Analog Comparator
    MCUCR  &= ~(1<<BODS);   //Disable Brownout Stuff
    sleep_bod_disable();    //Disable Brownout detect on sleep

    power_all_disable();    //Turn all the peripherals clock off
    power_timer0_enable();  //Turn on timer0 clock on
    power_timer1_enable();  //Turn on timer1 clock on

    DDRB  |= (1 << LED);	//Set notification pin as output
    PORTB &= ~(1 << LED);   //Set the notification pin as low just in case

    DDRB  &= (1<< Sens);    //Set Sens pin as input

    mySwitch.enableTransmit(TX);    //Enable transmit on pin TX
    mySwitch.setRepeatTransmit(2);  //Send the code twice just in case

    //Notify the user mcu has loaded fine
    beep();
    beep();

void loop() {
    analogComparator.setOn(INTERNAL_REFERENCE, AIN1); //Setup analog comparator
    analogComparator.enableInterrupt(battStatus, LOW);

    if (lowBattery) {
        mySwitch.send(low_Batt_code, 24); //send the 24bit low battery code
    }

    else sleep();
}

void sleep(){
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); //Set sleep mode to deep sleep
    sleep_enable();                      //Enable sleep mode

    analogComparator.setOff();           //Turn off analog comparator before sleeping

    sleep_mode();                        //Go to sleep
    sleep_disable();                     //Disable sleep
}

void beep(){
    delay(500);
    PORTB |= (1 << LED);     //Turn on
    delay(500);
    PORTB &= ~(1 << LED);    //Turn off
}

//interrupt to be raised by the analog comparator
void battStatus() {
    lowBattery = true; //let's inform the main loop that the condition has been reached by the analog comparator
}