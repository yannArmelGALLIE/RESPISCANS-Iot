#include "LoRaWan_APP.h"
#include "Arduino.h"
#include "HT_SSD1306Wire.h"
#include "DHT.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "setup_wifi.h"
#include "get_temp_msg.h"
#include "get_hum_msg.h"
#include "get_danger_level.h"
#include "reconnect_mqtt.h"
#include "config.h"
#include "get_mq2_msg.h"
#include "publish_dht22_json.h"
#include "publish_mq2_json.h"

extern SSD1306Wire display;


char txpacket[BUFFER_SIZE];
char rxpacket[BUFFER_SIZE];

static RadioEvents_t RadioEvents;

int16_t txNumber;
int16_t rssi, rxSize;

bool lora_idle = true;
bool showingLoRaMessage = false;
unsigned long loraMessageTime = 0;
const unsigned long LORA_DISPLAY_TIME = 3000;

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient mqttClient(espClient);

unsigned long lastDHTRead = 0;
const unsigned long DHT_INTERVAL = 5000;
unsigned long lastMqttReconnect = 0;

float lastH = 0, lastT = 0;

void setup() {
    Serial.begin(115200);
    
    Mcu.begin(HELTEC_BOARD, SLOW_CLK_TPYE);
    delay(100);
    
    // Initialisation OLED
    pinMode(Vext, OUTPUT);
    digitalWrite(Vext, LOW);
    delay(100);
    
    pinMode(RST_OLED, OUTPUT);
    digitalWrite(RST_OLED, LOW);
    delay(50);
    digitalWrite(RST_OLED, HIGH);
    delay(50);
    
    txNumber = 0;
    rssi = 0;
  
    // LoRa setup
    RadioEvents.RxDone = OnRxDone;
    Radio.Init(&RadioEvents);
    Radio.SetChannel(RF_FREQUENCY);
    Radio.SetRxConfig(MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                      LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                      LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                      0, true, 0, 0, LORA_IQ_INVERSION_ON, true);

    // Display setup
    display.init();
    display.flipScreenVertically();
    display.setContrast(255);
    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Initialisation...");
    display.display();

    // WiFi setup
    setup_wifi(ssid, password);
    
    // MQTT setup
    mqttClient.setServer(mqtt_server, mqtt_port);
    
    // DHT setup
    dht.begin();
    
    display.clear();
    display.drawString(0, 0, "WiFi: Connecté");
    display.drawString(0, 12, WiFi.localIP().toString());
    display.drawString(0, 24, "MQTT: Connexion...");
    display.display();
    delay(2000);
    
    Serial.println("Setup complete!");
}

void loop()
{
  // Maintenir la connexion MQTT
  if (!mqttClient.connected()) {
    reconnect_mqtt(mqttClient, lastMqttReconnect, mqtt_client_id);
  }
  mqttClient.loop();
  
  // LoRa processing
  if(lora_idle)
  {
    lora_idle = false;
    Radio.Rx(0);
  }
  Radio.IrqProcess();
  
  // Retour à l'affichage DHT après message LoRa
  if (showingLoRaMessage && (millis() - loraMessageTime >= LORA_DISPLAY_TIME)) {
    showingLoRaMessage = false;
  }
  
  // Lecture DHT22
  if (millis() - lastDHTRead >= DHT_INTERVAL) {
    lastDHTRead = millis();
    
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (isnan(h) || isnan(t)) {
      Serial.println(F("Echec de lecture du DHT22!"));
      
      if (!showingLoRaMessage) {
        display.clear();
        display.setFont(ArialMT_Plain_10);
        display.drawString(0, 0, "Erreur DHT22!");
        display.display();
      }
    } else {
      lastH = h;
      lastT = t;
      
      float hi = dht.computeHeatIndex(t, h, false);

      int valueMq2 = analogRead(MQ2PIN);
      
      // Affichage série
      Serial.print(F("T: "));
      Serial.print(t);
      Serial.print(F("°C  H: "));
      Serial.print(h);
      Serial.print(F("%  HI: "));
      Serial.print(hi);
      Serial.print(F("°C MQ-2: "));
      Serial.println(valueMq2);
      
      // Publier sur MQTT en JSON
      if (mqttClient.connected()) {
        // Créer le document JSON
        publish_dht22_json(t, h, hi , mqttClient);
        publish_mq2_json(valueMq2, mqttClient);
      
      }
      
      // Affichage OLED
      if (!showingLoRaMessage) {
        display.clear();
        display.setFont(ArialMT_Plain_10);
        display.drawString(0, 0, "AirHome | Port: COM10");
        display.setFont(ArialMT_Plain_16);
        display.drawString(0, 14,String(t, 2) + "°C | " + String(h, 2) + "%");
        display.drawString(0, 32, String(valueMq2) + " | ");
        display.display();
      }
    }
  }
}

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
{
    rxSize = size;
    memcpy(rxpacket, payload, size);
    rxpacket[size] = '\0';
    Radio.Sleep();
    
    Serial.printf("\r\nLoRa RX: \"%s\" RSSI:%d\r\n", rxpacket, rssi);
    
    // Publier sur MQTT en JSON
    if (mqttClient.connected()) {
      StaticJsonDocument<128> doc;
      doc["message"] = rxpacket;
      doc["rssi"] = rssi;
      doc["snr"] = snr;
      doc["timestamp"] = millis();
      
      char jsonBuffer[128];
      serializeJson(doc, jsonBuffer);
      
      if (mqttClient.publish(topic_lora, jsonBuffer)) {
        Serial.print("LoRa published to MQTT: ");
        Serial.println(jsonBuffer);
      }
    }
    
    // Affichage
    showingLoRaMessage = true;
    loraMessageTime = millis();
    
    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "LoRa Message:");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 16, rxpacket);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 38, "RSSI: " + String(rssi));
    
    String status = mqttClient.connected() ? "MQTT: OK" : "MQTT: ERR";
    display.drawString(0, 52, status);
    display.display();
    
    lora_idle = true;
}