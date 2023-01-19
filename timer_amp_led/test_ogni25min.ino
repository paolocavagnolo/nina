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

unsigned long tt = 0;
int s = 0;

void loop() {

  if (s == 0) {
    digitalWrite(rAMP, HIGH);
    digitalWrite(rLUX, LOW);

    if ((millis() - tt) > 30000) {
      s++;
      tt = millis();
    }
  }

  if (s == 1) {
    digitalWrite(rAMP, HIGH);
    digitalWrite(rLUX, HIGH);

    if ((millis() - tt) > 14 * 60000) {
      s++;
      tt = millis();
    }
  }

  if (s == 2) {
    digitalWrite(rAMP, LOW);
    digitalWrite(rLUX, LOW);

    if ((millis() - tt) > 10 * 60000) {
      s = 0;
      tt = millis();
    }
  } 
}
