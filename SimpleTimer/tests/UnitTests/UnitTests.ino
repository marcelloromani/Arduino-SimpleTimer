#include <ArduinoUnit.h>
#include <SimpleTimer.h>

// the timer object
SimpleTimer timer;

unsigned int c1 = 0;
unsigned int c2 = 0;

bool all_done = false;

void callMeOnce() {
    Serial.println("callMeOnce");
    c1++;
}

void callMeTwice() {
    Serial.println("callMeTwice");
    c2++;
}

void checkResults() {
    Serial.println("checkResults");
    assertEqual(c1, 1);
    assertEqual(c2, 2);

    all_done = true;
}

void setup() {
    Serial.begin(9600);

    assertEqual(timer.getNumTimers(), 0);

    timer.setTimer(10, callMeOnce, 1);
    timer.setTimer(10, callMeTwice, 2);
    timer.setTimeout(50, checkResults);

    assertEqual(timer.getNumTimers(), 3);
}

void loop() {
    timer.run();

    if (all_done) {
        unsigned int remaining = timer.getNumAvailableTimers();
        const unsigned int MAX = timer.MAX_TIMERS;
        assertEqual(remaining, MAX);
        Serial.println("Tests finished.");
        while (true);
    }
}
