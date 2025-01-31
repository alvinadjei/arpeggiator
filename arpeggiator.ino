/*
  GenEd1080 Lab 7 (EE Lab 2)
  13-key MIDI keyboard
*/

// Define some variables that have fixed value (const)
const int mystery1 = 0; // Acceptable values: -4 to +4
const int mystery2 = 127; // Acceptable values: 0 to 127

// Include the MIDI library
#include <MIDI.h>

// Create and bind the MIDI interface to the default hardware Serial port
MIDI_CREATE_DEFAULT_INSTANCE();

// Define some fixed variables re: the keyboard
const int numKeys = 13; // This is a 13-key keyboard
const int buttons[numKeys] = {A1, A2, A3, A4, A5, A6, 0, 1, 2, 3, 4, 5, 6}; // The keys will be connected to these pins on the Arduino
int buttonState = 0; // Stores the button state
int lastButtonState = 0; // Button's most recent state
int ledState = LOW; // Initialize LED to be off


// Initialize the notePlaying array to be all zeros. This array describes the status of all the notes - whether it is currently playing or not ('YES playing' or 'NOT playing').
bool notePlaying[numKeys] = {0};  // bool has two states: [0 and 1] = [FALSE and TRUE] = [LOW and HIGH]. 0 = this note is not playing (the key is not pressed); 1 = this note is already playing (the key is pressed) 

void setup() {
  // define pinMode for all the buttons as INPUT
  for (int i = 0; i < numKeys; i++) {
    pinMode(buttons[i], INPUT);
  }

  // set up the built-in LED as an OUTPUT (If we don't do this, the Arduino does not know "how to talk to" the built-inLED and we wouldn't be able to use it)
  pinMode(LED_BUILTIN, OUTPUT);

  MIDI.begin();
}


void loop() {
  
  for (int i = 0; i < numKeys; i++) {  // Loop through all 13 keys...
    
    buttonState = digitalRead(buttons[i]);  
    // Check if the button state has changed
    if (buttonState != lastButtonState) {
      // If the button is pressed, change the LED state
      if (buttonState == HIGH) {
        ledState = !ledState;  // Toggle the LED state
        notePlaying[i] = true;  // So if the i-th note is 'NOT playing', then update the status of i-th note to be 'YES playing'
        MIDI.sendNoteOn(60 + i + 12*mystery1, mystery2, 1); // and play the i-th note
        delay(100);
      }
    }
    
    digitalWrite(LED_BUILTIN, ledState);

    lastButtonState = buttonState;
  }
}