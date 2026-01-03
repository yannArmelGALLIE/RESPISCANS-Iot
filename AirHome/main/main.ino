/* Heltec Automation Receive communication test example
 *
 * Function:
 * 1. Receive the same frequency band lora signal program
 *  
 * Description:
 * 
 * HelTec AutoMation, Chengdu, China
 * 成都惠利特自动化科技有限公司
 * www.heltec.org
 *
 * this project also realess in GitHub:
 * https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series
 * */

#include "LoRaWan_APP.h"
#include "Arduino.h"
#include "HT_SSD1306Wire.h"

extern SSD1306Wire display;

#define RF_FREQUENCY                                915000000 // Hz

#define TX_OUTPUT_POWER                             14        // dBm

#define LORA_BANDWIDTH                              0
#define LORA_SPREADING_FACTOR                       7
#define LORA_CODINGRATE                             1
#define LORA_PREAMBLE_LENGTH                        8
#define LORA_SYMBOL_TIMEOUT                         0
#define LORA_FIX_LENGTH_PAYLOAD_ON                  false
#define LORA_IQ_INVERSION_ON                        false

#define RX_TIMEOUT_VALUE                            1000
#define BUFFER_SIZE                                 30

char txpacket[BUFFER_SIZE];
char rxpacket[BUFFER_SIZE];

static RadioEvents_t RadioEvents;

int16_t txNumber;
int16_t rssi, rxSize;

bool lora_idle = true;

void setup() {
    Serial.begin(115200);
    
    // Initialisation Heltec
    Mcu.begin(HELTEC_BOARD, SLOW_CLK_TPYE);
    
    // Délai pour stabilisation
    delay(100);
    
    // Initialisation manuelle de l'écran (AJOUTÉ)
    pinMode(Vext, OUTPUT);
    digitalWrite(Vext, LOW);  // Active l'alimentation OLED
    delay(100);
    
    pinMode(RST_OLED, OUTPUT);
    digitalWrite(RST_OLED, LOW);
    delay(50);
    digitalWrite(RST_OLED, HIGH);
    delay(50);
    
    txNumber = 0;
    rssi = 0;
  
    RadioEvents.RxDone = OnRxDone;
    Radio.Init(&RadioEvents);
    Radio.SetChannel(RF_FREQUENCY);
    Radio.SetRxConfig(MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                      LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                      LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                      0, true, 0, 0, LORA_IQ_INVERSION_ON, true);

    // Initialisation de l'écran avec luminosité maximale
    display.init();
    display.flipScreenVertically();
    display.setContrast(255);  // Luminosité maximale
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, "Hello Heltec!");
    display.display();
    delay(2000);
    
    Serial.println("Setup complete - waiting for messages...");
}

void loop()
{
  if(lora_idle)
  {
    lora_idle = false;
    Serial.println("into RX mode");
    Radio.Rx(0);
  }
  Radio.IrqProcess();
}

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
{
    rxSize = size;
    memcpy(rxpacket, payload, size);
    rxpacket[size] = '\0';
    Radio.Sleep();
    Serial.printf("\r\nreceived packet \"%s\" with rssi %d , length %d\r\n", rxpacket, rssi, rxSize);
    
    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Port: COM11");
    display.drawString(0, 15, "Recu de COM10:");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 30, rxpacket);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 50, "RSSI: " + String(rssi) + " dBm");
    display.display();
    
    lora_idle = true;
}