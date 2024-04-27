//#define DEBUG
//#define EXPORTVIEW

#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "MAX11300.h"
#include "MAX11300registers.h"
#include <DueTimer.h>

//##############################################"DEFINE"#############################################
//sorties analogiques
#define out1 13
#define out2 11
#define out3 9
#define out4 7
#define out5 5
#define out6 3
#define out7 1

//function to call max113000 before we inclued it's configuration (for configuration)
bool MAX11300regWrite(int regAddress8, int regData16) {
  uint16_t test = (uint16_t)regData16;
  return m_pMax11300->writeRegister(regAddress8, test);
}

uint16_t MAX11300regRead(uint8_t regAddress8) {
  return m_pMax11300->readRegister(regAddress8);
}

void MAX11300initDelayus(int delay_us) {
  delayMicroseconds(delay_us);
}

#include "MAX11300Hex.h"  //max11300 configuration files (editable by it's softaware)

void setup() {
  Ethernet.init(11);  //chip select
  Serial.begin(9600);
#ifdef DEBUG
  while (!Serial) {
    delay(10);
  }
#endif
  //##############################################"INIT MAX11300"#############################################
  m_pMax11300 = new MAX11300(&SPI, 11, 10);
  m_pMax11300->begin();

  uint16_t result = m_pMax11300->readRegister(MAX_DEVICE_ID);

  Serial.print("Device id : ");
  Serial.println(result, HEX);

  MAX11300init();
}

void loop() {
  //###############################################"data sending to PA"##############################################
  m_pMax11300->writeAnalogPin(out1, '1');
}