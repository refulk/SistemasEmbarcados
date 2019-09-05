
const int LM35 = 0;  // label que define o pino ADC usado.
float temperatura = 0; // inicializa a variável usada para armazenar o valor de temperatura
int ADClido = 0;  // inicializa a variável usada para armazenar o valor convertido pelo ADC
const int ledPin1 = 8;
const int ledPin2 = 9;
const int ledPin3 = 10;
const int ledPin4 = 11;
const int ledPin5 = 12;
const int ledPin6 = 13;
const int Buzzer = 7;
const int Botao1 = 2;
const int Botao2 = 3;
const int Botao3 = 4;
int EstadoBotao1 = 0;
int EstadoBotao2 = 0;
int EstadoBotao3 = 0;
int tempInt = 0;
int numBin[6];
int flag = 0;
int flagAnt = 0;
int qtd = 0;
int temp1 = 0;
int temp2 = 0;
int temp3 = 0;
int temp4 = 0;
int temp5 = 0;
float menorTemp = 999;
float maiorTemp = -999;
float somaTemp = 0;
float media = 0;
int qtdMedido = 0;
float vetTemp[30];
int bt1 = 0;
int bt2 = 0;
int bt3 = 0;

void setup(){
  Serial.begin(9600);
  analogReference(INTERNAL1V1); // Se estiver usando Arduino Mega, use INTERNAL
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Botao1, INPUT);
  pinMode(Botao2, INPUT);
  pinMode(Botao3, INPUT);
  for(int i = 0; i < 30; i++)
  {
    vetTemp[i] = 0;
  }
}
void loop(){
  
      EstadoBotao1 = digitalRead(Botao1);
      EstadoBotao2 = digitalRead(Botao2);
      EstadoBotao3 = digitalRead(Botao3);
      
      ADClido = analogRead(LM35); // converte e armaneza valores entre 0 e 1023.
      temperatura = ADClido * 0.1075268817;  // define o valor de temperatura para o valor convertido

      if(temperatura < menorTemp)
      {
        menorTemp = temperatura;
      }
      
      if(temperatura > maiorTemp)
      {
        maiorTemp = temperatura;
      }

      numBin[0] = tempInt >> 0 & 1;
      numBin[1] = tempInt >> 1 & 1;
      numBin[2] = tempInt >> 2 & 1;
      numBin[3] = tempInt >> 3 & 1;
      numBin[4] = tempInt >> 4 & 1;
      numBin[5] = tempInt >> 5 & 1;        

      if(temp2 >= 10)
      {
        digitalWrite(ledPin1, numBin[0]);
        digitalWrite(ledPin2, numBin[1]);
        digitalWrite(ledPin3, numBin[2]);
        digitalWrite(ledPin4, numBin[3]);
        digitalWrite(ledPin5, numBin[4]);
        digitalWrite(ledPin6, numBin[5]);
        temp2 = 0;
      }
      
      


      if(temp3 == 15)
      {
        Serial.print("Temperatura = ");
        Serial.print(temperatura);
        Serial.print(" *C = ");
        //tempInt = (int) (temperatura+0.5);
        
        Serial.print(tempInt);
        Serial.println(" *C");

        Serial.print(numBin[5]); 
        Serial.print(numBin[4]); 
        Serial.print(numBin[3]);
        Serial.print(numBin[2]);
        Serial.print(numBin[1]);
        Serial.println(numBin[0]);

        //Serial.print("Quantidade: ");
       // Serial.println(qtd);
        Serial.println("");
        temp3 = 0;
      }

      tempInt = (int) (temperatura);
     
      delay(100);
      temp1++;
      temp2++;
      temp3++;
      temp4++;
      temp5++;
      flagAnt = flag;
      flag = 0;

      if(temp4 == 10)
      {
        somaTemp = somaTemp + temperatura;
        somaTemp = somaTemp - vetTemp[0];
        for(int i = 1; i < 30; i++)
        {
          vetTemp[i - 1] = vetTemp[1];
        }
        vetTemp[29] = temperatura;
        if(qtdMedido < 30)
          qtdMedido++;
        temp4 = 0;
      }
      
      if(temperatura>= 26)
      {
        if(temp1 >= 3) // verificar se realmente tem necessidade
        {
          flag = 1;
          if(flagAnt == 0)
          {
            qtd++;
          }

          if(temp1 >= 10)
          {
            digitalWrite(ledPin1, LOW);
            digitalWrite(ledPin2, LOW);
            digitalWrite(ledPin3, LOW);
            digitalWrite(ledPin4, LOW);
            digitalWrite(ledPin5, LOW);
            digitalWrite(ledPin6, LOW); 
            temp1 = 0;
            temp2 = 5;
            
          }  
          
        } 
        digitalWrite(Buzzer, HIGH);
      }
      else
      {
        digitalWrite(Buzzer, LOW);          
      }

      if(EstadoBotao1)
      {        
        if(bt1 == 0)
        {
          Serial.print("Botão 1:  tempMin = ");
          Serial.print(menorTemp);
          Serial.println(" *C");
          Serial.println("");    
          bt1 = 1; 
        }        
      }
      else
      {
        bt1 = 0;
      }
      if(EstadoBotao2)
      {        
        if(bt2 == 0)
        {
          media = (somaTemp / qtdMedido);
          Serial.print("Botão 2:  media = ");
          Serial.println(media); 
          Serial.println("");   
          bt2 = 1; 
        }        
      }
      else
      {
        bt2 = 0;
      }
      if(EstadoBotao3)
      {
        if(bt3 == 0)
        {
          Serial.print("Botão 3:  tempMax = ");
          Serial.print(maiorTemp);
          Serial.println(" *C");      
          Serial.println("");   
          bt3 = 1; 
        }        
      }
      else
      {
        bt3 = 0;
      }
}


