/*
 * RAQIM32 — ESP32 Environmental Monitor
 * =======================================
 * To Do List:
 * 1. [x] WiFi connect/disconnect
 * 2. [ ] Configure Read/Write authority
 * 3. [ ] CRUD WiFi credentials
 * 4. [ ] Kirim data CO2, kelembapan, dan suhu ke Firebase RTDB
 * 5. [ ] Interval pengiriman data yang dapat diatur oleh admin
 * 6. [ ] Error handling (Buzzer / LED / LCD)
 * 7. [ ] Ambil data dari Firebase ke webapp
 * 8. [ ] Tampilkan di dashboard (webapp)
 * =======================================
 * Ringkasan Pola Penambahan Fitur
 * Untuk setiap fitur baru (contoh: Firebase):
 *
 * firebase_manager.h   ← Langkah 1: tulis deklarasi
 * firebase_manager.cpp ← Langkah 2: buat file
 *                      ← Langkah 3: #include "firebase_manager.h"
 *                      ← Langkah 5: tulis logika
 * RAQIM32.ino          ← Langkah 4: #include "firebase_manager.h"
 *                      ← Langkah 6: panggil fungsinya
 * =======================================
 */

#include "wifi_manager.h"

// ─── Konfigurasi ─────────────────────────────────────────────
#define WIFI_SSID "NAMA_WIFI_KAMU"
#define WIFI_PASSWORD "PASSWORD_KAMU"

// ─── Setup ───────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFiManager_Connect(WIFI_SSID, WIFI_PASSWORD);
}

// ─── Loop ────────────────────────────────────────────────────
void loop() {
  if (!WiFiManager_IsConnected()) {
    Serial.println("[Main] WiFi terputus, mencoba reconnect...");
    WiFiManager_Connect(WiFiManager_GetSSID(), NULL);
    delay(5000);
    return;
  }

  // TODO: Logika kirim data ke Firebase
}
