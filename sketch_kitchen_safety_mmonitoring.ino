#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11

#define LEDPIN 4
#define MQ2PIN A0
#define BUZZERPIN 2

#define HUMIDITY_THRESHOLD 90
#define GAS_THRESHOLD 445

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  dht.begin();

  pinMode(LEDPIN, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);

  digitalWrite(LEDPIN, LOW);
  digitalWrite(BUZZERPIN, LOW);

  Serial.println("Kitchen Safety Monitoring Started");
}

void loop() {

  // =========================
  // DHT11
  // =========================

  float humidity = dht.readHumidity();
  
  if (isnan(humidity)) {
    Serial.println("DHT11 ERROR!");
  }
  else {

    Serial.print("Humidity: ");
    Serial.println(humidity);

    if (humidity > HUMIDITY_THRESHOLD) {
      digitalWrite(LEDPIN, HIGH);
      Serial.println("High Humidity -> LED ON");
    }
    else {
      digitalWrite(LEDPIN, LOW);
      Serial.println("Normal Humidity -> LED OFF");
    }
  }


  // =========================
  // MQ-2
  // =========================

  int gasValue = analogRead(MQ2PIN);

  Serial.print("MQ-2 Value: ");
  Serial.println(gasValue);

  if (gasValue > GAS_THRESHOLD) {

    tone(BUZZERPIN, 50);

    Serial.println("GAS/SMOKE DETECTED -> BUZZER ON");
  }
  else {

    noTone(BUZZERPIN);

    Serial.println("No Gas/Smoke -> BUZZER OFF");
  }

  Serial.println("----------------------------");

  delay(2000);
}