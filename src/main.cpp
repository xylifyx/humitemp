#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "config.h"
#include "DHT.h"

extern void setup_dht();
extern void setup_wifi();
extern void setup_mqtt();
extern void read_dht_values();
extern void publish_data();

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht;

void setup()
{
    Serial.begin(9600);
    pinMode(2, INPUT);
    setup_dht();
    // setup_wifi();
    // setup_mqtt();
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

float humidity = NAN;
float temperature = NAN;
const char *status = "Initializing";

void read_dht_values()
{
    humidity = dht.getHumidity();
    temperature = dht.getTemperature();
    status = dht.getStatusString();
}

char buffer[50];

void publish_data()
{
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(", Humidity: ");
    Serial.print(humidity);
    Serial.print(", Status: ");
    Serial.print(status);
    Serial.println();

    sprintf(buffer, "{\"value\":\"%f\"}", humidity);
    client.publish(TEMP_TOPIC, buffer);
    Serial.println(buffer);
}

void setup_dht()
{
    dht.setup(2, DHT::DHT22);
}

void setup_wifi()
{
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Connecting to MQTT server ");
        Serial.println(MQTT_HOST);

        if (client.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD))
        {
            Serial.println("Connected");
        }
        else
        {

            Serial.print("Failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
}

void setup_mqtt()
{
    reconnect();
}
