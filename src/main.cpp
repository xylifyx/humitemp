#include <Arduino.h>

//#define LED_BUILTIN 4
void setup()
{

    // pinMode(LED_BUILTIN, OUTPUT);
    // digitalWrite(LED_BUILTIN, LOW);

    Serial.begin(115200);
    Serial.setTimeout(2000);

    // Wait for serial to initialize.
    while (!Serial)
    {
    }

    // digitalWrite(LED_BUILTIN, HIGH);
    ESP.deepSleep(3e6);
}

void loop()
{
}
