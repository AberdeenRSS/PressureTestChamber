#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include <commands.h>
#include <chamber_state_machine.h>

Adafruit_BMP3XX bmp;

#define SEALEVELPRESSURE_HPA (1013.25)

#define OUT_VALVE_PIN 17
#define IN_VALVE_PIN 16

void setup() {
  pinMode(OUT_VALVE_PIN, OUTPUT);
  pinMode(IN_VALVE_PIN, OUTPUT);

  Serial.begin(9600);
  while (!Serial);
  Serial.println("Adafruit BMP388 / BMP390 test");

  if (!bmp.begin_I2C()) {   // hardware I2C mode, can pass in address & alt Wire
    Serial.println("Could not find a valid BMP3 sensor, check wiring!");
    while (1);
  }

  Serial.println("BMP390 connection successful");

  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

}

void loop() {

  double pressure = bmp.pressure;
  double altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);

  readSerial();

  ValveInstructions newValveInstructions = updateState(pressure, altitude);

  digitalWrite(OUT_VALVE_PIN, newValveInstructions.outPosition == ValvePositions::Open ? HIGH : LOW);
  digitalWrite(IN_VALVE_PIN, newValveInstructions.inPosition == ValvePositions::Open ? HIGH : LOW);

  if (! bmp.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }


}
