#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "publish_mq2_json.h"
#include "get_mq2_msg.h"
#include "config.h"

void publish_mq2_json(int valueMq2, PubSubClient& mqttClient) {
  StaticJsonDocument<300> doc;
        doc["mq2"] = valueMq2; 
        doc["mq2_message"] = get_mq2_msg(valueMq2);
        doc["timestamp"] = millis();
        
        char jsonBuffer[300];
        serializeJson(doc, jsonBuffer);
        
        if (mqttClient.publish(topic_mq2, jsonBuffer)) {
          Serial.print("MQ-2 publie sur MQTT: ");
          Serial.println(jsonBuffer);
        } else {
          Serial.println("Echec de la publication sur MQTT");
        }
}
