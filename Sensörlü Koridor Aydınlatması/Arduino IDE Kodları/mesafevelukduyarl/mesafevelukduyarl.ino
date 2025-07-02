// Pin tanımlamaları 
const int ldrPin = A0;        // LDR bağlı analog pin
const int ledPin = 6;         // LED bağlı PWM pin
const int trigPin = 9;        // Arduino'dan sensöre giden çıkış sinyali pini
const int echoPin = 10;       // Sensörden Arduino'ya gelen veri pini
long duration;                // Echo pinindeki HIGH sinyal süresini saklar
int distance;                 // Hesaplanan mesafe değerini saklar

void setup() {
  pinMode(ledPin, OUTPUT);    // LED çıkış pini
  pinMode(trigPin, OUTPUT);   // sinyal çıkış pini
  pinMode(echoPin, INPUT);    // sinyal giriş pini
  Serial.begin(9600);         // Seri haberleşme başlat
}

void loop() {
  int ldrValue = analogRead(ldrPin);    // LDR değerini oku
  Serial.print("LDR Değeri: ");
  Serial.println(ldrValue);             // Seri monitöre yaz

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // cm cinsinden mesafe
  Serial.print("Mesafe: ");
  Serial.print(distance);             // Seri monitöre yaz
  Serial.println(" cm");

  int ledBrightness = map(ldrValue, 0, 500, 255, 0);
  int distanceBrightness = map(distance, 0, 200, 255, 0);

  if (ldrValue > 500 || distance>200) { //Ldr 500 lux üzerinde veya ultrasonic sensör 200cm'den uzak bir uzaklıkta cisim göremezse if içerisine gir.
    digitalWrite(ledPin, LOW);         // LED kapat.
  } else {                             // 500 lux altında veya 200cm den daha yakında bir cisim görür ise LED yak.
    int averageBrightness=(ledBrightness + distanceBrightness)/2; //mesafe ve lux değer ortalaması alınır.
    analogWrite(ledPin, averageBrightness);   //ortalama değere göre LED lux değeri ayarlanır ve yakılır. Karanlığa göre led lux değeri ayarlanmış olur.
    delay(5000);}                      //5sn led yanık kalsın
  delay(100);   // Okuma arası kısa bekleme
}
