#include <Arduino.h>

#include "estimate_co_ppm.h"

int estimate_co_ppm(int value) {
   if (value < 400) return 0;
  if (value < 600) return 10;
  if (value < 800) return 30;
  if (value < 1000) return 50;
  if (value < 1200) return 100;
  if (value < 1500) return 200;
  if (value < 2000) return 400;
  return 800;
}