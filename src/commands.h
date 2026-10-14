#pragma once

#include <Arduino.h>

#define SerialBufferSize 32

struct IntCommandOut {
  bool success;
  int value;
};

extern char commandReadBuffer[SerialBufferSize];

extern int commandReadBufferIndex;

void processCommands();

void readSerial();

bool checkCommand(String commandName, unsigned int length, String cmd);

IntCommandOut checkIntCommand(String commandName, unsigned int length, String cmd);
