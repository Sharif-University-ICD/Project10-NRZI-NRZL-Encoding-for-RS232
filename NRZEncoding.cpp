#include "NRZEncoding.h"

void encodeNRZI(byte* data, int length) {
  static bool lastBit = LOW;
  for (int i = 0; i < length; i++) {
    byte encodedByte = 0;
    for (int bit = 7; bit >= 0; bit--) {
      bool bitVal = (data[i] >> bit) & 0x01;
      lastBit = bitVal ? !lastBit : lastBit; // Toggle only on 1s
      encodedByte |= (lastBit << bit);
    }
    data[i] = encodedByte; // Store encoded value
  }
}

void encodeNRZL(byte* data, int length) {
  for (int i = 0; i < length; i++) {
    byte encodedByte = 0;
    for (int bit = 7; bit >= 0; bit--) {
      bool bitVal = (data[i] >> bit) & 0x01;
      bitVal = !bitVal; // Invert bits
      encodedByte |= (bitVal << bit); // Directly map 0 -> LOW, 1 -> HIGH
    }
    data[i] = encodedByte; // Store encoded value
  }
}

void decodeNRZI(byte* data, int length) {
  static bool lastBit = LOW;
  for (int i = 0; i < length; i++) {
    byte decodedByte = 0;
    for (int bit = 7; bit >= 0; bit--) {
      bool bitVal = (data[i] >> bit) & 0x01;
      bool originalBit = (bitVal == lastBit) ? 0 : 1; // If no change, it was 0; if toggled, it was 1
      lastBit = bitVal; // Update last bit
      decodedByte |= (originalBit << bit);
    }

    data[i] = decodedByte; // Store decoded value
  }
}

void decodeNRZL(byte* data, int length) {
  for (int i = 0; i < length; i++) {
    data[i] = ~data[i]; // Simply invert the bits back
  }
}

