#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>

// ─── Constants ───────────────────────────────────────────────
#define WIFI_SSID_MAX_LEN 32
#define WIFI_PASS_MAX_LEN 64
#define WIFI_CONNECT_TIMEOUT 20  // jumlah retries (× 500ms = 10 detik)

// ─── Public API ──────────────────────────────────────────────

/**
 * @brief Inisialisasi dan sambungkan ke jaringan WiFi.
 * @param ssid     Nama jaringan WiFi (maks. 31 karakter).
 * @param password Password WiFi (maks. 63 karakter).
 * @return true jika berhasil terhubung, false jika timeout.
 */
bool WiFiManager_Connect(const char* ssid, const char* password);

/**
 * @brief Cek apakah saat ini terhubung ke WiFi.
 * @return true jika terhubung.
 */
bool WiFiManager_IsConnected(void);

/**
 * @brief Putuskan koneksi WiFi.
 */
void WiFiManager_Disconnect(void);

/**
 * @brief Kembalikan SSID yang sedang aktif/tersimpan.
 * @return Pointer ke string SSID (read-only).
 */
const char* WiFiManager_GetSSID(void);

/**
 * @brief Update SSID yang tersimpan.
 * @param newSsid String SSID baru.
 */
void WiFiManager_SetSSID(const char* newSsid);

/**
 * @brief Update password yang tersimpan.
 * @param newPassword String password baru.
 */
void WiFiManager_SetPassword(const char* newPassword);

#endif  // WIFI_MANAGER_H
