#ifndef config_h
#define config_h

// WiFi credentials
extern const char* ssid;
extern const char* password;

// MQTT Broker settings
extern const char* mqtt_server;
extern const int mqtt_port;
extern const char* mqtt_client_id;

// MQTT Topics
extern const char* topic_dht;
extern const char* topic_mq2;
extern const char* topic_mq9;
extern const char* topic_lora;

// DHT
#define DHTPIN 3
#define DHTTYPE DHT22

// MQ2
#define MQ2PIN 4

// MQ9
#define MQ9PIN 5

// LoRa parameters
#define RF_FREQUENCY 915000000
#define TX_OUTPUT_POWER 14
#define LORA_BANDWIDTH 0
#define LORA_SPREADING_FACTOR 7
#define LORA_CODINGRATE 1
#define LORA_PREAMBLE_LENGTH 8
#define LORA_SYMBOL_TIMEOUT 0
#define LORA_FIX_LENGTH_PAYLOAD_ON false
#define LORA_IQ_INVERSION_ON false

#define RX_TIMEOUT_VALUE 1000
#define BUFFER_SIZE 30

#endif
