
const int LM35 = 0;  // label que define o pino ADC usado.
float temperatura = 0; // inicializa a variável usada para armazenar o valor de temperatura
int ADClido = 0;  // inicializa a variável usada para armazenar o valor convertido pelo ADC
const int ledPin1 = 8;
const int ledPin2 = 9;
const int ledPin3 = 10;
const int ledPin4 = 11;
const int ledPin5 = 12;
const int ledPin6 = 13;
int tempInt = 0;
int numBin[6];
int flag = 0;
int flagAnt = 0;
int qtd = 0;

void setup(){
  Serial.begin(9600);
  analogReference(INTERNAL1V1); // Se estiver usando Arduino Mega, use INTERNAL
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);
}
void loop(){
  
    
  ADClido = analogRead(LM35); // converte e armaneza valores entre 0 e 1023.
  temperatura = ADClido * 0.1075268817;  // define o valor de temperatura para o valor convertido

    
      Serial.print("Temperatura = ");
      Serial.print(temperatura);
      Serial.print(" *C = ");
      //tempInt = (int) (temperatura+0.5);
      tempInt = (int) (temperatura);
      Serial.print(tempInt);
      Serial.println(" *C");

      numBin[0] = tempInt >> 0 & 1;
      numBin[1] = tempInt >> 1 & 1;
      numBin[2] = tempInt >> 2 & 1;
      numBin[3] = tempInt >> 3 & 1;
      numBin[4] = tempInt >> 4 & 1;
      numBin[5] = tempInt >> 5 & 1;
        
      Serial.print(numBin[5]); 
      Serial.print(numBin[4]); 
      Serial.print(numBin[3]);
      Serial.print(numBin[2]);
      Serial.print(numBin[1]);
      Serial.println(numBin[0]);
      digitalWrite(ledPin1, numBin[0]);
      digitalWrite(ledPin2, numBin[1]);
      digitalWrite(ledPin3, numBin[2]);
      digitalWrite(ledPin4, numBin[3]);
      digitalWrite(ledPin5, numBin[4]);
      digitalWrite(ledPin6, numBin[5]);
      
      delay(1000);
      flagAnt = flag;
      flag = 0;
      if(tempInt>= 28)
      {
        flag = 1;
        if(flagAnt == 0)
        {
          qtd++;
        }
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);
      digitalWrite(ledPin5, LOW);
      digitalWrite(ledPin6, LOW);      
      }
      
      Serial.print("Quantidade: ");
      Serial.println(qtd);
      Serial.println("");
      
        
  
  delay(500);
}


