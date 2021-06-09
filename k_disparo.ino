unsigned long millis_atual25 = 0;
unsigned long millis_anterior25 = 0;
unsigned long millis_atual50 = 0;
unsigned long millis_anterior50 = 0;
unsigned long millis_atual100 = 0;
unsigned long millis_anterior100 = 0;

int trigger = 0;

int disparo25(){
  millis_atual25 = millis();
  if (millis_atual25 - millis_anterior25 >= 25){
    millis_anterior25 = millis_atual25;
    trigger = 1;
  }
  else trigger = 0;
  return trigger;
}

int disparo50(){
  millis_atual50 = millis();
  if (millis_atual50 - millis_anterior50 >= 50){
    millis_anterior50 = millis_atual50;
    trigger = 1;
  }
  else trigger = 0;
  return trigger;
}

int disparo100(){
  millis_atual100 = millis();
  if (millis_atual100 - millis_anterior100 >= 100){
    millis_anterior100 = millis_atual100;
    trigger = 1;
  }
  else trigger = 0;
  return trigger;
}
