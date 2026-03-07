#include "firebase_manager.h"
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>  // Helper untuk generate token autentikasi
#include <addons/RTDBHelper.h>   // Helper untuk operasi RTDB

// ─── Private State ────────────────────────────────────────────
static FirebaseData _fbdo;      // Objek untuk operasi RTDB
static FirebaseAuth _auth;      // Objek autentikasi
static FirebaseConfig _config;  // Objek konfigurasi

// ─── Private Helpers ─────────────────────────────────────────

/**
 * @brief Cek apakah path valid (tidak NULL dan tidak kosong).
 */
static bool _isValidPath(const char* path) {
  return (path != NULL && strlen(path) > 0);
}

/**
 * @brief Cetak pesan error Firebase ke Serial.
 */
static void _printError(const char* operation) {
  Serial.printf("[Firebase] %s gagal: %s\n", operation, _fbdo.errorReason().c_str());
}

// ─── Public Implementations ──────────────────────────────────

bool FirebaseManager_Init(void) {
  Serial.println("[Firebase] Menginisialisasi...");

  // Setup konfigurasi
  _config.host = FIREBASE_HOST;
  _config.api_key = FIREBASE_API_KEY;
  _config.token_status_callback = tokenStatusCallback;  // dari TokenHelper.h

  // Setup autentikasi email & password
  _auth.user.email = FIREBASE_EMAIL;
  _auth.user.password = FIREBASE_PASSWORD;

  // Mulai koneksi Firebase (SSL ditangani library secara internal)
  Firebase.begin(&_config, &_auth);
  Firebase.reconnectWiFi(true);

  // Tunggu token autentikasi siap (maks. 10 detik)
  int timeout = 0;
  Serial.print("[Firebase] Menunggu autentikasi");
  while (!Firebase.ready() && timeout < 20) {
    delay(500);
    Serial.print(".");
    timeout++;
  }
  Serial.println();

  if (Firebase.ready()) {
    Serial.println("[Firebase] Siap!");
    return true;
  }

  Serial.println("[Firebase] Inisialisasi gagal.");
  return false;
}

bool FirebaseManager_IsReady(void) {
  return Firebase.ready();
}

bool FirebaseManager_SendData(const char* path, SensorData_t data) {
  if (!_isValidPath(path)) {
    Serial.println("[Firebase] Error: Path kosong!");
    return false;
  }

  if (!FirebaseManager_IsReady()) {
    Serial.println("[Firebase] Error: Firebase belum siap!");
    return false;
  }

  // Gunakan FirebaseJson untuk mengirim semua field sekaligus
  FirebaseJson json;
  json.set("temperature", data.temperature);
  json.set("humidity", data.humidity);
  json.set("co2", data.co2);

  if (Firebase.RTDB.setJSON(&_fbdo, path, &json)) {
    Serial.printf("[Firebase] Data berhasil dikirim ke: %s\n", path);
    return true;
  }

  _printError("SendData");
  return false;
}

SensorData_t FirebaseManager_GetData(const char* path) {
  SensorData_t data = { 0.0f, 0.0f, 0, false };  // Default: isValid = false

  if (!_isValidPath(path)) {
    Serial.println("[Firebase] Error: Path kosong!");
    return data;
  }

  if (!FirebaseManager_IsReady()) {
    Serial.println("[Firebase] Error: Firebase belum siap!");
    return data;
  }

  if (Firebase.RTDB.getJSON(&_fbdo, path)) {
    FirebaseJson& json = _fbdo.jsonObject();
    FirebaseJsonData result;

    // Ambil tiap field dari JSON response
    if (json.get(result, "temperature")) data.temperature = result.floatValue;
    if (json.get(result, "humidity")) data.humidity = result.floatValue;
    if (json.get(result, "co2")) data.co2 = result.intValue;

    data.isValid = true;
    Serial.printf("[Firebase] Data berhasil dibaca dari: %s\n", path);
  } else {
    _printError("GetData");
  }

  return data;
}

bool FirebaseManager_DeleteData(const char* path) {
  if (!_isValidPath(path)) {
    Serial.println("[Firebase] Error: Path kosong!");
    return false;
  }

  if (!FirebaseManager_IsReady()) {
    Serial.println("[Firebase] Error: Firebase belum siap!");
    return false;
  }

  if (Firebase.RTDB.deleteNode(&_fbdo, path)) {
    Serial.printf("[Firebase] Data berhasil dihapus di: %s\n", path);
    return true;
  }

  _printError("DeleteData");
  return false;
}
