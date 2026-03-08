#ifndef FIREBASE_MANAGER_H
#define FIREBASE_MANAGER_H

#include <Arduino.h>
#include "sensor_manager.h"

#define FIREBASE_HOST "https://room-monitoring-f7720-default-rtdb.asia-southeast1.firebasedatabase.app//"
#define FIREBASE_AUTH "U8i3K61BlMCxnsJRFtCSeAlRSTUYRaKxyi5z5fMT"

bool FirebaseManager_Init(void);

bool FirebaseManager_SendData(const char* path, SensorData_t data);

#endif