#ifndef FIREBASE_MANAGER_H
#define FIREBASE_MANAGER_H

#include "sensor_manager.h"  // ← tambahkan ini

#include <Arduino.h>

// ─── Konfigurasi Firebase ─────────────────────────────────────
#define FIREBASE_HOST     "YOUR_PROJECT_ID.firebaseio.com"
#define FIREBASE_API_KEY  "YOUR_API_KEY"
#define FIREBASE_EMAIL    "YOUR_EMAIL"
#define FIREBASE_PASSWORD "YOUR_PASSWORD"

// ─── Public API ───────────────────────────────────────────────

/**
 * @brief Inisialisasi koneksi ke Firebase dengan autentikasi.
 * @return true jika berhasil terkoneksi.
 */
bool FirebaseManager_Init(void);

/**
 * @brief Cek apakah Firebase siap digunakan.
 * @return true jika Firebase siap.
 */
bool FirebaseManager_IsReady(void);

/**
 * @brief Kirim data sensor ke Firebase RTDB.
 * @param path Path tujuan di Firebase (contoh: "/ruangan/lantai1").
 * @param data Struct SensorData_t berisi data yang akan dikirim.
 * @return true jika berhasil dikirim.
 */
bool FirebaseManager_SendData(const char* path, SensorData_t data);

/**
 * @brief Ambil data sensor dari Firebase RTDB.
 * @param path Path sumber di Firebase (contoh: "/ruangan/lantai1").
 * @return SensorData_t berisi data hasil baca. Cek field isValid.
 */
SensorData_t FirebaseManager_GetData(const char* path);

/**
 * @brief Hapus data di path tertentu dari Firebase RTDB.
 * @param path Path yang akan dihapus.
 * @return true jika berhasil dihapus.
 */
bool FirebaseManager_DeleteData(const char* path);

#endif // FIREBASE_MANAGER_H
