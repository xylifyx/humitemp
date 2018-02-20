#include <Arduino.h>

/* WIFI INFO */
String WIFI_SSID        = "JaneOgErik";
String WIFI_PASSWORD    = "giraf50055005";

/* MQTT INFO */
String MQTT_HOST        = "io.adafruit.com";
String MQTT_USERNAME    = "xylifyx";
String MQTT_PASSWORD    = "37e1300e78ff4d7baf01ef9a45febe21";
String MQTT_CLIENT_ID   = "humitemp1";
String MQTT_PREFIX      = "xylifyx/feeds/";
String TEMP_TOPIC       = "xylifyx/feeds/humitemp1";
int MQTT_PORT           = 1883;
int PUBLISH_EVERY       = 10L * 1000;
int MQTT_CONNECT_TIMEOUT= 5000;

/*
// WIFI
const char* ssid = "JaneOgErik";
const char* password = "giraf50055005";
// MQTT
const char* topic = "xylifyx/feeds/humitemp1";
const char* host = " io.adafruit.com";
const char* user = "xylifyx";
const char* password = "37e1300e78ff4d7baf01ef9a45febe21";
*/
