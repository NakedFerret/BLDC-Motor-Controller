unsigned long l = 1234567890;
int i = 329;
unsigned char byteArray[10];
unsigned long timeBefore;
unsigned long timeAfter;

// the setup routine runs once when you press reset:
void setup() {  
  Serial.begin(9600);
  waitForSignal();
}

// the loop routine runs over and over again forever:
void loop() {

 byteArray[0] = 't';
 writeLongToByteArray(l, byteArray, 1);
 byteArray[5] = ',';
 byteArray[6] = 'v';
 byteArray[7] = '0';
 writeIntToByteArray(i, byteArray, 8);
 Serial.write(byteArray, 10);
 timeAfter = micros();
 
 delay(300);
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
}

void writeLongToByteArray(unsigned long input, byte a[], int start) {
 a[start] = (int)((input >> 24) & 0xFF);
 a[start + 1] = (int)((input >> 16) & 0xFF);
 a[start + 2] = (int)((input >> 8) & 0XFF);
 a[start + 3] = (int)((input & 0XFF));
}

void writeIntToByteArray(int input, byte a[], int start) {
 a[start] = (int)((input >> 8) & 0XFF);
 a[start + 1] = (int)((input & 0XFF));
}

