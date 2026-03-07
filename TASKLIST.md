Tasklist:
/*
 * RAQIM32 — ESP32 Environmental Monitor
 * =======================================
 * To Do List:
 * 1. [x] WiFi connect/disconnect
 * 2. [x] Kirim data CO2, kelembapan, dan suhu ke Firebase RTDB
 * 3. [x] Terima data dari Firebase RTDB
 * 4. [x] Hapus data dari Firebase RTDB
 * 5. [ ] Configure Read/Write authority
 * 6. [ ] CRUD WiFi credentials
 * 7. [ ] Interval pengiriman data yang dapat diatur oleh admin
 * 8. [ ] Error handling (Buzzer / LED / LCD)
 * 9. [ ] Tampilkan di dashboard (webapp)
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