#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

#define rLUX 6
#define rAMP 7

void setup() {

  pinMode(rLUX, OUTPUT);
  pinMode(rAMP, OUTPUT);

  digitalWrite(rLUX, LOW);
  digitalWrite(rAMP, LOW);

  //  if (getDate(__DATE__) && getTime(__TIME__)) {
  //    parse = true;
  //    // and configure the RTC with this info
  //    if (RTC.write(tm)) {
  //      config = true;
  //    }
  //  }

}

void loop() {

  

  if (!digitalRead(A3)) {
    
    // MAN
    if (digitalRead(A1)) {
      digitalWrite(rLUX, HIGH);
    }
    else {
      digitalWrite(rLUX, LOW);
    }
    
    if (digitalRead(A2)) {
      digitalWrite(rAMP, HIGH);
    }
    else {
      digitalWrite(rAMP, LOW);
    }
    
  }
  else {
    // AUTO

    tmElements_t tm;

    RTC.read(tm);

    //TRA LE 8.30 E LE 12.00
    if ((tm.Hour >= 8) && (tm.Hour < 12)) {
      //A .30 e .00 ACCENDI AMPLI PER 25 MIN
      if (((tm.Minute >= 30) && (tm.Minute < 55)) || ((tm.Minute >= 0) && (tm.Minute < 25))) {
        digitalWrite(rAMP, HIGH);
      }
      else {
        digitalWrite(rAMP, LOW);
      }
    }

    //DALLE 12.00 ALLE 17.00
    else if ((tm.Hour >= 12) && (tm.Hour < 16)) {

      if (((tm.Minute >= 30) && (tm.Minute < 55)) || ((tm.Minute >= 0) && (tm.Minute < 25))) {
        //A .30 e .00 ACCENDI AMPLI PER 25 MIN
        digitalWrite(rAMP, HIGH);

        //A .30 e .00 ACCENDI ACCENDI ANCHE LA LUCE
        switch (tm.Hour) {

          case 12:
            if (((tm.Minute >= 30) && (tm.Minute < 35)) || ((tm.Minute >= 0) && (tm.Minute < 5))) {
              digitalWrite(rLUX, HIGH);
            }
            else {
              digitalWrite(rLUX, LOW);
            }
            break;

          case 13:
            if (((tm.Minute >= 30) && (tm.Minute < 40)) || ((tm.Minute >= 0) && (tm.Minute < 10))) {
              digitalWrite(rLUX, HIGH);
            }
            else {
              digitalWrite(rLUX, LOW);
            }
            break;

          case 14:
            if (((tm.Minute >= 30) && (tm.Minute < 45)) || ((tm.Minute >= 0) && (tm.Minute < 15))) {
              digitalWrite(rLUX, HIGH);
            }
            else {
              digitalWrite(rLUX, LOW);
            }
            break;

          case 15:
            if (((tm.Minute >= 30) && (tm.Minute < 50)) || ((tm.Minute >= 0) && (tm.Minute < 20))) {
              digitalWrite(rLUX, HIGH);
            }
            else {
              digitalWrite(rLUX, LOW);
            }
            break;

          default:
            break;

        }

      }
      else {
        digitalWrite(rAMP, LOW);
      }
    }

    //DALLE 16.00 ALLE 20.00
    else if ((tm.Hour >= 16) && (tm.Hour < 21)) {

      digitalWrite(rAMP, HIGH);      
      digitalWrite(rLUX, HIGH);

    }

    else {
      // FUORI DAGLI ORARI DI APERTURA DEL MUSEO
      digitalWrite(rAMP, LOW);
      digitalWrite(rLUX, LOW);
    }

    delay(1000);

  }
}


// NINA CARINA
// NEOTECH
// VIA SAVONA 118
//
