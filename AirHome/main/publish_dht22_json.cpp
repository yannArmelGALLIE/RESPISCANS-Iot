#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "get_temp_msg.h"
#include "get_hum_msg.h"
#include "get_danger_level.h"
#include "config.h"

void publish_dht22_json(float t, float h, float hi, PubSubClient& mqttClient) {
  StaticJsonDocument<300> doc;
        doc["temperature"] = round(t * 10) / 10.0; 
        doc["humidity"] = round(h * 10) / 10.0;
        doc["heatindex"] = round(hi * 10) / 10.0;
        doc["temp_message"] = get_temp_msg(t);
        doc["hum_message"] = get_hum_msg(h);
        doc["danger_level"] = get_danger_level(t, h);
        doc["timestamp"] = millis();
        
        char jsonBuffer[300];
        serializeJson(doc, jsonBuffer);
        
        if (mqttClient.publish(topic_dht, jsonBuffer)) {
          Serial.print("DHT22 publie sur MQTT: ");
          Serial.println(jsonBuffer);
        } else {
          Serial.println("Echec de la publication sur MQTT");
        }
}
