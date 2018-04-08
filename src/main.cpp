#include <Arduino.h>
// #define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include <DHT.h>
#include "credentials.h"

#define VIRTUAL_CHANNEL 1

// const char *MQTT_USERNAME = "usernamea";
// const char *MQTT_PASSWORD = "password";
// const char *MQTT_CLIENT_ID = "clientid";

// const char *WIFI_SSID = "ssid";
// const char *WIFI_PASSWORD = "psk";

#define PIN_D2 4

DHT dht;

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    Cayenne.begin(MQTT_USERNAME, MQTT_PASSWORD, MQTT_CLIENT_ID, WIFI_SSID, WIFI_PASSWORD);

    dht.setup(PIN_D2, DHT::DHT22);
}

static unsigned long lastPoll;

// Default function for sending sensor data at intervals to Cayenne
void pullSensors()
{
    digitalWrite(LED_BUILTIN, LOW);

    float temperature = dht.getTemperature();
    float humidity = dht.getHumidity();
    const char *status = dht.getStatusString();

    CAYENNE_LOG("DHT22: status=%s temp=%f humi=%f ", status, temperature, humidity);
    
    if (!isnan(temperature))
    {
        Cayenne.celsiusWrite(1, temperature);
    }

    if (!isnan(humidity))
    {
        Cayenne.virtualWrite(2, humidity, TYPE_RELATIVE_HUMIDITY, UNIT_PERCENT);
    }

    digitalWrite(LED_BUILTIN, HIGH);
}

CAYENNE_IN_DEFAULT()
{
    CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
    //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}

void loop()
{
    Cayenne.loop();
    if (millis() - lastPoll > 15000)
    {
        pullSensors();
        lastPoll = millis();
    }
}
