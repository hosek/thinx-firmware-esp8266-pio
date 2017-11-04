#include "Arduino.h"
#include <THiNXLib.h>


THiNX thx;

/* Called after library gets connected and registered */
void finalizeCallback () {
  Serial.println("*INO: Finalize callback called.");
  ESP.deepSleep(3e9);
}

/* Example of using Environment variables */
void pushConfigCallback (String config) {
  
    // Convert incoming JSON string to Object
    DynamicJsonBuffer jsonBuffer(512);
    JsonObject& root = jsonBuffer.parseObject(config.c_str());
    JsonObject& configuration = root["configuration"];
  
    if ( !configuration.success() ) {
      Serial.println(F("Failed parsing configuration."));
    } else {
  
      // Parse and apply your Environment vars
      const char *ssid = configuration["THINX_ENV_SSID"];
      const char *pass = configuration["THINX_ENV_PASS"];
  
      // password may be empty string
      if ((strlen(ssid) > 2) && (strlen(pass) > 0)) {
        WiFi.disconnect();
        WiFi.begin(ssid, pass);
        long timeout = millis() + 20000;
        Serial.println("Attempting WiFi migration...");
        while (WiFi.status() != WL_CONNECTED) {
          yield();
          if (millis() > timeout) break;
        }
        if (WiFi.status() != WL_CONNECTED) {
          Serial.println("WiFi migration failed."); // TODO: Notify using publish() to device status channel
        } else {
          Serial.println("WiFi migration successful."); // TODO: Notify using publish() to device status channel
        }
      }
    }
  }

void setup() {

  Serial.begin(115200);
  // Sets location of the device (optional)
  thx.setLocation(49.19522,16.60796);

   // Enter API Key and Owner ID
  thx = THiNX();
  thx.setFinalizeCallback(finalizeCallback);
  thx.setPushConfigCallback(pushConfigCallback);
}

/* Loop must call the thx.loop() in order to pickup MQTT messages and advance the state machine. */
void loop()
{
  thx.loop();
}
