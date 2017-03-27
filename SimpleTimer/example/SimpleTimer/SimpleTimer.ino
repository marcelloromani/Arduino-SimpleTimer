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
    Serial.println("Starting");
    timer.setTimer(500, repeatMe, 0);
    //timer.setInterval(1000, repeatMe, 1);
}

void loop() {
    timer.run();
}
