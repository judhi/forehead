// ---------- Forehead (LCD i2c)
// ---------- Arduino No Touch Thermometer
// ---------- Components: Arduino Uno, CJMCU906 (MLX90614), OLED SSD1306, LCD
// ---------- by Judhi Prasetyo, March 2020 for The Arduino Day

#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();  // preparing sensor

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

float ta; // ambient temperature
float to; // object temperature

int loop_interval = 500; // check temp every 5 sec

void setup() {
  Serial.begin(115200);
  // starting LCD
  lcd.init();
  lcd.backlight();
}

void loop() {
  // reading object (to) and ambient (ta) temperature
  to = mlx.readObjectTempC();
  ta = mlx.readAmbientTempC();
  
  // log to Serial port
  Serial.println("Object:" + String(to) + ", Ambient:" + String(ta));
  
  // show on LCD
  lcd.setCursor(0,0);
  lcd.print("Object  : "  + String(to) + "C");
  lcd.setCursor(0,1);
  lcd.print("Ambient : " + String(ta) + "C");
}

