String deviceName = "PanIoT-relay";
String deviceLocation = "noveZarizeni";

#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
ESP8266WebServer server(80);

// senzors
#include "utility.h"
#include "beep.h"
#include "led.h"
#include "wifiManagerSetup.h"
#include "pir.h"
#include "ntp.h"
#include "elasticsearch.h"
#include "dht22.h"
#include "rellay.h"

// always on the end
#include "config.h"
#include "ota.h"
#include "webServer.h"


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  pinMode(rellayPin, OUTPUT);
  wifiManagerInit();
  webServerInit();
  fsInit();
  initOTA();
  loadConfig();


  // ntp
  if(WiFi.status() == WL_CONNECTED) {
    NTP.begin("pool.ntp.org", 1, true);
    NTP.setInterval(63);
  }

  NTP.onNTPSyncEvent([](NTPSyncEvent_t event) {
    ntpEvent = event;
    syncEventTriggered = true;
  });  

  stateRellay = true;
  handleRellay();
  delay(2000);
  stateRellay = false;
  handleRellay();
  // vse nastaveno, startuje se
  Serial.println("-- start --");
}

void loop() {
  server.handleClient();
  ArduinoOTA.handle();
  syncNtp();
  handleRellay();
}

