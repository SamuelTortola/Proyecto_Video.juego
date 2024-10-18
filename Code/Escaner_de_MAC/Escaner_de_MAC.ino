#include "WiFi.h"
#include "esp_wifi.h"


 // Buffer para almacenar la dirección MAC
 uint8_t mac[6];
  
void setup() {
  Serial.begin(115200);

  // Inicializa WiFi en modo estación (STA)
  WiFi.mode(WIFI_STA);


  

}

void loop() {
  // Obtener la dirección MAC utilizando esp_wifi_get_mac
  esp_wifi_get_mac(WIFI_IF_STA, mac);
  
  // Imprimir la dirección MAC en el formato correcto
  Serial.printf("Dirección MAC del ESP32: %02X:%02X:%02X:%02X:%02X:%02X\n", 
        mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

  delay(2000);

}
