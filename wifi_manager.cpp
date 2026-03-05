#include "wifi_manager.h"
#include <WiFi.h>

// ─── Private State ────────────────────────────────────────────
static char _ssid[WIFI_SSID_MAX_LEN] = "NAMA_WIFI_KAMU";
static char _password[WIFI_PASS_MAX_LEN] = "PASSWORD_KAMU";

// ─── Private Helpers ─────────────────────────────────────────
static bool _isValidSSID(const char* ssid) {
  return (ssid != NULL && strlen(ssid) > 0);
}

// ─── Public Implementations ──────────────────────────────────
bool WiFiManager_Connect(const char* ssid, const char* password) {
  if (!_isValidSSID(ssid)) {
    Serial.println("[WiFi] Error: SSID kosong!");
    return false;
  }

  // Simpan kredensial ke state internal
  WiFiManager_SetSSID(ssid);
  WiFiManager_SetPassword(password);

  Serial.printf("[WiFi] Menghubungkan ke \"%s\"", _ssid);
  WiFi.begin(_ssid, _password);

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < WIFI_CONNECT_TIMEOUT) {
    delay(500);
    Serial.print(".");
    retries++;
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("[WiFi] Terhubung!");
    Serial.printf("[WiFi] IP Address: %s\n", WiFi.localIP().toString().c_str());
    return true;
  }

  Serial.println("[WiFi] Gagal terhubung (timeout).");
  return false;
}

bool WiFiManager_IsConnected(void) {
  return (WiFi.status() == WL_CONNECTED);
}

void WiFiManager_Disconnect(void) {
  WiFi.disconnect(true);
  Serial.println("[WiFi] Koneksi diputus.");
}

const char* WiFiManager_GetSSID(void) {
  return (const char*)_ssid;
}

void WiFiManager_SetSSID(const char* newSsid) {
  if (newSsid == NULL) return;
  strncpy(_ssid, newSsid, WIFI_SSID_MAX_LEN - 1);
  _ssid[WIFI_SSID_MAX_LEN - 1] = '\0';
}

void WiFiManager_SetPassword(const char* newPassword) {
  if (newPassword == NULL) return;
  strncpy(_password, newPassword, WIFI_PASS_MAX_LEN - 1);
  _password[WIFI_PASS_MAX_LEN - 1] = '\0';
}
