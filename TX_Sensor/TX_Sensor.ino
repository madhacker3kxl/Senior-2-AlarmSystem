#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/io.h>
#include <avr/wdt.h> //Needed to enable/disable watch dog timer
#include <RCSwitch/RCSwitch.h>
#include <analogComp-master/analogComp.h>

#define TX   PINB4      //TX Pin
#define LED  PINB3		//LED Pin
#define Sens PINB2      //Input pin

#define low_Batt_code    13976880 //Code for low battery
const int Open_D =           8767848;
const int Close_D =         8767847;

RCSwitch mySwitch = RCSwitch();

volatile boolean lowBattery = false; //Used to check if the interrupt has raised low battery
volatile boolean is_open = false;    //If it is true that means the relay is open
volatile boolean wdt_setup = false;

void setup() {
    //Power off not needed stuff
    ADCSRA &= ~(1<<ADEN);	//Disable ADC
    ACSR   &= ~(1<<ACD);	//Disable Analog Comparator
    MCUCR  &= ~(1<<BODS);   //Disable Brownout Stuff
    sleep_bod_disable();    //Disable Brownout detect on sleep

    power_all_disable();    //Turn all the peripherals clock off
    power_timer0_enable();  //Turn on timer0 clock on
    power_timer1_enable();  //Turn on timer1 clock on

    //Setup needs pins
    DDRB  |= (1 << LED);	//Set notification pin as output
    PORTB &= ~(1 << LED);   //Set the notification pin as low just in case

    DDRB  &= ~(1<< Sens);   //Set Sens pin as input
    PORTB &= ~(1 << Sens);  //Tri-state the input (no pull-up)

    DDRB  |= (1 << TX);	    //Set notification pin as output

    mySwitch.enableTransmit(TX);     //Enable transmit on pin TX

    attachInterrupt(0, wakeup, LOW); // Setup initial interrupt from sleep

    //Notify the user mcu has loaded fine
    beep();
}

void loop() {

    if ((1<<Sens))
    {
        wdt_setup = false;          //Turn off WDT setup function
        wdt_disable();              //Turn off the WDT!
        //enable_batt_check();        //Enable comparitor for battery check

        send_data(Close_D);         //Send data for closed contact
        //check_battery();
        attachInterrupt(0, wakeup, LOW);   //Turn on wake up interrupt
    }

    if (wdt_setup)
    {
        //enable_batt_check();
        send_data(Open_D); //Send data out for open contact
        //check_battery();
        setup_watchdog(8); //Turn on watchdog for 4 sec delay
        beep();
        beep();
    }

    sleep();
}

void sleep(){
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); //Set sleep mode to deep sleep
    sleep_enable();                      //Enable sleep mode

    analogComparator.setOff();           //Turn off analog comparator before sleeping

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
    if (lowBattery) {
        LED_on();                         //Turn on LED
        mySwitch.send(low_Batt_code, 24); //send the 24bit low battery code
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

        //Set up the pins again just incase
        DDRB  &= ~(1<< Sens);   //Set Sens pin as input
        PORTB &= ~(1 << Sens);  //Tri-state the input (no pull-up)
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

ISR(WDT_vect) { //Watch-dog interrupt vector
    //Don't do anything. This is just here so that we wake up.
}