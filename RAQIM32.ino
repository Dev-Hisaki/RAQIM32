

#include "wifi_manager.h"
#include "firebase_manager.h"

// ─── Konfigurasi ─────────────────────────────────────────────
#define WIFI_SSID "NAMA_WIFI_KAMU"
#define WIFI_PASSWORD "PASSWORD_KAMU"

#define FIREBASE_PATH "/ruangan/lantai1"  // Path tujuan di Firebase
#define SEND_INTERVAL 10000               // Interval kirim data (10 detik)

// ─── Variabel Global ─────────────────────────────────────────
static unsigned long _lastSendTime = 0;

// ─── Forward Declarations ────────────────────────────────────
void handleSendData(void);
void handleGetData(void);
void handleDeleteData(void);
SensorData_t readSensors(void);

// ─── Setup ───────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  delay(1000);

  // 1. Koneksi WiFi
  if (!WiFiManager_Connect(WIFI_SSID, WIFI_PASSWORD)) {
    Serial.println("[Main] WiFi gagal — program berhenti.");
    while (true) { delay(1000); }  // Halt
  }

  // 2. Inisialisasi Firebase
  if (!FirebaseManager_Init()) {
    Serial.println("[Main] Firebase gagal — program berhenti.");
    while (true) { delay(1000); }  // Halt
  }

  Serial.println("[Main] Sistem siap!");
}

// ─── Loop ────────────────────────────────────────────────────
void loop() {
  // Cek koneksi WiFi, reconnect jika terputus
  if (!WiFiManager_IsConnected()) {
    Serial.println("[Main] WiFi terputus, mencoba reconnect...");
    WiFiManager_Connect(WiFiManager_GetSSID(), NULL);
    delay(5000);
    return;
  }

  // Kirim data setiap SEND_INTERVAL
  unsigned long now = millis();
  if (now - _lastSendTime >= SEND_INTERVAL) {
    _lastSendTime = now;
    handleSendData();
  }
}

// ─── Implementasi Handler ────────────────────────────────────

/**
 * @brief Baca data dari sensor lalu kirim ke Firebase.
 */
void handleSendData(void) {
  SensorData_t data = readSensors();

  if (FirebaseManager_SendData(FIREBASE_PATH, data)) {
    Serial.println("[Main] Data berhasil dikirim.");
  } else {
    Serial.println("[Main] Gagal mengirim data.");
  }
}

/**
 * @brief Ambil dan tampilkan data dari Firebase.
 */
void handleGetData(void) {
  SensorData_t data = FirebaseManager_GetData(FIREBASE_PATH);

  if (data.isValid) {
    Serial.println("[Main] Data diterima:");
    Serial.printf("  Suhu       : %.2f C\n", data.temperature);
    Serial.printf("  Kelembapan : %.2f %%\n", data.humidity);
    Serial.printf("  CO2        : %d ppm\n", data.co2);
  } else {
    Serial.println("[Main] Gagal membaca data.");
  }
}

/**
 * @brief Hapus data di path Firebase.
 */
void handleDeleteData(void) {
  if (FirebaseManager_DeleteData(FIREBASE_PATH)) {
    Serial.println("[Main] Data berhasil dihapus.");
  } else {
    Serial.println("[Main] Gagal menghapus data.");
  }
}

/**
 * @brief Simulasi pembacaan sensor.
 *        Ganti isi fungsi ini dengan pembacaan sensor asli.
 * @return SensorData_t berisi data sensor.
 */
SensorData_t readSensors(void) {
  SensorData_t data;
  data.temperature = 27.5f;  // TODO: ganti dengan baca sensor DHT/SHT
  data.humidity = 80.0f;     // TODO: ganti dengan baca sensor DHT/SHT
  data.co2 = 412;            // TODO: ganti dengan baca sensor MQ-135/SCD40
  data.isValid = true;
  return data;
}
