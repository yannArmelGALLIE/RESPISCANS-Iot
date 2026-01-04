#include <Arduino.h>
#include <WiFi.h>

#include "setup_wifi.h"

void setup_wifi(const char* ssid, const char* password) {
  delay(10);
  Serial.println("");
  Serial.print("Connexion à ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int compteur = 0;
  while (WiFi.status() != WL_CONNECTED && compteur < 20) {
    delay(500);
    Serial.print(".");
    compteur++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("Connecté au WiFi");
    Serial.print("Adresse IP : ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("");
    Serial.print("Connexion au WiFi échouée");
  }
}