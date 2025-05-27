#define potPin 9
#define ledPin 10

int potRawMin = 4;
int potRawMax = 1018;


void setup() {
  // put your setup code here, to run once:
  pinMode(potPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(ledPin, readPot());
}

uint8_t readPot() {
  int potValue = analogRead(potPin);
  potValue = map(potValue, potRawMin, potRawMax, 0, 255);
  potValue = constrain(potValue, 0, 255);
  Serial.println(potValue);
  return potValue;
}