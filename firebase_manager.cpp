#include "firebase_manager.h"
#include <Firebase_ESP_Client.h>

static FirebaseData fbdo;
static FirebaseAuth auth;
static FirebaseConfig config;

bool FirebaseManager_Init(void)
{
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&config, &auth);

  Firebase.reconnectWiFi(true);

  Serial.println("[Firebase] Initialized");

  return true;
}

bool FirebaseManager_SendData(const char* path, SensorData_t data)
{
  FirebaseJson json;

  json.set("temperature", data.temperature);
  json.set("humidity", data.humidity);
  json.set("co2", data.co2);
  json.set("timestamp", millis());

  if (Firebase.RTDB.setJSON(&fbdo, path, &json))
  {
    Serial.println("[Firebase] Data sent");

    return true;
  }

  Serial.println(fbdo.errorReason());

  return false;
}