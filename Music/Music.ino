/*
 Melody
 
 Plays a melody 
 
 circuit:
 * 8-ohm speaker on digital pin 2
 
 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe 
 modified  8 Aug 2014 for bitDuino13
 by @maris_HY

This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/Tone
 
 */
#include <avr/pgmspace.h> 
#include "pitches.h"
#include "melody2.h"

//#define led 3
#define spk 4

void setup() {
//  pinMode(led,OUTPUT);
}

void loop() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < (sizeof(noteDurations)>>1); thisNote++) {
    unsigned int noteDuration = pgm_read_word_near(noteDurations+thisNote);
    tone(spk, pgm_read_word_near(melody+thisNote));
//    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    delay(noteDuration);

    // stop the tone playing:
    noTone(spk);
//   digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
//   delay(noteDuration>>2);
   delay(64);
  }
  delay(1500);
}
