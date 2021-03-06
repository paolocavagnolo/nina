#include <ThreeWire.h>  
#include <RtcDS1302.h>

#define rLUX 6
#define rAMP 7

ThreeWire myWire(3,4,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);


void setup() {
  
  pinMode(rLUX, OUTPUT);
  pinMode(rAMP, OUTPUT);

  digitalWrite(rLUX, LOW);
  digitalWrite(rAMP, LOW);

  Rtc.Begin();
  //RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
}

void loop() {
  
  RtcDateTime now = Rtc.GetDateTime();

  //TRA LE 8.30 E LE 13.00
  if ((now.Hour() >= 8) && (now.Hour() < 13)) {
    //A .30 ACCENDI AMPLI PER 25 MIN
    if ((now.Minute() >= 30) && (now.Minute() < 55)) {
      digitalWrite(rAMP, HIGH);
    }
    else {
      digitalWrite(rAMP, LOW);
    }
  }

  //DALLE 13.30 ALLE 17.00
  else if ((now.Hour() >= 13) && (now.Hour() < 17)) {
  
    if ((now.Minute() >= 30) && (now.Minute() < 55)) {
      //A .30 ACCENDI AMPLI PER 25 MIN
      digitalWrite(rAMP, HIGH);

      //A .30 ACCENDI ACCENDI ANCHE LA LUCE
      switch(now.Hour()) {
        
        case 13:
          if (now.Minute() < 40) {
            digitalWrite(rLUX, HIGH);
          }
          else {
            digitalWrite(rLUX, LOW);
          }
          break;

        case 14:
          if (now.Minute() < 45) {
            digitalWrite(rLUX, HIGH);
          }
          else {
            digitalWrite(rLUX, LOW);
          }
          break;

        case   15:
          if (now.Minute() < 50) {
            digitalWrite(rLUX, HIGH);
          }  
          else {
            digitalWrite(rLUX, LOW);
          }
          break;

        case   16:
          if (now.Minute() < 52) {
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
  else if ((now.Hour() >= 17) && (now.Hour() < 20)) {
    
    //OGNI 30 MIN PER 25 MIN ACCENDI AMP
    if (((now.Minute() >= 30) && (now.Minute() < 55)) || ((now.Minute() >= 0) && (now.Minute() < 25))) {
      digitalWrite(rAMP, HIGH);
    }    
    else {
      digitalWrite(rAMP, LOW);
    }

    //LUCE SEMPRE ACCESA
    digitalWrite(rLUX, HIGH);
    
  }

  else {
    // FUORI DAGLI ORARI DI APERTURA DEL MUSEO
    digitalWrite(rAMP, LOW);
    digitalWrite(rLUX, LOW);
  }

  delay(1000);
  
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );  
    Serial.print(datestring);
}

// NINA CARINA
// NEOTECH
// VIA SAVONA 118
// 
