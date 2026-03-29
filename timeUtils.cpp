#include "timeUtils.h"

TimeUtils::TimeUtils()
    : day(1), month(1), year(MIN_YEAR), hour(0), minute(0), second(0) {
}

void TimeUtils::initialize() {
    rtc.begin();
    initializeRTCIfNeeded();
}

void TimeUtils::initializeRTCIfNeeded() {
    if (!isRTCRunning()) {
        Serial.println("RTC is NOT running!");
        rtc.adjust(DateTime(MIN_YEAR, 1, 1, 0, 0, 0));
    }
}

bool TimeUtils::isRTCRunning() {
    return rtc.isrunning();
}

void TimeUtils::update() {
    DateTime now = rtc.now();
    day = now.day();
    month = now.month();
    year = now.year();
    hour = now.hour();
    minute = now.minute();
    second = now.second();
}

int TimeUtils::getDay() { return day; }
int TimeUtils::getMonth() { return month; }
int TimeUtils::getYear() { return year; }
int TimeUtils::getHour() { return hour; }
int TimeUtils::getMinute() { return minute; }
int TimeUtils::getSecond() { return second; }

String TimeUtils::padZero(int value) {
    return value < 10 ? "0" + String(value) : String(value);
}

String TimeUtils::formatTime() {
    return padZero(hour) + ":" + padZero(minute) + ":" + padZero(second);
}

String TimeUtils::formatDate() {
    return padZero(day) + "-" + padZero(month) + "-" + String(year - 2000);
}

String TimeUtils::getFormattedDay() { return padZero(day); }
String TimeUtils::getFormattedMonth() { return padZero(month); }
String TimeUtils::getFormattedYear() { return String(year - 2000); }
String TimeUtils::getFormattedHour() { return padZero(hour); }
String TimeUtils::getFormattedMinute() { return padZero(minute); }
String TimeUtils::getFormattedSecond() { return padZero(second); }

void TimeUtils::setDateTime(int y, int mo, int d, int h, int mi, int s) {
    rtc.adjust(DateTime(y, mo, d, h, mi, s));
    update();
}