#include <Arduino.h>
#include "config.h"

extern void setup_dht();
extern void setup_wifi();
extern void setup_mqtt();
extern void read_dht_values();
extern void publish_data();

void setup()
{
    Serial.begin(9600);
    setup_dht();
    setup_wifi();
    setup_mqtt();
}

void loop()
{
    delay(1000);
    read_dht_values();
    publish_data();
}

    // Initialize DHT sensor.
    // Note that older versions of this library took an optional third parameter to
    // tweak the timings for faster processors.  This parameter is no longer needed
    // as the current DHT reading algorithm adjusts itself to work on faster procs.

#include "DHT.h"
DHT dht;

void setup_dht()
{
    dht.setup(4, DHT::DHT22);
}

float humidity = NAN;
float temperature = NAN;

void read_dht_values()
{
    humidity = dht.getHumidity();
    temperature = dht.getTemperature();
}

void publish_data()
{
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(", Humidity: ");
    Serial.println(humidity);
}

void setup_wifi() {}
void setup_mqtt() {}
