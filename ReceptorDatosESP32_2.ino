#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "esp_wifi.h"


#define NUM_SECTIONS 8

// Estructura de datos recibida
typedef struct struct_message {
  float voltage;
} struct_message;

struct_message incomingData;

// Pines conectados a los relés (ajusta según tu conexión real)
const int relayPins[NUM_SECTIONS] = {15, 4, 16, 17, 5, 18, 19, 21};

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingDataRaw, int len) {
  memcpy(&incomingData, incomingDataRaw, sizeof(incomingData));
  float v = incomingData.voltage;

  Serial.print("Voltaje recibido: ");
  Serial.println(v);

  // Desactivar todas las salidas
  for (int i = 0; i < NUM_SECTIONS; i++) {
    digitalWrite(relayPins[i], HIGH);
  }

  // Activar salidas dependiendo del voltaje
  float step = 58.5 / NUM_SECTIONS;
  int numRelaysOn = v / step;

  for (int i = 0; i < numRelaysOn && i < NUM_SECTIONS; i++) {
    digitalWrite(relayPins[i], LOW);  // Encender rele
  }
}

void setup() {
  Serial.begin(19200);
  Serial.println("Iniciando ESP32...");

  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(0, WIFI_SECOND_CHAN_NONE);

  Serial.println("Modo WiFi STA activado.");

  // Configurar pines de relé como salidas
  for (int i = 0; i < NUM_SECTIONS; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH);  // Iniciar apagado
  }

  Serial.println("Relés configurados.");

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error iniciando ESP-NOW");
    return;
  }

  Serial.println("ESP-NOW iniciado correctamente.");
  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("ESP32 receptora lista.");
  Serial.print("MAC Address (para el emisor): ");
  Serial.println(WiFi.macAddress());
}

void loop(){
  
}







