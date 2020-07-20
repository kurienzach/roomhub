#ifndef IR_TRANS
#define IR_TRANS

#include <IRremoteESP8266.h>
#include <IRsend.h>

void setupIR();

void sendIR(const uint16_t buf[]);

#endif