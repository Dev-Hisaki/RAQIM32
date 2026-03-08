#include "sensor_manager.h"
#include <DHT.h>

static DHT dht(PIN_DHT22, DHT22);

float RO = MQ135_RO_CLEAN;


// membaca ADC rata-rata
static int MQ135_ReadADC()
{
  long total = 0;

  for(int i=0;i<10;i++)
  {
    total += analogRead(PIN_MQ135);
    delay(20);
  }

  return total / 10;
}


// hitung RS
static float MQ135_GetRS(int adc)
{
  if(adc <= 0) adc = 1;

  float voltage = ((float)adc / MQ135_ADC_MAX) * MQ135_VCC;

  float rs = ((MQ135_VCC - voltage) / voltage) * MQ135_RL;

  return rs;
}


// konversi RS ke ppm
static int MQ135_GetPPM(float rs)
{
  float ratio = rs / RO;

  float ppm = 116.602 * pow(ratio, -2.769);

  if(ppm < 0) ppm = 0;
  if(ppm > 5000) ppm = 5000;   // batas realistis

  return (int)ppm;
}


// kalibrasi sensor
static float MQ135_Calibrate()
{
  Serial.println("[MQ135] Calibrating...");

  float rs = 0;

  for(int i=0;i<50;i++)
  {
    int adc = MQ135_ReadADC();

    rs += MQ135_GetRS(adc);

    delay(200);
  }

  rs = rs / 50;

  float ro = rs / 3.6;

  Serial.print("[MQ135] RO = ");
  Serial.println(ro);

  return ro;
}


void SensorManager_Init(void)
{
  dht.begin();

  analogReadResolution(12);

  Serial.println("[Sensor] Warming MQ135...");

  delay(20000);   // warm up sensor

  RO = MQ135_Calibrate();

  Serial.println("[Sensor] Ready");
}


SensorData_t SensorManager_ReadAll(void)
{
  SensorData_t data;

  data.temperature = dht.readTemperature();
  data.humidity = dht.readHumidity();

  int adc = MQ135_ReadADC();

  float rs = MQ135_GetRS(adc);

  data.co2 = MQ135_GetPPM(rs);

  data.isValid = !(isnan(data.temperature) || isnan(data.humidity));

  return data;
}


float SensorManager_GetTemperature(void)
{
  return dht.readTemperature();
}


float SensorManager_GetHumidity(void)
{
  return dht.readHumidity();
}


int SensorManager_GetCO2(void)
{
  int adc = MQ135_ReadADC();

  float rs = MQ135_GetRS(adc);

  return MQ135_GetPPM(rs);
}