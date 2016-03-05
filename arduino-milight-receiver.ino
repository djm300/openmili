#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <printf.h>

#include "PL1167_nRF24.h"
#include "MiLightRadio.h"

#define CE_PIN 8
#define CSN_PIN 10

// create nrf object
RF24 nrf24(CE_PIN, CSN_PIN);
// create pl1167 abstract object
PL1167_nRF24 prf(nrf24);
// create MiLight Object
MiLightRadio mlr(prf);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("# MiLight receiver / sniffer");
  printf_begin();
  // setup mlr (wireless settings)
  mlr.begin();
}

static int dupesPrinted = 0;

void loop() {

    if (mlr.available()) {
      Serial.print("\n\r");
      uint8_t packet[7];
      size_t packet_length = sizeof(packet);
      mlr.read(packet, packet_length);

      for (int i = 0; i < packet_length; i++) {
        printf("%02X ", packet[i]);
      }
    }
    
    int dupesReceived = mlr.dupesReceived();
    for (; dupesPrinted < dupesReceived; dupesPrinted++) {
      Serial.print(".");
    }

}
