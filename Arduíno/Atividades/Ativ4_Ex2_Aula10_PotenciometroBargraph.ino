const int LM35 = 0;
float temperatura = 0;
int PotLido = 0;
float Tensao = 0;
const int LED[] = {2,3,4,5,6,7,8,9,10,11};

const int PinoPotenciometro = A1;

int Tmax = 5;

int tempo = 0;



void setup()
{
  analogReference(INTERNAL1V1); 
  for(int x = 0; x < 10; x++)
  {
    pinMode(LED[x], OUTPUT);
    Serial.begin(9600);  
  }
}
void loop()
{
  PotLido = analogRead(PinoPotenciometro);
  Tensao = ( (float) (5*PotLido) / (float) 1023);
  //temperatura = ADClido * 0.1075268817204301; //no Leonardo use 0.4887585532
  if(tempo == 100)
  {
    Serial.print(PotLido);
    Serial.print(" Ohms - ");
    Serial.print(Tensao);
    Serial.print(" V = ");
    Serial.print((float) (Tensao*100)/ (float) 5);
    Serial.println("%");
    Serial.println("");
    tempo = 0;
  }
  
/*
  for(int x = 0; x < 10; x++)
  {
    digitalWrite(LED[x], LOW); 
  }
 */ 
  delay(10);  

  tempo++;
  
  if(Tensao >= (float) 0.1* Tmax){
  digitalWrite(LED[0], HIGH);
  }
  else{
  digitalWrite(LED[0], LOW);
  }
  if(Tensao >= (float) 0.2* Tmax){
  digitalWrite(LED[1], HIGH);
  }
  else{
  digitalWrite(LED[1], LOW);
  }
  if(Tensao >= (float) 0.3* Tmax){
  digitalWrite(LED[2], HIGH);
  }
  else{
  digitalWrite(LED[2], LOW);
  }
  if(Tensao >= (float) 0.4* Tmax){
  digitalWrite(LED[3], HIGH);
  }
  else{
  digitalWrite(LED[3], LOW);
  }
  if(Tensao >= (float) 0.5* Tmax){
  digitalWrite(LED[4], HIGH);
  }
  else{
  digitalWrite(LED[4], LOW);
  }
  if(Tensao >= (float) 0.6* Tmax){
  digitalWrite(LED[5], HIGH);
  }
  else{
  digitalWrite(LED[5], LOW);
  }
  if(Tensao >= (float) 0.7* Tmax){
  digitalWrite(LED[6], HIGH);
  }
  else{
  digitalWrite(LED[6], LOW);
  }
  if(Tensao >= (float) 0.8* Tmax){
  digitalWrite(LED[7], HIGH);
  }
  else{
  digitalWrite(LED[7], LOW);
  }
  if(Tensao >= (float) 0.9* Tmax){
  digitalWrite(LED[8], HIGH);
  }
  else{
  digitalWrite(LED[8], LOW);
  }
  if(Tensao >= (float) Tmax){
  digitalWrite(LED[9], HIGH);
  }
  else{
  digitalWrite(LED[9], LOW);
  }

}
