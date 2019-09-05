// CHAVES DE FUN��O:
//  --------CHAVE1--------  --------CHAVE2---------
// |GLCD\LCD ( 1) = ON    |DIS1    ( 1) = OFF   |
// |RX       ( 2) = OFF   |DIS2    ( 2) = OFF   |
// |TX       ( 3) = OFF   |DIS3    ( 3) = OFF   |
// |REL1     ( 4) = OFF   |DIS4    ( 4) = OFF   |
// |REL2     ( 5) = OFF   |INFR    ( 5) = OFF   |
// |SCK      ( 6) = OFF   |RESIS   ( 6) = OFF   |
// |SDA      ( 7) = OFF   |TEMP    ( 7) = OFF   |
// |RTC      ( 8) = OFF   |VENT    ( 8) = OFF   |
// |LED1     ( 9) = OFF   |AN0     ( 9) = OFF   |
// |LED2     (10) = OFF   |AN1     (10) = OFF   |
//  --------------------- ----------------------

// --- Liga��es entre PIC e LCD ---
sbit LCD_RS at RE2_bit;   // PINO 2 DO PORTD INTERLIGADO AO RS DO DISPLAY
sbit LCD_EN at RE1_bit;   // PINO 3 DO PORTD INTERLIGADO AO EN DO DISPLAY
sbit LCD_D7 at RD7_bit;  // PINO 7 DO PORTD INTERLIGADO AO D7 DO DISPLAY
sbit LCD_D6 at RD6_bit;  // PINO 6 DO PORTD INTERLIGADO AO D6 DO DISPLAY
sbit LCD_D5 at RD5_bit;  // PINO 5 DO PORTD INTERLIGADO AO D5 DO DISPLAY
sbit LCD_D4 at RD4_bit;  // PINO 4 DO PORTD INTERLIGADO AO D4 DO DISPLAY

// Selecionando dire��o de fluxo de dados dos pinos utilizados para a comunica��o com display LCD
sbit LCD_RS_Direction at TRISE2_bit;  // SETA DIRE��O DO FLUXO DE DADOS DO PINO 2 DO PORTD
sbit LCD_EN_Direction at TRISE1_bit;  // SETA DIRE��O DO FLUXO DE DADOS DO PINO 3 DO PORTD
sbit LCD_D7_Direction at TRISD7_bit;  // SETA DIRE��O DO FLUXO DE DADOS DO PINO 7 DO PORTD
sbit LCD_D6_Direction at TRISD6_bit;  // SETA DIRE��O DO FLUXO DE DADOS DO PINO 6 DO PORTD
sbit LCD_D5_Direction at TRISD5_bit;  // SETA DIRE��O DO FLUXO DE DADOS DO PINO 5 DO PORTD
sbit LCD_D4_Direction at TRISD4_bit;  // SETA DIRE��O DO FLUXO DE DADOS DO PINO 4 DO PORTD

