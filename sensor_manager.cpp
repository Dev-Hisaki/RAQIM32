#include "sensor_manager.h"
#include <DHT.h>

// ─── Private State ────────────────────────────────────────────
static DHT _dht(PIN_DHT22, DHT22);

// ─── Private Helpers ─────────────────────────────────────────

/**
 * @brief Hitung resistance sensor MQ-135 dari nilai ADC.
 * @param adcValue Nilai mentah ADC (0–4095).
 * @return Nilai RS dalam kOhm.
 */
static float _MQ135_GetRS(int adcValue) {
  if (adcValue <= 0) adcValue = 1;  // Hindari pembagian nol
  float voltage = (adcValue / MQ135_ADC_MAX) * MQ135_VCC;
  return ((MQ135_VCC - voltage) / voltage) * MQ135_RL;
}

/**
 * @brief Konversi RS/Ro menjadi ppm CO2 menggunakan kurva karakteristik MQ-135.
 *        Rumus: ppm = a * (RS/Ro)^b  (a=116.602, b=-2.769 untuk CO2)
 * @param rs Nilai RS sensor saat ini.
 * @return Estimasi kadar CO2 dalam ppm.
 */
static int _MQ135_ConvertToPPM(float rs) {
  float ratio = rs / MQ135_RO_CLEAN;
  float ppm = 116.602f * pow(ratio, -2.769f);
  return (int)ppm;
}

// ─── Public Implementations ──────────────────────────────────

void SensorManager_Init(void) {
  _dht.begin();
  analogReadResolution(12);  // Set ADC ESP32 ke 12-bit (0–4095)
  Serial.println("[Sensor] Inisialisasi DHT22 dan MQ-135 selesai.");
}

SensorData_t SensorManager_ReadAll(void) {
  SensorData_t data;

  data.temperature = SensorManager_GetTemperature();
  data.humidity = SensorManager_GetHumidity();
  data.co2 = SensorManager_GetCO2();

  // isValid = true hanya jika DHT22 tidak mengembalikan NAN
  data.isValid = (!isnan(data.temperature) && !isnan(data.humidity));

  if (!data.isValid) {
    Serial.println("[Sensor] Gagal membaca DHT22!");
  }

  return data;
}

float SensorManager_GetTemperature(void) {
  float temp = _dht.readTemperature();
  if (isnan(temp)) {
    Serial.println("[Sensor] Error: Gagal baca suhu DHT22.");
  }
  return temp;
}

float SensorManager_GetHumidity(void) {
  float hum = _dht.readHumidity();
  if (isnan(hum)) {
    Serial.println("[Sensor] Error: Gagal baca kelembapan DHT22.");
  }
  return hum;
}

int SensorManager_GetCO2(void) {
  int adcValue = analogRead(PIN_MQ135);
  float rs = _MQ135_GetRS(adcValue);
  return _MQ135_ConvertToPPM(rs);
}

void SensorManager_RunTemperatureMonitoring(void) {
  float temp = SensorManager_GetTemperature();
  if (!isnan(temp)) {
    Serial.printf("[Sensor] Suhu       : %.2f C\n", temp);
  }
}

void SensorManager_RunHumidityMonitoring(void) {
  float hum = SensorManager_GetHumidity();
  if (!isnan(hum)) {
    Serial.printf("[Sensor] Kelembapan : %.2f %%\n", hum);
  }
}

void SensorManager_RunCO2Monitoring(void) {
  int co2 = SensorManager_GetCO2();
  Serial.printf("[Sensor] CO2        : %d ppm\n", co2);
}