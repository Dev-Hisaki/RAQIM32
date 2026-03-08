#include "wifi_manager.h"
#include <WiFi.h>

static char _ssid[WIFI_SSID_MAX_LEN] = "";
static char _password[WIFI_PASS_MAX_LEN] = "";

bool WiFiManager_Connect(const char* ssid, const char* password)
{
  if (ssid == NULL || strlen(ssid) == 0)
  {
    Serial.println("[WiFi] SSID tidak valid");
    return false;
  }

  WiFiManager_SetSSID(ssid);
  WiFiManager_SetPassword(password);

  Serial.printf("[WiFi] Connecting to %s", _ssid);

  WiFi.begin(_ssid, _password);

  int retry = 0;

  while (WiFi.status() != WL_CONNECTED && retry < WIFI_CONNECT_TIMEOUT)
  {
    delay(500);
    Serial.print(".");
    retry++;
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("[WiFi] Connected!");
    Serial.print("[WiFi] IP: ");
    Serial.println(WiFi.localIP());
    return true;
  }

  Serial.println("[WiFi] Connection failed");

  return false;
}

bool WiFiManager_Reconnect(void)
{
  Serial.println("[WiFi] Reconnecting...");

  WiFi.disconnect();

  WiFi.begin(_ssid, _password);

  int retry = 0;

  while (WiFi.status() != WL_CONNECTED && retry < WIFI_CONNECT_TIMEOUT)
  {
    delay(500);
    Serial.print(".");
    retry++;
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("[WiFi] Reconnected!");
    return true;
  }

  Serial.println("[WiFi] Reconnect failed");

  return false;
}

bool WiFiManager_IsConnected(void)
{
  return WiFi.status() == WL_CONNECTED;
}

void WiFiManager_Disconnect(void)
{
  WiFi.disconnect(true);
}

const char* WiFiManager_GetSSID(void)
{
  return _ssid;
}

const char* WiFiManager_GetPassword(void)
{
  return _password;
}

void WiFiManager_SetSSID(const char* newSsid)
{
  if (newSsid == NULL) return;

  strncpy(_ssid, newSsid, WIFI_SSID_MAX_LEN - 1);
}

void WiFiManager_SetPassword(const char* newPassword)
{
  if (newPassword == NULL) return;

  strncpy(_password, newPassword, WIFI_PASS_MAX_LEN - 1);
}