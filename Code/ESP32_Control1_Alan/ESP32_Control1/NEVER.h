// -------------------------------------------------
// Copyright (c) 2024 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "pitches.h"

#define BUZZER_PIN 32


void NEVER(){ 
    int melody[] = {
    NOTE_A4, REST, NOTE_B4, REST, NOTE_C5, REST, NOTE_A4, REST,
    NOTE_D5, REST, NOTE_E5, REST, NOTE_D5, REST,

    NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_E5, NOTE_E5, REST,
    NOTE_D5, REST,

    NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_D5, NOTE_D5, REST,
    NOTE_C5, REST, NOTE_B4, NOTE_A4, REST,

    NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_D5, REST,
    NOTE_B4, NOTE_A4, NOTE_G4, REST, NOTE_G4, REST, NOTE_D5, REST, NOTE_C5, REST,

    NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_E5, NOTE_E5, REST,
    NOTE_D5, REST,

    NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_G5, NOTE_B4, REST,
    NOTE_C5, REST, NOTE_B4, NOTE_A4, REST,

    NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_D5, REST,
    NOTE_B4, NOTE_A4, NOTE_G4, REST, NOTE_G4, REST, NOTE_D5, REST, NOTE_C5, REST,

    NOTE_C5, REST, NOTE_D5, REST, NOTE_G4, REST, NOTE_D5, REST, NOTE_E5, REST,
    NOTE_G5, NOTE_F5, NOTE_E5, REST,

    NOTE_C5, REST, NOTE_D5, REST, NOTE_G4, REST
  };

  int durations[] = {
    8, 8, 8, 8, 8, 8, 8, 4,
    8, 8, 8, 8, 2, 2,

    8, 8, 8, 8, 2, 8, 8,
    2, 8,

    8, 8, 8, 8, 2, 8, 8,
    4, 8, 8, 8, 8,

    8, 8, 8, 8, 2, 8, 8,
    2, 8, 4, 8, 8, 8, 8, 8, 1, 4,

    8, 8, 8, 8, 2, 8, 8,
    2, 8,

    8, 8, 8, 8, 2, 8, 8,
    2, 8, 8, 8, 8,

    8, 8, 8, 8, 2, 8, 8,
    4, 8, 3, 8, 8, 8, 8, 8, 1, 4,

    2, 6, 2, 6, 4, 4, 2, 6, 2, 3,
    8, 8, 8, 8,

    2, 6, 2, 6, 2, 1
  };

  int size = sizeof(durations) / sizeof(int);

  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);

    //stop the tone playing:
    noTone(BUZZER_PIN);
  }
}
