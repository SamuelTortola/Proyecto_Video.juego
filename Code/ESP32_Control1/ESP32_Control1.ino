/**
   ******************************************************************************
 Universidad Del Valle De Guatemala
 IE2023: Electrónica digital 2
 Autor: Samuel Tortola - 22094, Alan Gomez - 22115
 Proyecto: Video juego
 Hardware: STM32
 Creado: 30/09/2024
 Última modificación: 4/10/2024
******************************************************************************
 **/ 

#include "ESP32_NOW.h"
#include "WiFi.h"


// Definir el pin donde está conectado el potenciómetro
const int potPinx = 34; // ADC1_CH6 en el ESP32
const int potPiny = 35; // ADC1_CH7 en el ESP32
const int botonPin = 15; // Elige el GPIO, en este caso GPIO 15, boton del jostick
const int botonPin1 = 4; // Elige el GPIO, en este caso GPIO 4
const int botonPin2 = 0; // Elige el GPIO, en este caso GPIO 0

int estadoBotonjos = 0;
int estadoBoton1 = 0;
int estadoBoton2 = 0;

// Variable para almacenar el valor de lectura del potenciómetro
int valorPotx = 0;
int valorPoty = 0;


// Dirección MAC del ESP32 B (reemplazar con la dirección MAC real)
const uint8_t macReceptorB[] = {0x94, 0xB5, 0x55, 0xF2, 0x98, 0x10};  

// Crear una clase que herede de ESP_NOW_Peer
class ESP_NOW_Peer_Class : public ESP_NOW_Peer {
public:
  ESP_NOW_Peer_Class(const uint8_t *mac_addr, uint8_t channel, wifi_interface_t iface, const uint8_t *lmk) 
  : ESP_NOW_Peer(mac_addr, channel, iface, lmk) {}

  ~ESP_NOW_Peer_Class() {}

  // Método público para enviar datos
  bool send_message(const uint8_t *data, int len) {
    return ESP_NOW_Peer::send(data, len);
  }

  bool add_peer() {
    if (!add()) {
      log_e("Error registrando el peer");
      return false;
    }
    return true;
  }

  void onReceive(const uint8_t *data, size_t len, bool broadcast) {
    // Asegurarse de que el mensaje recibido esté bien formado
  char mensaje[32];
  if (len < sizeof(mensaje)) {
    memcpy(mensaje, data, len);
    mensaje[len] = '\0'; // Asegurarse de terminar la cadena con un carácter nulo

    Serial.println(mensaje);
  } else {
    //Serial.println("Mensaje demasiado largo para buffer");
  }
  }
};

// Crear el peer del ESP32 B
ESP_NOW_Peer_Class peer_B(macReceptorB, 1, WIFI_IF_STA, NULL);

void setup() {
  Serial.begin(115200);
  pinMode(botonPin,INPUT);
  pinMode(botonPin1,INPUT_PULLUP);
  pinMode(botonPin2,INPUT_PULLUP);

  // Inicializar WiFi en modo estación (STA)
  WiFi.mode(WIFI_STA);

  // Inicializar ESP-NOW
  if (!ESP_NOW.begin()) {
   // Serial.println("Error inicializando ESP-NOW");
    return;
  }

  // Añadir el peer
  if (!peer_B.add_peer()) {
   // Serial.println("Error añadiendo el peer ESP32 B");
    return;
  }

 // Serial.println("Configuración de ESP32 A completa.");
}

void loop() {
  // Leer el valor del potenciómetro (entre 0 y 4095 en el ESP32)
  valorPotx = analogRead(potPinx);
  valorPoty = analogRead(potPiny);
  estadoBotonjos = digitalRead(botonPin);
  estadoBoton1 = digitalRead(botonPin1);
  estadoBoton2 = digitalRead(botonPin2);

  if(valorPotx >= 4090){
    Serial.println("8");
    enviar("8");
    
    while(valorPotx >= 4090){
      delay(20);
      valorPotx = analogRead(potPinx);
    }
    
  }

   else if(valorPotx <= 30){
    Serial.println("9");
    enviar("9");
    
    while(valorPotx <= 30){
      delay(20);
      valorPotx = analogRead(potPinx);
    }
  }

   if(valorPoty >= 4090){
    Serial.println("A");
    enviar("A");

    while(valorPoty >= 4090){
      delay(20);
      valorPoty = analogRead(potPiny);
    }
    
  }

   else if(valorPoty <= 30){
    Serial.println("B");
    enviar("B");

    while(valorPoty <= 30){
      delay(20);
      valorPoty = analogRead(potPiny);
    }
  }

  // Si el botón del jostick  está presionado (el estado será LOW)
  if (estadoBotonjos == LOW) {
    delay(20);
    Serial.println("C");
    enviar("C");

    while(estadoBotonjos == LOW){
      delay(20);
      estadoBotonjos = digitalRead(botonPin);
    }
  
  }

    // Si el botón 1  está presionado (el estado será LOW)
  if (estadoBoton1 == LOW) {
    delay(20);
    Serial.println("D");
    enviar("D");

    while(estadoBoton1 == LOW){
      delay(20);
      estadoBoton1 = digitalRead(botonPin1);
    }
  
  }

      // Si el botón 2  está presionado (el estado será LOW)
  if (estadoBoton2 == LOW) {
    delay(20);
    Serial.println("E");
    enviar("E");

    while(estadoBoton2 == LOW){
      delay(20);
      estadoBoton2 = digitalRead(botonPin2);
    }
  
  }

  
  // Pequeña pausa para no saturar el monitor serial
  delay(5);

 
}


void enviar (const char* dato){

  // Asegurarse de que los datos enviados están bien formateados
  char mensaje[32]; // Buffer para el mensaje con un tamaño adecuado
  snprintf(mensaje, sizeof(mensaje), "%s", dato);  // Copiar los datos al buffer con formato correcto
   
  if (!peer_B.send_message((uint8_t *)mensaje, strlen(mensaje) + 1)) {  // Enviar el mensaje pasado como parámetro, // Incluir terminador nulo
   // Serial.println("Error enviando mensaje");
  } 
  
  else {
   // Serial.println("Mensaje enviado desde ESP32 B");
  }
}
