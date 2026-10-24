#include <Arduino.h>
#include <Wire.h>
// #include <Adafruit_NeoPixel.h>
#include "config.h"
#include <ModbusRTU.h>
#include <ModbusTCP.h>

// SERIAL_8N1 — без parity
// SERIAL_8E1 — Even
// SERIAL_8O1 — Odd

unsigned long lastPt100 = 0;
unsigned long lastDisplay = 0;
unsigned long lastLed = 0;

const unsigned long PT100_INTERVAL = 500;    // 500 мс
const unsigned long DISPLAY_INTERVAL = 1000; // 1 с
const unsigned long LED_INTERVAL = 200;      // 200 мс
int count = 0;

#define REGN 10 // 40011, потому что там часто используется нумерация 40001 + offset
#define REG_COUNT  11   // 40012

#define SLAVE_ID 1

ModbusRTU mb;
// Adafruit_NeoPixel led = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup()
{

  Serial1.begin(9600, SERIAL_8N1, PIN_RS485_RX, PIN_RS485_TX);
  Serial.begin(115200);
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  mb.begin(&Serial1);
  mb.slave(SLAVE_ID);
  mb.addHreg(REGN);
  mb.addHreg(REG_COUNT);
  mb.Hreg(REGN, 100); 
   mb.Hreg(REG_COUNT, 150); 
  delay(1000);
  Serial.println("ESP32-C3 started");
}

void loop()
{
  unsigned long now = millis();

  if (now - lastPt100 >= PT100_INTERVAL)
  {
    lastPt100 = now;
    ReadPt100();
  }
  if (now - lastDisplay >= DISPLAY_INTERVAL)
  {
    lastDisplay = now;
    UpdateDisplay();
  }

   mb.task();
   yield();

}

void ReadPt100()
{
  count = count + 1;
  Serial.printf("count = %d\n", count);
  mb.Hreg(REGN, count);
}

void UpdateDisplay()
{
  Serial.println("Update display");
}

void UpdateLed()
{
  Serial.println("Update LED");
}