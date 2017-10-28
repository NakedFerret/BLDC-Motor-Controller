unsigned long startTime;
unsigned long currentTime;
unsigned long timeBefore; 
int count;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(250000);
  startTime = 0;
  waitForSignal();
}

// the loop routine runs over and over again forever:
void loop() {
  // TODO: what happens when micros() overflows?
  if(count < 100) {
    currentTime = micros();
    Serial.println(currentTime - timeBefore);
    timeBefore =  currentTime;
    count++;
  } else {
    waitForSignal();
  }
}

void waitForSignal() {
  while(Serial.available() <= 0) {
    Serial.println('A');
    delay(300);
  }

  // Clear buffer of all input
  int available = Serial.available();
  for(int i = 0; i < available; i++) {
    Serial.read();
  }

  // Setup state
  startTime = micros();
  timeBefore = startTime;
  count = 0;
}

