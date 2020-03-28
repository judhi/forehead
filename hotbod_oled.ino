// ---------- HotBod (OLED)
// ---------- Arduino No Touch Thermometer
// ---------- Components: Arduino Uno, CJMCU906 (MLX90614), OLED SSD1306
// ---------- by Judhi Prasetyo, March 2020 for The Arduino Day

#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

float ta; // ambient temperature
float to; // object temperature

int loop_interval = 1000; // check temp every 1 sec

void setup() {
  // start serial port
  Serial.begin(115200);
  // setting up the OLED display ~  use i2c scanner
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(1000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  // reading object (to) and ambient (ta) temperature
  to = 8 + mlx.readObjectTempC();
  ta = mlx.readAmbientTempC();
  // log to Serial port
  Serial.println("Object:" + String(to) + "C, Ambient:" + String(ta) + "C");
  // show on OLED
  display.clearDisplay();
  display.setTextSize(1); //Size 1 means w=6 h=8
  display.setCursor(0, 2);
  display.print("Arduino Thermometer");
  display.setTextSize(2);  //Size 2 means w=12 h=16
  display.setCursor(0, 20);
  display.print("To: " + String(to) + "C");
  display.setCursor(0, 40);
  display.print("Ta: " + String(ta) + "C");
  display.display();  // send to screen
  delay(loop_interval); // wait for a while
}
