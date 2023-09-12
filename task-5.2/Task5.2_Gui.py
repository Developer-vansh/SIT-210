# Import the tkinter library as 'tk' for creating the GUI
import tkinter as tk

# Import the RPi.GPIO library as 'GPIO' for controlling GPIO pins on a Raspberry Pi
import RPi.GPIO as GPIO

# Set the GPIO mode to 'BOARD' mode, which uses physical pin numbers
GPIO.setmode(GPIO.BOARD)

# Define GPIO pin numbers for the red, green, and blue LEDs
red = 36
green = 38
blue = 40

# Disable GPIO warnings
GPIO.setwarnings(False)

# Set up GPIO pins as output pins for the LEDs
GPIO.setup(red, GPIO.OUT)
GPIO.setup(green, GPIO.OUT)
GPIO.setup(blue, GPIO.OUT)

# Function to turn off all LEDs
def LEDsOFF():
    GPIO.output(red, GPIO.LOW)
    GPIO.output(green, GPIO.LOW)
    GPIO.output(blue, GPIO.LOW)

# Function to turn on the red LED
def OnRedLED():
    LEDsOFF()  # Turn off all LEDs first
    GPIO.output(red, GPIO.HIGH)  # Turn on the red LED
    print("Turn on red LED")

# Function to turn on the green LED
def OnGreenLED():
    LEDsOFF()  # Turn off all LEDs first
    GPIO.output(green, GPIO.HIGH)  # Turn on the green LED
    print("Turn on green LED")

# Function to turn on the blue LED
def OnBlueLED():
    LEDsOFF()  # Turn off all LEDs first
    GPIO.output(blue, GPIO.HIGH)  # Turn on the blue LED
    print("Turn on blue LED")

# Function to close the GUI window and clean up GPIO settings
def close():
    LEDsOFF()  # Turn off all LEDs
    GPIO.cleanup()  # Clean up GPIO settings
    window.destroy()  # Destroy the tkinter window

# Create a tkinter window and set its title
window = tk.Tk()
window.title('Vansh LED Control')

# Created a button for turning on the red LED 
button = tk.Button(window, text='Turn RED', command=OnRedLED, bg='red', height=1, width=40)
button.pack()

# Created a button for turning on the green LED 
button = tk.Button(window, text='Turn GREEN', command=OnGreenLED, bg='green', height=1, width=40)
button.pack()

# Created a button for turning on the blue LED 
button = tk.Button(window, text='Turn BLUE', command=OnBlueLED, bg='blue', height=1, width=40)
button.pack()

# Created an exit button to close the application 
exitbutton = tk.Button(window, text='Exit', command=close, bg='yellow', height=2, width=30)
exitbutton.pack()

# Start the tkinter main event loop
window.mainloop()
