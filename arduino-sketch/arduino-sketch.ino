unsigned long startTime;
unsigned long sensor1Time;
int sensor1Value;

char buffer[20] = {0};


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(19200);
  startTime = 0;
  waitForSignal();
}

// the loop routine runs over and over again forever:
void loop() {
  // TODO: what happens when micros() overflows?
  if(micros() - startTime < 1000000) {
    sensor1Value = analogRead(A0);
    sensor1Time = micros();
    Serial.println("1," + String(sensor1Time) + ',' + String(sensor1Value));
  } else {
    startTime = 0;
    waitForSignal();
  }
}

void waitForSignal() {
  while(Serial.available() <= 0) {
    Serial.println('A');
    delay(300);
  }
  int available = Serial.available();
  for(int i = 0; i < available; i++) {
    Serial.read();
  }
  startTime = micros();   
}

