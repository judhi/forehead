// ---------- Arduino No Touch Thermometer to battle COVID-19
// ---------- Components: Arduino Uno, CJMCU906 (MLX90614), TFmini distance sensor, OLED SSD1306
// ---------- by Judhi Prasetyo, March 2020 for The Arduino Day

#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>

#include <SoftwareSerial.h>
#include "TFMini.h"
// Setup software serial port
SoftwareSerial mySerial(8, 9);      // Uno RX (TFMINI TX), Uno TX (TFMINI RX)
TFMini tfmini;

int distance;//actual distance measurements of LiDAR
int strength;//signal strength of LiDAR
int check;//save check value

float ta;
float to;
float offset = 10.8;

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define LEDPin 13 // Onboard LED

int maximumRange = 70; // Maximum range needed
int minimumRange = 50; // Minimum range needed

String txt = "", line1 = "", line2 = "";

int loop_interval = 300, waiting_time = 500; // check temp every 200 msec

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(115200);
  mySerial.begin(TFMINI_BAUDRATE);
  tfmini.begin(&mySerial);
  
  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Middlesex");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("University Dubai");
  delay(1000);
  lcd.clear();//Clean the screen
  lcd.setCursor(0, 0);
  lcd.print("RobotechX ");
  lcd.setCursor(0, 1);
  lcd.print("Lab ");
  delay(1000);
}

void loop() {

  // ----- LIDAR distance checking -----
  // Take one TF Mini distance measurement
  uint16_t distance = tfmini.getDistance();
  uint16_t strength = tfmini.getRecentSignalStrength();

  // Display the measurement
//  Serial.print(distance);
//  Serial.print(" cm      sigstr: ");
//  Serial.println(strength);

  // end of LIDAR check ----
  
    // reading object (to) and ambient (ta) temperature
    to = mlx.readObjectTempC() + offset;
    //to = round(mlx.readObjectTempC()*10)/10;
    ta = mlx.readAmbientTempC();
    // log to Serial port
  
    Serial.println("to=" + String(to) + ", ta=" + String(ta));
  
    if (distance > maximumRange) {
      line1 = "MOVE CLOSER";
      waiting_time = 0;
    }
    if (distance < minimumRange) {
      line1 = "TOO CLOSE!";
      waiting_time = 0;
    }
    if ((distance >= minimumRange) && (distance <= maximumRange)) {
      line1 = String(to).substring(0, 4) + "C";
      line1 = "Your temp: " + line1;
      waiting_time = 500;
    }

    line2 = distance;
    line2 = "Distance : " + line2 + " cm";

    if (distance < 30 | distance > 100) { // behind the glass
      line1 = "COME AND CHECK";
      line2 = "YOUR TEMPERATURE";
      waiting_time = 0;
    }    

        
    lcd.clear();//Clean the screen
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
  
    delay(loop_interval + waiting_time);
  }
