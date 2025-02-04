#include "NRZEncoding.h"

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial3.begin(9600);
  randomSeed(analogRead(A0));
}

static bool useNRZI = true;

void loop()
{
  static unsigned long lastSend = 0;
  static bool turn = false;

  if (millis() - lastSend >= 10000)
  {
    lastSend = millis();
    byte data = random(256);

    Serial.print("Original: ");
    Serial.println(data, BIN);

    if (useNRZI)
    {
      encodeNRZI(&data, 1);
      Serial.print("NRZI Encoded: ");
    }
    else
    {
      encodeNRZL(&data, 1);
      Serial.print("NRZL Encoded: ");
    }
    Serial.println(data, BIN);

    if (!turn)
    {
      Serial1.write(data);
      Serial.print("Sent from 1: ");
    }
    else
    {
      Serial3.write(data);
      Serial.print("Sent from 3: ");
    }
    Serial.println(data, BIN);
    turn = !turn;
  }
}

void serialEvent1()
{

  byte receivedData = Serial1.read();
  Serial.print("Received on Serial1 (Encoded): ");
  Serial.println(receivedData, BIN);

  byte decodedData = receivedData;
  if (useNRZI)
  {
    decodeNRZI(&decodedData, 1);
    Serial.print("Decoded (NRZI): ");
  }
  else
  {
    decodeNRZL(&decodedData, 1);
    Serial.print("Decoded (NRZL): ");
  }
  Serial.println(decodedData, BIN);
}

void serialEvent3()
{

  byte receivedData = Serial3.read();
  Serial.print("Received on Serial3 (Encoded): ");
  Serial.println(receivedData, BIN);

  byte decodedData = receivedData;
  if (useNRZI)
  {
    decodeNRZI(&decodedData, 1);
    Serial.print("Decoded (NRZI): ");
  }
  else
  {
    decodeNRZL(&decodedData, 1);
    Serial.print("Decoded (NRZL): ");
  }
  Serial.println(decodedData, BIN);
}