#define LED_PIN 13

volatile char receivedChar;
volatile bool newData = false;

void setup() {
  // Configura la velocidad del puerto serie
  Serial.begin(9600);

  // Configura un LED en el pin 13 para verificar la recepción de datos
  pinMode(LED_PIN, OUTPUT);
  
  // Habilitar la interrupción de recepción
  UCSR0B |= (1 << RXCIE0);  // Habilita la interrupción de recepción UART
  
  // Habilitar interrupciones globales
  sei();
}

void loop() {
  if (newData) {
    Serial.print("Dato recibido: ");
    Serial.println(receivedChar);
    
    // Parpadeo del LED para indicar recepción
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    
    // Reiniciar el indicador de nuevo dato
    newData = false;
  }
}

// Rutina de servicio de interrupción para la recepción UART
ISR(USART_RX_vect) {
  receivedChar = UDR0;  // Lee el dato recibido
  newData = true;       // Indica que hay un nuevo dato disponible
}
