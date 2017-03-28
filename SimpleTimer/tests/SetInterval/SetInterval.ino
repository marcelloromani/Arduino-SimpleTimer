#include <SimpleTimer.h>

// the timer object
SimpleTimer timer;

unsigned int counter = 0;

boolean pass = true;

// a function to be executed periodically
void repeatMe() {
    counter++;
    Serial.print("Uptime (s): ");
    Serial.println(millis() / 1000);
}

void checkResult(void* param) {
    unsigned int expected = (unsigned int)param;

    Serial.print("Checking param = ");
    Serial.println(expected);
    Serial.print("counter = ");
    Serial.println(counter);

    if (expected == counter) {
        Serial.println("OK");
    }
    else {
        Serial.println("ERROR");
        pass = false;
    }
}

void start() {
    Serial.println("Test start");
}

void stopSketch() {
    Serial.println("Test stop");
    Serial.println(pass ? "PASS" : "FAIL");
    while(true);
}

void setup() {
    Serial.begin(9600);
    timer.setTimeout(100, start);
    timer.setInterval(500, repeatMe);
    timer.setTimeout(550, checkResult, 1);
    timer.setTimeout(1050, checkResult, 2);
    timer.setTimeout(1550, checkResult, 3);
    timer.setTimeout(2000, stopSketch);
}

void loop() {
    timer.run();
}
