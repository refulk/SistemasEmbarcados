
const int LM35 = 0;  // label que define o pino ADC usado.
float temperatura = 0; // inicializa a variável usada para armazenar o valor de temperatura
int ADClido = 0;  // inicializa a variável usada para armazenar o valor convertido pelo ADC
const int ledPin1 = 8;
const int ledPin2 = 9;
const int ledPin3 = 10;
const int ledPin4 = 11;
const int Botao = 2;
int EstadoBotao = 0;
int controle = 0; // Evita que seja exibido caso botao seja continuamente pressionado
int contadorBotao = 0; // Conta quantidade de vezes que foi exibido
int numBin[4];
int contTempo = 0;
const int Buzzer = 12;
int Buz = 0;

void setup(){
  pinMode(Botao, INPUT);
  Serial.begin(9600);
  analogReference(INTERNAL1V1); // Se estiver usando Arduino Mega, use INTERNAL
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(Buzzer, OUTPUT);
}
void loop(){
  
  EstadoBotao = digitalRead(Botao);
    
  ADClido = analogRead(LM35); // converte e armaneza valores entre 0 e 1023.
  temperatura = ADClido * 0.1075268817;  // define o valor de temperatura para o valor convertido
  
  if(EstadoBotao)
  {
    if(controle != 1)
    {
      Serial.print("Temperatura = ");
      Serial.print(temperatura);
      Serial.println(" *C");
      contadorBotao++;
      if(contadorBotao >= 16)
      {
        contadorBotao = 0;
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
        digitalWrite(ledPin4, LOW);
        delay(500);
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, HIGH);
        digitalWrite(ledPin4, HIGH);
        delay(500);
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
        digitalWrite(ledPin4, LOW);
        delay(500);
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, HIGH);
        digitalWrite(ledPin4, HIGH);
        delay(600);
        
      }
      numBin[0] = contadorBotao >> 0 & 1;
      numBin[1] = contadorBotao >> 1 & 1;
      numBin[2] = contadorBotao >> 2 & 1;
      numBin[3] = contadorBotao >> 3 & 1;/**/
      Serial.print(contadorBotao);   
      Serial.print(" - ");      
      Serial.print(numBin[3]);
      Serial.print(numBin[2]);
      Serial.print(numBin[1]);
      Serial.println(numBin[0]);
      digitalWrite(ledPin1, numBin[0]);
      digitalWrite(ledPin2, numBin[1]);
      digitalWrite(ledPin3, numBin[2]);
      digitalWrite(ledPin4, numBin[3]);
      
    }    
    controle = 1;
  }
  else
  {
    controle = 0;
  }
  contTempo++;
  delay(100);
  if(contTempo >= 50 && temperatura >= 25) // Delay 5 segundos
  {
      digitalWrite(Buzzer, HIGH);  
      Buz = 1;    
      contTempo = 0;
  }
  else
  {
    if(contTempo >= 10 && Buz == 1)
    {
      digitalWrite(Buzzer, LOW);
      Buz = 0;
      contTempo = 0;
    }
  }
}


