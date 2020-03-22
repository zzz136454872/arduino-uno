/* @author f4prime
 * @email zzz136454872@163.com
 */

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 card(SS_PIN, RST_PIN);   // Create MFRC522 instance.

const byte block=1;
byte buffer[18];
byte waarde[64][16];

const byte KEYA=1;
const byte KEYB=2;

MFRC522::StatusCode status;
    
MFRC522::MIFARE_Key key;

byte knownKeys[8][MFRC522::MF_KEY_SIZE] =  {
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // FF FF FF FF FF FF = factory default
    {0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5}, // A0 A1 A2 A3 A4 A5
    {0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5}, // B0 B1 B2 B3 B4 B5
    {0x4d, 0x3a, 0x99, 0xc3, 0x51, 0xdd}, // 4D 3A 99 C3 51 DD
    {0x1a, 0x98, 0x2c, 0x7e, 0x45, 0x9a}, // 1A 98 2C 7E 45 9A
    {0xd3, 0xf7, 0xd3, 0xf7, 0xd3, 0xf7}, // D3 F7 D3 F7 D3 F7
    {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff}, // AA BB CC DD EE FF
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}  // 00 00 00 00 00 00
};

void printmem(const void * const start, const int len, const char* info) 
{
    unsigned char *ptr = (unsigned char*)start;
    int i;
    Serial.print(info);
    for(i=0;i<len;i++)
    {
        if(i%16==0)
            Serial.write('\n');
        if(ptr[i] < 0xf)
            Serial.print(0);
        Serial.print(ptr[i],HEX);
        Serial.write(' ');
    }
    Serial.write('\n');
}

void setup() {
    Serial.begin(9600);
    Serial.println("start");
    SPI.begin();
    card.PCD_Init();         // Init MFRC522 card
    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }
}

bool tryKey(MFRC522::MIFARE_Key *key,byte block,byte chosenKey)
{
    bool result=false;
    Serial.println("Authenticating using key A...");
    status = card.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, key, &(card.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(card.GetStatusCodeName(status));
        return false;
    }
    // Read block
    byte byteCount = sizeof(buffer);
    status = card.MIFARE_Read(block, buffer, &byteCount);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Read() failed: "));
        Serial.println(card.GetStatusCodeName(status));
    }
    else {
        // Successful read
        result = true;
        printmem((*key).keyByte, MFRC522::MF_KEY_SIZE, "right key");
        // Dump block data
        printmem(buffer, 16,"block data");
        Serial.println();
    }
    return result;
}

void loop() {
    delay(200);
    if ( ! card.PICC_IsNewCardPresent())
        return;
    if ( ! card.PICC_ReadCardSerial())
        return;
    printmem(card.uid.uidByte,card.uid.size,"card uid");

    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0x01;
    }
    tryKey(&key,block,KEYA);
    card.PCD_Init();         // Init MFRC522 card

    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0x05;
    }
    card.PCD_Init();         // Init MFRC522 card
    tryKey(&key,block,KEYA);

    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }
    tryKey(&key,block,KEYB);
    card.PCD_Init();         // Init MFRC522 card

    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xab;
    }
    tryKey(&key,block,KEYB);
    card.PCD_Init();         // Init MFRC522 card
    
    card.PICC_HaltA();       // Halt PICC
    card.PCD_StopCrypto1();  // Stop encryption on PCD
}
