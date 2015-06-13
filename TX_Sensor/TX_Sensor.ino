//Function of the system:
//The system is based on 433MHz ASK RF
//On startup everything is shutoff to conserve power and goes to sleep
//When the interrupt pin goes low the MCU wakes up
//It turns of the watchdog flag on and turns off the interrupt 0
//In the main loop it checks for if the Sens pin goes back to high
//If it is not high it sets up watchdog on for every 4 seconds
//It also sends the open signal through RF
//Before sending signal the analog comparator is turned on to check for battery level
//If the battery is low, the low battery signal is sent
//If the Sens pin goes back high, the watchdog is turned back off, then goes to sleep
//The process repeats

#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/wdt.h> //Needed to enable/disable watch dog timer

//External Libraries
#include <RCSwitch.h>
#include <analogComp.h>

#define TX   PINB4      //TX Pin
#define LED  PINB3		//LED Pin
#define Sens PINB2      //Input pin
#define Fet  PINB0      //Power MOSFET for TX & Analog Comparator

const int low_Batt_code = 6880;  //Code for low battery
const int Open_D        = 5102;  //Code for Open
const int Close_D       = 5202;  //Code for Close

RCSwitch mySwitch = RCSwitch();

volatile boolean lowBattery = false;      //Used to check if the interrupt has raised low battery
volatile boolean is_data_sent = false;    //If it is true that means the relay is open
volatile boolean wdt_setup = false;       //Flag for watchdog

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
    DDRB  |= (1 << LED);	//Set notification pin as output
    PORTB &= ~(1 << LED);   //Set the notification pin as low just in case

    DDRB  &= ~(1<< Sens);   //Set Sens pin as input
    PORTB &= ~(1 << Sens);  //Tri-state the input (no pull-up)

    DDRB  |= (1 << TX);	    //Set notification pin as output

    DDRB  |= (1 << Fet);	//Set fet pin as output
    PORTB &= ~(1 << Fet);   //Set the fet pin as low to turn off power

    mySwitch.enableTransmit(TX);     //Enable transmit on pin TX

    attachInterrupt(0, wakeup, LOW); // Setup initial interrupt from sleep

    //Notify the user mcu has loaded fine
    beep();
}

void loop() {

    if (PINB && Sens)
    {
        FET_on();
        wdt_setup = false;               //Turn off WDT setup function
        wdt_disable();                   //Turn off the WDT!

        //enable_batt_check();             //Enable comparator for battery check

        send_data(Close_D);              //Send data for closed contact

        //check_battery();
        is_data_sent = false;            //Revert data sent flag
        attachInterrupt(0, wakeup, LOW); //Turn on wake up interrupt
    }

    if (wdt_setup == true)
    {
        FET_on();                   //Turn on power MOSFET
        //enable_batt_check();
        if (is_data_sent == false)  //Check for data sent flag
        {
            send_data(Open_D);      //Send data out for open contact
            is_data_sent = true;    //Set flag that data has been sent
        }

        //check_battery();
        setup_watchdog(8);          //Turn on watchdog for 4 sec delay
    }

    sleep();
}

void sleep(){
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); //Set sleep mode to deep sleep
    sleep_enable();                      //Enable sleep mode
    analogComparator.setOff();           //Turn off analog comparator before sleeping
    FET_off();                           //Turn off power MOSFET
    sleep_mode();                        //Go to sleep
    sleep_disable();                     //Disable sleep
}

void beep(){ //For various status display function
    LED_on();
    delay(500);
    LED_off();
    delay(500);
}

void enable_batt_check(){ //Functions for analog setup
     analogComparator.setOn(INTERNAL_REFERENCE, AIN1);  //Setup analog comparator
     analogComparator.enableInterrupt(battStatus, LOW); //Set interrupt for comparator
}

void check_battery(){
    if (lowBattery == true)
    {
        mySwitch.send(low_Batt_code, 24); //send low battery code
    }
}

void setup_watchdog(int timerPrescaler) {
    if (timerPrescaler > 9 ) timerPrescaler = 9; //Limit incoming amount to legal settings
    byte bb = timerPrescaler & 7;
    if (timerPrescaler > 7) bb |= (1<<5);        //Set the special 5th bit if necessary

    //This order of commands is important and cannot be combined
    MCUSR &= ~(1<<WDRF);                         //Clear the watch dog reset
    WDTCR |= (1<<WDCE) | (1<<WDE);               //Set WD_change enable, set WD enable
    WDTCR  = bb;                                 //Set new watchdog timeout value
    WDTCR |= _BV(WDIE);                          //Set the interrupt enable, this will keep unit from resetting after each int
}

//interrupt to be raised by the analog comparator
void battStatus(){
    lowBattery = true; //let's inform the main loop that the condition has been reached by the analog comparator
}

void wakeup(){  //interrupt for contact open
        detachInterrupt(0);     //Turn off pin interrupt
        wdt_setup = true;       //Activate the watch-dog setup function
}

void send_data(int data){
         LED_on();
         mySwitch.send(data, 24);
         LED_off();
}

void LED_on(){
    PORTB |= (1 << LED);     //Turn on LED
}

void LED_off(){
    PORTB &= ~(1 << LED);    //Turn off LED
}

void FET_on(){
    PORTB |= (1 << Fet);     //Turn on FET
}

void FET_off(){
    PORTB &= ~(1 << Fet);    //Turn off FET
}

ISR(WDT_vect) { //Watch-dog interrupt vector
    //Don't do anything. This is just here so that we wake up.
}
