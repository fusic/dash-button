#include <M5Stack.h>
#include "net_config.h"

#define COUNT_OF(array) (sizeof(array) / sizeof(array[0]))
#define MAX_OF(array) (COUNT_OF(array) - 1)

char* menu[] = {
  "インスタントコーヒー",
  "マドラー",
  "紙コップ",
  "箱ティッシュ",
  "ウェットティッシュ",
  "ペーパータオル"
};

uint8_t selected = 0;

void printMenu()
{
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.setTextColor(GREEN);

  M5.Lcd.println("消耗品の減少を");
  M5.Lcd.println("BOに通知します");
  M5.Lcd.println("");

  for(uint8_t i = 0; i < COUNT_OF(menu); i++)
  {
    M5.Lcd.setTextColor((i == selected) ? WHITE : BLACK);
    M5.Lcd.print("> ");
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.println(menu[i]);
  }
}

void notify()
{
  WiFiClient client;
  uint8_t buffer[256] = {0};
  size_t bytesToRead = 0;

  if(!client.connected()) {
    Serial.println("Connecting...");
    if(!client.connect("unified.soracom.io", 23080)) {
      Serial.println("Failed to connect...");
      return;
    }
  }

  Serial.println("Sending...");
  client.write((char*)&selected, sizeof(selected));
  Serial.println("Sended.");

  while((bytesToRead = client.available()) > 0) {
    bytesToRead = bytesToRead > sizeof(buffer) ? sizeof(buffer) : bytesToRead;
    auto bytesRead = client.readBytes(buffer, bytesToRead); 
    Serial.write(buffer, bytesRead);
  }
}

void printThanks()
{
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.setTextColor(GREEN);

  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.print(menu[selected]);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println("の");
  M5.Lcd.println("減少を通知しました");
  M5.Lcd.println("");
  M5.Lcd.println("ありがとうございます");
}

void setup()
{
  Params* params = 0;

  M5.begin();
  Serial.println("M5Stack started.");

  params = restoreParams();
  setupWifi(params);
  setupArc(params);
  backupParams(params);
  delay(1000);

  String f24 = "genshin-regular-24pt";
  M5.Lcd.loadFont(f24, SD);
  M5.Lcd.setRotation(2);

  M5.Lcd.fillScreen(BLACK);
  printMenu();
}

void loop()
{
  M5.update();

  if (M5.BtnA.wasPressed()) {
    selected = (selected == MAX_OF(menu)) ? 0 : selected + 1;
    printMenu();
  }
  if (M5.BtnB.wasPressed()) {
    M5.Lcd.fillScreen(BLACK);
    notify();
    printThanks();
    delay(3000);
    M5.Lcd.fillScreen(BLACK);
    printMenu();
  }
  if (M5.BtnC.wasPressed()) {
    selected = (selected == 0) ? MAX_OF(menu) : selected - 1;
    printMenu();
  }
  delay(10);
}
