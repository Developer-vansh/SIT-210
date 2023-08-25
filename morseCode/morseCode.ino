// Define time units for different parts of Morse code
#define UNIT 500
#define DOT_LENGTH (1 * UNIT)
#define DASH_LENGTH (3 * UNIT)
#define CODE_PART_SPACE (1 * UNIT)
#define LETTER_SPACE (3 * UNIT)

// Define the pin numbers for LED and button
#define LED_PIN 13
#define BUTTON_PIN 2

// Variable to store the input name
String name="VANSH";

// Morse code representation of alphabets
String letters_code[26] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
    ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
    "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(LED_PIN, OUTPUT);     // Set LED pin as output
  pinMode(BUTTON_PIN, INPUT_PULLUP);   // Set button pin as input
}

// Function to blink a dot
void blink_dot() {
    digitalWrite(LED_PIN, HIGH);  // Turn on the LED
    delay(DOT_LENGTH);            // Keep LED on for DOT_LENGTH milliseconds
    digitalWrite(LED_PIN, LOW);   // Turn off the LED
}

// Function to blink a dash
void blink_dash() {
    digitalWrite(LED_PIN, HIGH);  // Turn on the LED
    delay(DASH_LENGTH);           // Keep LED on for DASH_LENGTH milliseconds
    digitalWrite(LED_PIN, LOW);   // Turn off the LED
}

// Delay between different parts of a Morse code symbol
void symboldelay() {
    delay(CODE_PART_SPACE);
}

// Delay after blinking one letter
void letterdelay() {
    delay(LETTER_SPACE);
}

// Decode a single letter's Morse code and blink the LED accordingly
char decode_letter(char ch) {
    int index = ch - 'A';  // Calculate index for the letter in the Morse code array
    String morse_code = letters_code[index];  // Get Morse code for the letter

    for (int i = 0; i < morse_code.length(); i++) {
        if (morse_code[i] == '.') {
            blink_dot();
        } else if (morse_code[i] == '-') {
            blink_dash();
        }
        if (i + 1 < morse_code.length() - 1) {
            symboldelay();
        }
    }
}

// Decode a whole word and blink the LED accordingly
void decode_word(String word) {
     Serial.println(word);
    for (int i = 0; i < word.length(); i++) {
       Serial.println(word[i]);
        decode_letter(word[i]);
        if (i + 1 < word.length() - 1) {
            letterdelay();
        }
    }
}

// Function to read input from serial monitor until newline character

// void takeInput() {
//   Serial.println("Enter your name");
//     while (name=="") {
//         name=Serial.readStringUntil('/n');
//     }
//     name.toUpperCase();  // Convert input to uppercase
    
// }
void loop() {
    //Check if the button is pressed
    if (digitalRead(BUTTON_PIN) == LOW) {
        decode_word(name);  // Decode and blink the Morse code
        delay(500);
    } else {
        digitalWrite(LED_PIN, LOW);  // Turn off the LED
    }
   


}

