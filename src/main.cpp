#include <Arduino.h>
#define CAYENNE_PRINT Serial
#include "CayenneMQTTESP8266.h"

#define VIRTUAL_CHANNEL 1

const char *MQTT_USERNAME =  "f7698140-108d-11e8-9094-712b97c1b05a";
const char *MQTT_PASSWORD =  "c93e09b2d794c9caf357be5d514594fdbf745718";
const char *MQTT_CLIENT_ID = "6ee2a210-390b-11e8-9beb-4d400e603e7e";

const char *SSID = "JaneOgErik";
const char *WIFI_PASSWORD = "giraf50055005";

int lastMillis;

void setup()
{
    Serial.begin(9600);

    Cayenne.begin(MQTT_USERNAME, MQTT_PASSWORD, MQTT_CLIENT_ID, SSID, WIFI_PASSWORD);
    pinMode(LED_BUILTIN, OUTPUT);
    lastMillis = 0;
}

void loop()
{
    Cayenne.loop();

    //Publish data every 10 seconds (10000 milliseconds). Change this value to publish at a different interval.
	if (millis() - lastMillis > 10000) {
		lastMillis = millis();
		//Write data to Cayenne here. This example just sends the current uptime in milliseconds.
		// Cayenne.virtualWrite(0, lastMillis);
		//Some examples of other functions you can use to send data.
		Cayenne.celsiusWrite(1, 22.0);
        Cayenne.virtualWrite(2, 50, TYPE_RELATIVE_HUMIDITY, UNIT_PERCENT);
	}
}

