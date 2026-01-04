#include <Arduino.h>

#include "get_hum_msg.h"

String get_hum_msg(float hum) {
  if (hum < 30) return "DANGER: Air trop sec, muqueuses irritées";
  else if (hum < 40) return "ATTENTION: Air sec, risque infection";
  else if (hum >= 40 && hum <= 60) return "OPTIMAL: Idéal santé respiratoire";
  else if (hum < 70) return "ATTENTION: Humidité élevée";
  else if (hum < 80) return "ALERTE: Risque moisissures élevé";
  else return "DANGER: Prolifération bactérienne";
}