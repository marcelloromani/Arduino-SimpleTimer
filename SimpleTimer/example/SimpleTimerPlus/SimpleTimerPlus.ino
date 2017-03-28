/*
 * SimpleTimerAlarmExample.ino
 *
 * Based on usage example for Time + TimeAlarm + SimpleTimer libraries
 *
 * A timer is called every 15 seconds
 * Another timer is called once only after 10 seconds
 * A third timer is called 10 times.
 * Toggle an IO pin 100mSec LOW, 900mSec HIGH
 *
 */

#include <SimpleTimer.h>

// There must be one global SimpleTimer object.
// More SimpleTimer objects can be created and run,
// although there is little point in doing so.
SimpleTimer timer;

// Pin to toggle
const unsigned int PIN = 13;

// function to be called repeatedly
void RepeatTask(void) {
  Serial.println("15 second timer");        
}

// function to be called just once
void OnceOnlyTask(void) {
  Serial.println("This timer only triggers once");  
}

// function to be called exactly 10 times
void TenTimesTask(void) {
  static int k = 0;
  k++;
  Serial.print("called ");
  Serial.print(k);
  Serial.println(" / 10 times.");
}

// print current arduino "uptime" on the serial port
void DigitalClockDisplay(void) {
  int h,m,s;
  s = millis() / 1000;
  m = s / 60;
  h = s / 3600;
  s = s - m * 60;
  m = m - h * 60;
  Serial.print(h);
  printDigits(m);
  printDigits(s);
  Serial.println();
}

//
// utility function for digital clock display:
// prints preceding colon and leading 0
//
void printDigits(int digits) {
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

// This callback function takes an arg.  The arg can be cast to a value
// as in this example or cast to a pointer to a structure or even a
// function.  If a structure, it must be present in memory when the
// callback fuction is called. In other words it must be a global or
// declared 'static' and not a structure local to the function that
// created the timer such as setup() or loop().
void setPin(void* args)
{
  int state = (int)args;
  unsigned long duration;

  if (state == LOW)
    {
    digitalWrite(PIN, LOW);
    state = HIGH;           // set the pin high
    duration = 100;         // after 100 mSec
    }
  else
    {
    digitalWrite(PIN, HIGH);
    state = LOW;            // set the pin low
    duration = 900;         // after 900 mSec
    }

  timer.setTimeout(duration, setPin, (void *)state);
}

void setup() {
  Serial.begin(9600);

  // welcome message
  Serial.println("SimpleTimer Example");
  Serial.println("One timer is triggered every 15 seconds");
  Serial.println("Another timer is set to trigger only once after 10 seconds");
  Serial.println("Another timer is set to trigger 10 times");
  Serial.println();

  // timed actions setup
  timer.setInterval(15000, RepeatTask);
  timer.setTimeout(10000, OnceOnlyTask);
  timer.setInterval(1000, DigitalClockDisplay);
  timer.setTimer(1200, TenTimesTask, 10);
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, LOW);
  // Set the pin HIGH after 100 mSec
  timer.setTimeout(100, setPin, (void *)HIGH);
}

void loop() {
  // this is where the "polling" occurs
  timer.run();
}
