#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
//#include <FS.h>

ESP8266WebServer server(80);

#define LED 2

long Previous = 0;

char x [50];

String ReadStr;

byte CmdTime[] =  {0xC0, 0x48, 0x69, 0xD5, 0xFD, 0x00, 0x31, 0xDE, 0x0B, 0x00, 0xD0, 0x01, 0x20, 0x9B, 0xC0};//запрос времени
byte CmdEtope[] = {0xC0, 0x48, 0x69, 0xD5, 0xFD, 0x00, 0x31, 0xDE, 0x0B, 0x00, 0xD2, 0x01, 0x30, 0x00, 0x00, 0x1F, 0xC0};//запрос показаний
//byte CmdVolt[] =  {0xC0, 0x48, 0x69, 0xD5, 0xFD, 0x00, 0x31, 0xDE, 0x0B, 0x00, 0xD0, 0x01, 0x60, 0x2b, 0xC0};//запрос текущего потребления
//byte CmdVolt[] =  {0xC0, 0x48, 0x69, 0xD5, 0xFD, 0x00, 0x31, 0xDE, 0x0B, 0x00, 0xD0, 0x01, 0x32, 0x68, 0xC0};//запрос текущего потребления
/*END (0xС0) – флаг, обозначающий начало и конец пакета. Если в пакете встречается байт с
кодом, идентичным END, то такой байт замещается на последовательность из 2 байтов: 0xDB,
0xDC. Специальный символ 0xDB называется ESC-символом. Если в пакете встречается байт с
кодом ESC-символа, он замещается двухбайтовой последовательностью 0xDB, 0xDD*/

#define DIR D6
SoftwareSerial UART(D8, D7); // RX, TX

unsigned long ms;
int lastms = 0;

String Time;
String  Etope = "";
String  SSS = "";
//long  Etope;

File file;

void setup()
{
  Serial.begin(115200);
  //SPIFFS.begin();
  //file = SPIFFS.open("/base", "w+");

  WiFi.mode(WIFI_STA);
  WiFi.begin("A", "1234554321");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  ArduinoOTA.setHostname("esp_energo");
  ArduinoOTA.begin();
  Serial.println("IP address: " + WiFi.localIP());
  startwww();
  UART.begin(9600);
  pinMode(DIR, OUTPUT);
  digitalWrite(DIR, HIGH);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
  delay(200);
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
  delay(200);
  digitalWrite(LED, HIGH);
}

void loop()
{
  ArduinoOTA.handle();
  ms = millis();
  if (ms < 500)
    lastms = 0;
  if (floor(ms / 5000) > lastms) {
    lastms = floor(ms / 5000 );
    EmergomeraWrite(lastms % 2);
    //Serial.println(strtol("AA10", NULL, 16));
  }
  EnergomeraCycle();//получение данных счетчика
  server.handleClient();
}
