#include "alarmHandler.h"

AlarmHandler::AlarmHandler(int buzzer) 
    : alarmHour(12), alarmMinute(0), alarmEnabled(false), alarmTriggered(false),
      timeUtils(nullptr), lastAlarmTriggerTime(0), melodyIndex(0), lastToneTime(0),
      buzzerPin(buzzer) {
    
    pinMode(buzzerPin, OUTPUT);
    
    // Initialize alarm melody
    alarmMelody[0] = 600;
    alarmMelody[1] = 800;
    alarmMelody[2] = 1000;
    alarmMelody[3] = 1200;
}

void AlarmHandler::initialize(TimeUtils* tu) {
    timeUtils = tu;
    loadAlarmFromEEPROM();
}

void AlarmHandler::setAlarmTime(int hour, int minute) {
    if (hour >= 0 && hour <= MAX_HOUR && minute >= 0 && minute <= MAX_MINUTE) {
        alarmHour = hour;
        alarmMinute = minute;
    }
}

void AlarmHandler::loadAlarmFromEEPROM() {
    alarmHour = EEPROM.read(EEPROM_ALARM_HOUR);
    alarmMinute = EEPROM.read(EEPROM_ALARM_MINUTE);
    
    // Validate loaded values
    if (alarmHour > MAX_HOUR) alarmHour = 0;
    if (alarmMinute > MAX_MINUTE) alarmMinute = 0;
}

void AlarmHandler::saveAlarmToEEPROM() {
    EEPROM.write(EEPROM_ALARM_HOUR, alarmHour);
    EEPROM.write(EEPROM_ALARM_MINUTE, alarmMinute);
}

int AlarmHandler::getAlarmHour() {
    return alarmHour;
}

int AlarmHandler::getAlarmMinute() {
    return alarmMinute;
}

String AlarmHandler::getAlarmTimeFormatted() {
    String hour = alarmHour < 10 ? "0" + String(alarmHour) : String(alarmHour);
    String minute = alarmMinute < 10 ? "0" + String(alarmMinute) : String(alarmMinute);
    return hour + ":" + minute;
}

void AlarmHandler::enableAlarm() {
    alarmEnabled = true;
}

void AlarmHandler::disableAlarm() {
    alarmEnabled = false;
    stopAlarm();
}

bool AlarmHandler::isAlarmEnabled() {
    return alarmEnabled;
}

bool AlarmHandler::shouldTrigger() {
    if (!alarmEnabled || !timeUtils) {
        return false;
    }
    
    int currentHour = timeUtils->getHour();
    int currentMinute = timeUtils->getMinute();
    int currentSecond = timeUtils->getSecond();
    
    if (alarmMinute == currentMinute && alarmHour == currentHour && currentSecond <= ALARM_TRIGGER_WINDOW) {
        return true;
    }
    
    return false;
}

void AlarmHandler::triggerAlarm() {
    alarmTriggered = true;
    lastAlarmTriggerTime = millis();
    melodyIndex = 0;
}

void AlarmHandler::stopAlarm() {
    alarmTriggered = false;
    noTone(buzzerPin);
}

void AlarmHandler::updateMelodyIndex() {
    unsigned long currentMillis = millis();
    
    if (currentMillis - lastToneTime > ALARM_INTERVAL) {
        lastToneTime = currentMillis;
        tone(buzzerPin, alarmMelody[melodyIndex], ALARM_TONE_DURATION);
        melodyIndex = (melodyIndex + 1) % ALARM_MELODY_SIZE;
    }
}

void AlarmHandler::playAlarmTone() {
    if (alarmTriggered) {
        updateMelodyIndex();
    }
}

bool AlarmHandler::isAlarmTriggered() {
    return alarmTriggered;
}