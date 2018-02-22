#include <Stepper.h>

const int ledPin = 8;
const int buttonPin = 10;
const int servoPin = 0;
Stepper stepper(200, 4, 5, 6, 7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  stepper.setSpeed(60);
}

char buffer[255];

int lastButtonState = HIGH;

void rotate() {
  stepper.step(200);
  delay(5000);
  stepper.step(0);
}

void blink() {
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}

int i = 0;
void loop() {
    if(Serial.available() > 0) {
        char c = Serial.read();
        if(c == '\n') {
          buffer[i] = '\0';

          String message(buffer);

          if(message == "BLINK") {
              blink();
          } else if(message == "ROTATE") {
              rotate();
          }
          i = 0;
        } else {
          buffer[i] = c;
          i++;
        }
      }

      int buttonState = digitalRead(buttonPin);
      if(buttonState !=  lastButtonState) {
        if(buttonState == LOW) {
          Serial.println("Message2");
        }
        lastButtonState = buttonState;
      }
}
