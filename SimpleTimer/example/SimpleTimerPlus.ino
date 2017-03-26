/*
 * SimpleTimerPlusAlarmExample.ino
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

// There must be one global SimpleTimerPlus object.
// More SimpleTimer objects can be created and run,
// although there is little point in doing so.
SimpleTimer timer;

// function to be called repeatedly
void RepeatTask(void* args) {
  Serial.println("15 second timer");        
}

// function to be called just once
void OnceOnlyTask(void* args) {
  Serial.println("This timer only triggers once");  
}

// function to be called exactly 10 times
void TenTimesTask(void* args) {
  static int k = 0;
  k++;
  Serial.print("called ");
  Serial.print(k);
  Serial.println(" / 10 times.");
}

// print current arduino "uptime" on the serial port
void DigitalClockDisplay(void* args) {
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

void setPin(void *args)
{
  int state = (int)args;
  unsigned long duration;

  if (state == LOW)
    {
    digitalWrite(13, LOW);
    state = HIGH;           // set the pin high
    duration = 100;         // after 100 mSec
    }
  else
    {
    digitalWrite(13, HIGH);
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
  timer.setInterval(15000, RepeatTask, NULL);
  timer.setTimeout(10000, OnceOnlyTask, NULL);
  timer.setInterval(1000, DigitalClockDisplay, NULL);
  timer.setTimer(1200, TenTimesTask, 10, NULL);
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  // Set the pin HIGH after 100 mSec
  timer.setTimeout(100, setPin, (void *)HIGH);
}

void loop() {
  // this is where the "polling" occurs
  timer.run();
}
