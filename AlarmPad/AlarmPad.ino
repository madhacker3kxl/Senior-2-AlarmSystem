/*
 * LCD RS pin to digital pin 9
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 7
 * LCD D5 pin to digital pin 6
 * LCD D6 pin to digital pin 5
 * LCD D7 pin to digital pin 4
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
*/
#include <LiquidCrystal.h>
#include <RCSwitch.h>

#define TX   11       //TX Pin

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

void setup()
{
    lcd.begin(24, 1);
    
    lcd.print("hello, world!");
    
    mySwitch.enableTransmit(TX);
    mySwitch.enableReceive(0);     //Enable receive on interrupt pin 0
     
}

void loop()
{
    lcd.setCursor(15, 1);
    // print the number of seconds since reset:
    lcd.print(millis() / 1000);

}
