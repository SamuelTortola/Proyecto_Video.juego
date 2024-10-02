/**
   ******************************************************************************
 Universidad Del Valle De Guatemala
 IE2023: Electrónica digital 2
 Autor: Samuel Tortola - 22094, Alan Gomez - 22115
 Proyecto: Video juego
 Hardware: STM32
 Creado: 30/09/2024
 Última modificación: 1/10/2024
******************************************************************************
 **/ 

#include <esp_now.h>
#include <WiFi.h>




// Definir el pin donde está conectado el potenciómetro
const int potPinx = 34; // ADC1_CH6 en el ESP32
const int potPiny = 35; // ADC1_CH7 en el ESP32
const int botonPin = 15; // Elige el GPIO, en este caso GPIO 15
const int botonPin1 = 4; // Elige el GPIO, en este caso GPIO 2
const int botonPin2 = 0; // Elige el GPIO, en este caso GPIO 0
int estadoBotonjos = 0;
int estadoBoton1 = 0;
int estadoBoton2 = 0;


// Variable para almacenar el valor de lectura del potenciómetro
int valorPotx = 0;
int valorPoty = 0;


void setup() {
   // Inicializamos la comunicación serial para ver los resultados en el monitor
  Serial.begin(9600);
  pinMode(botonPin,INPUT);
  pinMode(botonPin1,INPUT_PULLUP);
  pinMode(botonPin2,INPUT_PULLUP);

}

void loop() {
  // Leer el valor del potenciómetro (entre 0 y 4095 en el ESP32)
  valorPotx = analogRead(potPinx);
  valorPoty = analogRead(potPiny);
  estadoBotonjos = digitalRead(botonPin);
  estadoBoton1 = digitalRead(botonPin1);
  estadoBoton2 = digitalRead(botonPin2);

  if(valorPotx >= 4090){
    Serial.println("1");
  }

   else if(valorPotx <= 10){
    Serial.println("2");
  }

   if(valorPoty >= 4090){
    Serial.println("3");
  }

   else if(valorPoty <= 10){
    Serial.println("4");
  }

  // Si el botón del jostick  está presionado (el estado será LOW)
  if (estadoBotonjos == LOW) {
    delay(20);
    Serial.println("5");

    while(estadoBotonjos == LOW){
      delay(20);
      estadoBotonjos = digitalRead(botonPin);
    }
  
  }

    // Si el botón 1  está presionado (el estado será LOW)
  if (estadoBoton1 == LOW) {
    delay(20);
    Serial.println("6");

    while(estadoBoton1 == LOW){
      delay(20);
      estadoBoton1 = digitalRead(botonPin1);
    }
  
  }

      // Si el botón 2  está presionado (el estado será LOW)
  if (estadoBoton2 == LOW) {
    delay(20);
    Serial.println("7");

    while(estadoBoton2 == LOW){
      delay(20);
      estadoBoton2 = digitalRead(botonPin2);
    }
  
  }

  
  // Pequeña pausa para no saturar el monitor serial
  delay(5);
   
}
