const int PinoPotenciometro = A1;  // Define como uma constante inteira
int ValorPot = 0;   
int pwm = 0;
const int LED[] = {2,3,4,5,6,7,8,9,10,11};
int tempCont = 0;

float DutyPorc = 0;
float Tensao = 0;
const int Led1 = 13; 

void setup() {
  pinMode(Led1, OUTPUT);
for(int x = 0; x < 10; x++)
  {
    pinMode(LED[x], OUTPUT);
    Serial.begin(9600);  
  }
}
void loop() {
ValorPot = analogRead(PinoPotenciometro);
pwm = map(ValorPot, 0, 1023, 0, 255); // Os valores da variável pwm irão variar de 0 a 255, conforme o potenciômetro varia de 0 a 1023.
DutyPorc = (float)100 * ((float)pwm/(float)255);
Tensao = ( (float) (5*DutyPorc) / (float) 100);
analogWrite(Led1, pwm); 



tempCont++;
delay(10);
if(tempCont == 200)
{
  tempCont = 0;
  Serial.print("Potenciometro: ");
  Serial.print(ValorPot);
  Serial.println(" Ohms");
  Serial.print("Duty Cycle: ");
  Serial.print(DutyPorc);
  Serial.println(" %");
  Serial.print("Tensão: ");
  Serial.print(Tensao);
  Serial.println(" Volts");
  Serial.println("");
}


if(ValorPot >= 0) 
{
  if(ValorPot <= 102)
  {
    pwm = map(ValorPot, 0, 102, 0, 255);
    analogWrite(LED[0], pwm); // Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.

  }

}
else
{
  digitalWrite(LED[0], LOW);  
}

if(ValorPot >= 102) 
{
  if(ValorPot <= 204)
  {
    pwm = map(ValorPot, 102, 204, 0, 255);
    analogWrite(LED[1], pwm); // Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.

  }
  
}
else
{
  digitalWrite(LED[1], LOW);

}

if(ValorPot >= 204)
{
  if(ValorPot <= 306)
  {
    pwm = map(ValorPot, 204, 306, 0, 255);
    analogWrite(LED[2], pwm); // Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.

  }
  
}
else
{
  digitalWrite(LED[2], LOW);
}

if(ValorPot >= 306)
{
   if(ValorPot <= 408)
  {
    pwm = map(ValorPot, 306, 408, 0, 255);
    analogWrite(LED[3], pwm); // Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.

  }
  
}
else
{
  digitalWrite(LED[3], LOW);
}
if(ValorPot >= 408)
{
   if(ValorPot <= 510)
  {
    pwm = map(ValorPot, 408, 510, 0, 255);
    analogWrite(LED[4], pwm); // Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.

  }
  
}
else
{
  digitalWrite(LED[4], LOW);
}
if(ValorPot >= 510)
{
   if(ValorPot <= 612)
  {
    pwm = map(ValorPot, 510, 612, 0, 255);
    analogWrite(LED[5], pwm); // Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.

  }
  
}
else
{
  digitalWrite(LED[5], LOW);
}
if(ValorPot >= 612)
{
   if(ValorPot <= 715)
  {
    pwm = map(ValorPot, 612, 715, 0, 255);
    analogWrite(LED[6], pwm); // Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.

  }
  
}
else
{
  digitalWrite(LED[6], LOW);
}
if(ValorPot >= 715)
{
   if(ValorPot <= 818)
  {
    pwm = map(ValorPot, 715, 818, 0, 255);
    analogWrite(LED[7], pwm); // Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.

  }
  
}
else
{
  digitalWrite(LED[7], LOW);
}
if(ValorPot >= 818)
{
   if(ValorPot <= 921)
  {
    pwm = map(ValorPot, 818, 921, 0, 255);
    analogWrite(LED[8], pwm); // Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.

  }
  
}
else
{
  digitalWrite(LED[8], LOW);
}
if(ValorPot >= 921)
{
   if(ValorPot <= 1023)
  {
    pwm = map(ValorPot, 921, 1023, 0, 255);
    analogWrite(LED[9], pwm); // Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.

  }
  
}
else
{
  digitalWrite(LED[9], LOW);
}
}


