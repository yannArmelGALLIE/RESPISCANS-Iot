#ifndef reconnect_mqtt_h
#define reconnect_mqtt_h

void reconnect_mqtt(PubSubClient& mqttClient, unsigned long& lastMqttReconnect, const char* mqtt_client_id);

#endif