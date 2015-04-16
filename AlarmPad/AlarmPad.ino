#include <avr/power.h>
#include <avr/sleep.h>
//External Libraries
#include <LiquidCrystal.h>
#include <RCSwitch.h>

//Pin definition
#define TX      13   //TX Pin
#define RX      0    //Pin 2 in Arudino for External INT0
#define BL      9    //Backlight pin
#define Status 13    //Status pin

//Codes for Door / window sensors
#define Sensor_1    5101
#define Sensor_2    5102
#define Sensor_3    5103
#define Sensor_4    5104
#define Sensor_5    5105
#define Sensor_6    5106
#define Sensor_7    5107
#define Sensor_8    5108

//Codes for Motion Sensor
#define Motion_1    8767849
#define Motion_2    6037225
#define Motion_3    12265513
#define Motion_4    13953641

//Other codes
#define Alarm_On    5592332
#define Alarm_Off   5592512

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

bool is_armed = false;
long startTime;
long duration;

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
    
    //Setup needed pins
    DDRB  |= (1 << BL);	    //Set Back light pin as output
    analogWrite(BL,255);

    mySwitch.enableTransmit(TX);

    setup_display();
    
    send_data(Notify_Code);  //Notify user that system is ready
}

void loop()
{
    timing_stuff(); //Sets up timing for timed functions
    
    if (mySwitch.available()) { //check for received code
        
        int value = mySwitch.getReceivedValue();
        Serial.println(value);
        
        //Compare the received code and run the defined function
        switch (value) {
            case Alarm_On:
                is_armed = true;
                lcd.setCursor(0,3);
                lcd.print("****** ARMED ******");
                break;
            case Alarm_Off:
                is_armed = false;
                lcd.setCursor(0,3);
                lcd.print("**** NOT ARMED ****");
                send_data(Panic_off);
                break;
            case Motion_1:
            case Motion_2:
            case Motion_3:
            case Motion_4:
                if (is_armed)
                {
                    send_data(Panic_On);
                } 
                else
                {
                    
                }
                break;
            case Sensor_1:
                if (is_armed)
                {
                    alarmed_door_open();
                }
            case Sensor_2:
            case Sensor_3:
            case Sensor_4:
            case Sensor_5:
            case Sensor_6:
            case Sensor_7:
            case Sensor_8:
                 if (is_armed)
                 {
                     send_data(Panic_On);
                 } 
                 else
                 {
                     
                 }
                 break;
        }            
        mySwitch.resetAvailable();
    }
    
    if (duration > 20)
    {
        lcd.clear();
        duration = 0;
    }

}

void timing_stuff()
{
    startTime = millis();
    duration  = ((millis() - startTime) / 1000);
    
    lcd.setCursor(9, 1);
    //print the number of seconds since reset
    lcd.print((startTime / 1000));
    lcd.setCursor(8,2);
    lcd.print(duration);
    
    if (duration > 40) {duration = 0;}
}

void send_data(int data)
{
    mySwitch.disableReceive();  //Disable transmit before sending
    mySwitch.send(data,24);     //Send data out
    mySwitch.enableReceive(0); //Enable transmit
}

void alarmed_door_open() {
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
    
    if (is_armed)
    lcd.print("****** ARMED ******");
    else
    lcd.print("**** NOT ARMED ****");
}