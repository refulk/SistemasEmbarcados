const int LDR = 0;
const int LM35 = 1;
const int Buzzer = 2;
const int led[] = {
  5, 6, 7, 8, 9, 10, 11
};
float ValorLDR = 0;
float tensao = 0;
int ADClido = 0;
float temperatura = 0;
int pwm0 = 255;
int pwm1 = 255;
int pwm2 = 255;

int flagBuzzer = 0;
int flagBuzzer2 = 0;
int flagBuzzer3 = 1;
int tempAmbiente = 24;

int millisBase = 0;
int millisLed1 = 0;
int millisExibe = 0;
int millisBuzzer = 0;
int millisLuz1 = 0;

int contExibe = 0;
int contExibe2 = 0;

int tempo1 = 0;
int tempo2 = 0;
int tempo3 = 0;
int tempo4 = 0;
int tempoLed1 = 0;
int tempoLed2 = 0;
int tempoLed3 = 0;

char buf[20];

void setup() {
  Serial.begin(9600);
  for (int x = 0; x < 7 ; x++) {
    pinMode(led[x], OUTPUT);
  }
  pinMode(Buzzer, OUTPUT);
}

int exibe1(char texto[], int tempo)
{
  if (millis() >= tempo + 1000)
  {
    tempo = millis();
    Serial.println(texto);
  }
  return tempo;
}

void loop() {
  millisBase = millis();
  ValorLDR = analogRead(LDR);
  tensao = (float)(ValorLDR*5)/(float)1023;
  //tensao = 99;
  ADClido = analogRead(LM35);
  temperatura = ADClido * 0.4887585532;
  
  if (millisBase >= (millisLed1 + 100))
  {
    millisLed1 = millisBase;
    if ((int) temperatura > tempAmbiente)
    {
      if (pwm0 > 20)
        pwm0 -= 20;
      else if (pwm0 > 0)
        pwm0--;
    }
    else
    {
      if (pwm0 < 235)
        pwm0 += 20;
    }

    if ((int) temperatura > tempAmbiente + 1)
    {
      if (pwm1 > 20)
        pwm1 -= 20;
      else if (pwm1 > 0)
        pwm1--;
    }
    else
    {
      if (pwm1 < 235)
        pwm1 += 20;
    }

    if ((int) temperatura > tempAmbiente + 2)
    {
      if (pwm2 > 20)
        pwm2 -= 20;
      else if (pwm2 > 0)
      {
        pwm2--;
        if (pwm2 == 0)
        {
          flagBuzzer = 1;
        }
      }
    }
    else {
      //tempo1 = exibe1("entrou1", tempo1);
      if (pwm2 < 235)
      {
        //tempo2 = exibe1("entrou2", tempo2);
        pwm2 += 20;

      }
    }
    analogWrite(led[0], pwm0);
    analogWrite(led[1], pwm1);
    analogWrite(led[2], pwm2);
    
    contExibe2++;
    if(contExibe2 >= 10)
    {
      contExibe2= 0;
      Serial.print("Temperatura: ");
      Serial.print((int) temperatura);
      Serial.println(" C");
    }

    if (flagBuzzer == 1)
    {
      millisBuzzer = millisBase;
      //BUZZER APITAR 2 VEZES
      digitalWrite(Buzzer, HIGH);
      delay(700);
      digitalWrite(Buzzer, LOW);
      delay(700);
      digitalWrite(Buzzer, HIGH);
      delay(700);
      digitalWrite(Buzzer, LOW);
      flagBuzzer = 0;
    }
  }

  // LUMINOSIDADE
  if (millisBase >= (millisLuz1 + 100))
  {
    millisLuz1 = millisBase;
    if (ValorLDR > 50)
    {
      digitalWrite(led[3], HIGH);
    }
    else
    {
      digitalWrite(led[3], LOW);
    }

    if (ValorLDR > 100)
    {
      digitalWrite(led[4], HIGH);
    }
    else
    {
      digitalWrite(led[4], LOW);
    }

    if (ValorLDR > 150)
    {
      digitalWrite(led[5], HIGH);
    }
    else
    {
      digitalWrite(led[5], LOW);
    }

    if (ValorLDR > 200)
    {
      digitalWrite(led[6], HIGH);
      if (flagBuzzer3 == 1)
        flagBuzzer2 = 1;
      flagBuzzer3 = 0;
    }
    else
    {
      digitalWrite(led[6], LOW);
      flagBuzzer3 = 1;
    }


    //sprintf(buf, "%d", (int) tensao);
    //tempo4 = exibe1(buf, tempo4);
    contExibe++;
    if(contExibe >= 10)
    {
      contExibe = 0;
      Serial.print("valorLDR: ");
      Serial.println(ValorLDR);
      Serial.print(tensao);
      Serial.println(" V");
      Serial.println("");
    }
    
    tempo1 = exibe1("", tempo1);
    /*
        tempo3 = exibe1("", tempo3);
        sprintf(buf, "%d", (int) temperatura);
        tempo4 = exibe1(buf, tempo4);

        sprintf(buf, "%d", pwm0);
        tempoLed1 = exibe1(buf, tempoLed1);
        sprintf(buf, "%d", pwm1);
        tempoLed2 = exibe1(buf, tempoLed2);
        sprintf(buf, "%d", pwm2);
        tempoLed3 = exibe1(buf, tempoLed3);
    */

    if (flagBuzzer2 == 1)
    {
      //BUZZER APITAR 2 VEZES
      digitalWrite(Buzzer, HIGH);
      delay(700);
      digitalWrite(Buzzer, LOW);
      delay(700);
      digitalWrite(Buzzer, HIGH);
      delay(700);
      digitalWrite(Buzzer, LOW);
      delay(700);
      digitalWrite(Buzzer, HIGH);
      delay(700);
      digitalWrite(Buzzer, LOW);
      flagBuzzer2 = 0;
    }

  }

}
