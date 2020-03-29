// ---------- Forehead Fusion (input temp & distance sensors, output to OLED, LCD, Buzzer)
// ---------- Arduino No Touch Thermometer
// ---------- Components: Arduino Uno, CJMCU906 (MLX90614), OLED SSD1306, LCD, Ultrasonic
// ---------- by Judhi Prasetyo, March 2020 for The Arduino Day
// ---------- add passive buzzer to pin D5

#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

// --------- Ultrasonic Sensor preparation
#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define LEDPin 13 // Onboard LED
int maximumRange = 40; // Maximum range needed
int minimumRange = 30; // Minimum range needed
long duration, distance; // Duration used to calculate distance

float ta; // ambient temperature
float to, stemp; // object temperature

int loop_interval = 100; // check temp every 200 msec
int readcount = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
  Serial.begin(115200);
  // setting up the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(1000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  lcd.init();
  lcd.backlight();
}

void loop() {
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration / 58.2;


  // reading object (to) and ambient (ta) temperature, and round it
  to = 8.5 + round(mlx.readObjectTempC() * 10) * .1;
  ta = round(mlx.readAmbientTempC() * 10) * .1;

  // log to Serial port
  Serial.println("Object:" + String(to) + ", Ambient:" + String(ta));

  // display on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 45);
  display.print("Dist:" + String(distance) + "cm");
  display.setCursor(0, 55);
  display.print("Ambient:" + String(ta) + "C");
  display.setTextSize(2);
  display.setCursor(0, 0);
  if (distance > maximumRange) {
    display.print("GET CLOSER");
  }
  if (distance < minimumRange) {
    display.print("TOO CLOSE!");
  }
  if ((distance >= minimumRange) && (distance <= maximumRange)) {
    if (readcount == 5) {   // after reading 5 consecutive time
      to = stemp / 5;       // get the average temp and show it
      display.print("YOUR TEMP:");
      display.setTextSize(3);
      display.setCursor(20, 18);
      display.print(String(to).substring(0, 4) + "C");
      display.display();
      readcount = 0;
      stemp = 0;
      if (to >= 37.5) {
        play_alert();
      } else {
        play_ok();
      }
      loop_interval = 5000; // wait for 5 seconds
    } else {
      display.print("HOLD ON"); // when in range, ask user to hold position
      stemp = stemp + to;
      readcount++;
      loop_interval = 200;      // until approx. 5 x 200 ms = 1 sec
    }
  } else {                      // if user is out of range, reset calculation
    loop_interval = 100;
    readcount = 0;
    stemp = 0;
  }
  display.display();
  delay(loop_interval);

  // show on LCD
  lcd.setCursor(0, 0);
  lcd.print("Object  : "  + String(to) + "C");
  lcd.setCursor(0, 1);
  lcd.print("Ambient : " + String(ta) + "C");

  pinMode(echoPin, OUTPUT);
  digitalWrite(echoPin, 0);
  delayMicroseconds(200);
}

void play_ok() {  // play three sequential notes when object temperature is below 37.5C
  tone(3, 600, 200);
  delay(100);
  tone(3, 750, 200);
  delay(100);
  tone(3, 1000, 200);
  delay(100);
  noTone(3);
}

void play_alert() { // beep 3x when object temperature is >= 37.5C
  tone(3, 1000, 500);
  delay(1000);
  tone(3, 1000, 500);
  delay(1000);
  tone(3, 1000, 500);
  delay(1000);
  noTone(3);
}
