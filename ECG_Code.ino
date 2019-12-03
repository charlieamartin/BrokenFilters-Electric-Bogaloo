#include <Arduino.h>

int analogInPin = A0;
float ECG_value = 0.0;
float time1 = 0.0;
float time2 = 0.0;
float elapsed_time = 0.0;
float threshold = 1.0;
float HR = 0.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  plotData();
  measure_time();
  if (elapsed_time > 0) {
    HR = calculateHR(elapsed_time);
  }
  Serial.print("Heart Rate:");
  Serial.println(HR);
}

void plotData() {
  ECG_value = -1 * analogRead(analogInPin);
  Serial.println(ECG_value);
  delay(2);
}

void measure_time() {
  if (ECG_value <= threshold) {
    elapsed_time = 0;
  }
  else if (ECG_value > threshold) {
    time2 = millis();
    elapsed_time = time2 - time1;
  }
}

float calculateHR(float elapsed_time) {
  float HR = (1 / elapsed_time) * 1000 * 60;
  time1 = time2;
  return(HR);
}
