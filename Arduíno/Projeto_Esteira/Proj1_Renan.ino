
#include <LiquidCrystal.h>
LiquidCrystal lcd(52, 51, 50, 49, 48, 47); //LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int pulsosPorSegundo = 0;
volatile int contPulsos = 0;
int pwm = 0;
int potMotor = 140;
int qtdVelocidade = 0;
float velEscolhida = 5;
float voltasPorSegundo = 0;
float velocidadeLinear = 0;
float velocidadeMotor = 0;
float velocidadeSoma = 0;
float velocidadeMedia = 0;

float velMax = 9.0;
float velMin = 4.0;
float velIntervalo = 0;  //bargraph

float distanciaTotal = 0;
float caloriasTotais = 0;
float tempoTotal = 0;

const int qtdMedia = 10;
float velocidade[qtdMedia];

int flagEncoder = 1;
int flagBotao[5] = {1, 1, 1, 1, 1};
int flagTeste = 0;
int flagLigado = 0;
int flagInicio = 0;
int flagTela = 0;
int flagBuz = 0;
int flagPosDisplay = 0;

int EstadoEncoder = 0;
int EstadoBotao[5] = {0, 0, 0, 0, 0};

long millisBase = 0;
long millisVel = 0;
long millisBounce[5] = {0, 0, 0, 0, 0};
long millisMotor = 0;
long millisExibir = 0;
long millisBuz = 0;
long millisBargraph = 0;

int tempoExibirM = 0;
int tempoExibirS = 0;
long tempoLigou = 0;

const int encoderIn = 2;
const int Botao[5] = {13, 12, 11, 10, 9};
const int motorPWM = 3;
const float raioMotor = 2.5; //centimetros
const float pi = 3.14159265359;
const int Buzzer = 44;
const int BARGRAPH[] = {40, 38, 36, 34, 32, 30, 28, 26, 24, 22, 20};

void interrupcao() // Cada pulso do sensor laser de encoder gera uma interrupcao
{
  EstadoEncoder = digitalRead(encoderIn);

  if (EstadoEncoder == 1 && flagEncoder == 0)
  {

    contPulsos++;

  }
  flagEncoder = EstadoEncoder;

}

void setup()
{
  Serial.begin(9600);  // Esta função "setup" roda uma vez quando a placa e ligada ou resetada
  attachInterrupt(digitalPinToInterrupt(2), interrupcao, CHANGE);  // Configurando a interrupção externa

  pinMode(encoderIn, INPUT);
  pinMode(motorPWM, OUTPUT);
  pinMode(Botao[0], INPUT);
  pinMode(Botao[1], INPUT);
  pinMode(Botao[2], INPUT);
  pinMode(Botao[3], INPUT);
  pinMode(Botao[4], INPUT);
  pinMode(Buzzer, OUTPUT);
  velocidadeLinear = 0;

  for (int i = 0; i < 5; i++)
  {
    velocidade[i] = 0;
  }


  for (int i = 0; i < 10; i++)
  {
    pinMode(BARGRAPH[i], OUTPUT);
    Serial.begin(9600);
  }

  lcd.begin(16, 2);  // Define o número de colunas e linhas do display LCD usado
  
}

void bargraphControle()
{

  if ((millis() - millisBargraph) >= 500)
  {
    millisBargraph = millis();

    velIntervalo = (velMax - velMin) / 10;
    for (int i = 0; i <= 9; i++)
    {
      if ((velMin + (velIntervalo * i) ) <= velocidadeLinear)
      {
        digitalWrite(BARGRAPH[i], HIGH);
      }
      else
      {
        digitalWrite(BARGRAPH[i], LOW);
      }
    }
  }
}

