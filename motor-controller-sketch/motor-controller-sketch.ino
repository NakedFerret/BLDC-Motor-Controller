// 't' + time: u long - 5 bytes
// ',' + sensor0: int - 3 bytes
// ',' + sensor1: int - 3 bytes
// ',' + sensor2: int - 3 bytes
// ',' + sensor3: int - 3 bytes
// ',' + sensor4: int - 3 bytes
// ',' + sensor5: int - 3 bytes 
// ';'                - 1 byte
unsigned char messageArray[24];
unsigned long currentTime;
int sensor0Value;
int sensor1Value;
int sensor2Value;
int sensor3Value;
int sensor4Value;
int sensor5Value;
int count;
int input;

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
  sbi(ADCSRA,ADPS2);
  cbi(ADCSRA,ADPS1);
  cbi(ADCSRA,ADPS0);

  messageArray[0] = 't';
  // 4 bytes for time
  messageArray[5] = ',';
  // 2 bytes for sensor0
  messageArray[8] = ',';
  // 2 bytes for sensor1
  messageArray[11] = ',';
  // 2 bytes for sensor2
  messageArray[14] = ',';
  // 2 bytes for sensor3
  messageArray[17] = ',';
  // 2 bytes for sensor4
  messageArray[20] = ',';
  // 2 bytes for sensor5
  messageArray[23] = ';';
  
  Serial.begin(500000);
  waitForSignal();
}

// the loop routine runs over and over again forever:
void loop() {
  // TODO: what happens when micros() overflows?
  if(count < 5000) {
    currentTime = micros();
    
    sensor0Value = analogRead(A0);
    sensor1Value = analogRead(A1);
    sensor2Value = analogRead(A2);
    sensor3Value = analogRead(A3);
    sensor4Value = analogRead(A4);
    sensor5Value = analogRead(A5);

    input = pow(sensor0Value / 1024.0, 7) * 255;

    adjustMotorSpeed(input);
    
    writeUnsignedLongToByteArray(currentTime, messageArray, 1);
    writeIntToByteArray(input, messageArray, 6);
    writeIntToByteArray(sensor1Value, messageArray, 9);
    writeIntToByteArray(sensor2Value, messageArray, 12);
    writeIntToByteArray(sensor3Value, messageArray, 15);
    writeIntToByteArray(sensor4Value, messageArray, 18);
    writeIntToByteArray(sensor5Value, messageArray, 21);
    Serial.write(messageArray, 24);
    
    count++;
  } else {
    waitForSignal();
  }
}

void waitForSignal() {
  adjustMotorSpeed(0);
  while(Serial.available() <= 0) {
    Serial.println('A');
    delay(300);
  }

  // Clear buffer of all input
  int available = Serial.available();
  for(int i = 0; i < available; i++) {
    Serial.read();
  }

  count = 0;
}

void adjustMotorSpeed(int input){
  analogWrite(3, input);
}

void writeUnsignedLongToByteArray(unsigned long input, byte a[], int start) {
 a[start] = (int)((input >> 24) & 0xFF);
 a[start + 1] = (int)((input >> 16) & 0xFF);
 a[start + 2] = (int)((input >> 8) & 0XFF);
 a[start + 3] = (int)((input & 0XFF));
}

void writeIntToByteArray(int input, byte a[], int start) {
 a[start] = (int)((input >> 8) & 0XFF);
 a[start + 1] = (int)((input & 0XFF));
}

