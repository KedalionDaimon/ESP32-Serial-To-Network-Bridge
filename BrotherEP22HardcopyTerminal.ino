#define SRL Serial
#include <WiFi.h>
const char* ssid = "BrotherEP22";
const char* password = "HardcopyTerminal";
WiFiServer wifiServer(8088);
WiFiClient client = wifiServer.available();
unsigned char ch;
void setup() {
  SRL.begin(300, SERIAL_8N1);
  WiFi.softAP(ssid, password); delay(500);
  SRL.print("    WiFi");
  wifiServer.begin();
  SRL.print(" Net:BrotherEP22 Password:HardcopyTerminal");
  SRL.print(" IP:"); SRL.print(WiFi.softAPIP()); SRL.println(" Port:8088");
    for (;;) {
    client = wifiServer.available();
    if (client) {
        while (client.connected()) {
        if (client.available()) {
          ch = client.read();
          if ((ch != '\r') && (ch != '\n')) {
            SRL.write((unsigned char) ch);
            delay(125);
          } else if (ch == '\n') { // i.e. ignore CR and turn LF into CRLF
            SRL.write((unsigned char) '\r'); SRL.write((unsigned char) '\n');
            delay(750);
          }
          Serial.flush();
        }
        if (Serial.available()) {
          ch = SRL.read();
          client.write((unsigned char) ch);
        }
}}}}
void loop() {}
