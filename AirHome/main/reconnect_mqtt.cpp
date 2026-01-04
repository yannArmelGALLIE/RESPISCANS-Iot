#include <Arduino.h>
#include <PubSubClient.h>

#include "reconnect_mqtt.h"

void reconnect_mqtt(PubSubClient& mqttClient, unsigned long& lastMqttReconnect, const char* mqtt_client_id) {
    if (millis() - lastMqttReconnect < 5000) return;
  lastMqttReconnect = millis();

  if (!mqttClient.connected()) {
    Serial.print("Connexion MQTT...");
    if (mqttClient.connect(mqtt_client_id)) {
      Serial.println("connecté");
    } else {
      Serial.print("Echec, rc=");
      Serial.print(mqttClient.state());
      Serial.println("Essaye encore dans 5 sec");
    }
  }
}