#ifndef ASSERT_EQUALS_H
#define ASSERT_EQUALS_H

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

#endif

