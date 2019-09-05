const int LM35 = 0;
float temperatura = 0;
int ADClido = 0;
const int Buzzer = 12;
const int LED[] = {2,3,4,5,6,7,8,9,10,11};
const int PinoTemp = A0;

const int PinoPotenciometro = A1;
unsigned int ValorPot = 0;

int tempBase = 22;


void setup()
{
  analogReference(INTERNAL1V1); 
  pinMode(Buzzer, OUTPUT);
  for(int x = 0; x < 10; x++)
  {
    pinMode(LED[x], OUTPUT);
    Serial.begin(9600);  
  }
}
void loop()
{
  ValorPot = analogRead(PinoPotenciometro);
  
  ADClido = analogRead(PinoTemp);
  temperatura = ADClido * 0.1075268817204301; //no Leonardo use 0.4887585532
  Serial.println(temperatura);
  Serial.println(ValorPot);
  Serial.println("");

  for(int x = 0; x < 10; x++)
  {
    digitalWrite(LED[x], LOW); 
  }
  
  delay(ValorPot);  
  
  if(temperatura >= tempBase){
  digitalWrite(LED[0], HIGH);
  }
  else{
  digitalWrite(LED[0], LOW);
  }
  if(temperatura >= (tempBase + 1)){
  digitalWrite(LED[1], HIGH);
  }
  else{
  digitalWrite(LED[1], LOW);
  }
  if(temperatura >= (tempBase + 2)){
  digitalWrite(LED[2], HIGH);
  }
  else{
  digitalWrite(LED[2], LOW);
  }
  if(temperatura >= (tempBase + 3)){
  digitalWrite(LED[3], HIGH);
  }
  else{
  digitalWrite(LED[3], LOW);
  }
  if(temperatura >= (tempBase + 4)){
  digitalWrite(LED[4], HIGH);
  }
  else{
  digitalWrite(LED[4], LOW);
  }
  if(temperatura >= (tempBase + 5)){
  digitalWrite(LED[5], HIGH);
  }
  else{
  digitalWrite(LED[5], LOW);
  }
  if(temperatura >= (tempBase + 6)){
  digitalWrite(LED[6], HIGH);
  }
  else{
  digitalWrite(LED[6], LOW);
  }
  if(temperatura >= (tempBase + 7)){
  digitalWrite(LED[7], HIGH);
  }
  else{
  digitalWrite(LED[7], LOW);
  }
  if(temperatura >= (tempBase + 8)){
  digitalWrite(LED[8], HIGH);
  }
  else{
  digitalWrite(LED[8], LOW);
  }
  if(temperatura >= (tempBase + 9)){
  digitalWrite(LED[9], HIGH);
  digitalWrite(Buzzer,HIGH);
  }
  else{
  digitalWrite(LED[9], LOW);
  digitalWrite(Buzzer,LOW);
  }
  delay(ValorPot);
}
