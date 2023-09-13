import RPi.GPIO as GPIO
import time

# Set GPIO pins
TRIG_PIN = 24
ECHO_PIN = 23
LED_PIN = 16

# Initialize GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(TRIG_PIN, GPIO.OUT)
GPIO.setup(ECHO_PIN, GPIO.IN)
GPIO.setup(LED_PIN, GPIO.OUT)

# Created a PWM object for the LED
led_pwm = GPIO.PWM(LED_PIN, 100)  # Frequency = 100 Hz

def calculateDistance():
    # Trigger the ultrasonic sensor
    GPIO.output(TRIG_PIN, True)
    time.sleep(0.00001)
    GPIO.output(TRIG_PIN, False)

    # Measure the time it takes for the echo signal to return
    while GPIO.input(ECHO_PIN) == 0:
        pulse_start = time.time()

    while GPIO.input(ECHO_PIN) == 1:
        pulse_end = time.time()

    # Calculate distance in centimeters
    pulse_duration = pulse_end - pulse_start
    distance = pulse_duration * 17150  

    return round(distance, 2)

try:
    led_pwm.start(0)  # Start PWM with 0% duty cycle
    while True:
        distance = calculateDistance()
        print(f"Distance: {distance} cm")
        # Map the distance to LED Intensity (0% to 100%)
        if distance<80:
                Intensity = ((80-distance)*2)
                print(f"Intensity: {Intensity}%")                 
                # Update LED Intensity
                led_pwm.ChangeDutyCycle(Intensity)
       
        else:
          led_pwm.start(0)
        time.sleep(1)

except KeyboardInterrupt:
    led_pwm.stop()  # Stop PWM on exit
    GPIO.cleanup()

