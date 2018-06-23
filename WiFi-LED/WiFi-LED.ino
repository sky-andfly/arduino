#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

String echo;
int message=0;
int valueLED=0;
int value=0;
int LedPin=D5;
int Door_Led_Pin = D6; // выбрать контакт для светодиода
int Door_Sensor_Pin = D7; // контакт для датчика
int val = 0;                         // По умолчанию диод не горит
const char *ssid = "Ardulogic";      // Название сети WiFi
const char *password = "1234567890"; // Пароль для подключения
ESP8266WebServer server(80);         // Создаем веб сервер на 80 порту

// Метод формирует стартовую страницу http://192.168.4.1
// Выводит в браузер текущее состояние диода и две кнопки
void handleRoot() {
  String s = (val) ? "<h1>Signalization On</h1>" : "<h1>Signalization Off</h1>";
  s += "<h2><a href=\"/led/on\"> On</a> ";
  s += "<a href=\"/led/off\"> Off</a></h2>";
  if (message == 1){
    s += "<h2>Door open </h2> ";
  }
  server.send(200, "text/html", s);
}

// Метод включения диода
void ledOn() {
  val = 1; // Включаем диод
  valueLED = 1;
  digitalWrite(LedPin, val);
  
  // Перенаправление обратно на стартовую страницу
  server.sendHeader("Location", String("/"), true);
  server.send ( 302, "text/plain", "");
}

// Метод выключения диода
void ledOff() {
  val = 0; // Выключаем диод
  valueLED = 0;
  digitalWrite(LedPin, val);
   digitalWrite(Door_Led_Pin, LOW);
  // Перенаправление обратно на стартовую страницу
  server.sendHeader("Location", String("/"), true);
  server.send ( 302, "text/plain", "");
}

// Функция настройки. Выполняется один раз при запуске
void setup() {
  delay(1000);                 // Ждём секунду
  WiFi.softAP(ssid, password); // Создаём точку WiFi
  // Указываем по каким роутам какие методы запускать
  server.on("/", handleRoot);
  server.on("/led/on", ledOn);
  server.on("/led/off", ledOff);
  server.begin();
  // Диод по умолчанию выключен
  pinMode(LedPin, OUTPUT);
  digitalWrite(LedPin, val);
  pinMode(Door_Led_Pin, OUTPUT); // установить Door_Led_Pin как выход
  pinMode(Door_Sensor_Pin, INPUT); // установить Door_Sensor_Pin как вход
}

// Основной цикл программы
void loop() {
  // Ждём подключения
  server.handleClient();
  value = digitalRead(Door_Sensor_Pin); // читать Door_Sensor_Pin
  if(valueLED == 1){
  digitalWrite(LedPin, HIGH);  
   if (value == HIGH) { // Если Door_Sensor N.C. (без магнита) -> HIGH : Дверь открыта / LOW : Дверь закрыта
  // Если Door_Sensor N.0. (nc с магнитом) -> HIGH : Дверь открыта / LOW : Дверь закрыта
  digitalWrite(Door_Led_Pin, LOW); //выключить светодиод Door_Led
  digitalWrite(LedPin, LOW);
  } else {
  digitalWrite(LedPin, HIGH);  
  digitalWrite(Door_Led_Pin, HIGH); //включить светодиод Door_Led
  delay(30);
  digitalWrite(Door_Led_Pin, LOW); //включить светодиод Door_Led
  delay(20);
  digitalWrite(Door_Led_Pin, HIGH); //включить светодиод Door_Led
  delay(30);
  
  message = 1;
 
  
}
  } else{
  digitalWrite(Door_Led_Pin, LOW);
  digitalWrite(LedPin, LOW);
  message = 0;
  }
  
}
