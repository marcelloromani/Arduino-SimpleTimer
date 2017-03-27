#include <SimpleTimer.h>

// the timer object
SimpleTimer timer;

unsigned int c0 = 0;
unsigned int c1 = 0;
unsigned int c2 = 0;

void dontExecute() {
  c0++;
}

void callMeOnce() {
  c1++;
}

void callMeTwice() {
  c2++;
}

template <typename T> void assertEquals(T actual, T expected, const char* testName = NULL) {
  if (testName != NULL) {
    Serial.print(testName);
    Serial.print(": ");
  }
  if (actual == expected) {
    Serial.println("OK");
  }
  else {
    Serial.print("ERR: expected: ");
    Serial.print(expected);
    Serial.print(" actual: ");
    Serial.println(actual);
  }
}

void checkResults() {
  assertEquals<unsigned int>(c0, 0, "setTimer 0");
  assertEquals<unsigned int>(c1, 1, "setTimer 1");
  assertEquals<unsigned int>(c2, 2, "setTimer 2");
}

void setup() {
    Serial.begin(9600);
    timer.setTimer(10, dontExecute, 0);
    timer.setTimer(10, callMeOnce, 1);
    timer.setTimer(10, callMeTwice, 2);
    timer.setTimeout(50, checkResults);
}

void loop() {
    timer.run();
}

