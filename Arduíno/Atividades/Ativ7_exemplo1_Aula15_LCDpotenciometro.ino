#include <LiquidCrystal.h>
// Define a biblioteca para utilização das funções referentes ao display LCD.
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// Define as GPIO para o envio dos caracteres.
void setup() {
  lcd.begin(16, 2);
  // Define o número de colunas e linhas do display LCD usado.
  lcd.setCursor(0, 0);
  // Define a posição que o Atmega irá escrever no display LCD.
  lcd.print("Ola, meu nome e:");
  // Escreve a string no LCD de forma semelhante ao realizado no monitor serial.
  lcd.setCursor(0, 1);
  // Define a posição de inicio da escrita da segunda string.
  lcd.print("Epaminondas");
  // Coloque seu nome no lugar nesse lugar.
}
void loop() {
}
