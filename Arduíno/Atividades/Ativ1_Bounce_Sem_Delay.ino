const int  buttonPin = 2;  // the pin that the pushbutton is attached to
const int ledPin = 13;  // the pin that the LED is attached to

uint32_t contAtual = 0;
uint32_t contTotal = 0;

int buttonPushCounter = 0;  // counter for the number of button presses
int buttonState = 0;  // current state of the button
int lastButtonState = 0;  // previous state of the button
int cont = 0;

void setup() {
pinMode(buttonPin, INPUT); // initialize the button pin as a input.
pinMode(ledPin, OUTPUT); // initialize the LED as an output.
Serial.begin(9600); // initialize serial communication.
}

void loop() {
buttonState = digitalRead(buttonPin); // read the pushbutton input pin.
if (buttonState != lastButtonState) { // if the state has changed, increment the counter
if (buttonState == HIGH) { // if the current state is HIGH then the button went from off to on.

contTotal = millis();
if((contTotal - contAtual) >= 200)
{
  contAtual = contTotal;
  buttonPushCounter++;
  Serial.print("number of button pushes: ");
  Serial.println(buttonPushCounter); // Delay a little bit to avoid bouncing
  if (buttonPushCounter % 4 == 0) { // turns on the LED every four button pushes by checking the modulo of the button push counter.
  digitalWrite(ledPin, HIGH); Serial.println("Led on");
  } else {
  digitalWrite(ledPin, LOW); Serial.println("Led off");
  }
}

}}
lastButtonState = buttonState; // save the current state as the last state, for next time through the loop
}