void regulaMotor()
{
  if ((millisBase - millisMotor) >= 600)
  {
    millisMotor = millisBase;
    // regula PWM de acordo com a velocidade media
    velocidadeMotor = velocidadeMedia;
    if (velocidadeMedia > velEscolhida)
    {
      if (potMotor > 100)
      {
        if ((velocidadeMedia - velEscolhida) > 2 && potMotor > 10)
          potMotor -= 5;
        else
        {
          //if (velocidadeLinear > velEscolhida)
          potMotor--;
        }
      }
    }
    else
    {
      if (potMotor < 255)
      {
        if ((velEscolhida - velocidadeMedia) > 2 && potMotor < 245)
          potMotor += 5;
        else
        {
          //if (velocidadeLinear < velEscolhida)
          potMotor++;
        }
      }
    }
    Serial.print("Vel média = ");
    Serial.println((float)(velocidadeMedia));
    //Serial.print("POT = ");
    //Serial.println(velocidadeLinear);
    Serial.print("PWM = ");
    Serial.println(pwm);
    //Serial.print("Tempo = ");
    //Serial.println(tempoTotal);
    Serial.println("");
  }
}

void calcular()
{
  if ((millisBase - millisVel) >= 100) // Calcula velocidade momentanea, média
  {
    millisVel = millisBase;
    pulsosPorSegundo = contPulsos;
    contPulsos = 0;
    voltasPorSegundo = ((float) pulsosPorSegundo / (float) 60) * (float) 10;
    velocidadeLinear = (voltasPorSegundo * 2 * pi * raioMotor) * (3.6 / 100.0);

    velocidadeSoma = 0;//
    for (int i = 0; i < (qtdMedia - 1); i++)
    {
      velocidade[i] = velocidade[i + 1];
      //Serial.println(velocidade[i]);//
      velocidadeSoma += velocidade[i]; //
    }
    //Serial.println();
    velocidade[qtdMedia - 1] = velocidadeLinear;

    velocidadeSoma += velocidadeLinear; //

    //velocidadeSoma += velocidadeLinear;
    if (qtdVelocidade < qtdMedia)
    {
      qtdVelocidade++;
    }
    velocidadeMedia = (velocidadeSoma / (float) qtdVelocidade);

    tempoTotal += 0.1;
    distanciaTotal += ((velocidadeLinear) / 36.0); // em metros.
    caloriasTotais =  (tempoTotal / 3600.0) * (70.0) * ((3.6 * distanciaTotal) / (tempoTotal)); // 1h   70kg   10km/h   ->   1h x 70kg x 10km/h   =   700kcal
  }
}

void ligar()
{
  digitalWrite(Buzzer, HIGH);
  delay(500);
  digitalWrite(Buzzer, LOW);
  delay(500);
  digitalWrite(Buzzer, HIGH);
  delay(500);
  digitalWrite(Buzzer, LOW);
  flagInicio = 1;
  tempoLigou = millis();
}

void desligar()
{
  flagBotao[4] = 1;
  analogWrite(motorPWM, 0);
  lcd.clear();

  for (int i = 0; i < 5; i++)
  {
    velocidade[i] = 0;
  }


  pulsosPorSegundo = 0;
  contPulsos = 0;
  pwm = 0;
  potMotor = 140;
  qtdVelocidade = 0;
  velEscolhida = 5;
  voltasPorSegundo = 0;
  velocidadeLinear = 0;
  velocidadeSoma = 0;
  velocidadeMedia = 0;

  distanciaTotal = 0;
  caloriasTotais = 0;
  tempoTotal = 0;

  flagEncoder = 1;
  flagTeste = 0;
  flagLigado = 0;//
  flagInicio = 0;//
  flagTela = 0;
  flagBuz = 0;//

  EstadoEncoder = 0;

  for (int i = 0; i <= 9; i++)
  {
    digitalWrite(BARGRAPH[i], LOW);
  }
}

void telaVelocidade()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vel real: ");
  lcd.setCursor(10, 0);
  lcd.print(velocidadeLinear);
  lcd.setCursor(0, 1);
  lcd.print("Desejada: ");
  lcd.setCursor(10, 1);
  lcd.print(velEscolhida);
}

