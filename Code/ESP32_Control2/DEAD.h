#ifndef DEAD_h
#define DEAD_h

int attack[] = {

  //https://musescore.com/user/27103612/scores/4834399

  NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
  NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4, 
  NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
  NOTE_A4, 2, 
};
void DEAD(int pin) {

  int tempo = 180;
  int notes = sizeof(attack) / sizeof(attack[0]) / 2;
  int wholenote = (60000 * 4) / tempo;
  int divider = 0, noteDuration = 0;

  ledcAttachPin(pin, 0); // Asignamos el pin 32 al canal 0 de PWM
  EasyBuzzer.setPin(pin);

  for (int thisNote = 0; thisNote < notes * 2; thisNote += 2) {
    divider = attack[thisNote + 1];
    if (divider > 0) {
      noteDuration = wholenote / divider;
    } else if (divider < 0) {
      noteDuration = wholenote / abs(divider);
      noteDuration *= 1.5;
    }
    EasyBuzzer.singleBeep(attack[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    EasyBuzzer.stopBeep();
  }
}

#endif