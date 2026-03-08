#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Arduino.h>

#define PIN_DHT22 4
#define PIN_MQ135 34

#define MQ135_RL 10.0
#define MQ135_RO_CLEAN 76.63
#define MQ135_ADC_MAX 4095.0
#define MQ135_VCC 3.3

typedef struct
{
  float temperature;
  float humidity;
  int co2;
  bool isValid;

} SensorData_t;

void SensorManager_Init(void);

SensorData_t SensorManager_ReadAll(void);

float SensorManager_GetTemperature(void);

float SensorManager_GetHumidity(void);

int SensorManager_GetCO2(void);

#endif