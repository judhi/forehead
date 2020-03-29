# Forehead
Forehead is an Arduino No Touch Thermometer with MLX90614 sensor and various output options.
It was inspired by commercial thermometer used to measure the temperature of shopping mall goers in the time of COVID-19 outbreak.

Unlike the commercial no touch thermometer that requires very close proximity to the measured object, Forehead's sensor can be placed further away from the person's forehead and still get good reading. Consistent reading can be met by adding ultrasonic sensor to measure the distance between the sensor and the MLX90614, so far the ideal distance found is between 30 to 40 cm. You may need to calibrate the values according to the parts you are using.

# Hardware
This project caters for various types of hardware, currently it supports:
- Arduino Uno/Nano
- MLX90614 Infrared temperature sensor
- Optional
  - SSD1306 OLED display
  - LCD i2c, two or four lines
  - Ultrasonic sensor
  - Passive buzzer or speaker
  
  
![Image of Forehead Wiring](https://github.com/judhi/forehead/blob/master/img/forehead-wiring.png)

Minimum hardware parts needed are only the Arduino and MLX90614 sensor.

# Preparation
- On the Arduino IDE, install the library according to the parts you are going to use by doing:
  - Menu -> Sketch -> Include Library -> Manage Libraries and wait for Library Manager dialog.
  - On 'Filter your search' type in the name of the parts such as: Adafruit MLX90614, Adafruit SSD1306, Liquid Crystal i2c.
  - Click install
  - Repeat the obve with other libraries
  
# Running
- Copy any of the _.ino_ sketch file in this repository and paste it on your Arduino IDE.
  Available sketches:
  - _forehead_fusion.ino_	Reading MDX90614 + Ultrasonic (Sensor Fusion), output to OLED, LCD, Buzzer	
  - _forehead_lcd.ino_	Reading from MLX90614 and output to LCD with i2c only
  - _forehead_oled.ino_	Reading from MLX90614 and output to Serial + OLED	only
  - _forehead_serial.ino_  Reading from MLX90614 and output to Serial port only
- Compile and upload to Arduino
