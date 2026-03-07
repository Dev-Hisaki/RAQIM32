#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Arduino.h>

// ─── Konfigurasi Pin ──────────────────────────────────────────
#define PIN_DHT22 4   // GPIO pin untuk DHT22
#define PIN_MQ135 34  // GPIO pin untuk MQ-135 (ADC input)

// ─── Konfigurasi MQ-135 ───────────────────────────────────────
#define MQ135_RL 10.0f         // Load resistance dalam kOhm
#define MQ135_RO_CLEAN 76.63f  // Ro di udara bersih (kalibrasi awal)
#define MQ135_ADC_MAX 4095.0f  // Resolusi ADC ESP32 (12-bit)
#define MQ135_VCC 3.3f         // Tegangan referensi ESP32

// ─── Struct Data Sensor ───────────────────────────────────────

/**
 * @brief Struktur data sensor yang dikirim/diterima dari Firebase.
 */
typedef struct {
  float temperature;  // Suhu dalam Celsius
  float humidity;     // Kelembapan dalam persen (%)
  int co2;            // Kadar CO2 dalam ppm
  bool isValid;       // true jika semua data berhasil dibaca
} SensorData_t;

// ─── Public API ───────────────────────────────────────────────

/**
 * @brief Inisialisasi semua sensor (DHT22 dan MQ-135).
 *        Wajib dipanggil sekali di setup().
 */
void SensorManager_Init(void);

/**
 * @brief Baca semua sensor sekaligus dan kembalikan sebagai struct.
 * @return SensorData_t berisi semua data. Cek field isValid.
 */
SensorData_t SensorManager_ReadAll(void);

/**
 * @brief Pantau dan cetak data suhu ke Serial secara berkala.
 */
void SensorManager_RunTemperatureMonitoring(void);

/**
 * @brief Pantau dan cetak data kelembapan ke Serial secara berkala.
 */
void SensorManager_RunHumidityMonitoring(void);

/**
 * @brief Pantau dan cetak data CO2 ke Serial secara berkala.
 */
void SensorManager_RunCO2Monitoring(void);

/**
 * @brief Baca nilai suhu dari sensor DHT22.
 * @return Suhu dalam Celsius, atau NAN jika gagal.
 */
float SensorManager_GetTemperature(void);

/**
 * @brief Baca nilai kelembapan dari sensor DHT22.
 * @return Kelembapan dalam persen (%), atau NAN jika gagal.
 */
float SensorManager_GetHumidity(void);

/**
 * @brief Baca nilai CO2 dari sensor MQ-135.
 * @return Kadar CO2 dalam ppm.
 */
int SensorManager_GetCO2(void);

#endif  // SENSOR_MANAGER_H