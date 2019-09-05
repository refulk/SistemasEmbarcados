const int LDR = 0;
const int Led = 6;
int ValorLido = 0;
int pwm[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int referencial = 30;
int cont = 0;
int flag = 0;
const int LED[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

void setup()
{
  //pinMode(Led, OUTPUT);

  for (int x = 0; x < 10; x++)
  {
    pinMode(LED[x], OUTPUT);
    Serial.begin(9600);
  }
}
void loop()
{
  ValorLido = analogRead(LDR);

  //ValorLido = 1024 - ValorLido;

  Serial.print("Valor lido pelo LDR = ");
  Serial.println(ValorLido);



  if (ValorLido <= referencial)
  {
    if (flag == 0)
    {
      flag = 1;
      digitalWrite(LED[cont], HIGH);
      cont++;
      if (cont >= 10)
      {
        delay(500);
        for (int x = 0; x < 10; x++)
        {
          digitalWrite(LED[x], LOW);
        }
        delay(500);
        for (int x = 0; x < 10; x++)
        {
          digitalWrite(LED[x], HIGH);
        }
        delay(500);
        for (int x = 0; x < 10; x++)
        {
          digitalWrite(LED[x], LOW);
        }
        cont = 0;
      }
    }

  }
  else
  {
    flag = 0;
  }

  delay(100);

}
