/* Enviando dados do PC para o Arduíno.
  Vamos piscar um LED de forma proporcional ao valor recebido a partir do PC */

const int ledPin = 13; // Pino ao qual o LED será conectado
int piscando = 0; // variável para armazenar taxa de “piscagem”
int piscandoNovo = 0;
char caractere;
int flagExibir = 0;

const int Botao = 2;
volatile int estadoBtn = 0;
volatile int estadoBtnOld = 0;
volatile int flagInterrupcao = 0;

int numBin[4] = {0, 0, 0, 0};
const int a = 7;
const int b = 8;
const int c = 9;
const int d = 10;

void interrupcao() {
  estadoBtn = digitalRead(Botao);
  if (estadoBtn == 1 && estadoBtnOld == 0)
  {
    flagInterrupcao = 1;
  }
  estadoBtnOld = estadoBtn;
}

/* Declarando a função pisca() que fará o LED piscar na taxa determinada pelo valor armazenado na variável piscando */
void acionar()
{
  digitalWrite(ledPin, HIGH);
  delay(piscandoNovo);
  digitalWrite(ledPin, LOW);
  delay(piscandoNovo);
  if (flagExibir)
  {
    Serial.println ();
    Serial.print ("NOVO DELAY: ");
    Serial.println (piscandoNovo);
    Serial.println ();

    deco();

    flagExibir = 0;
  }
}

void deco()
{
  digitalWrite(a, numBin[0] );
  digitalWrite(b, numBin[1] );
  digitalWrite(c, numBin[2] );
  digitalWrite(d, numBin[3] );
    Serial.println ("FOI: ");
}

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); // Pino 13 será de saída de sinais
  attachInterrupt(digitalPinToInterrupt(2), interrupcao, CHANGE); // Configurando a interrupção externa

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);

}

void loop()
{
  //piscando = 500;
  if (Serial.available()) { // Verificar se há caracteres disponíveis
    caractere = Serial.read(); // Armazena caractere lido. Mude o tipo da variável int para char!!!
    Serial.print ("O caracter digitado em ASCII: ");
    Serial.println(caractere);
    if (isDigit(caractere)) {  // Verificar se o caractere ASCII é um dígito entre 0 e 9
      piscando = (caractere - 48); // Convertendo ASCII em valor numérico (0 = 48)
      Serial.print ("O numero inteiro equivalente: ");
      Serial.println (piscando);
      piscando = piscando * 100; // Escalonamento da taxa de tempo, com base de 100ms
    }
  }
  if (flagInterrupcao == 1)
  {
    piscandoNovo = piscando;
    flagInterrupcao = 0;
    flagExibir = 1;

    numBin[0] = (piscandoNovo / 100) >> 0 & 1;
    numBin[1] = (piscandoNovo / 100) >> 1 & 1;
    numBin[2] = (piscandoNovo / 100) >> 2 & 1;
    numBin[3] = (piscandoNovo / 100) >> 3 & 1;
  }

  acionar(); // Chamando a função blink(), que será declarada abaixo.
}



