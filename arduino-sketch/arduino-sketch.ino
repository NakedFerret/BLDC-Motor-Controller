unsigned long startTime;
unsigned long currentTime;
int sensor0Value;
int count;


// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// the setup routine runs once when you press reset:
void setup() {
  // set prescale to 16
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
  
  Serial.begin(250000);
  startTime = 0;
  waitForSignal();
}

// the loop routine runs over and over again forever:
void loop() {
  // TODO: what happens when micros() overflows?
  if(count < 100) {
    currentTime = micros();
    sensor0Value = analogRead(A0);
    Serial.println(String(currentTime) + ", " + String(sensor0Value));
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
  count = 0;
  Serial.println(startTime);

}

