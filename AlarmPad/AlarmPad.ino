#include <avr/power.h>
#include <avr/sleep.h>
//External Libraries
#include <LiquidCrystal.h>
#include <Keypad_I2Ca.h>
#include <Wire.h>
#include <Keypad.h>
#include <RCSwitch.h>

//Pin definition
#define TX      13   //TX Pin
#define RX      0    //Pin 2 in Arudino for External INT0
#define BL      9    //Backlight pin
#define Status 13    //Status pin

//LCD value display positions
#define MotionPos 8  //Starting location for motion sensor display
#define MagPos    8  //Starting location for magnetic sensor display

//Keypad Stuffs
#define I2CADDR 0x3f

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};
byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pin outs of the keypad
byte colPins[COLS] = {4, 5, 6, 7}; //connect to the column pin outs of the keypad

Keypad_I2Ca keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR );

//Codes for Door / window sensors
#define Sensor_1        5101
#define Sensor_1_Off    5201
#define Sensor_2        5102
#define Sensor_2_Off    5202
#define Sensor_3        5103
#define Sensor_3_Off    5203
#define Sensor_4        5104
#define Sensor_4_Off    5204
#define Sensor_5        5105
#define Sensor_5_Off    5205
#define Sensor_6        5106
#define Sensor_6_Off    5206
#define Sensor_7        5107
#define Sensor_7_Off    5207
#define Sensor_8        5108
#define Sensor_8_Off    5208

//Codes for Motion Sensor
#define Motion_1    8767849
#define Motion_2    6037225
#define Motion_3    12265513
#define Motion_4    13953641

//Other codes
#define Away_On     5592332
#define Stay_ON     'A'
#define Alarm_Off   5592512
#define Doorbell_btn 13976880

//Output codes
#define Notify_Code 8080
#define Doorbell    8180
#define Panic_On    9198
#define Panic_off   9098

// initialize the libraries with the numbers of the interface pins
//Setup LCD
LiquidCrystal lcd(8, //RS Pin
                  7, //Enable Pin
                  3, //D4
                  4, //D5
                  5, //D6
                  6);//D7
                
RCSwitch mySwitch = RCSwitch();

//Motion sensor location clear
#define Motion_Clr_Wait 4
bool motion_tmr_flag = false;
byte m1;
byte m2;
byte m3;
byte m4;

bool is_away = false;
bool is_stay = false;

//Other testing stuff


void setup()
{
    Serial.begin(9600);
    //Power off not needed stuff
    ADCSRA &= ~(1<<ADEN);	//Disable ADC
    ACSR   &= ~(1<<ACD);	//Disable Analog Comparator
    MCUCR  &= ~(1<<BODS);   //Disable Brownout Stuff
    sleep_bod_disable();    //Disable Brownout detect on sleep

    power_all_disable();    //Turn all the peripherals clock off
    power_timer0_enable();  //Turn on timer0 clock on
    power_timer1_enable();  //Turn on timer1 clock on
    
    lcd.begin(20, 4);       //Setup LCD
   // keypad.begin( );        //Setup Keypad
    
    //Setup needed pins
    DDRB  |= (1 << BL);	    //Set Back light pin as output
    analogWrite(BL,255);

    mySwitch.enableTransmit(TX);

    setup_display();
    
    send_data(Notify_Code);  //Notify user that system is ready
}

void loop()
{
    MotionClr();
    
    if (mySwitch.available()) { //check for received code
        
        unsigned int value = mySwitch.getReceivedValue();
        Serial.println(value);
        
        //Compare the received code and run the defined function       
        
        delay(1000);
        if (is_away)
        {
            motion(&value);
            mag(&value);
            send_data(Panic_On);
        }
        else if (is_stay)
        {
            mag(&value);
            send_data(Panic_On);
        }
        else
        {
            motion(&value);
            mag(&value);
            mag_clr(&value);
        }
		Alarm_ON_Off(&value);
		Others(&value);
        
        mySwitch.resetAvailable();
    }
}

//Routine for Alarm ON/Off and notification on display
void Alarm_ON_Off(unsigned int *x)
{
    switch (*x) {
        case Away_On:
        is_away = true;
        lcd.setCursor(0,3);
        lcd.print("****** AWAY ******");
        break;
        case Stay_ON:
        is_stay = true;
        lcd.setCursor(0,3);
        lcd.print("****** Stay ******");
        break;
        case Alarm_Off:
        is_away = false;
        is_stay = false;
        lcd.setCursor(0,3);
        lcd.print("**** NOT ARMED ****");
        send_data(Panic_off);
        break;
    }
}