void telaTempo()
{
  tempoExibirS = (int)((int)tempoTotal % 60);  //em segundos
  tempoExibirM = (int)(tempoTotal - tempoExibirS) / 60;  //em segundos
  if (tempoExibirM < 10)
  {
    flagPosDisplay = 1;
  }
  else if (tempoExibirM < 100)
  {
    flagPosDisplay = 2;
  }
  else if (tempoExibirM < 1000)
  {
    flagPosDisplay = 3;
  }
  else
  {
    flagPosDisplay = 4;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tempo Total: ");
  lcd.setCursor(0, 1);
  lcd.print(tempoExibirM);
  lcd.setCursor(flagPosDisplay, 1);
  lcd.print(":");
  lcd.setCursor((flagPosDisplay + 1), 1);
  lcd.print(tempoExibirS);
  lcd.setCursor(9, 1);
}

void loop()
{
  millisBase = millis();
  EstadoBotao[0] = digitalRead(Botao[0]);
  EstadoBotao[1] = digitalRead(Botao[1]);
  EstadoBotao[2] = digitalRead(Botao[2]);
  EstadoBotao[3] = digitalRead(Botao[3]);
  EstadoBotao[4] = digitalRead(Botao[4]);

  if (flagLigado == 1)
  {
    //Ligado
    if (flagInicio == 0)
    {
      ligar();
    }
    pwm = map(potMotor, 0, 255, 0, 255);
    analogWrite(motorPWM, pwm);
    if (EstadoBotao[0] == 1 || EstadoBotao[1] == 1 || EstadoBotao[2] == 1 || EstadoBotao[3] == 1 || EstadoBotao[4] == 1)
    {
      if ((millisBase - millisBounce[0]) >= 250)
      {
        millisBounce[0] = millisBase;
        if (EstadoBotao[0] == 1 && velEscolhida < velMax)
        {
          velEscolhida += 0.5;
        }
        if (EstadoBotao[1] == 1 && velEscolhida > velMin)
        {
          velEscolhida -= 0.5;
        }
        if (EstadoBotao[3] == 1) // Mudar tela
        {
          if (flagBotao[3] == 0)
          {
            flagBotao[3] = 1;
            flagTela++;
            if (flagTela >= 4)
              flagTela -= 4;
          }
        }
        else
        {

        }
        if (EstadoBotao[4] == 1) // Desligar
        {
          if (flagBotao[4] == 0)
          {
            desligar();
          }
        }
      }

    }
    else
    {
      if (EstadoBotao[4] == 0)
        flagBotao[4] = 0;
      if (EstadoBotao[3] == 0)
        flagBotao[3] = 0;
    }

    calcular();
    regulaMotor();
    bargraphControle();

    if ((millisBase - millisExibir) >= 750 && flagTeste == 0)  //exibe no display
    {
      millisExibir = millisBase;
      if (EstadoBotao[2] == 1)
      {
        if (flagTela == 0)
        {
          telaTempo();
        }
        if (flagTela == 3)
        {
          telaVelocidade();
        }

      }
      else
      {
        if (flagTela == 0)
        {
          telaVelocidade();
        }
        if (flagTela == 1)
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Distancia Total: ");
          lcd.setCursor(0, 1);
          lcd.print(distanciaTotal);
          lcd.setCursor(10, 1);
          lcd.print("metros");
        }
        if (flagTela == 2)
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Calorias Totais: ");
          lcd.setCursor(0, 1);
          lcd.print(caloriasTotais);
          lcd.setCursor(10, 1);
          lcd.print("Kcal");
        }
        if (flagTela == 3)
        {
          telaTempo();
        }
      }

    }
  }
  else
  {
    //Desligado
    flagInicio = 0;
    if ((EstadoBotao[4] == 1))
    {
      if (flagBotao[4] == 0 && (millisBase - millisBounce[0]) >= 150)
      {
        millisBounce[0] = millisBase;
        flagBotao[4] = 1;
        flagLigado = 1;
      }
    }
    else
    {
      flagBotao[4] = 0;
    }
  }

}
