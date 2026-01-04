#include <Arduino.h>

#include "get_temp_msg.h"

String get_temp_msg(float temp) {
  if (temp < 16) return "DANGER: Hypothermie possible";
  else if (temp < 18) return "ALERTE: Risque respiratoire élevé";
  else if (temp < 20) return "ATTENTION: Trop froid pour malades";
  else if (temp >= 20 && temp <= 22) return "OPTIMAL: Idéal santé respiratoire";
  else if (temp < 26) return "BON: Température confortable";
  else if (temp < 30) return "ATTENTION: Chaleur inconfortable";
  else if (temp < 35) return "ALERTE: Risque déshydratation";
  else return "DANGER: Coup de chaleur possible";
}