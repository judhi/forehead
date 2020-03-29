// ---------- HotBod (Serial)
// ---------- Arduino No Touch Thermometer
// ---------- Components: Arduino Uno, CJMCU906 (MLX90614) output to serial port
// ---------- by Judhi Prasetyo, March 2020 for The Arduino Day

#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

float ta;
float to;

int loop_interval = 1000; // check temp every 1 sec

void setup() {
  mlx.begin();  // enable the MLX90614 reading
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  // reading object (to) and ambient (ta) temperature
  to = 8 + mlx.readObjectTempC();
  ta = mlx.readAmbientTempC();
  // log to Serial port
  Serial.println("Object:" + String(to) + "C, Ambient:" + String(ta) + "C");
  delay(loop_interval);
}
