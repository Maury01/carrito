#include <SoftwareSerial.h>

// Configuración de los pines RX y TX del módulo Bluetooth
const int BT_RX_PIN = 6;  // Conectado al pin TX del módulo Bluetooth
const int BT_TX_PIN = 7;  // Conectado al pin RX del módulo Bluetooth

SoftwareSerial bluetoothSerial(BT_RX_PIN, BT_TX_PIN);

// Pines de los componentes
const int LED1_PIN = 12;
const int LED2_PIN = 13;
const int MOTOR_IZQ_PIN = 10;
const int MOTOR_DERCH_PIN = 11;
const int BUZZER_PIN = 8;

// Variables para controlar el estado de los componentes
bool led1Encendido = false;
bool led2Encendido = false;

void setup() {
  Serial.begin(9600);
  bluetoothSerial.begin(9600);
  
  // Esperar hasta que se establezca la conexión Bluetooth
  while (!bluetoothSerial) {
    delay(100);
  }
  
  Serial.println("Conexión Bluetooth establecida");
  
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(MOTOR_IZQ_PIN, OUTPUT);
  pinMode(MOTOR_DERCH_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Apagar todos los componentes
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(MOTOR_IZQ_PIN, LOW);
  digitalWrite(MOTOR_DERCH_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  // Verificar si hay datos disponibles en el módulo Bluetooth
  if (bluetoothSerial.available()) {
    // Leer el dato recibido del módulo Bluetooth
    char receivedChar = bluetoothSerial.read();
    
    // Imprimir el dato recibido en el puerto serial
    Serial.print("Comando recibido desde Bluetooth: ");
    Serial.println(receivedChar);
    
    // Ejecutar el comando correspondiente
    switch (receivedChar) {
      case 'F':  // Ambos motores se activarán
        digitalWrite(MOTOR_IZQ_PIN, HIGH);
        digitalWrite(MOTOR_DERCH_PIN, HIGH);
        break;
      case 'L':  // El motorIzq se apagará y el motorDerch se encenderá
        digitalWrite(MOTOR_IZQ_PIN, LOW);
        digitalWrite(MOTOR_DERCH_PIN, HIGH);
        break;
      case 'R':  // El motorIzq se encenderá y el motorDerch se apagará
        digitalWrite(MOTOR_IZQ_PIN, HIGH);
        digitalWrite(MOTOR_DERCH_PIN, LOW);
        break;
      case 'W':  // Se encenderá el led1
        digitalWrite(LED1_PIN, HIGH);
        led1Encendido = true;
        break;
      case 'U':  // Se encenderá el led2
        digitalWrite(LED2_PIN, HIGH);
        led2Encendido = true;
        break;
      case 'V':  // Hará sonar el buzzer
        digitalWrite(BUZZER_PIN, HIGH);
        delay(1000);
        digitalWrite(BUZZER_PIN, LOW);
        break;
        case '4':  // El motorIzq se apagará y el motorDerch se encenderá
        digitalWrite(MOTOR_IZQ_PIN, LOW);
        digitalWrite(MOTOR_DERCH_PIN, LOW);
        break;
      default:  // Comando inválido
        break;
    }
  }
  // Verificar si los leds deben apagarse
  if (led1Encendido && !bluetoothSerial.available()) {
    digitalWrite(LED1_PIN, LOW);
    led1Encendido = false;
  }

  if (led2Encendido && !bluetoothSerial.available()) {
    digitalWrite(LED2_PIN, LOW);
    led2Encendido = false;
  }
}