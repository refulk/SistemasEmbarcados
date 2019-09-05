#include <EEPROM.h> //Carrega a biblioteca

struct Objeto {
  char nome[10];
  float numero;
};

//float numero = 3.14159; //Numero a ser armazenado
//float ValorLido;
Objeto var1 = {"Renan", 3.14159};
Objeto var2;
//char nome[5] = "Renan";
//char NomeLido[5];
int endereco = 0; //  Altere para 5000

//EEMEM unsigned long foo;  //The variable stored in EEPROM.


void setup()
{
Serial.begin(9600);
//Escrita
EEPROM.put(endereco, var1);
Serial.print("Gravando na memoria EEPROM: \n");
Serial.println(var1.nome);
Serial.println(var1.numero);

delay(2000);
//Leitura
EEPROM.get(endereco, var2);
Serial.println("\nValores lidos da EEPROM: ");
Serial.println(var2.nome);
Serial.println(var2.numero);

}
void loop(){ }
