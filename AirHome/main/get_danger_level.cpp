#include <Arduino.h>

#include "get_danger_level.h"

String get_danger_level(float temp, float hum) {
   if ((temp < 18 && hum > 70) || (temp < 16)) {
    return "CRITIQUE";
  }
  if ((temp < 20 && hum > 65) || (temp > 32 && hum > 70) || hum < 30) {
    return "DANGER";
  }
  if ((temp >= 20 && temp <= 22 && hum >= 40 && hum <= 60)) {
    return "OPTIMAL";
  }
  if ((temp < 20 || temp > 26) || (hum < 40 || hum > 60)) {
    return "ATTENTION";
  }
  return "BON";
}