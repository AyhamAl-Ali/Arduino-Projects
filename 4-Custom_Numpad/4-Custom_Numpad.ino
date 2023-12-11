#include <Keyboard.h>
#include <Keypad.h>


// toggle special keys with numlock
// special keys can make anything you like
bool special_keys_status = false; // default false

const int BUILTIN_LED = 13;

const byte ROWS = 5; // define the number of rows on the keypad
const byte COLS = 4; // define the number of columns on the keypad

// Define the keymap
// char keys[ROWS][COLS] = {
//   {'Enter', '.', '0', '0'},
//   {'Enter', '3', '2', '1'},
//   {'+', '6', '5', '4'},
//   {'+', '9', '8', '7'},
//   {'-', '*', '/', 'num'}
// };
char keys[ROWS][COLS] = {
  {'KEY_KP_ENTER', 'KEY_KP_DOT'     , 'KEY_KP_0'    , 'KEY_KP_0'    },
  {'KEY_KP_ENTER', 'KEY_KP_3'       , 'KEY_KP_2'    , 'KEY_KP_1'    },
  {'KEY_KP_PLUS' , 'KEY_KP_6'       , 'KEY_KP_5'    , 'KEY_KP_4'    },
  {'KEY_KP_PLUS' , 'KEY_KP_9'       , 'KEY_KP_8'    , 'KEY_KP_7'    },
  {'KEY_KP_MINUS', 'KEY_KP_ASTERISK', 'KEY_KP_SLASH', 'KEY_NUM_LOCK'} // KEY_NUM_LOCK
};
char special_keys[ROWS][COLS] = {
  {'KEY_KP_ENTER', 'KEY_KP_DOT', 'KEY_LEFT_ALT+KEY_KP_0', 'KEY_LEFT_ALT+KEY_KP_0'},
  {'KEY_KP_ENTER', 'KEY_LEFT_ALT+KEY_KP_3', 'KEY_LEFT_ALT+KEY_KP_2', 'KEY_LEFT_ALT+KEY_KP_1'},
  {'KEY_LEFT_ALT+KEY_KP_PLUS', 'KEY_LEFT_ALT+KEY_KP_6', 'KEY_LEFT_ALT+KEY_KP_5', 'KEY_LEFT_ALT+KEY_KP_4'},
  {'KEY_LEFT_ALT+KEY_KP_PLUS', 'KEY_LEFT_ALT+KEY_KP_9', 'KEY_LEFT_ALT+KEY_KP_8', 'KEY_LEFT_ALT+KEY_KP_7'},
  {'KEY_LEFT_ALT+KEY_KP_MINUS', 'KEY_LEFT_ALT+KEY_KP_ASTERISK', 'KEY_LEFT_ALT+KEY_KP_SLASH', 'KEY_NUM_LOCK'} // KEY_NUM_LOCK
};

byte rowPins[ROWS] = {6, 5, 4, 3, 2}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {10, 9, 8, 7}; // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
Keypad specialKeypad = Keypad(makeKeymap(special_keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  pinMode(BUILTIN_LED, OUTPUT); // built-in LED for special keys indicator
}

void loop() {
  char key = keypad.getKey();
  char specialKey = specialKeypad.getKey();

  if (key) {
    if (key == 224) { // KEY_NUM_LOCK
      toggleSpecialKeys();

    } else {
      if (isSpecialKeys()) {
        Serial.print("Special Key Pressed: ");
        Serial.println(specialKey);
        if (specialKey)

      } else {
        Serial.print("Key Pressed: ");
        Serial.println(key);
        Keyboard.write(key); // Simulate key press
      }
    }
    
    delay(1); // Adjust delay based on your needs
  }
}

bool isSpecialKeys() {
  return special_keys_status;
}

void toggleSpecialKeys() {
  if (special_keys_status == true) { // turn off
    special_keys_status = false;
  } else { // turn on
    special_keys_status = true;
  }

  toggleSpecialKeysLED();
}

void toggleSpecialKeysLED() {
  while (special_keys_status == true) {
    digitalWrite(BUILTIN_LED, HIGH); // on
    delay(100);
    digitalWrite(BUILTIN_LED, LOW); // off
    delay(100);
  }
  // force on
  digitalWrite(BUILTIN_LED, HIGH);
}
