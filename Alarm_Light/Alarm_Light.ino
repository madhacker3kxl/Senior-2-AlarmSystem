//Function of the system:
//The system is based on 433MHz ASK RF

#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/wdt.h> //Needed to enable/disable watch dog timer

//External Libraries
#include <RCSwitch.h>
#include <pitches.h>

//Pins going to use
//#define RX   INT0    //RX Pin
#define Light  PINB3   //Flasher Pin
#define Sound  PINB4   //Sound output pin

//Receive codes
const int N_Code     = 8080; //Notification code
const int D_Code     = 8180; //Doorbell code
const int P_Code_On  = 9198; //Panic mode on code
const int P_Code_Off = 9098; //Panic mode off code

RCSwitch mySwitch = RCSwitch();

void setup() {
  //Power off not needed stuff
  ADCSRA &= ~(1 << ADEN); //Disable ADC
  ACSR   &= ~(1 << ACD);  //Disable Analog Comparator
  MCUCR  &= ~(1 << BODS); //Disable Brownout Stuff
  sleep_bod_disable();    //Disable Brownout detect on sleep

  power_all_disable();    //Turn all the peripherals clock off
  power_timer0_enable();  //Turn on timer0 clock on
  power_timer1_enable();  //Turn on timer1 clock on

  //Setup needed pins
  DDRB  |= (1 << Light);  //Set Out pin as output
  PORTB &= ~(1 << Light); //Set the pin as low just in case
  DDRB  |= (1 << Sound);  //Set Sound pin as output
  PORTB &= ~(1 << Sound); //Set the pin as low just in case

  mySwitch.enableReceive(0); //Enable receive on pin RX

  //Notify the user mcu has loaded fine
  notify();
}

void loop() {
  if (mySwitch.available()) {

    int value = mySwitch.getReceivedValue();

    if (value == N_Code) {
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

//Strobe for 2 seconds for notification
void notify() {
  PORTB |= (1 << Light);
  delay(2000);
  PORTB &= ~(1 << Light);
}

//Strobe and play audio for notification
void doorbell() {
  PORTB |= (1 << Light); //
  Doorbell_Audio();     //Play the doorbell audio
  PORTB &= ~(1 << Light);
}

void panic_on() {
  PORTB |= (1 << Light);
}

void panic_off() {
  PORTB &= ~(1 << Light);
}

//Underworld melody
const int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underworld tempo
const int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

//Audio for the doorbell
void Doorbell_Audio() {
  // iterate over the notes of the melody:
  int size = sizeof(underworld_melody) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / underworld_tempo[thisNote];

    tone(Sound, underworld_melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    // stop the tone playing:
    tone(Sound, 0, noteDuration);
  }
}
