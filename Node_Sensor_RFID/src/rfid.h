#include <MFRC522.h>
#include <SPI.h>

// Constants
#define SS_PIN 5//2
#define RST_PIN 21//15
// Parameters
const int ipaddress[4] = {103, 97, 67, 25};
// Variables
byte nuidPICC[4] = {0, 0, 0, 0};
MFRC522::MIFARE_Key key;
MFRC522 rfid = MFRC522(SS_PIN, RST_PIN);

char buff[20] = {0};

unsigned long uidDec, temp;

// string id of tag, check id tag
#define Hoang 1690581329
#define Huy 3292349009
#define Thanh 2765897297
#define anomynous 3810707460
#define Huu 3047175377
/**
    Helper routine to dump a byte array as hex values to Serial.
*/
void printHex(byte *buffer, byte bufferSize)
{
    for (byte i = 0; i < bufferSize; i++)
    {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}
/**
    Helper routine to dump a byte array as dec values to Serial.
*/
void printDec(byte *buffer, byte bufferSize)
{
    uidDec = 0;
    for (byte i = 0; i < bufferSize; i++)
    {
        // buff[i] = (buffer[i] < 0x10) ? '0' : 'a';
        //  Serial.print(buff[i]);
        //  buff[i] = buffer[i], DEC;
        //  Serial.print(buff[i]);
        // Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        // Serial.print(buffer[i], HEX);
        // content.concat(String(buffer[i] < 0x10 ? " 0" : " "));
        // content.concat(String(buffer[i], HEX));
        temp = buffer[i];
        uidDec = uidDec*256+temp;
    }
    Serial.println(uidDec);
}

void readRFID(void)
{ /* function readRFID */
    ////Read RFID card
    for (byte i = 0; i < 6; i++)
    {
        key.keyByte[i] = 0xFF;
    }
    // Look for new 1 cards
    if (!rfid.PICC_IsNewCardPresent())
        return;
    // Verify if the NUID has been readed
    if (!rfid.PICC_ReadCardSerial())
        return;
    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++)
    {
        nuidPICC[i] = rfid.uid.uidByte[i];
    }
    Serial.print(F("RFID In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    // if (uidDec == Hoang|Huu|anomynous)
    // {
    //     // open door
    //     // digitalWrite(relay, HIGH);
    //     Serial.println("Relative!!");
    // }
    Serial.println();
    // Halt PICC
    rfid.PICC_HaltA();
    // Stop encryption on PCD
    rfid.PCD_StopCrypto1();
}
