#include <BluetoothSerial.h>

#include <esp_now.h>
#include <WiFi.h>

BluetoothSerial SerialBT;

// Dirección MAC de broadcast (para todos los ESP32 receptores)
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct struct_message {
  float voltaje;
  float corriente;
  float rpm;
} struct_message;

struct_message myData;

// Pines
const int pinVoltaje = 34;
const int pinCorriente = 39;
const int pinSensorHall = 14;

// Variables RPM
volatile int conteoPulsos = 0;
unsigned long tiempoAnterior = 0;
unsigned long tiempoUltimoPulso = 0;
unsigned long tiempoEntrePulsos = 0;

void contarPulsos() {
  unsigned long ahora = millis();
  tiempoEntrePulsos = ahora - tiempoUltimoPulso;
  tiempoUltimoPulso = ahora;
  conteoPulsos++;
}

void OnSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("ESP-NOW ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "OK" : "Fallo");
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");  // Nombre del dispositivo Bluetooth
  pinMode(pinSensorHall, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinSensorHall), contarPulsos, FALLING);

  // Inicializa WiFi en modo estación
  WiFi.mode(WIFI_STA);

  // Inicializa ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error iniciando ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Error agregando peer");
    return;
  }

  Serial.println("ESP32 lista para enviar por Bluetooth y ESP-NOW");
}

void loop() {
  // Lectura de sensores
  int analogValue = analogRead(pinVoltaje);
  float v_a = (analogValue * 3.3) / 4095.0;
  float v_adc = v_a + 0.2;
  //myData.voltaje = 15.81 * exp(4.5 * v_adc) - 38.7;
  myData.voltaje = (-21.565 * (v_adc*v_adc))+(91.939 * v_adc)-17.475;

  int lecturaCorriente = analogRead(pinCorriente);
float voltajeCorriente = (lecturaCorriente * 3.3) / 4095.0;
float corrienteCalculada = ((voltajeCorriente - 2.5) / 0.1) + 1.6;
myData.corriente = corrienteCalculada < 0 ? 0 : corrienteCalculada;

  //float rpm = 0;
  // unsigned long ahora = millis();

  // noInterrupts();
  // unsigned long tiempoLocal = tiempoEntrePulsos;
  // unsigned long ultimoPulso = tiempoUltimoPulso;
  // interrupts();

  // if (tiempoLocal > 0 && (ahora - ultimoPulso < 1500)) {
  //   rpm = 60000.0 / tiempoLocal;
  // }
  // myData.rpm = rpm;

  myData.rpm = myData.voltaje * (218.0 / 60.0);  // Aproximadamente rpm = voltaje × 3.633



  
  // Enviar por ESP-NOW broadcast
  esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

  // Enviar por Bluetooth
  Serial.println(v_adc);
  SerialBT.print(myData.voltaje, 2);
  Serial.println(myData.voltaje, 2);
  SerialBT.print(",");
  SerialBT.print(myData.corriente, 2);
  SerialBT.print(",");
  SerialBT.println(myData.rpm, 1);

  Serial.println("Enviado por BT y ESP-NOW");

  delay(500);
}

