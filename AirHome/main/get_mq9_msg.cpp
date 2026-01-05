#include <Arduino.h>

#include "get_mq9_msg.h"
#include "estimate_co_ppm.h"

String get_mq9_msg(int value) {
  int co_ppm = estimate_co_ppm(value);
  
  if (co_ppm == 0) {
    return "Air pur - Aucun CO détecté";
  } else if (co_ppm < 10) {
    return "Traces de CO - Ventiler";
  } else if (co_ppm < 35) {
    return "ATTENTION: CO détecté (10-35 ppm)";
  } else if (co_ppm < 100) {
    return "ALERTE: CO élevé - Évacuer";
  } else if (co_ppm < 200) {
    return "DANGER: Intoxication CO - Sortir!";
  } else if (co_ppm < 400) {
    return "DANGER CRITIQUE: CO mortel";
  } else {
    return "URGENCE: Concentration CO fatale";
  }
}