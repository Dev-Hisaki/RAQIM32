#include "wifi_manager.h"
#include "sensor_manager.h"
#include "firebase_manager.h"

#define WIFI_SSID "YNSama_4G"
#define WIFI_PASSWORD "Diki290603"

#define FIREBASE_PATH "/ruangan/lantai1"

#define SEND_INTERVAL 10000

unsigned long lastSend = 0;

void setup()
{
  Serial.begin(115200);

  WiFiManager_Connect(WIFI_SSID, WIFI_PASSWORD);

  SensorManager_Init();

  FirebaseManager_Init();
}

void loop()
{
  if (!WiFiManager_IsConnected())
  {
    WiFiManager_Reconnect();
  }

  if (millis() - lastSend > SEND_INTERVAL)
  {
    lastSend = millis();

    SensorData_t data = SensorManager_ReadAll();

    if (data.isValid)
    {
      FirebaseManager_SendData(FIREBASE_PATH, data);

      Serial.println("Data sent to Firebase");
    }
    else
    {
      Serial.println("Sensor error");
    }
  }
}