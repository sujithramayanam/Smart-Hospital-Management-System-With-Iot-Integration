#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

#define ONE_WIRE_BUS 2  // DS18B20 pin
#define RX_PIN 3        // EM-18 RX pin
#define TX_PIN 4        // EM-18 TX pin
#define PULSE_PIN A0    // Pulse sensor pin
#define buzzer 6
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
SoftwareSerial em18(RX_PIN, TX_PIN);
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);  // RS, EN, D4, D5, D6, D7

struct Patient {
  String id;
  String name;
  int age;
  String joinDate;
  String disease;
  String medicine;
};

Patient patients[] = {
  {"4A003A382961", "raju", 35, "01/01/2023", "Diabetes", "Metformin"},
  {"4A003B0D87FB", "kishore", 45, "15/03/2023", "Hypertension", "Lisinopril"},
  {"4A0039EBC159", "vinodh", 28, "22/02/2023", "Asthma", "Albuterol"}
};

void setup() {
  Serial.begin(9600);
  sensors.begin();
  em18.begin(9600);
  lcd.begin(16, 2);
  pinMode(PULSE_PIN, INPUT);
  pinMode(buzzer,OUTPUT);
  lcd.print("SMART_HSPTL");
  lcd.setCursor(0,1);
  lcd.print("MNGMNT_SYS");
  digitalWrite(buzzer,HIGH);delay(1000);digitalWrite(buzzer,LOW);
  delay(1000);
}

void loop() {
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  int pulseValue = analogRead(PULSE_PIN);

  if (em18.available()) {
    String cardID = em18.readString();
    em18.flush();

    for (int i = 0; i < 3; i++) {
      if (cardID == patients[i].id) {
        lcd.clear();
        lcd.print(patients[i].name);
        lcd.setCursor(0, 1);
        lcd.print("Age: ");
        lcd.print(patients[i].age);
        Serial.print("Patient Name: ");
        Serial.println(patients[i].name);
        Serial.print("Age: ");delay(1000);
        Serial.println(patients[i].age);lcd.clear();
        Serial.print("Join Date: ");
        lcd.print("Join Date: ");
        Serial.println(patients[i].joinDate);
        lcd.print(patients[i].joinDate);
        Serial.print("Disease: ");lcd.setCursor(0,1);
        lcd.print("Disease: ");delay(1000);
        Serial.println(patients[i].disease);
        lcd.print(patients[i].disease);delay(1000);
        Serial.println("Medicine: ");
        lcd.print("Medicine: ");delay(1000);
        Serial.println(patients[i].medicine);
        lcd.print(patients[i].medicine);
        delay(3000);
      }
    }
  }

  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print((char)223); // Degree symbol
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Pulse: ");
  lcd.print(pulseValue);
  delay(1000);
  lcd.clear();
}
