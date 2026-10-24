#pragma once

#define PIN_SPI_SCK      4
#define PIN_SPI_MISO     5
#define PIN_SPI_MOSI     6
#define PIN_MAX31865_CS  7

#define PIN_I2C_SDA      8
#define PIN_I2C_SCL      9

#define PIN_RS485_RX     0
#define PIN_RS485_TX     21
#define PIN_RS485_DE     3

void ReadPt100(); 
void UpdateDisplay();
void UpdateLed(); 

// Свободные:
// GPIO0
// GPIO1
// GPIO2
// GPIO10
// GPIO3