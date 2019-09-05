/* Enviando dados entre PIC18F4520 e ATmega2560.*/

int millisEnviar = 0; //Controla o quando enviar dados ao PIC
int tempoEnviar = 100;  //Controla intervalo entre os dados enviados

const int motorPWM = 3; //Porta para controlar o PWM
//é preciso escolher uma porta que suporte essa operação

const int BARGRAPH[] = {40, 38, 36, 34, 32, 30, 28, 26, 24, 22, 20}; //Portas para controlar o bargraph
long millisBargraph = 0; //Controla o intervalo de tempo entre a atualização do Bargraph
// utilizadas no controle do Bargraph //
float velIntervalo = 0; // irá ser utilzada para receber o intervalo de velocidade para acendimento entre os Leds
float velMax = 30;  // Aqui deve ser definido a velocidade máxima do sistema que será exibida
float velMin = 1;   // Aqui deve ser definido a velocidade mínima do sistema
//////////////////////////////

float velocidadeLinear = 1.5; //Velocidade inicial do motor
int pwm;  // Irá receber o valor do PWM

void setup() {
  Serial.begin(9600); // utilizada para exibir informações no monitor serial
  Serial1.begin(9600);  // utilizada para permitir que dados sejam enviados ao PIC, numa taxa de transferência determinada
  
  pinMode(motorPWM, OUTPUT); // declara a saída de controle do motor
  
  for (int i = 0; i < 10; i++)
  {
    pinMode(BARGRAPH[i], OUTPUT); // declara as saídas de controle do Bargraph
  }
}

void bargraphControle(int vel) //Função de controle do Bargraph
{
  if ((millis() - millisBargraph) >= 500) // Atualiza as luzes a cada 0,5 segundo
  {
    millisBargraph = millis(); // atualiza valor do contador para definir próximo intervalo de atualização

    velIntervalo = (velMax - velMin) / 10; // Divide o intervalo de velocidade em 10, um para cada luz do bargraph
    for (int i = 0; i <= 9; i++)
    {
      if ((velMin + (velIntervalo * i) ) <= vel) // verifica qual Led deve ser acendido ou apagado
      {
        digitalWrite(BARGRAPH[i], HIGH);  // acende um determinado led do bargraph
      }
      else
      {
        digitalWrite(BARGRAPH[i], LOW); // apaga um determinado led do bargraph
      }
    }
  }
}

void enviarPic(int vel) // Função que irá enviar dados ao PIC
{
  int i;
  String aux;
  char texto[2];
  char ab;

  if (vel >= 10) // Caso a velocidade seja maior que 10, será utilizado letras para sua representação
  {
    texto[0] = 'a'; // Insere valor inicial da variável
    for (i = 10; i < vel; i++) // repete até atingir a velocidade atual do motor
      (texto[0])++; // Percorre o alfabeto até chegar na letra desejada (por exemplo, 11 = 'b')
  }
  else // Caso seja menor que 10, então será representado por um número
  {
    aux = (String)vel;  // converte o número para String
    aux.toCharArray(texto, 2); // converte a String para um char
  }

  Serial.print("Enviado - ");  // Exibe informação no monitor Serial
  Serial.println(texto[0]);   // Exibe informação no monitor Serial

  Serial1.write(texto[0]); // Envia o caracter, que representa a velocidade atual, para o PIC
}

void controlarMotor(int vel) // Função que controla o PWM para regular velocidade do Motor
{  
  // Vale ressaltar que o motor utilizado só começa a girar aproximadamente quando PWM >= 50
  if(vel == 0) 
    pwm = map(vel, 0, 30, 0, 255); // Caso a velocidade for zero, a tensão no motor será zero
  else    
    pwm = map(vel, 0, 30, 50, 255); // Caso Vel>0, o motor já inicia com PWM = 50, e posteriormente aumenta de forma gradual
  analogWrite(motorPWM, pwm);
}

void loop() // Função de repetição do arduíno
{
  if (millisEnviar == 1) // Envia informações ao PIC a cada 100ms
  {
    millisEnviar = 0; // Zera variável de controle
    enviarPic(velocidadeLinear * 2); // Chama função de envio para o PIC
    // A velocidadeLinear, que é a velocidade atual do motor, é uma variável Float
    // Seu valor é multiplicado por 2 pois assim é possível converter para inteiro
    // e obter uma precisao de 0,5 apenas sabendo que o valor inteiro representa
    // metade. Por exemplo, caso velocidadeLinear seja 3,5 km/h, o valor enviado ao PIC
    // será 7, que representa um número quebrado. Permitindo uma maior precisão e mais
    // facilidade de comunicação entre o PIC e o Arduíno.
  }

  if (Serial1.available()) // Verificar se há caracteres disponíveis
  { 
    char caractere = Serial1.read(); // Armazena caracter lido.
    if (caractere == 'x' || caractere == 'y' || caractere == 'z') // caracteres de controle de velocidade
    {
        Serial.print(caractere); // Exibe informações no monitor Serial
        Serial.print(" - ");
      if (caractere == 'x') // o caracter 'x' significa que o Arduíno deve AUMENTAR a velocidade do motor
      {
        Serial.println("aumentar");
        velocidadeLinear = velocidadeLinear + 0.1; // Aumenta a velocidade do motor
      }
      else if (caractere == 'y') // o caracter 'y' significa que o Arduíno deve DIMINUIR a velocidade do motor
      {
        Serial.println("diminuir");
        velocidadeLinear = velocidadeLinear - 0.1; // Diminui a velocidade do motor        
      }
      else // o caracter 'z' significa que o Arduíno deve MANTER a velocidade do motor
      {
        Serial.println("manter"); // Não altera o valor da velocidade atual
      }
        
      Serial.println(""); // Exibe no monitor Serial, para melhor visualização
    }
  }
  controlarMotor(velocidadeLinear * 2); // Chama função de controle de velocidade do motor (pwm)
  millisEnviar++;                       // Acrescenta 1 na variável de controle de envio de informações ao PIC
  bargraphControle(velocidadeLinear * 2); // Chama função de controle do Bargraph
  delay(tempoEnviar);                    // Intervalo devinido
}




