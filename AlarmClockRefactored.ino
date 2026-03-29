// Complete refactored code for Alarm Clock
// Implementing non-blocking design, encapsulation, and error handling

#include <Arduino.h>

class AlarmClock {
private:
    int alarmHour;
    int alarmMinute;
    bool alarmEnabled;
    unsigned long previousMillis;
    const long interval = 1000; // 1 second interval

public:
    AlarmClock() : alarmHour(0), alarmMinute(0), alarmEnabled(false), previousMillis(0) {}

    void setAlarm(int hour, int minute) {
        alarmHour = hour;
        alarmMinute = minute;
        alarmEnabled = true;
    }

    void disableAlarm() {
        alarmEnabled = false;
    }

    void checkAlarm(int currentHour, int currentMinute) {
        if (alarmEnabled && currentHour == alarmHour && currentMinute == alarmMinute) {
            ringAlarm();
        }
    }

    void ringAlarm() {
        // Code to ring the alarm
        Serial.println("Alarm ringing!");
    }

    void update() {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            // Code to get current hour and minute
            int currentHour = getCurrentHour();
            int currentMinute = getCurrentMinute();
            checkAlarm(currentHour, currentMinute);
        }
    }

    int getCurrentHour() {
        // Replace with actual implementation to get current hour
        return 0;
    }

    int getCurrentMinute() {
        // Replace with actual implementation to get current minute
        return 0;
    }
};

AlarmClock alarmClock;

void setup() {
    Serial.begin(9600);
    alarmClock.setAlarm(7, 30); // Set alarm for 7:30 AM
}

void loop() {
    alarmClock.update(); // Update the alarm clock
}