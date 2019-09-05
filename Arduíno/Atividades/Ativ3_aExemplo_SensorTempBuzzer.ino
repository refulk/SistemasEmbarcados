const int LM35 = 0;
float temperatura = 0;
int ADClido = 0;
const int Buzzer = 12;
void setup(){
analogReference(INTERNAL1V1); 
pinMode(Buzzer, OUTPUT);
}
void loop(){
ADClido = analogRead(LM35);
temperatura = ADClido * 0.1075268817204301; 
if(temperatura > 27){  
// setei como 25ºC
digitalWrite(Buzzer, HIGH);
}
else{
digitalWrite(Buzzer, LOW);
}
}

