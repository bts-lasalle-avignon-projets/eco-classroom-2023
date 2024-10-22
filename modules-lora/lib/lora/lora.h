#ifndef LORA_H
#define LORA_H

#include "Arduino.h"
#include "LoRa_E32.h"

// #define DEBUG_LORA

extern LoRa_E32 loraE32;

bool initialiserLora();
void configurer(
  byte               ADDL             = 0x00,
  byte               ADDH             = 0x00,
  byte               channel          = 0x06,
  FIDEX_TRANSMISSION typeTransmission = FT_TRANSPARENT_TRANSMISSION,
  bool               maintien         = true);
void   selectionnerMode(MODE_TYPE mode = MODE_0_NORMAL);
int    traiterMessage();
bool   envoyerMessage(String message);
bool   envoyerMessage(byte ADDH, byte ADDL, byte CHANNEL, String message);
void   afficherParametres();
void   afficherParametres(struct Configuration configuration);
String extraireMessage(String& message, char delimiteur, unsigned int numero);
String getMessage(String message, char separateur, int index);
int    count(const String& str, const String& sub);

#endif
