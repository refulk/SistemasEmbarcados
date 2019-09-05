const int ledPin1 = 13;
const int ledPin2 = 12;
const int ledPin3 = 11;
const int Botao1 = 2;
const int Botao2 = 3;
const int Botao3 = 4;
int EstadoBotao1 = 0;
int EstadoBotao2 = 0;
int EstadoBotao3 = 0;
int cont = 0;
void setup(){
pinMode(ledPin1, OUTPUT);
pinMode(Botao1, INPUT);
pinMode(ledPin2, OUTPUT);
pinMode(Botao2, INPUT);
pinMode(ledPin3, OUTPUT);
pinMode(Botao3, INPUT);
Serial.begin(9600);  // initialize serial communication.
}
void loop(){
EstadoBotao1 = digitalRead(Botao1);
EstadoBotao2 = digitalRead(Botao2);
EstadoBotao3 = digitalRead(Botao3);

if (EstadoBotao1 == HIGH){

}

if (EstadoBotao1 == HIGH || EstadoBotao2 == HIGH){
cont++;
Serial.println(cont);
delay(200);
}

if(cont % 2 == 0)
{
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin2, LOW);
}
else
{
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, LOW);
}

if(EstadoBotao3 == HIGH)
{
  cont = 0;
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin1, HIGH);
  delay(500);
  digitalWrite(ledPin1, LOW);
  delay(500);
  digitalWrite(ledPin1, HIGH);
  delay(500);
  digitalWrite(ledPin1, LOW);
}
}
