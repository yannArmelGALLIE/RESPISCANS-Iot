#include "config.h"

// WiFi credentials
const char* ssid = "SSID du WiFi";
const char* password = "Mot de passe du WiFi";

// MQTT Broker settings
const char* mqtt_server = "192.168.1.XX";
const int mqtt_port = 1883;
const char* mqtt_client_id = "ESP32_Heltec_COM10";

// MQTT Topics
const char* topic_dht = "respiscans/dht22";
const char* topic_mq2 = "respiscans/mq2";
const char* topic_lora = "respiscans/lora";
