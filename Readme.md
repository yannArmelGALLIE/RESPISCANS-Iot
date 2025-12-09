# RESPISCANS-IoT  
Firmware IoT du système SmartAirCare composé de deux stations : **AirBand** (portable) et **AirHome** (fixe).

![Last Commit](https://img.shields.io/github/last-commit/yannArmelGALLIE/RESPISCANS-Iot.git?style=for-the-badge&logoColor=white)

---

## 📡 Aperçu du projet

RESPISCANS-IOT regroupe le code embarqué des deux modules IoT du projet SmartAirCare :

- **AirBand**  
  Station portable portée par l’utilisateur. Mesure la qualité de l’air locale, la température corporelle et envoie les données au serveur/cloud.

- **AirHome**  
  Station fixe installée à domicile. Surveille la qualité de l’air intérieur et transmet en continu les mesures.

Les deux stations fonctionnent sur **ESP32** via PlatformIO.

---

## 🗂️ Architecture du projet

```
RESPISCANS-IOT/
 ├── AirBand/
 │   ├── .pio/
 │   ├── .vscode/
 │   ├── include/
 │   ├── lib/
 │   ├── src/
 │   │   └── main.cpp
 │   ├── test/
 │   ├── .gitignore
 │   └── platformio.ini
 │
 └── AirHome/
     ├── .pio/
     ├── .vscode/
     ├── include/
     ├── lib/
     ├── src/
     │   └── main.cpp
     ├── test/
     ├── .gitignore
     └── platformio.ini

```
Chaque dossier AirBand et AirHome correspond à un projet PlatformIO indépendant.

---

## ⚙️ Technologies utilisées

![c++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)

![arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)

![node-red](https://img.shields.io/badge/node--red-8F0000?style=for-the-badge&logo=node-red&logoColor=white)

![MQTT](https://img.shields.io/badge/MQTT-00779D?style=for-the-badge&logo=mqtt&logoColor=white)

![PlatformIO](https://img.shields.io/badge/PlatformIO-orange?style=for-the-badge&logo=Platformio&logoColor=white)
 

---

## 🧩 Capteurs intégrés

### **1. DHT22 — Température & Humidité (x2)**  
- Température : -40°C à +80°C  
- Précision : ±0.5°C  
- Humidité : 0 à 100% RH  
- Précision : ±2–5%  
- Alimentation : 3.3V / 5V  
- Protocole : digital 1-wire  
- Temps de réponse : ~2 s  

---

### **2. MQ-2 — Fumée, GPL, Butane, Propane**  
- Fumée : 300 à 10 000 ppm  
- Sensible à LPG, butane, propane, H₂  
- Mode analogique  
- Temps de préchauffage : 20–30 s  

---

### **3. MQ-9 — CO & Gaz inflammables**  
- CO : 10–1000 ppm  
- Gaz inflammables : 100–10 000 ppm  
- Consommation (chauffage) : 150 mA  
- Sortie analogique  

---

### **4. MQ-135 — Pollution & Qualité de l’air**  
- Gaz détectés : CO₂, NH₃, NOx, benzène  
- Large plage de 10 à 2000 ppm (type CO₂)  
- Sortie analogique  

---

### **5. DS18B20 — Température corporelle**  
- Plage : -55°C à +125°C  
- Idéal entre 35–40°C (±0.2°C)  
- Protocole : 1-wire digital  
- Disponible en version étanche  

---

## 🧱 Rôle des deux stations

### **AirBand (portable)**  
- DS18B20 : température corporelle  
- MQ135 : qualité de l’air proche  
- MQ2 : fumée/gaz autour de l’utilisateur  
- DHT22 : humidité & température ambiante  
- Envoi des mesures → MQTT ou HTTP (JSON)

---

### **AirHome (fixe)**  
- DHT22 (x2) : pièce principale & air entrant  
- MQ2 : fumée  
- MQ9 : CO  
- MQ135 : pollution intérieure  
- Transmission continue → MQTT / cloud

---

## 🚀 Compilation & Déploiement

### Prérequis
- VS Code  
- PlatformIO  
- Carte ESP32 DevKit  

### Build & Upload
Dans VS Code / PlatformIO :

Project Tasks → Build
Project Tasks → Upload


Sélectionner AirBand ou AirHome selon la cible.

---

## 🌐 Communication & Format JSON

### MQTT Topics
smartaircare/airband<br/>
smartaircare/airhome


## 🧭 Roadmap IoT
 Calibration automatique des MQ

 Détection d’événements critiques (CO, fumée)

 Mode basse consommation (AirBand)

 Synchronisation NTP

 Sécurisation MQTT (TLS léger)


## 👨‍💻 Authors

Koffi Yann-Armel GALLIE – [github](https://github.com/yannArmelGALLIE/)<br/>
Samuel ZOUHOU – [github](https://github.com/Samiiii5/)<br/>
Albert COULIBALY – [github](https://github.com/Volbis/)


