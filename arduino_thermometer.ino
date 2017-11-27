int sensorPin = A0; // select the input pin for the potentiometer
int sensorValue = 0; // variable to store the value coming from the sensor
const byte latchPin = 6;
const byte clockPin = 7;
const byte dataPin  = 5;

float i = 0;
float fixtemp = 20.;
int fixInput = 560;
float fixedDegreeValue = 5.5;
const int  countIndicator = 3;
byte arrayNumber[] = {0b11000000, 0b11111001, 0b10100100,
                      0b10110000, 0b10011001, 0b10010010,
                      0b10000010, 0b11111000, 0b10000000,
                      0b10010000
                     };

void echoNumber(int number, int indicatorCount = 1, int point = 0) {
  digitalWrite(latchPin, LOW);
  for (int i = indicatorCount; i > 0; i--) {
    byte pointByte = 0b0;
    if (point > 0 && (point - 1) == (indicatorCount - i)) {
      pointByte = 0b10000000;
    }
    shiftOut(dataPin, clockPin, MSBFIRST, arrayNumber[number % 10] - pointByte);
    number /= 10;
  }
  digitalWrite(latchPin, HIGH);
}

int countRank(float number) {
  int intNumber = number;
  int rank = 0;
  while (intNumber % 10 > 0 || intNumber / 10 > 0) {
    intNumber /= 10;
    rank++;
  }
  return rank;
}

void echoNumber(float number, int indicatorCount = 1) {
  int point = indicatorCount - countRank(number);
  echoNumber((int)((float)pow(10, point) * number), indicatorCount, point);
}

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  i =  fixInput - sensorValue;
  i = i / fixedDegreeValue;
  echoNumber(fixtemp + i, countIndicator);
  delay(500);
}
