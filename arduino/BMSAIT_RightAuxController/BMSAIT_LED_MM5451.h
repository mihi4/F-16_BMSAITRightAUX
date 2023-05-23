// settings and functions to drive LEDs through an MM5451 LED driver chip
// V0.1 13.09.2022

// datenfeld.target defines the MM5451 device (in an array)
// datenfeld.ref2 sets the pin of a single LED
// datenfeld.ref2 sets a timemark for fast blink (2 switches per second)
// datenfeld.ref3 sets a timemark for slow blink (1 switch per second)

#include "MM5451.h"

#define BLINKSPEED 500  //pause (in ms) between on/off for fast blinking. Slow blinking will be 50%
unsigned long LEDTimer;


MM5451 mm5451[]={
    MM5451(4,5)
    //MM5451(6,7)
}; // create instances of chip classes, parameters are CLK and DATA pin 

const byte mm5451anz = sizeof(mm5451)/sizeof(mm5451[0]); 

void SetupLED_MM5451()
{
    for (byte x=0; x<mm5451anz; x++) {
        mm5451[x].lightAll();
    }
    delay(800);
    for (byte x=0; x<mm5451anz; x++) {
        mm5451[x].clearAll();
    }
}

void UpdateBlink()
{
  LEDTimer=millis();
  for(byte a = 0; a < VARIABLENANZAHL; a++)
  {
    if (datenfeld[a].typ==13)
    {
      if (datenfeld[a].ref3==1)
      {
        datenfeld[a].ref3=0;
        if (datenfeld[a].ref4==0)
          {datenfeld[a].ref4=1;}
        else
          {datenfeld[a].ref4=0;}
      }
      else
      {
        datenfeld[a].ref3=1;
      }
    }
  }
}

void LED_On(byte chipIndex, byte ledNumber) {  // this function sets the status of the appropriate output of the chip, but doesn't send it yet
    mm5451[chipIndex].setOutput(ledNumber, true);
}
void LED_Off(byte chipIndex, byte ledNumber) {
    mm5451[chipIndex].setOutput(ledNumber, false);
}

void UpdateLED_MM5451(byte p)
{
  // if the first character is T(rue) or 1 (on, no blink), the LED will be turned on
  if ((datenfeld[p].wert[0]=='T') || (datenfeld[p].wert[0]=='1'))
  {
    LED_On(datenfeld[p].target,datenfeld[p].ref2);
  }
  else if (datenfeld[p].wert[0]=='3') //fast blinking LED
  {
    if (datenfeld[p].ref3==1)
    { LED_On(datenfeld[p].target,datenfeld[p].ref2); }
    else
    { LED_Off(datenfeld[p].target,datenfeld[p].ref2); }
  }
  else if (datenfeld[p].wert[0]=='2') //slow blinking LED
  {
    if (datenfeld[p].ref4==1)
    { LED_On(datenfeld[p].target,datenfeld[p].ref2); }
    else
    { LED_Off(datenfeld[p].target,datenfeld[p].ref2);}
  }
  else         // otherwise the LED will be turned off
  {
    LED_Off(datenfeld[p].target,datenfeld[p].ref2);
  }
  
  mm5451[(datenfeld[p].target)].outputDataBits();  // let MM5451 chip send out all LED data bits
  
  if (millis()>LEDTimer+BLINKSPEED)
  { UpdateBlink(); }
}
