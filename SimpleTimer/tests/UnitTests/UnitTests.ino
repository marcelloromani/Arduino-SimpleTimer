#include <SimpleTimer.h>
#include "assertEquals.h"

// the timer object
SimpleTimer timer;

unsigned int c0 = 0;
unsigned int c1 = 0;
unsigned int c2 = 0;

bool all_done = false;

void dontExecute() {
    c0++;
}

void callMeOnce() {
    c1++;
}

void callMeTwice() {
    c2++;
}

void checkResults() {
    assertEquals<unsigned int>(c0, 0, "setTimer 0");
    assertEquals<unsigned int>(c1, 1, "setTimer 1");
    assertEquals<unsigned int>(c2, 2, "setTimer 2");

    all_done = true;
}

void setup() {
    Serial.begin(9600);

    assertEquals<unsigned int>(timer.getNumTimers(), 0, "initial timers count");

    timer.setTimer(10, dontExecute, 0);
    assertEquals<unsigned int>(timer.getNumTimers(), 0, "allocate 0 times timer");

    timer.setTimer(10, callMeOnce, 1);
    timer.setTimer(10, callMeTwice, 2);
    timer.setTimeout(50, checkResults);

    assertEquals<unsigned int>(timer.getNumTimers(), 3, "count allocated timers");
}

void loop() {
    timer.run();

    if (all_done) {
        unsigned int remaining = timer.getNumAvailableTimers();
        assertEquals<unsigned int>(remaining, timer.MAX_TIMERS, "free timers after all expired");
        Serial.println("stopped.");
        while (true);
    }
}
