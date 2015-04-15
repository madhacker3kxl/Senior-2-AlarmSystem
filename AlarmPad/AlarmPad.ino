/*
* LCD RS pin to digital pin 3
* LCD Enable pin to digital pin 4
* LCD D4 pin to digital pin 5
* LCD D5 pin to digital pin 6
* LCD D6 pin to digital pin 7
* LCD D7 pin to digital pin 8
* LCD R/W pin to ground
* LCD VSS pin to ground
* LCD VCC pin to 5V
*/

#include <avr/power.h>
#include <avr/sleep.h>
//External Libraries
#include <LiquidCrystal.h>
#include <RCSwitch.h>

//Pin definition
#define TX      11   //TX Pin
#define RX      0    //Pin 2 in Arudino for External INT0
#define BL      9    //Backlight pin
#define Status 13    //Status pin

//Codes for Door / window sensors
#define Sensor_1    5101
#define Sensor_2    5102
#define Sensor_3    5103
#define Sensor_4    5104
#define Sensor_5    5105
#define Sensor_6    5105
#define Sensor_7    5106
#define Sensor_8    5107

//Codes for Motion Sensor

//Other codes
#define Alarm_On    1234
#define Alarm_Off   5678

//Output codes
#define Notify_Code 8080
#define Doorbell    8180
#define Panic_On    9198
#define Panic_off   9098

// initialize the libraries with the numbers of the interface pins
LiquidCrystal lcd(8, //RS Pin
                  7, //Enable Pin
                  3, //D4
                  4, //D5
                  5, //D6
                  6);//D7
                  
RCSwitch mySwitch = RCSwitch();

bool is_armed = false;
long startTime;
long duration;

void setup()
{
    //Power off not needed stuff
    ADCSRA &= ~(1<<ADEN);	//Disable ADC
    ACSR   &= ~(1<<ACD);	//Disable Analog Comparator
    MCUCR  &= ~(1<<BODS);   //Disable Brownout Stuff
    sleep_bod_disable();    //Disable Brownout detect on sleep

    power_all_disable();    //Turn all the peripherals clock off
    power_timer0_enable();  //Turn on timer0 clock on
    power_timer1_enable();  //Turn on timer1 clock on
    
    lcd.begin(20, 4);       //Setup LCD
    
    //Setup needed pins
    DDRB  |= (1 << BL);	    //Set Back light pin as output
    analogWrite(BL,255);

    mySwitch.enableTransmit(TX);

    setup_display();
    
    send_data(Notify_Code);     //Notify user that system is ready
}

void loop()
{
    timing_stuff(); //Sets up timing for timed functions

}

void timing_stuff()
{
    startTime = millis();
    duration  = ((millis() - startTime) / 1000);
    
    if (duration >= 20) //Every 20 seconds redraw screen
    {
        lcd.clear(); //for to test the code
    }
    
    lcd.setCursor(9, 1);
    //print the number of seconds since reset
    lcd.print((startTime / 1000));
    lcd.setCursor(8,2);
    lcd.print(duration);
}

void send_data(int data)
{
    mySwitch.disableReceive();  //Disable transmit
    mySwitch.send(data,24);     //Send data out
    mySwitch.enableReceive(RX); //Enable transmit
}

void setup_display()
{
    lcd.setCursor(0,0);
    lcd.print("** Ninja Security **");
    lcd.setCursor(0,1);
    lcd.print("MAG Sen: ");
    lcd.setCursor(0,2);
    lcd.print("Motion: ");
    lcd.setCursor(0,3);
    
    if (is_armed)
    lcd.print("****** ARMED ******");
    else
    lcd.print("**** NOT ARMED ****");
}