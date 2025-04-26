#include "pitches.h"
#define BUZZER_PIN 9

int super_note = 0; 

int melody[] = {
  NOTE_E2, NOTE_E2, NOTE_E3, NOTE_E2, NOTE_E2, NOTE_D3, NOTE_E2, NOTE_E2, 
  NOTE_C3, NOTE_E2, NOTE_E2, NOTE_AS2, NOTE_E2, NOTE_E2, NOTE_B2, NOTE_C3,
  NOTE_E2, NOTE_E2, NOTE_E3, NOTE_E2, NOTE_E2, NOTE_D3, NOTE_E2, NOTE_E2,
  NOTE_C3, NOTE_E2, NOTE_E2, NOTE_AS2,
};

int durations[] = {
  8, 8, 8, 8, 8, 8, 8, 8, 
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 2,
  
};
const int trigPin = 3;
const int echoPin = 2; 
const int buzzer = 9; 
float duration, distance; 
void setup()
{
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(buzzer, OUTPUT); 
  Serial.begin(9600);
}

int getDistance()
{
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH); 
  distance = (duration*0.343)/2; 
  return distance;
}

void printVals(int val1, int super_note)
{
  Serial.print("note: ");
  Serial.print(val1);
  Serial.print(" | super_note: ");
  Serial.println(super_note);
}

void loop()
{
  int size = sizeof(durations) / sizeof(int);

  for (int note = super_note; note < size; note++) 
  {
    int distance = getDistance();
    printVals(note, super_note); 

    if (distance < 100)
    {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = (distance * 10) / durations[note]; 
    tone(BUZZER_PIN, melody[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    
    //stop the tone playing:
    noTone(BUZZER_PIN);
    }
    else
    {
      super_note = note;
      break;
    }
    if (note == size - 1)
    {
      super_note = 0; 
      break;
    }
  }
  Serial.print("Distance: "); 
  Serial.println(distance); 
  delay(100); 
}