void main(){

   char ucRead;        // Variavel para armazenar o dado lido (proveniente do Arduíno)
   char texto[2];       // Variavel utilizada na conversão e para exibir velocidade
   unsigned int ucStatus_inc = 0; // Armazena estado anterior do botão RB3
   unsigned int  ligado = 0;    // Controla se a esteira está ligada ou desligada
   int i = 0;                   // utilzada nos laçoes de repetições
   int valorRecebido = 0;       // Utilizada na conversão da velocidade recebida
   int flagLetra = 0;           // Utilizada na conversão da velocidade recebida
   int velSistema = 0;          
   float velEscolhida = 2;      // Velocidade inicial. Variável irá armazenar a velocidade escolhida pelo usuário através dos botões.
   char velSel[2];              // Utilizada na conversão da velocidade recebida

   ADCON1  = 0x0E;                           //Configura os pinos do PORTB como digitais, e RA0 (PORTA) como anal�gico
   Lcd_Init();                               //Inicializa m�dulo LCD
   Lcd_Cmd(_LCD_CURSOR_OFF);                 //Apaga cursor
   Lcd_Cmd(_LCD_CLEAR);                      //Limpa display
   UART1_Init(9600);  // Utiliza bibliotecas do compilador para configura��o o Baud rate.
   TRISB.RB3=1;         // Define o pino RB0 do PORTB como entrada. (botão)
   TRISB.RB4=1;         // Define o pino RB1 Do PORTB como entrada. (botão)
    TRISB0_bit = 1;     // Define o pino de entrada (botão)
    TRISB1_bit = 1;     // Define o pino de entrada (botão)
    TRISB2_bit = 1;     // Define o pino de entrada (botão)



   while(1){   // laço de repetição do PIC

    if((PORTB.RB3==0)&&(ucStatus_inc ==0)){   // Incrementa somente uma vez quando a tecla for pressionada.
       if(ligado == 0)
       {
                 ligado = 1;  // define flag para ligar a Esteira
                 velEscolhida = 2; // Inicializa a velocidade inicial

       }
       else
       {
            Lcd_Cmd(_LCD_CLEAR);   // Clear display
           ligado = 0;  // define flag para desligar a esteira
           velEscolhida = 0;  // Motor deve desligar
       }
    }
    
    if((PORTB.RB3==1)&&(ucStatus_inc==1)){   // Volta a disponibilizar a opcao de incremento quando a tecla for solta.
       ucStatus_inc=0;
    }
         Delay_ms(50);
     if(ligado == 1)  // Caso a esteira esteja ligada
     {
         
         if(Button(&PORTB,0,1,0)) // Botão utilizado para aumentar velocidade pelo usuário
         {
          velEscolhida = velEscolhida + 0.5;
         }
         if(Button(&PORTB,1,1,0)) // Botão utilizado para diminuir velocidade pelo usuário
         {
          velEscolhida = velEscolhida - 0.5;
         }
        // Comeca o controle de velocidade
         velSistema = (velEscolhida * 2); // multiplica por 2 para ter uma escala de 0,5
    // A velEscolhida, que é a velocidade desejado pelo usuário, é uma variável Float
    // Seu valor é multiplicado por 2 pois assim é possível converter para inteiro
    // e obter uma precisao de 0,5 apenas sabendo que o valor inteiro representa
    // metade. Por exemplo, caso velEscolhida seja 3,5 km/h, o valor em inteiro
    // será 7, que representa um número quebrado. Permitindo uma maior precisão e mais
    // facilidade de comunicação entre o PIC e o Arduíno.

         if( velSistema > 30) // Velocidade limite é 15, mas é representada por 30
         {
             velSistema = 30;
             velEscolhida = 15; // velocidade real que o usuário escolheu
         }
         if( velSistema < 0) // Não pode assumir valores negativos!
         {
             velSistema = 0;
             velEscolhida = 0;
         }
             velSel[0] = 'a'; // Insere valor inicial da variável
             for(i = 10; i <= 30; i++) // repete até atingir a velocidade desejada e converter para o char desejado
             {
                   if(i ==  velSistema) // caso seja a velocidade desejada, deve sair do laço
                   {
                    i = 31;
                    flagLetra = 1; // flag indica que velSistema > 10 portanto será representado por uma letra
                   }
                   else
                   {
                     (velSel[0])++; // Percorre o alfabeto até chegar na letra desejada (por exemplo, 11 = 'b')
                   }
             }
             if(flagLetra != 1) // Caso seja menor que 10, então será representado por um número
             {
              velSel[0] = velSistema + '0'; // converte o número para char
             }
             flagLetra = 0; // zera variável de controle

           if(UART1_Data_Ready()){  // Verifica se o dado enviado foi recebido no buffer
             ucRead = UART1_Read(); // Ler o dado da serial.
             valorRecebido = 10;  // zera variável de controle
             texto[0] = 'a'; // Insere valor inicial da variável

             for(i = 0; i <= 30; i++)// repete até atingir a velocidade recebida (do arduíno) e converte para o char desejado
             {
                   if(texto[0] ==  ucRead) // caso seja a velocidade recebida, deve sair do laço
                   {
                    i = 31;
                    flagLetra = 1; // flag indica que velSistema > 10 portanto será representado por uma letra
                   }
                   else
                   {
                     valorRecebido++; // armazena a velocidade recebida em inteiro para uso futuro
                     (texto[0])++;  // Percorre o alfabeto até chegar na letra desejada (por exemplo, 11 = 'b')
                   }
             }
             if(flagLetra != 1) // Caso seja menor que 10, então será representado por um número
             {
              //exibir[0] = ucRead;
              valorRecebido = ucRead - '0'; // armazena a velocidade recebida em inteiro para uso futuro
              texto[0] = valorRecebido + '0'; // converte o número para char
             }
             flagLetra = 0; // zera variável de controle

                //// Exibe informações no display ////
                lcd_out(1,1,"SendComand"); 
                lcd_out(2,1,"Sel: ");
                lcd_chr_cp (velSel[0]); // Exibe Velocidade desejada (selecionada) pelo usuário
                //////////////////////////////////////

                if (valorRecebido < velSistema) // Caso o arduíno precise AUMENTAR a velocidade do motor
               {
                 UART1_Write('x'); // envia sinal de controle para o Arduíno
                 lcd_out(1,12,"+"); // exibe uma representação do sinal de controle no Display
               }
               else if(valorRecebido > velSistema)// Caso o arduíno precise DIMINUIR a velocidade do motor
               {
                 UART1_Write('y'); // envia sinal de controle para o Arduíno
                 lcd_out(1,12,"-"); // exibe uma representação do sinal de controle no Display
               }
               else// Caso o arduíno precise MANTER a velocidade do motor
               {
                 UART1_Write('z'); // envia sinal de controle para o Arduíno
                 lcd_out(1,12,"="); // exibe uma representação do sinal de controle no Display
               }
                 lcd_out(2,9, "Vel:");
                lcd_chr_cp (texto[0]); // Exibe Velocidade atual do motor
           }
     }
     else  // Caso a esteira seja desligada
     {
              // é importante existir essa repetição após o usuário ter pressionado o botão de desligar,
              // pois quando a esteira é desligada, o PIC deve continuar mandando sinais para o
              // Arduíno, informando para diminuir a velocidade até chegar a zero.

              // Outra solução que poderia ser implementada, seria criar mais um sinal de controle
              // para ligar e desligar o motor. Como por exemplo o char 'w'

             velSistema = 0; // A velocidade do motor deve ser zero
               // lcd_out(1,1,"DESLIGADOAAA");
             velEscolhida = 0; // A velocidade escolhida tbm é zerada
             
             if(UART1_Data_Ready()){  // Verifica se o dado enviado foi recebido no buffer
             ucRead = UART1_Read(); // L� o dado da serial.
             valorRecebido = 10; // zera variável de controle
             texto[0] = 'a';// Insere valor inicial da variável

             for(i = 0; i <= 30; i++)// repete até atingir a velocidade recebida (do arduíno) e converte para o char desejado
             {
                   if(texto[0] ==  ucRead) // caso atinja a velocidade recebida, deve sair do laço
                   {
                    i = 31;
                    flagLetra = 1;// flag indica que velSistema > 10 portanto será representado por uma letra
                   }
                   else
                   {
                     valorRecebido++; // armazena a velocidade recebida em inteiro para uso futuro
                     (texto[0])++;  // Percorre o alfabeto até chegar na letra desejada (por exemplo, 11 = 'b')
                   }
             }
             if(flagLetra != 1)
              valorRecebido = ucRead - '0';// armazena a velocidade recebida em inteiro para uso futuro
             flagLetra = 0;// zera variável de controle


             //No caso quando o sistema é desligado, o PIC irá enviar o sinal 'y' até que a velocidade do motor
             // seja zero. Após isso, é enviado o zinal 'z'. Indicando apenas para manter a velocidade zero.
                if (valorRecebido < velSistema)
               {
                 UART1_Write('x');// envia sinal de controle para o Arduíno
               }
               else if(valorRecebido > velSistema)
               {
                 UART1_Write('y');// envia sinal de controle para o Arduíno
               }
               else
               {
                 UART1_Write('z');// envia sinal de controle para o Arduíno
               }
           }
           Lcd_Cmd(_LCD_CLEAR);               // Clear display
     }
     Delay_ms(50);

   }
}