//Comparison for motion sensor values.
//It also sets the notification timers for the sensor
void motion(unsigned int *x)
{
    switch (*x)
    {
        case Motion_1:
        lcd.setCursor(MotionPos,2);
        lcd.print("1");
        m1 = (millis() / 1000);
        motion_tmr_flag = true;
        break;
        case Motion_2:
        lcd.setCursor(MotionPos + 2,2);
        lcd.print("2");
        m2 = (millis() / 1000);
        motion_tmr_flag = true;
        break;
        case Motion_3:
        lcd.setCursor(MotionPos + 4,2);
        lcd.print("3");
        m3 = (millis() / 1000);
        motion_tmr_flag = true;
        break;
        case Motion_4:
        lcd.setCursor(MotionPos + 6,2);
        lcd.print("4");
        m4 = (millis() / 1000);
        motion_tmr_flag = true;
        break;
    }
}

//Comparison for Window/Door sensor values.
void mag(unsigned int *x)
{
    switch (*x) {
        case Sensor_1:
        lcd.setCursor(MagPos,1);
        lcd.print("1");
        break;
        case Sensor_2:
        lcd.setCursor(MagPos + 1,1);
        lcd.print("2");
        break;
        case Sensor_3:
        lcd.setCursor(MagPos + 2,1);
        lcd.print("3");
        break;
        case Sensor_4:
        lcd.setCursor(MagPos + 3,1);
        lcd.print("4");
        break;
        case Sensor_5:
        lcd.setCursor(MagPos + 4,1);
        lcd.print("5");
        break;
        case Sensor_6:
        lcd.setCursor(MagPos + 5,1);
        lcd.print("6");
        break;
        case Sensor_7:
        lcd.setCursor(MagPos + 6,1);
        lcd.print("7");
        break;
        case Sensor_8:
        lcd.setCursor(MagPos + 7,1);
        lcd.print("8");
        break;
    }
}

//Routine for clearing the Window/Door sensor notification on LCD display
void mag_clr(unsigned int *x)
{
    switch (*x) {
        case Sensor_1_Off:
        lcd.setCursor(MagPos,1);
        lcd.print(" ");
        break;
        case Sensor_2_Off:
        lcd.setCursor(MagPos + 1,1);
        lcd.print(" ");
        break;
        case Sensor_3_Off:
        lcd.setCursor(MagPos + 2,1);
        lcd.print(" ");
        break;
        case Sensor_4_Off:
        lcd.setCursor(MagPos + 3,1);
        lcd.print(" ");
        break;
        case Sensor_5_Off:
        lcd.setCursor(MagPos + 4,1);
        lcd.print(" ");
        break;
        case Sensor_6_Off:
        lcd.setCursor(MagPos + 5,1);
        lcd.print(" ");
        break;
        case Sensor_7_Off:
        lcd.setCursor(MagPos + 6,1);
        lcd.print(" ");
        break;
        case Sensor_8_Off:
        lcd.setCursor(MagPos + 7,1);
        lcd.print(" ");
        break;
    }
}

//Routine for clearing the motion sensor notification on LCD display
void MotionClr()
{
    byte pos1 = ((millis() / 1000) - m1);
    byte pos2 = ((millis() / 1000) - m2);
    byte pos3 = ((millis() / 1000) - m3);
    byte pos4 = ((millis() / 1000) - m4);
    
    if (pos1 > Motion_Clr_Wait)
    {
        m1 = 0;
        lcd.setCursor(MotionPos,2);
        lcd.print(" ");
    }
    
    if (pos2 > Motion_Clr_Wait)
    {
        m2 = 0;
        lcd.setCursor(MotionPos + 2,2);
        lcd.print(" ");
    }
    
    if (pos3 > Motion_Clr_Wait)
    {
        m3 = 0;
        lcd.setCursor(MotionPos + 4,2);
        lcd.print(" ");
    }
    
    if (pos4 > Motion_Clr_Wait)
    {
        m4 = 0;
        lcd.setCursor(MotionPos + 6,2);
        lcd.print(" ");
    }
}

void Others(unsigned int *x)
{
	switch (*x) {
        case Doorbell_btn:
        send_data(Doorbell); //Send the Doorbell code
        break;
    }        
}

void send_data(int data)
{
    mySwitch.disableReceive(); //Disable transmit before sending
    mySwitch.send(data,24);    //Send data out
    mySwitch.enableReceive(0); //Enable transmit
}

void alarmed_door_open() 
{
    //When the main door is opened, turn the buzzer on the alarm pad,
    //give the user 15 second to put the right password
    long startTime = millis();
    long duration;
    bool pass_correct = false;
    while (duration < 15)
    {
        duration = ((millis() - startTime) / 1000);
    }
    
    if (pass_correct)
    {
        
    } 
    else
    {
        send_data(Panic_On);
    }
        
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
    
    if (is_away)
    lcd.print("****** ARMED ******");
    else
    lcd.print("**** NOT ARMED ****");
}