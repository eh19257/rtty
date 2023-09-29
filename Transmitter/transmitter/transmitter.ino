void setup() {
  Serial.begin(9600);
  
  pinMode(12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(12, HIGH);
  Serial.println("HIGH");
  delay(1000);
  digitalWrite(12, LOW);
  Serial.println("LOW");
  delay(1000);
}
