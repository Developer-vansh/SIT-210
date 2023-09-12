import tkinter as tk
import RPi.GPIO as GPIO
import time

# Define GPIO pin for the LED
LED_PIN = 36

# Define time units for Morse code
UNIT = 0.5  
DOT_LENGTH = 1 * UNIT
DASH_LENGTH = 3 * UNIT
CODE_PART_SPACE = 1 * UNIT
LETTER_SPACE = 3 * UNIT  

# Define Morse code representation of alphabets
letters_code = {
    'A': '.-', 'B': '-...', 'C': '-.-.', 'D': '-..', 'E': '.',
    'F': '..-.', 'G': '--.', 'H': '....', 'I': '..', 'J': '.---',
    'K': '-.-', 'L': '.-..', 'M': '--', 'N': '-.', 'O': '---',
    'P': '.--.', 'Q': '--.-', 'R': '.-.', 'S': '...', 'T': '-',
    'U': '..-', 'V': '...-', 'W': '.--', 'X': '-..-', 'Y': '-.--', 'Z': '--..'
}

# Initialize GPIO settings
GPIO.setmode(GPIO.BOARD)
GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.output(LED_PIN, GPIO.LOW)

# Function to blink a dot
def blink_dot():
    GPIO.output(LED_PIN, GPIO.HIGH)
    time.sleep(DOT_LENGTH)
    GPIO.output(LED_PIN, GPIO.LOW)
    time.sleep(CODE_PART_SPACE)

# Function to blink a dash
def blink_dash():
    GPIO.output(LED_PIN, GPIO.HIGH)
    time.sleep(DASH_LENGTH)
    GPIO.output(LED_PIN, GPIO.LOW)
    time.sleep(CODE_PART_SPACE)

# Function to decode a word into Morse code and blink the LED
def decode_and_blink():
    word = input.get().upper()
    for letter in word:
        if letter == ' ':
            time.sleep(LETTER_SPACE)  # Space between words
        elif letter in letters_code:
            code = letters_code[letter]
            for symbol in code:
                if symbol == '.':
                    blink_dot()
                elif symbol == '-':
                    blink_dash()

# Create the main window
window = tk.Tk()
window.title("LED Blinker For Morse Code ")

# Create a label and an entry widget for entering the word
label = tk.Label(window, text="Enter a word:")
label.pack()
input = tk.Entry(window)
input.pack()

# Create a button to start blinking
button = tk.Button(window, text="Blink LED", command=decode_and_blink)
button.pack()

# Start the GUI event loop
window.mainloop()

# Cleanup GPIO settings when the application exits
GPIO.cleanup()
