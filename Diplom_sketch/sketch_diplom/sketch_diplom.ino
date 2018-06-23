unsigned long counttime;
int potPin = A0;
int ledPin = 9;
int ledON = 8;
int PIR=  2; // назначаем порт для светодиода
int Door_Sensor_Pin = 4; // контакт для датчика
int val = 0; // переменная для хранения состояния датчика
int buzzer=6;
void setup() {
  // порт для светодиода на выход
  pinMode(ledPin, OUTPUT);
  pinMode(ledON, OUTPUT);
 
  // пин с потенциометром - вход
  // мы хотим считывать напряжение,
  // выдаваемое им
  pinMode(buzzer, OUTPUT);
  pinMode(potPin, INPUT);
  Serial.begin(9600);
  pinMode(PIR, INPUT);
  pinMode(Door_Sensor_Pin, INPUT); // установить Door_Sensor_Pin как вход
}

void loop() {
  // значение напряжения с потенциометра
  int rotation;
  // значение яркости
  int brightness;  
  rotation = analogRead(potPin);
  brightness = rotation / 4;
  
  digitalWrite(ledON, HIGH);//по умолчанию включаем диод активности
    // если есть движение включаем светодиод
  if (digitalRead(PIR) == HIGH) {
    analogWrite(ledPin, brightness); }

   // если нет движения
  if (digitalRead(PIR) == LOW) {

  // включаем счетчик на 1 минуту
  counttime = millis();
  millis() - counttime > 20000;

  // если нет движения в течении 1 минуты выключаем светодиод
  analogWrite(ledPin, LOW);
}
  val = digitalRead(Door_Sensor_Pin); // читать Door_Sensor_Pin
  if (val == HIGH) { // Если Door_Sensor N.C. (без магнита) -> HIGH : Дверь открыта / LOW : Дверь закрыта
    // Если Door_Sensor N.0. (nc с магнитом) -> HIGH : Дверь открыта / LOW : Дверь закрыта
    noTone(buzzer);
    digitalWrite(ledON, HIGH);
  } else {
    tone (buzzer, 600); // включаем на пьезодинамик 600 Гц
    digitalWrite(ledON, HIGH);
    delay(70);
    digitalWrite(ledON, LOW);
    delay(70);
  }
}
