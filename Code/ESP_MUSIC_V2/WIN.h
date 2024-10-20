#ifndef WIN_h
#define WIN_hwin

int win[] = {

  //https://musescore.com/user/27103612/scores/4834399

  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
  
};
void WIN(int pin) {

  int tempo = 180;
  int notes = sizeof(win) / sizeof(win[0]) / 2;
  int wholenote = (60000 * 4) / tempo;
  int divider = 0, noteDuration = 0;

  ledcAttachPin(pin, 0); // Asignamos el pin 32 al canal 0 de PWM
  EasyBuzzer.setPin(pin);

  for (int thisNote = 0; thisNote < notes * 2; thisNote += 2) {
    divider = win[thisNote + 1];
    if (divider > 0) {
      noteDuration = wholenote / divider;
    } else if (divider < 0) {
      noteDuration = wholenote / abs(divider);
      noteDuration *= 1.5;
    }
    EasyBuzzer.singleBeep(win[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    EasyBuzzer.stopBeep();
  }
}

#endif
