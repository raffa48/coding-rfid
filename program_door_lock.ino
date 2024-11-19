#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 5 // ESP32 pin GPIO5
#define RST_PIN 27 // ESP32 pin GPIO27
#define RELAY_PIN 32 // ESP32 pin GPIO32 controls the solenoid lock via therelay
MFRC522 rfid(SS_PIN, RST_PIN);
byte authorizedUID[4] = {0xFF, 0xFF, 0xFF, 0xFF};
void setup() {
Proyek TAV 2024 – Raffa Ibnu Bahri – NIS. 2324.10.348– Kelas XI TAV 2
 Serial.begin(9600);
 SPI.begin(); // init SPI bus
 rfid.PCD_Init(); // init MFRC522
 pinMode(RELAY_PIN, OUTPUT); // initialize pin as an output.
 digitalWrite(RELAY_PIN, LOW); // deactivate the solenoid lock => locked
 Serial.println("Tap RFID Tag on reader");
}
void loop() {
 if (rfid.PICC_IsNewCardPresent()) { // new tag is available
 if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
 MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
 if (rfid.uid.uidByte[0] == authorizedUID[0] &&
 rfid.uid.uidByte[1] == authorizedUID[1] &&
 rfid.uid.uidByte[2] == authorizedUID[2] &&
 rfid.uid.uidByte[3] == authorizedUID[3] ) {
 Serial.println("Authorized Tag");
 digitalWrite(RELAY_PIN, LOW); // deactivate the solenoid lock => unlocked
 delay(2000);
 digitalWrite(RELAY_PIN, HIGH); // activate the solenoid lock => locked
 }else{
 Serial.print("Unauthorized Tag:");
 for (int i = 0; i < rfid.uid.size; i++) {
 Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
 Serial.print(rfid.uid.uidByte[i], HEX);}
 Serial.println();}
 rfid.PICC_HaltA(); // halt PICC
 rfid.PCD_StopCrypto1(); // stop encryption on PCD}}}
