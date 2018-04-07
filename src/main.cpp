#include <Arduino.h>
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
int lastMillis;

void setup()
{
    Serial.begin(9600);

    Cayenne.begin(MQTT_USERNAME, MQTT_PASSWORD, MQTT_CLIENT_ID, WIFI_SSID, WIFI_PASSWORD);
    pinMode(LED_BUILTIN, OUTPUT);

    lastMillis = 0;

    dht.setup(PIN_D2, DHT::DHT22);
}

void checkSensors()
{
    float temperature = dht.getTemperature();
    float humidity = dht.getHumidity();
    const char *status = dht.getStatusString();

    Serial.printf("DHT22: status=%s temp=%f humi=%f ", status, temperature, humidity);
    Serial.println();

    if (!isnan(temperature))
    {
        Cayenne.celsiusWrite(1, temperature);
    }

    if (!isnan(humidity))
    {
        Cayenne.virtualWrite(2, humidity, TYPE_RELATIVE_HUMIDITY, UNIT_PERCENT);
    }
}

void loop()
{
    Cayenne.loop();

    //Publish data every 10 seconds (10000 milliseconds). 
    if (millis() - lastMillis > 10000)
    {
        lastMillis = millis();
        checkSensors();
    }
}
