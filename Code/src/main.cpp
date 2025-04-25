#include <Arduino.h>

#include "SevSeg.h"
#include "bit_macros.h"

SevSeg sevseg;

int displayTimeSecs = 1;
long displayTime = displayTimeSecs * 1000;
long buzzerFrequency = 500;
long buzzerDuration = 100;
long startMinutes = 10;
long startSeconds = 40;
long endMinutes = 0;
long endSeconds = 0;

const int buzzerPin = 0;
bool countdownEnded = false;
unsigned long previousMillis = 0;
unsigned long buzzerMillis = 0;
bool buzzerState = false;

void setup() 
{
    SET_BIT(DDRD, buzzerPin); 
    
    byte numDigits = 4;
    byte digitPins[] = {10, 11, 12, 13};
    byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};

    bool resistorsOnSegments = false;
    byte hardwareConfig = COMMON_CATHODE;
    bool updateWithDelays = false;
    bool leadingZeros = true;
    bool disableDecPoint = true;

    sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
    sevseg.setBrightness(90);
}

void loop() 
{
    unsigned long currentMillis = millis();

    if (!countdownEnded) 
    {
        if (currentMillis - previousMillis >= displayTime) 
        {
            previousMillis = currentMillis;

            if (startMinutes > endMinutes || (startMinutes == endMinutes && startSeconds > endSeconds)) 
            {
                long displayValue = startMinutes * 100 + startSeconds;
                sevseg.setNumber(displayValue, 0);

                if (startSeconds == 0) 
                {
                    if (startMinutes > 0) 
                    {
                        startMinutes--;
                        startSeconds = 59;
                    }
                } 
                else 
                {
                    startSeconds--;
                }

                TOGGLE_BIT(PORTD, buzzerPin); 
            } 
            else 
            {
                countdownEnded = true;
                buzzerMillis = millis(); 
            }
        }
    } 
    else 
    {
        sevseg.setNumber(0, 0);

        if (millis() - buzzerMillis < 1000) 
        {
            if (millis() - buzzerMillis >= (buzzerState ? 200 : 100)) 
            {
                buzzerState = !buzzerState;
                if (buzzerState) {
                    SET_BIT(PORTD, buzzerPin);
                } 
                else 
                {
                    CLEAR_BIT(PORTD, buzzerPin);
                }
                buzzerMillis = millis();
            }
        } 
        else 
        {
            CLEAR_BIT(PORTD, buzzerPin); 
        }
    }
    sevseg.refreshDisplay();
}