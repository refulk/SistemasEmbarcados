const int ledPin1 = 13;
const int ledPin2 = 12;
const int ledPin3 = 11;
const int Botao1 = 2;
const int Botao2 = 3;
const int Botao3 = 4;
const int Buzzer = 10; //O buzzer está colocado no pino 10
int EstadoBotao1 = 0;
int EstadoBotao2 = 0;
int EstadoBotao3 = 0;
int Senha = 0; // 1 1 3 2
int Seq = 0;
int qtd = 0;
int Tom = 0; //Variavel para armazenar a nota musical
void setup() {
pinMode(Buzzer, OUTPUT);
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

if(EstadoBotao1 || EstadoBotao2 || EstadoBotao3)// pressionou algum botão
{
  delay(200);
    if(EstadoBotao1 && !EstadoBotao2 && !EstadoBotao3 && Seq == 0 && qtd == 0)// BTN1
    {
      Seq = 1;
      qtd = 1;
      Serial.println("1");
    }
    else
    {
      if(EstadoBotao1 && !EstadoBotao2 && !EstadoBotao3 && Seq == 1 && qtd == 1)//BTN1
      {
        Seq = 2;
        qtd = 2;
        Serial.println("2");
      }
      else
      {
        if(EstadoBotao3 && !EstadoBotao2 && !EstadoBotao1 && Seq == 2 && qtd == 2)//BTN3
        {
          Seq = 3;
          qtd = 3;
          Serial.println("3");
        }
        else
        {
          if(EstadoBotao2 && !EstadoBotao1 && !EstadoBotao3 && Seq == 3 && qtd == 3) //BTN2
          {
            Seq = 4;
            qtd = 4;
            Serial.println("4");
          }
          else
          {
              if(qtd == 3) //Senha incorreta
              {
                  Serial.println("6 - Errou, reiniciando");
                  digitalWrite(ledPin1, HIGH);
                  delay(500);
                  digitalWrite(ledPin1, LOW);
                  delay(500);
                  digitalWrite(ledPin1, HIGH);
                  delay(500);
                  digitalWrite(ledPin1, LOW);
                  qtd = 0;
                  Seq = 0;
              }
              else
              {//errou o botao atual
                qtd++;
                Serial.println("7");
              }
            
          }
        }
      }
    }
    if(Seq == 4 && qtd == 4) //Senha correta
    {

          digitalWrite(ledPin1, HIGH);
          digitalWrite(ledPin2, HIGH);
          digitalWrite(ledPin3, HIGH);
          digitalWrite(Buzzer, HIGH); // Liga buzzer
          delay(500);
          digitalWrite(ledPin1, LOW);
          digitalWrite(ledPin2, LOW);
          digitalWrite(ledPin3, LOW);
          digitalWrite(Buzzer, LOW); // Desliga buzzer
          delay(500);
          digitalWrite(ledPin1, HIGH);
          digitalWrite(ledPin2, HIGH);
          digitalWrite(ledPin3, HIGH);
          delay(500);
          digitalWrite(ledPin1, LOW);
          digitalWrite(ledPin2, LOW);
          digitalWrite(ledPin3, LOW);
          delay(500);
          digitalWrite(ledPin1, HIGH);
          digitalWrite(ledPin2, HIGH);
          digitalWrite(ledPin3, HIGH);
          delay(500);
          digitalWrite(ledPin1, LOW);
          digitalWrite(ledPin2, LOW);
          digitalWrite(ledPin3, LOW);
          qtd = 0;
          Seq = 0;
          Serial.println("5");
    }

}

}
