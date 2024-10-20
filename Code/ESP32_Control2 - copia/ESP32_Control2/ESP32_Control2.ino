#include <esp_now.h>
#include <WiFi.h>

///////////////////////////////////////////////////////////////////////////////
// Librerias de musica buzzer
///////////////////////////////////////////////////////////////////////////////
#include <EasyBuzzer.h>
#include "pitches.h"
#include "ZELDA.h"
#include "NEVER.h"
#include "DEAD.h"
#include "WIN.h"
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Variables
///////////////////////////////////////////////////////////////////////////////
const int potPinx = 34; // ADC1_CH6 en el ESP32
const int potPiny = 35; // ADC1_CH7 en el ESP32
const int botonPin = 15; // Elige el GPIO, en este caso GPIO 15, boton del jostick
const int botonPin1 = 4; // Elige el GPIO, en este caso GPIO 4
const int botonPin2 = 16; // Elige el GPIO, en este caso GPIO 16
const int motor = 17; // Elige el GPIO, en este caso GPIO 17

char datos;

int estadoBotonjos = 0;
int estadoBoton1 = 0;
int estadoBoton2 = 0;

int valorPotx = 0;
int valorPoty = 0;

#define BUZZER 32 // Elige el GPIO, en este caso GPIO 32

// Dirección MAC del ESP32 A 
uint8_t macReceptorA[] = {0x94, 0xB5, 0x55, 0xF2, 0x98, 0x10};

// Callback para recibir mensajes
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
  char mensaje[32];
  if (len < sizeof(mensaje)) {
    memcpy(mensaje, incomingData, len);
    mensaje[len] = '\0'; // Asegurarse de terminar la cadena con un carácter nulo
    Serial.print("Mensaje recibido: ");
    Serial.println(mensaje);
  }
}

// Callback para confirmar el envío
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  if (status == ESP_NOW_SEND_SUCCESS) {
    Serial.println("Mensaje enviado con éxito");
  } else {
    Serial.println("Error enviando mensaje");
  }
}

//////////////////////////////////////////////////////////////////////////////////
// Modulos
//////////////////////////////////////////////////////////////////////////////////
void espNowTask(void *pvParameters) {
  Serial.print("ESP-NOW Task inicializada\n");
  while (true) {
    if (Serial.available()) {
      datos = Serial.read();
      Serial.print("Dato recibido: ");
      Serial.println(datos);

      char cadena[2] = {datos, '\0'};
      enviar(cadena); // Llamar a enviar con una cadena correctamente formateada
    }

    // Leer el valor del potenciómetro (entre 0 y 4095 en el ESP32)
    valorPotx = analogRead(potPinx);
    valorPoty = analogRead(potPiny);
    estadoBotonjos = digitalRead(botonPin);
    estadoBoton1 = digitalRead(botonPin1);
    estadoBoton2 = digitalRead(botonPin2);

    if (valorPotx >= 4090) {
      Serial.println("1");
      enviar("1");

      while (valorPotx >= 4090) {
        delay(20);
        valorPotx = analogRead(potPinx);
      }
    } else if (valorPotx <= 30) {
      Serial.println("2");
      enviar("2");

      while (valorPotx <= 30) {
        delay(20);
        valorPotx = analogRead(potPinx);
      }
    }

    if (valorPoty >= 4090) {
      Serial.println("3");
      enviar("3");

      while (valorPoty >= 4090) {
        delay(20);
        valorPoty = analogRead(potPiny);
      }
    } else if (valorPoty <= 30) {
      Serial.println("4");
      enviar("4");

      while (valorPoty <= 30) {
        delay(20);
        valorPoty = analogRead(potPiny);
      }
    }

    if (estadoBotonjos == LOW) {
      delay(20);
      Serial.println("5");
      enviar("5");

      while (estadoBotonjos == LOW) {
        delay(20);
        estadoBotonjos = digitalRead(botonPin);
      }
    }

    if (estadoBoton1 == LOW) {
      delay(20);
      Serial.println("6");
      enviar("6");

      while (estadoBoton1 == LOW) {
        delay(20);
        estadoBoton1 = digitalRead(botonPin1);
      }
    }

    if (estadoBoton2 == LOW) {
      delay(20);
      Serial.println("7");
      enviar("7");

      while (estadoBoton2 == LOW) {
        delay(20);
        estadoBoton2 = digitalRead(botonPin2);
      }
    }

    // Pequeña pausa para no saturar el monitor serial
    delay(5);
  }
}

void enviar(const char* dato) {
  char mensaje[32];
  snprintf(mensaje, sizeof(mensaje), "%s", dato);

  esp_err_t result = esp_now_send(macReceptorA, (uint8_t *)mensaje, strlen(mensaje) + 1);
  if (result == ESP_OK) {
    Serial.println("Mensaje enviado");
  } else {
    Serial.println("Error enviando mensaje");
  }
}

//////////////////////////////////////////////////////////////////////////////////
// BUZZER
//////////////////////////////////////////////////////////////////////////////////
void buzzerTask(void *pvParameters) {
  while (true) {
    WIN(BUZZER);
    delay(1000);
    ZELDA(BUZZER);
    delay(1000);
    NEVER(BUZZER);
    delay(10000);
    DEAD(BUZZER);
    delay(100);
  }
   EasyBuzzer.update(); // Actualiza el estado del buzzer
}

//////////////////////////////////////////////////////////////////////////////////
// Principal Code
//////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  pinMode(botonPin, INPUT);
  pinMode(botonPin1, INPUT_PULLUP);
  pinMode(botonPin2, INPUT_PULLUP);
  pinMode(motor, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Inicializar WiFi en modo estación (STA)
  WiFi.mode(WIFI_STA);

  // Inicializar ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error inicializando ESP-NOW");
    return;
  }

  // Registrar el callback de envío
  esp_now_register_send_cb(OnDataSent);

  // Registrar el callback de recepción
  esp_now_register_recv_cb(OnDataRecv);

  // Añadir peer
  esp_now_peer_info_t peerInfo;
  memset(&peerInfo, 0, sizeof(peerInfo)); // Inicializar en cero
  memcpy(peerInfo.peer_addr, macReceptorA, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Error añadiendo peer");
    return;
  }

  Serial.println("Configuración ESP-NOW completa");

  xTaskCreatePinnedToCore(espNowTask, "ESP-NOW Task", 4096, NULL, 1, NULL, 0); // Núcleo 0
  xTaskCreatePinnedToCore(buzzerTask, "Buzzer Task", 4096, NULL, 1, NULL, 1);  // Núcleo 1
}

void loop() {
 

  if (Serial.available()) {
    datos = Serial.read();
    Serial.print(datos);

    if (datos == 'M') {
      digitalWrite(motor, 1);
      delay(1000);
      digitalWrite(motor, 0);
      delay(1000);
      digitalWrite(motor, 1);
      delay(1000);
      digitalWrite(motor, 0);
    }

    char cadena[2] = {datos, '\0'};
    enviar(cadena);  // Enviar el dato leído
  }
}
