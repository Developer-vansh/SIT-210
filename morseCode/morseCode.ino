#define UNIT 500
#define DOT_LENGTH (1*UNIT) 
#define DASH_LENGTH (1*UNIT) 
#define CODE_PART_SPACE (1*UNIT)      
#define LETTER_SPACE (3 * UNIT) 
#define  LED_PIN 13
#define BUTTON_PIN 2
String name;
//This array is declared for storing the morse code for all the alphabets
String letters_code[26]={".-","-...","-.-.","-..",".","..-.","--.","....","..",
                          ".---","-.-",".-..","--","-.","---",".--.","--.-",".-.",
                          "...","-","..-","...-",".--","-..-","-.--","--.."                        
                        };

void setup() {
  Serial.begin(9600);
  pinMode( LED_PIN ,OUTPUT);
  pinMode( BUTTON_PIN ,INPUT);
}

//used to blink the dot
void blink_dot() {
    digitalWrite( LED_PIN , HIGH);
    delay(DOT_LENGTH);
    digitalWrite( LED_PIN , LOW);
}
//used to blink the dash
void blink_dash() {
    digitalWrite( LED_PIN , HIGH);
    delay(DASH_LENGTH);
    digitalWrite( LED_PIN , LOW);
}
//delay b/w the . and - of morse code
void symboldelay() {
    delay(CODE_PART_SPACE);+

}
//delay after blinking one letter
void letterdelay() {
    delay(LETTER_SPACE);
}
//it  decodes the code for letter  and blink the led
char decode_letter(char ch)
{
  int index=ch-'A';
 String morse_code= letters_code[index];
 for(int i=0;i<morse_code.length();i++){
   if(morse_code[i]=='.'){
     blink_dot();
     if(i!=morse_code.length()-1)symboldelay();
   }
   else if(morse_code[i]=='-'){
     blink_dash();
     if(i+1<morse_code.length()-1)symboldelay();
     }
 }
}
//it  decodes the letters in the word and blink the led
void decode_word(String word){
 for(int i=0;i<word.length();i++){
   decode_letter(word[i]);
     if(i+1<word.length()-1)letterdelay();
 }
 }

String takeInput() {
  String input = "";
  while (Serial.available() > 0) {
    char ch = Serial.read();
    if (ch == '\n') {
      break;
    }
    input += ch;
  }
  input.toUpperCase();
  return input;
}

void loop() {

if(digitalRead(BUTTON_PIN)==LOW){
name = takeInput();
decode_word(name);
}
else{
  digitalWrite( LED_PIN , LOW);
}

}
