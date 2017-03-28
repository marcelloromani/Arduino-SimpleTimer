#include <ArduinoUnit.h>
#include <SimpleTimer.h>

// the timer object
SimpleTimer timer;

bool all_done = false;

int counter = 0;

void callMeOnce() {
    Serial.print("callMeOnce: counter=");
    counter++;
    Serial.println(counter);
}

void setup() {
    Serial.begin(9600);

    for (int i = 0; i < timer.MAX_TIMERS; i++) {
        int id = timer.setTimer(10, callMeOnce, 1);
        assertNotEqual(id, -1);
    }
    
    int id = timer.setTimer(10, callMeOnce, 1);
    assertEqual(id, -1);
    assertEqual(timer.getNumTimers(), timer.MAX_TIMERS);
}

void loop() {
    timer.run();

    if (counter == timer.MAX_TIMERS) {
        Serial.println("Tests finished.");
        while (true);
    }
}
