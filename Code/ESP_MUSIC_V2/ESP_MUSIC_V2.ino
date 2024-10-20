#include <EasyBuzzer.h>
#include "pitches.h"
#include "ZELDA.h"
#include "NEVER.h"
#include "DEAD.h"
#include "WIN.h"

void setup() {
  WIN(32);
  delay(1000);
  ZELDA(32);
  delay(1000);
  NEVER(32);
  delay(1000);
  DEAD(32);
  delay(1000);
}

void loop() {
  EasyBuzzer.update(); // Actualiza el estado del buzzer
}
