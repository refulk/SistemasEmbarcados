const int PinoPotenciometro = A1;  // Define como uma constante inteira
int ValorPot = 0;
float t = 0;
float tReal = 0;
int pwm = 0;
const int LED[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int tempCont = 0;
int contLed = 0;
int contPWM = 0;
int PWMupdowm = 0;
int LedIdaVolta = 0;


const int Botao1 = 12;
const int Botao2 = 13;
int EstadoBotao1 = 0;
int EstadoBotao2 = 0;
int btn = 0;


int intervaloPWM = 1023;

//float DutyPorc = 0;
//float Tensao = 0;
//const int Led1 = 13;

void setup() {
  pinMode(Botao1, INPUT);
  pinMode(Botao2, INPUT);
  for (int x = 0; x < 10; x++)
  {
    pinMode(LED[x], OUTPUT);
    Serial.begin(9600);
  }
}
void loop() {

  EstadoBotao1 = digitalRead(Botao1);
  EstadoBotao2 = digitalRead(Botao2);

  if (EstadoBotao1 == 1 && btn != 1)
  {
    btn = 1;
    for (int x = 0; x < 10; x++)
    {
      digitalWrite(LED[x], LOW);
    }
    contLed = 0;
    PWMupdowm = 0;
    LedIdaVolta = 0;
  }
  if (EstadoBotao2 == 1 && btn != 2)
  {
    btn = 2;
    for (int x = 0; x < 10; x++)
    {
      digitalWrite(LED[x], LOW);
    }
    contLed = 0;
    PWMupdowm = 0;
    LedIdaVolta = 0;
  }


  ValorPot = analogRead(PinoPotenciometro);
  t = (float) (((1.5 / 1023) * (float) ValorPot) + 0.5) * 2000;
  tReal = (float) t / (float) intervaloPWM;
  //pwm = map(ValorPot, 0, 1023, 0, 255); // Os valores da variável pwm irão variar de 0 a 255, conforme o potenciômetro varia de 0 a 1023.
  //DutyPorc = (float)100 * ((float)pwm/(float)255);
  //Tensao = ( (float) (5*DutyPorc) / (float) 100);
  //analogWrite(Led1, pwm);

  tempCont++;
  delay(tReal);
  if (tempCont == 1023)
  {
    tempCont = 0;
    Serial.print("Potenciometro: ");
    Serial.print(ValorPot);
    Serial.println(" Ohms");
    Serial.print("t: ");
    Serial.print(t);
    Serial.println(" milisegundo(s)");

    /*
      Serial.print("Duty Cycle: ");
      Serial.print(DutyPorc);
      Serial.println(" %");
      Serial.print("Tensão: ");
      Serial.print(Tensao);
      Serial.println(" Volts");
    */
    Serial.println("");
  }



  if (btn == 2)
  {
    if (contLed == 0)
    {
      if (PWMupdowm == 0) //aumentar brilho
      {
        contPWM++;
        if (contPWM == intervaloPWM)
        {
          PWMupdowm = 1;
        }
      }
      else //diminuir brilho
      {
        contPWM--;
        if (contPWM == 0)
        {
          if (LedIdaVolta == 0) //ida
          {
            contLed = 1;
            digitalWrite(LED[0], LOW);
            digitalWrite(LED[2], LOW);
          }
          else
          {
            contLed = 1;
            LedIdaVolta = 0;
            digitalWrite(LED[0], LOW);
            digitalWrite(LED[2], LOW);
          }
          PWMupdowm = 0;
        }
      }
      pwm = map(contPWM, 0, intervaloPWM, 0, 255);
      analogWrite(LED[0], pwm);
      analogWrite(LED[2], pwm);// Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.
    }
    else
    {
      //digitalWrite(LED[0], LOW);
      //digitalWrite(LED[2], LOW);
    }

    if (contLed == 1)
    {
      if (PWMupdowm == 0) //aumentar brilho
      {
        contPWM++;
        if (contPWM == intervaloPWM)
        {
          PWMupdowm = 1;
        }
      }
      else //diminuir brilho
      {
        contPWM--;
        if (contPWM == 0)
        {
          if (LedIdaVolta == 0) //ida
          {
            contLed = 2;
            digitalWrite(LED[2], LOW);
            digitalWrite(LED[4], LOW);
          }
          else //volta
          {
            contLed = 0;
            digitalWrite(LED[2], LOW);
            digitalWrite(LED[4], LOW);
          }
          PWMupdowm = 0;
        }
      }
      pwm = map(contPWM, 0, intervaloPWM, 0, 255);
      analogWrite(LED[2], pwm);
      analogWrite(LED[4], pwm); // Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.
    }
    else
    {
      //digitalWrite(LED[2], LOW);
      //digitalWrite(LED[4], LOW);

    }

    if (contLed == 2)
    {
      if (PWMupdowm == 0) //aumentar brilho
      {
        contPWM++;
        if (contPWM == intervaloPWM)
        {
          PWMupdowm = 1;
        }
      }
      else //diminuir brilho
      {
        contPWM--;
        if (contPWM == 0)
        {
          if (LedIdaVolta == 0) //ida
          {
            contLed = 3;
            digitalWrite(LED[4], LOW);
            digitalWrite(LED[6], LOW);
          }
          else //volta
          {
            contLed = 1;
            digitalWrite(LED[4], LOW);
            digitalWrite(LED[6], LOW);
          }
          PWMupdowm = 0;
        }
      }
      pwm = map(contPWM, 0, intervaloPWM, 0, 255);
      analogWrite(LED[4], pwm);
      analogWrite(LED[6], pwm); // Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.
    }
    else
    {
      //digitalWrite(LED[4], LOW);
      //digitalWrite(LED[6], LOW);
    }

    if (contLed == 3)
    {
      if (PWMupdowm == 0) //aumentar brilho
      {
        contPWM++;
        if (contPWM == intervaloPWM)
        {
          PWMupdowm = 1;
        }
      }
      else //diminuir brilho
      {
        contPWM--;
        if (contPWM == 0)
        {
          if (LedIdaVolta == 0) //ida
          {
            contLed = 4;
            digitalWrite(LED[6], LOW);
            digitalWrite(LED[8], LOW);
          }
          else //volta
          {
            contLed = 2;
            digitalWrite(LED[6], LOW);
            digitalWrite(LED[8], LOW);
          }
          PWMupdowm = 0;
        }
      }
      pwm = map(contPWM, 0, intervaloPWM, 0, 255);
      analogWrite(LED[6], pwm);
      analogWrite(LED[8], pwm); // Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.
    }
    else
    {
      //digitalWrite(LED[6], LOW);
      //digitalWrite(LED[8], LOW);
    }

    if (contLed == 4)
    {
      if (PWMupdowm == 0) //aumentar brilho
      {
        contPWM++;
        if (contPWM == intervaloPWM)
        {
          PWMupdowm = 1;
        }
      }
      else //diminuir brilho
      {
        contPWM--;
        if (contPWM == 0)
        {
          if (LedIdaVolta == 0) //ida
          {
            LedIdaVolta = 1; //volta
            contLed = 3;
            digitalWrite(LED[9], LOW);
          }
          else //volta
          {
            contLed = 3;
            digitalWrite(LED[9], LOW);
          }
          PWMupdowm = 0;
        }
      }
      pwm = map(contPWM, 0, intervaloPWM, 0, 255);
      analogWrite(LED[9], pwm);// Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.
    }
    else
    {
      //digitalWrite(LED[9], LOW);
    }
  }




  if (btn == 1)
  {
    if (contLed == 0)
    {
      if (PWMupdowm == 0) //aumentar brilho
      {
        contPWM++;
        if (contPWM == intervaloPWM)
        {
          PWMupdowm = 1;
        }
      }
      else //diminuir brilho
      {
        contPWM--;
        if (contPWM == 0)
        {
          if (LedIdaVolta == 0) //ida
          {
            contLed = 1;
          }
          else
          {
            contLed = 1;
            LedIdaVolta = 0;
          }
          PWMupdowm = 0;
        }
      }
      pwm = map(contPWM, 0, intervaloPWM, 0, 255);
      analogWrite(LED[0], pwm);
      analogWrite(LED[9], pwm);// Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.
    }
    else
    {
      digitalWrite(LED[0], LOW);
      digitalWrite(LED[9], LOW);
    }

    if (contLed == 1)
    {
      if (PWMupdowm == 0) //aumentar brilho
      {
        contPWM++;
        if (contPWM == intervaloPWM)
        {
          PWMupdowm = 1;
        }
      }
      else //diminuir brilho
      {
        contPWM--;
        if (contPWM == 0)
        {
          if (LedIdaVolta == 0) //ida
          {
            contLed = 2;
          }
          else //volta
          {
            contLed = 0;
          }
          PWMupdowm = 0;
        }
      }
      pwm = map(contPWM, 0, intervaloPWM, 0, 255);
      analogWrite(LED[1], pwm);
      analogWrite(LED[8], pwm); // Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.
    }
    else
    {
      digitalWrite(LED[1], LOW);
      digitalWrite(LED[8], LOW);

    }

    if (contLed == 2)
    {
      if (PWMupdowm == 0) //aumentar brilho
      {
        contPWM++;
        if (contPWM == intervaloPWM)
        {
          PWMupdowm = 1;
        }
      }
      else //diminuir brilho
      {
        contPWM--;
        if (contPWM == 0)
        {
          if (LedIdaVolta == 0) //ida
          {
            contLed = 3;
          }
          else //volta
          {
            contLed = 1;
          }
          PWMupdowm = 0;
        }
      }
      pwm = map(contPWM, 0, intervaloPWM, 0, 255);
      analogWrite(LED[2], pwm);
      analogWrite(LED[7], pwm); // Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.
    }
    else
    {
      digitalWrite(LED[2], LOW);
      digitalWrite(LED[7], LOW);
    }

    if (contLed == 3)
    {
      if (PWMupdowm == 0) //aumentar brilho
      {
        contPWM++;
        if (contPWM == intervaloPWM)
        {
          PWMupdowm = 1;
        }
      }
      else //diminuir brilho
      {
        contPWM--;
        if (contPWM == 0)
        {
          if (LedIdaVolta == 0) //ida
          {
            contLed = 4;
          }
          else //volta
          {
            contLed = 2;
          }
          PWMupdowm = 0;
        }
      }
      pwm = map(contPWM, 0, intervaloPWM, 0, 255);
      analogWrite(LED[3], pwm);
      analogWrite(LED[6], pwm); // Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.
    }
    else
    {
      digitalWrite(LED[3], LOW);
      digitalWrite(LED[6], LOW);
    }

    if (contLed == 4)
    {
      if (PWMupdowm == 0) //aumentar brilho
      {
        contPWM++;
        if (contPWM == intervaloPWM)
        {
          PWMupdowm = 1;
        }
      }
      else //diminuir brilho
      {
        contPWM--;
        if (contPWM == 0)
        {
          if (LedIdaVolta == 0) //ida
          {
            LedIdaVolta = 1; //volta
            contLed = 3;
          }
          else //volta
          {
            contLed = 3;
          }
          PWMupdowm = 0;
        }
      }
      pwm = map(contPWM, 0, intervaloPWM, 0, 255);
      analogWrite(LED[4], pwm);
      analogWrite(LED[5], pwm); // Ativa o pino Led como uma saída PWM. O sinal é definido pelo valor de dyty cycle com período fixo.
    }
    else
    {
      digitalWrite(LED[4], LOW);
      digitalWrite(LED[5], LOW);
    }
  }




}


