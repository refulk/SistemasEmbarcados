//********************************************************************************
//          PROGRAMA EXEMPLO: Display LCD 16x2 e conversor ADC.
//   OBJETIVO: Aprender a utilizar o LCD e o Conversor ADC do PIC18F4520.

//                       MICROCONTROLADOR: PIC18F4520.
//         http://ww1.microchip.com/downloads/en/DeviceDoc/39631E.pdf

//********************************************************************************

// CHAVES DE FUN??O:
//  ----- Chave 1 ------  ------- Chave 2 ---------
// |GLCD\LCD ( 1) = ON    |DIS1     ( 1) = OFF    |
// |RX       ( 2) = OFF   |DIS2     ( 2) = OFF    |
// |TX       ( 3) = OFF   |DIS3     ( 3) = OFF    |
// |REL1     ( 4) = OFF   |DIS4     ( 4) = OFF    |
// |REL2     ( 5) = OFF   |INFR     ( 5) = OFF   |
// |SCK      ( 6) = OFF   |RESIS    ( 6) = OFF   |
// |SDA      ( 7) = OFF   |TEMP     ( 7) = OFF   |
// |RTC      ( 8) = OFF   |VENT     ( 8) = OFF   |
// |LED1     ( 9) = OFF   |AN0      ( 9) = ON    |
// |LED2     (10) = OFF   |AN1      (10) = ON   |
//  ----------------------------------------------

// Selecionando pinos utilizados para comunica??o com display LCD
sbit LCD_RS at RE2_bit;// PINO 2 DO PORTD INTERLIGADO AO RS DO DISPLAY
sbit LCD_EN at RE1_bit;// PINO 3 DO PORTD INTERLIGADO AO EN DO DISPLAY
sbit LCD_D7 at RD7_bit;// PINO 7 DO PORTD INTERLIGADO AO D7 DO DISPLAY
sbit LCD_D6 at RD6_bit;// PINO 6 DO PORTD INTERLIGADO AO D6 DO DISPLAY
sbit LCD_D5 at RD5_bit;// PINO 5 DO PORTD INTERLIGADO AO D5 DO DISPLAY
sbit LCD_D4 at RD4_bit;// PINO 4 DO PORTD INTERLIGADO AO D4 DO DISPLAY

// Selecionando dire??o de fluxo de dados dos pinos utilizados para a comunica??o com display LCD
sbit LCD_RS_Direction at TRISE2_bit;// SETA DIRE??O DO FLUXO DE DADOS DO PINO 2 DO PORTD
sbit LCD_EN_Direction at TRISE1_bit;// SETA DIRE??O DO FLUXO DE DADOS DO PINO 3 DO PORTD
sbit LCD_D7_Direction at TRISD7_bit;// SETA DIRE??O DO FLUXO DE DADOS DO PINO 7 DO PORTD
sbit LCD_D6_Direction at TRISD6_bit;// SETA DIRE??O DO FLUXO DE DADOS DO PINO 6 DO PORTD
sbit LCD_D5_Direction at TRISD5_bit;// SETA DIRE??O DO FLUXO DE DADOS DO PINO 5 DO PORTD
sbit LCD_D4_Direction at TRISD4_bit;// SETA DIRE??O DO FLUXO DE DADOS DO PINO 4 DO PORTD

char pot1_string [8];// STRING PARA RECEBER O VALOR CONVERTIDO DA LEITURA DO POTENCI?METRO 1
char pot2_string [8];// STRING PARA RECEBER O VALOR CONVERTIDO DA LEITURA DO POTENCI?METRO 2
char apagar [] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};//STRING PARA APAGAR O CONTE?DO DAS RESPECTIVAS LINHAS

unsigned int pot1 = 0;// VARIAVEL PARA ARMAZENAR O VALOR OBTIDO PELO AN0
unsigned int pot2 = 0;// VARIAVEL PARA ARMAZENAR O VALOR OBTIDO PELO AN1

void main()
{
    TRISA0_bit = 1;  // CONFIGURA O PINO EM QUE SE ENCONTRA A PORTA ANAL?GICA AN0 COMO ENTRADA
    TRISA1_bit = 1;  // CONFIGURA O PINO EM QUE SE ENCONTRA A PORTA ANAL?GICA AN1 COMO ENTRADA

    ADCON1 = 0b00001110; //0b00001100;//SELECIONA OS PINOS 1, 2 DO PORTA COMO ENTRADAS ANAL?GICAS (AN0, AN1)
    ADC_Init();//INICIALIZA M?DULO ANALG?GICO
    CMCON = 0b00000111;//DESABILITA COMPARADORES INTERNOS

    Lcd_Init();//INICIALIZA DISPLAY LCD
    Lcd_Cmd(_LCD_CLEAR);//ENVIA O COMANDO DE LIMPAR TELA PARA O DISPLAY LCD
    Lcd_Cmd(_LCD_CURSOR_OFF);// ENVIA O COMANDO DE DESLIGAR CURSOR PARA O DISPLAY LCD

    while(1)
    {
         pot1 = ADC_Get_Sample(0);//RECEBE O VALOR DE TENS?O DO POTENCIOMETRO NA PORTA AN0
         pot2 = ADC_Get_Sample(1);//RECEBE O VALOR DE TENS?O DO POTENCIOMETRO NA PORTA AN1

         IntToStr (pot1,pot1_string);//CONVERTE O VALOR DO TIPO INTEIRO OBTIDO PELO CONVERSOR AD NA PORTA AN0 PARA UMA STRING
         IntToStr (pot2,pot2_string);//CONVERTE O VALOR DO TIPO INTEIRO OBTIDO PELO CONVERSOR AD NA PORTA AN1 PARA UMA STRING

         Ltrim(pot1_string);//REMOVE TODOS OS ESPA?OS EM BRANCO LOCALIZADOS A ESQUERDA DO PRIMEIRO CHAR DA STRING COM O VALOR DE AN0
         Ltrim(pot2_string);//REMOVE TODOS OS ESPA?OS EM BRANCO LOCALIZADOS A ESQUERDA DO PRIMEIRO CHAR DA STRING COM O VALOR DE AN1

         Lcd_Cmd(_LCD_CLEAR);                      // Apaga display.
         Lcd_Out(1,1,"S1:");//ESCREVE A MENSAGEM POT1 NA PRIMEIRA LINHA E PRIMEIRA COLUNA DO DISPLAY LCD
         Lcd_Out(1,4, pot1_string);//ESCREVE O VALOR OBTIDO DO CONVERSOR A/D NA POSI??O EM QUE SE ENCONTRA O CURSOR DO DISPLAY

         Lcd_Out(1,9,"S2:");//ESCREVE A MENSAGEM POT2 NA PRIMEIRA LINHA E DECIMA PRIMEIRA COLUNA DO DISPLAY LCD
         Lcd_Out_Cp(pot2_string);//ESCREVE O VALOR OBTIDO DO CONVERSOR A/D NA POSI??O EM QUE SE ENCONTRA O CURSOR DO DISPLAY

         delay_ms(100);// AGUARDA 0,1 s
    }
}