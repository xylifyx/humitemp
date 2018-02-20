#include <Arduino.h>
#include <MqttConnector.h>
// #include <DHT.h>

//extern int relayPinState;
extern MqttConnector* mqtt;
//extern int relayPin;
//extern char myName[];
//extern DHT dht;

static void readSensor();

// sensor
float temperature = 0;
//float humidity = 0;

extern String DEVICE_NAME;
extern int PUBLISH_EVERY;

void register_publish_hooks() {
  mqtt->on_prepare_data_once([&](void) {
    Serial.println("initializing sensor...");
  });

  mqtt->on_before_prepare_data([&](void) {
    Serial.println("on_before_prepare_data");
    readSensor();
  });

  mqtt->on_prepare_data([&](JsonObject *root) {
    (*root)["value"] = temperature;
  }, PUBLISH_EVERY);

  mqtt->on_after_prepare_data([&](JsonObject * root) {
    Serial.println("on_after_prepare_data");
  });
}

static void readSensor() {
  temperature = temperature+1;
  Serial.println("readSensor()");
}
