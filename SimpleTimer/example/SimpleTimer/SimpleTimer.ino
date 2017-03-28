#include <SimpleTimer.h>

// the timer object
SimpleTimer timer;

// a function to be executed periodically
void repeatMe() {
    Serial.print("Uptime (s): ");
    Serial.println(millis() / 1000);
}

void setup() {
    Serial.begin(9600);
    timer.setInterval(1000, repeatMe);
}

void loop() {
    timer.run();
}
