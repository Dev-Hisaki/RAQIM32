<h1>RAQIM32 (Room Air Quality Monitoring with ESP32)</h1>
<dl>
  <dt><h2>Overview</h2></dt>
  <dd><p>RAQIM32 adalah sebuah project IoT yang menggunakan analisis ML untuk mengevaluasi kualitas udara (CO2, Suhu dan Kelembapan) pada ruangan.</p></dd>
  <dt><h2>Component Used</h2></dt>
  <dd>
    <ul>
      <li>ESP32</li>
      <li>DHT22</li>
      <li>MQ135</li>
    </ul>
  </dd>
  <dt><h2>Konfigurasi</h2></dt>
  <dd>
    <ul>
      <li>#define WIFI_SSID "SSID_NAME"</li>
      <li>#define WIFI_PASSWORD "SSID_PASSWORD"</li>
      <li>#define FIREBASE_PATH "/ruangan/lantai1"</li>
      <li>#define SEND_INTERVAL 10000</li>
      <li>static unsigned long _lastSendTime = 0;</li>
    </ul>
  </dd>
</dl>
