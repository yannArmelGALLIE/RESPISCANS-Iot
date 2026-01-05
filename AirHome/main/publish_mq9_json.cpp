#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "publish_mq9_json.h"
#include "get_mq9_msg.h"
#include "config.h"
#include "estimate_co_ppm.h"

void publish_mq9_json(int valueMq9, PubSubClient& mqttClient) {
  StaticJsonDocument<300> doc;
        doc["mq9"] = valueMq9; 
        doc["mq9_co"] = estimate_co_ppm(valueMq9);
        doc["mq9_message"] = get_mq9_msg(valueMq9);
        doc["timestamp"] = millis();
        
        char jsonBuffer[300];
        serializeJson(doc, jsonBuffer);
        
        if (mqttClient.publish(topic_mq9, jsonBuffer)) {
          Serial.print("MQ-9 publie sur MQTT: ");
          Serial.println(jsonBuffer);
        } else {
          Serial.println("Echec de la publication sur MQTT");
        }
}
