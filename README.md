# HotBod
HotBod is an Arduino No Touch Thermometer with MLX90614 sensor and various output options.
It was inspired by commercial thermometer used to measure the temperature of shopping mall goers in the time of COVID-19 outbreak.


# Preparation
- On the Arduino IDE, install the library according to the parts you are going to use by doing:
  - Menu -> Sketch -> Include Library -> Manage Libraries and wait for Library Manager dialog.
  - On 'Filter your search' type in the name of the parts such as: Adafruit MLX90614, Adafruit SSD1306, Liquid Crystal i2c.
  - Click install
  - Repeat the obve with other libraries
  
# Running
- Copy any of the .ino file in this repository and paste it on your Arduino IDE.
  Available files:
  - hotbod_fusion	Reading MDX90614 + Ultrasonic (Sensor Fusion), output to OLED, LCD, Buzzer	
  - hotbod_lcd	Reading from MLX90614 and output to LCD with i2c	
  - hotbod_oled.ino	Reading from MLX90614 and output to Serial + OLED	
  - hotbod_serial.ino  Reading from MLX90614 and output to Serial port only
- Compile and upload to Arduino
