// Definimos los pines de los LEDs y el pin del sensor
const int ledPins[] = {3, 4, 5, 6}; // Pines donde están conectados los LEDs
const int numLeds = 4; // Número de LEDs
const int sensorPin = 2;

void setup() {
  // Configuramos los pines de los LEDs como salida
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); // Aseguramos que los LEDs estén apagados al inicio
  }
  // Configuramos el pin del sensor como entrada
  pinMode(sensorPin, INPUT);
}

void loop() {
  // Leemos el estado del sensor
  int sensorValue = digitalRead(sensorPin);

  // Si el sensor detecta algo, encendemos los LEDs
  if (sensorValue == HIGH) {
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
  } else {
    // Si el sensor no detecta nada, apagamos los LEDs
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  }
}
