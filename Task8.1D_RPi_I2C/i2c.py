import smbus2
from bh1750 import BH1750

# Define the I2C bus and the sensor address
i2c_bus = smbus2.SMBus(1)  # Uses I2C bus 1 
light_sensor = BH1750(i2c_bus,0x23)  #This is the Bydefault I2C address of BH1750

# Function to check the type of light intensity
def check_type(intensity):
    if intensity > 1000:
        return "Too Bright"
    elif intensity > 500:
        return "Bright"
    elif intensity > 200:
        return "Medium"
    elif intensity > 100:
        return "Dark"
    else:
        return "Too Dark"
        
def calculate():
      intensity = light_sensor.measure_high_res()
      print("Current Light Intensity:",  intensity, "lux")
      intensity_type = check_type( intensity/10)
      print("Light Intensity Type:",  intensity_type )

try:
    while True:
        calculate()
      
except KeyboardInterrupt:
        GPIO.cleanup()
