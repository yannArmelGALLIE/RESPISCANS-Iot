#include <Arduino.h>

#include "get_mq2_msg.h"

String get_mq2_msg(int value) {
    if (value < 400) {
    return "Air pur - Aucun gaz détecté";
  } else if (value < 600) {
    return "ATTENTION: Traces de gaz/fumée";
  } else if (value < 1000) {
    return "ALERTE: GPL ou fumée détecté";
  } else if (value < 1500) {
    return "DANGER: Concentration élevée";
  } else if (value < 2500) {
    return "DANGER CRITIQUE: Évacuer immédiatement";
  } else {
    return "URGENCE: Fuite massive - Appeler secours";
  }
}