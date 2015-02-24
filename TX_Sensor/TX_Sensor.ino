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
#define Open_D           8767848
#define Close_D          8767847

RCSwitch mySwitch = RCSwitch();

volatile boolean lowBattery = false; //Used to check if the interrupt has raised low battery
volatile boolean is_open = false;    //If it is true that means the relay is open
volatile boolean wdt_setup = false;
volatile boolean wdt_on = false;

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

    DDRB  &= ~(1<< Sens);    //Set Sens pin as input

    mySwitch.enableTransmit(TX);    //Enable transmit on pin TX
    mySwitch.setRepeatTransmit(2);  //Send the code twice just in case

    attachInterrupt(INT0, wakeup, LOW);

    //Notify the user mcu has loaded fine
    beep();
    beep();
}

void loop() {
    if (wdt_setup) {
        send_data(Open_D); //Send data out for open contact
        setup_watchdog(8); //Turn on watchdog for 4 sec delay
    }
    if (wdt_on)
    {
        PORTB |= (1 << LED);
    }

    else
    {
        wdt_disable(); //Turn off the WDT!
        attachInterrupt(INT0, wakeup, LOW);
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

void beep(){
    LED_on();
    delay(500);
    LED_off();
    delay(500);
}

void check_battery(){
    analogComparator.setOn(INTERNAL_REFERENCE, AIN1); //Setup analog comparator
    analogComparator.enableInterrupt(battStatus, LOW);
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
//    WDTCR |= (1<<WDCE) | (1<<WDE);               //Set WD_change enable, set WD enable
//    WDTCR = bb;                                  //Set new watchdog timeout value
 //   WDTCR |= _BV(WDIE);                          //Set the interrupt enable, this will keep unit from resetting after each int
}

//interrupt to be raised by the analog comparator
void battStatus(){
    lowBattery = true; //let's inform the main loop that the condition has been reached by the analog comparator
}

//interrupt for contact open
void wakeup(){
        wdt_setup = true;
        detachInterrupt(INT0);
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