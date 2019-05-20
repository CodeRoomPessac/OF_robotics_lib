/*
  Light Reflexion

  Plug Infrared Reflective Component in D2 port
*/
#define PIN_REFLECTIVE_LIGHT 2
#define PIN_BUILTIN LED_BUILTIN


void setup() {
  Serial.begin(9600);
  Serial.println("Reflective Component setup");

  pinMode(PIN_REFLECTIVE_LIGHT, INPUT);
  pinMode(PIN_BUILTIN, OUTPUT);

  for( int i =0; i<3; i++ ) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
}

void loop() {
  int result = digitalRead(PIN_REFLECTIVE_LIGHT);
  Serial.print("Reflective Component value : ");
  Serial.println(result);

  delay(500);
}
