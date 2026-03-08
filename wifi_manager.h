#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>

#define WIFI_SSID_MAX_LEN 32
#define WIFI_PASS_MAX_LEN 64
#define WIFI_CONNECT_TIMEOUT 20

bool WiFiManager_Connect(const char* ssid, const char* password);

bool WiFiManager_Reconnect(void);

bool WiFiManager_IsConnected(void);

void WiFiManager_Disconnect(void);

const char* WiFiManager_GetSSID(void);

const char* WiFiManager_GetPassword(void);

void WiFiManager_SetSSID(const char* newSsid);

void WiFiManager_SetPassword(const char* newPassword);

#endif