#ifndef NRZ_ENCODING_H
#define NRZ_ENCODING_H

#include <Arduino.h>

void encodeNRZI(byte* data, int length);
void encodeNRZL(byte* data, int length);
void decodeNRZI(byte* data, int length);
void decodeNRZL(byte* data, int length);

#endif // NRZ_ENCODING_H



