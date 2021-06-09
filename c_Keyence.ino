//------------------------------------------------------------------------------------------------------
// FUNCOES - Leitura Keyence
//------------------------------------------------------------------------------------------------------

void Ler_Keyence() {

  Keyence_Area_Interna = digitalRead(PIN_Keyence_AUX1_INTERNA);            // PORTA 23
  Keyence_Area_Intermediaria = digitalRead(PIN_Keyence_AUX2_INTERMED);     // PORTA 25
  Keyence_Area_Externa = digitalRead(PIN_Keyence_AUX3_EXTERNA);            // PORTA 27
  Keyence_Area_AUX4 = digitalRead(PIN_Keyence_AUX4);                    // PORTA 29

  int aux_ler_keyence = 0;
  if (Keyence_Area_Interna == HIGH && estado_manual != HIGH) {    //AO ACIONAR A AREA MAIS INTERNA REALIZA PARADA DE EMERGENCIA
    parar_emergencia();                    // Area mais interna = 3
    Serial.println("Key Emergencia");
    delay(1000);
  }
  else {
    if (Keyence_Area_Intermediaria == HIGH && estado_manual != HIGH) {  //AREA INTERMEDIARIA ACIONADA, VELOCIDADE REDUZ A METADE
      cv3 = 0.5;                // Vel max  50%
    }
    else {
      if (Keyence_Area_Externa == HIGH && estado_manual != HIGH) {      //AREA EXTERNA ACIONADA, VELOCIDADE REDUZ A 70%
        cv3 = 0.7;              // Vel max 70%
      }
      else {                    //NENHUMA DAS AREAS ACIONADAS, VELOCIDADE TOTAL
        cv3 = 1;;                
      }
    }
  }
}


//------------------------------------------------------------------------------------------------------
// FUNCOES - Bancos Keyence
//------------------------------------------------------------------------------------------------------

void Bancos_Keyence(int aux_bancos) {
  switch ( aux_bancos) {
    case 0:     //Banco 0
      digitalWrite(BANCO_A, LOW);    // DENTRO KEYENCE = BANK A     Relay 05 - IN5 - 37
      digitalWrite(BANCO_B, LOW);    // DENTRO KEYENCE = BANK B     Relay 06 - IN6 - 39
      digitalWrite(BANCO_C, LOW);    // DENTRO KEYENCE = BANK C     Relay 07 - IN7 - 41
      digitalWrite(BANCO_D, LOW);    // DENTRO KEYENCE = BANK D     Relay 08 - IN8 - 43
      digitalWrite(BANCO_a, HIGH);     // DENTRO KEYENCE = BANK a     Relay 01 - IN1 - 22
      digitalWrite(BANCO_b, HIGH);    // DENTRO KEYENCE = BANK b     Relay 02 - IN2 - 24
      digitalWrite(BANCO_c, HIGH);    // DENTRO KEYENCE = BANK c     Relay 03 - IN3 - 26
      digitalWrite(BANCO_d, HIGH);    // DENTRO KEYENCE = BANK d     Relay 04 - IN4 - 28
      break;
    case 1:   //Banco 1
      digitalWrite(BANCO_A, HIGH);    // DENTRO KEYENCE = BANK A     Relay 05 - IN5 - 37
      digitalWrite(BANCO_B, LOW);    // DENTRO KEYENCE = BANK B     Relay 06 - IN6 - 39
      digitalWrite(BANCO_C, LOW);    // DENTRO KEYENCE = BANK C     Relay 07 - IN7 - 41
      digitalWrite(BANCO_D, LOW);    // DENTRO KEYENCE = BANK D     Relay 08 - IN8 - 43
      digitalWrite(BANCO_a, LOW);     // DENTRO KEYENCE = BANK a     Relay 01 - IN1 - 22
      digitalWrite(BANCO_b, HIGH);    // DENTRO KEYENCE = BANK b     Relay 02 - IN2 - 24
      digitalWrite(BANCO_c, HIGH);    // DENTRO KEYENCE = BANK c     Relay 03 - IN3 - 26
      digitalWrite(BANCO_d, HIGH);    // DENTRO KEYENCE = BANK d     Relay 04 - IN4 - 28
      break;
    case 2:   //Banco 2
      digitalWrite(BANCO_A, LOW);    // DENTRO KEYENCE = BANK A     Relay 05 - IN5 - 37
      digitalWrite(BANCO_B, HIGH);    // DENTRO KEYENCE = BANK B     Relay 06 - IN6 - 39
      digitalWrite(BANCO_C, LOW);    // DENTRO KEYENCE = BANK C     Relay 07 - IN7 - 41
      digitalWrite(BANCO_D, LOW);    // DENTRO KEYENCE = BANK D     Relay 08 - IN8 - 43
      digitalWrite(BANCO_a, HIGH);     // DENTRO KEYENCE = BANK a     Relay 01 - IN1 - 22
      digitalWrite(BANCO_b, LOW);    // DENTRO KEYENCE = BANK b     Relay 02 - IN2 - 24
      digitalWrite(BANCO_c, HIGH);    // DENTRO KEYENCE = BANK c     Relay 03 - IN3 - 26
      digitalWrite(BANCO_d, HIGH);    // DENTRO KEYENCE = BANK d     Relay 04 - IN4 - 28
      break;
    case 3:   //Banco 3
      digitalWrite(BANCO_A, HIGH);    // DENTRO KEYENCE = BANK A     Relay 05 - IN5 - 37
      digitalWrite(BANCO_B, HIGH);    // DENTRO KEYENCE = BANK B     Relay 06 - IN6 - 39
      digitalWrite(BANCO_C, LOW);    // DENTRO KEYENCE = BANK C     Relay 07 - IN7 - 41
      digitalWrite(BANCO_D, LOW);    // DENTRO KEYENCE = BANK D     Relay 08 - IN8 - 43
      digitalWrite(BANCO_a, LOW);     // DENTRO KEYENCE = BANK a     Relay 01 - IN1 - 22
      digitalWrite(BANCO_b, LOW);    // DENTRO KEYENCE = BANK b     Relay 02 - IN2 - 24
      digitalWrite(BANCO_c, HIGH);    // DENTRO KEYENCE = BANK c     Relay 03 - IN3 - 26
      digitalWrite(BANCO_d, HIGH);    // DENTRO KEYENCE = BANK d     Relay 04 - IN4 - 28
      break;
    case 4:   //Banco 4
      digitalWrite(BANCO_A, LOW);    // DENTRO KEYENCE = BANK A     Relay 05 - IN5 - 37
      digitalWrite(BANCO_B, LOW);    // DENTRO KEYENCE = BANK B     Relay 06 - IN6 - 39
      digitalWrite(BANCO_C, HIGH);    // DENTRO KEYENCE = BANK C     Relay 07 - IN7 - 41
      digitalWrite(BANCO_D, LOW);    // DENTRO KEYENCE = BANK D     Relay 08 - IN8 - 43
      digitalWrite(BANCO_a, HIGH);     // DENTRO KEYENCE = BANK a     Relay 01 - IN1 - 22
      digitalWrite(BANCO_b, HIGH);    // DENTRO KEYENCE = BANK b     Relay 02 - IN2 - 24
      digitalWrite(BANCO_c, LOW);    // DENTRO KEYENCE = BANK c     Relay 03 - IN3 - 26
      digitalWrite(BANCO_d, HIGH);    // DENTRO KEYENCE = BANK d     Relay 04 - IN4 - 28
      break;
    case 5:   //Banco 5
      digitalWrite(BANCO_A, HIGH);    // DENTRO KEYENCE = BANK A     Relay 05 - IN5 - 37
      digitalWrite(BANCO_B, LOW);    // DENTRO KEYENCE = BANK B     Relay 06 - IN6 - 39
      digitalWrite(BANCO_C, HIGH);    // DENTRO KEYENCE = BANK C     Relay 07 - IN7 - 41
      digitalWrite(BANCO_D, LOW);    // DENTRO KEYENCE = BANK D     Relay 08 - IN8 - 43
      digitalWrite(BANCO_a, LOW);     // DENTRO KEYENCE = BANK a     Relay 01 - IN1 - 22
      digitalWrite(BANCO_b, HIGH);    // DENTRO KEYENCE = BANK b     Relay 02 - IN2 - 24
      digitalWrite(BANCO_c, LOW);    // DENTRO KEYENCE = BANK c     Relay 03 - IN3 - 26
      digitalWrite(BANCO_d, HIGH);    // DENTRO KEYENCE = BANK d     Relay 04 - IN4 - 28
      break;
    case 6:   //Banco 6
      digitalWrite(BANCO_A, LOW);    // DENTRO KEYENCE = BANK A     Relay 05 - IN5 - 37
      digitalWrite(BANCO_B, HIGH);    // DENTRO KEYENCE = BANK B     Relay 06 - IN6 - 39
      digitalWrite(BANCO_C, HIGH);    // DENTRO KEYENCE = BANK C     Relay 07 - IN7 - 41
      digitalWrite(BANCO_D, LOW);    // DENTRO KEYENCE = BANK D     Relay 08 - IN8 - 43
      digitalWrite(BANCO_a, HIGH);     // DENTRO KEYENCE = BANK a     Relay 01 - IN1 - 22
      digitalWrite(BANCO_b, LOW);    // DENTRO KEYENCE = BANK b     Relay 02 - IN2 - 24
      digitalWrite(BANCO_c, LOW);    // DENTRO KEYENCE = BANK c     Relay 03 - IN3 - 26
      digitalWrite(BANCO_d, HIGH);    // DENTRO KEYENCE = BANK d     Relay 04 - IN4 - 28
      break;
    case 7:   //Banco 7
      digitalWrite(BANCO_A, HIGH);    // DENTRO KEYENCE = BANK A     Relay 05 - IN5 - 37
      digitalWrite(BANCO_B, HIGH);    // DENTRO KEYENCE = BANK B     Relay 06 - IN6 - 39
      digitalWrite(BANCO_C, HIGH);    // DENTRO KEYENCE = BANK C     Relay 07 - IN7 - 41
      digitalWrite(BANCO_D, LOW);    // DENTRO KEYENCE = BANK D     Relay 08 - IN8 - 43
      digitalWrite(BANCO_a, LOW);     // DENTRO KEYENCE = BANK a     Relay 01 - IN1 - 22
      digitalWrite(BANCO_b, LOW);    // DENTRO KEYENCE = BANK b     Relay 02 - IN2 - 24
      digitalWrite(BANCO_c, LOW);    // DENTRO KEYENCE = BANK c     Relay 03 - IN3 - 26
      digitalWrite(BANCO_d, HIGH);    // DENTRO KEYENCE = BANK d     Relay 04 - IN4 - 28
      break;
    case 8:   //Banco 8
      digitalWrite(BANCO_A, LOW);    // DENTRO KEYENCE = BANK A     Relay 05 - IN5 - 37
      digitalWrite(BANCO_B, LOW);    // DENTRO KEYENCE = BANK B     Relay 06 - IN6 - 39
      digitalWrite(BANCO_C, LOW);    // DENTRO KEYENCE = BANK C     Relay 07 - IN7 - 41
      digitalWrite(BANCO_D, HIGH);    // DENTRO KEYENCE = BANK D     Relay 08 - IN8 - 43
      digitalWrite(BANCO_a, HIGH);     // DENTRO KEYENCE = BANK a     Relay 01 - IN1 - 22
      digitalWrite(BANCO_b, HIGH);    // DENTRO KEYENCE = BANK b     Relay 02 - IN2 - 24
      digitalWrite(BANCO_c, HIGH);    // DENTRO KEYENCE = BANK c     Relay 03 - IN3 - 26
      digitalWrite(BANCO_d, LOW);    // DENTRO KEYENCE = BANK d     Relay 04 - IN4 - 28
      break;
    case 9:   //Banco 9
      digitalWrite(BANCO_A, HIGH);    // DENTRO KEYENCE = BANK A     Relay 05 - IN5 - 37
      digitalWrite(BANCO_B, LOW);    // DENTRO KEYENCE = BANK B     Relay 06 - IN6 - 39
      digitalWrite(BANCO_C, LOW);    // DENTRO KEYENCE = BANK C     Relay 07 - IN7 - 41
      digitalWrite(BANCO_D, HIGH);    // DENTRO KEYENCE = BANK D     Relay 08 - IN8 - 43
      digitalWrite(BANCO_a, LOW);     // DENTRO KEYENCE = BANK a     Relay 01 - IN1 - 22
      digitalWrite(BANCO_b, HIGH);    // DENTRO KEYENCE = BANK b     Relay 02 - IN2 - 24
      digitalWrite(BANCO_c, HIGH);    // DENTRO KEYENCE = BANK c     Relay 03 - IN3 - 26
      digitalWrite(BANCO_d, LOW);    // DENTRO KEYENCE = BANK d     Relay 04 - IN4 - 28
      break;
    case 10:   //Banco 10
      digitalWrite(BANCO_A, LOW);    // DENTRO KEYENCE = BANK A     Relay 05 - IN5 - 37
      digitalWrite(BANCO_B, HIGH);    // DENTRO KEYENCE = BANK B     Relay 06 - IN6 - 39
      digitalWrite(BANCO_C, LOW);    // DENTRO KEYENCE = BANK C     Relay 07 - IN7 - 41
      digitalWrite(BANCO_D, HIGH);    // DENTRO KEYENCE = BANK D     Relay 08 - IN8 - 43
      digitalWrite(BANCO_a, HIGH);     // DENTRO KEYENCE = BANK a     Relay 01 - IN1 - 22
      digitalWrite(BANCO_b, LOW);    // DENTRO KEYENCE = BANK b     Relay 02 - IN2 - 24
      digitalWrite(BANCO_c, HIGH);    // DENTRO KEYENCE = BANK c     Relay 03 - IN3 - 26
      digitalWrite(BANCO_d, LOW);    // DENTRO KEYENCE = BANK d     Relay 04 - IN4 - 28
      break;
    case 11:   //Banco 11
      digitalWrite(BANCO_A, HIGH);    // DENTRO KEYENCE = BANK A     Relay 05 - IN5 - 37
      digitalWrite(BANCO_B, HIGH);    // DENTRO KEYENCE = BANK B     Relay 06 - IN6 - 39
      digitalWrite(BANCO_C, LOW);    // DENTRO KEYENCE = BANK C     Relay 07 - IN7 - 41
      digitalWrite(BANCO_D, HIGH);    // DENTRO KEYENCE = BANK D     Relay 08 - IN8 - 43
      digitalWrite(BANCO_a, LOW);     // DENTRO KEYENCE = BANK a     Relay 01 - IN1 - 22
      digitalWrite(BANCO_b, LOW);    // DENTRO KEYENCE = BANK b     Relay 02 - IN2 - 24
      digitalWrite(BANCO_c, HIGH);    // DENTRO KEYENCE = BANK c     Relay 03 - IN3 - 26
      digitalWrite(BANCO_d, LOW);    // DENTRO KEYENCE = BANK d     Relay 04 - IN4 - 28
      break;
    case 12:   //Banco 12
      digitalWrite(BANCO_A, LOW);    // DENTRO KEYENCE = BANK A     Relay 05 - IN5 - 37
      digitalWrite(BANCO_B, LOW);    // DENTRO KEYENCE = BANK B     Relay 06 - IN6 - 39
      digitalWrite(BANCO_C, HIGH);    // DENTRO KEYENCE = BANK C     Relay 07 - IN7 - 41
      digitalWrite(BANCO_D, HIGH);    // DENTRO KEYENCE = BANK D     Relay 08 - IN8 - 43
      digitalWrite(BANCO_a, HIGH);     // DENTRO KEYENCE = BANK a     Relay 01 - IN1 - 22
      digitalWrite(BANCO_b, HIGH);    // DENTRO KEYENCE = BANK b     Relay 02 - IN2 - 24
      digitalWrite(BANCO_c, LOW);    // DENTRO KEYENCE = BANK c     Relay 03 - IN3 - 26
      digitalWrite(BANCO_d, LOW);    // DENTRO KEYENCE = BANK d     Relay 04 - IN4 - 28
      break;
    case 13:   //Banco 13
      digitalWrite(BANCO_A, HIGH);    // DENTRO KEYENCE = BANK A     Relay 05 - IN5 - 37
      digitalWrite(BANCO_B, LOW);    // DENTRO KEYENCE = BANK B     Relay 06 - IN6 - 39
      digitalWrite(BANCO_C, HIGH);    // DENTRO KEYENCE = BANK C     Relay 07 - IN7 - 41
      digitalWrite(BANCO_D, HIGH);    // DENTRO KEYENCE = BANK D     Relay 08 - IN8 - 43
      digitalWrite(BANCO_a, LOW);     // DENTRO KEYENCE = BANK a     Relay 01 - IN1 - 22
      digitalWrite(BANCO_b, HIGH);    // DENTRO KEYENCE = BANK b     Relay 02 - IN2 - 24
      digitalWrite(BANCO_c, LOW);    // DENTRO KEYENCE = BANK c     Relay 03 - IN3 - 26
      digitalWrite(BANCO_d, LOW);    // DENTRO KEYENCE = BANK d     Relay 04 - IN4 - 28
      break;
    case 14:   //Banco 14
      digitalWrite(BANCO_A, LOW);    // DENTRO KEYENCE = BANK A     Relay 05 - IN5 - 37
      digitalWrite(BANCO_B, HIGH);    // DENTRO KEYENCE = BANK B     Relay 06 - IN6 - 39
      digitalWrite(BANCO_C, HIGH);    // DENTRO KEYENCE = BANK C     Relay 07 - IN7 - 41
      digitalWrite(BANCO_D, HIGH);    // DENTRO KEYENCE = BANK D     Relay 08 - IN8 - 43
      digitalWrite(BANCO_a, HIGH);     // DENTRO KEYENCE = BANK a     Relay 01 - IN1 - 22
      digitalWrite(BANCO_b, LOW);    // DENTRO KEYENCE = BANK b     Relay 02 - IN2 - 24
      digitalWrite(BANCO_c, LOW);    // DENTRO KEYENCE = BANK c     Relay 03 - IN3 - 26
      digitalWrite(BANCO_d, LOW);    // DENTRO KEYENCE = BANK d     Relay 04 - IN4 - 28
      break;
    case 15:   //Banco 15
      digitalWrite(BANCO_A, HIGH);    // DENTRO KEYENCE = BANK A     Relay 05 - IN5 - 37
      digitalWrite(BANCO_B, HIGH);    // DENTRO KEYENCE = BANK B     Relay 06 - IN6 - 39
      digitalWrite(BANCO_C, HIGH);    // DENTRO KEYENCE = BANK C     Relay 07 - IN7 - 41
      digitalWrite(BANCO_D, HIGH);    // DENTRO KEYENCE = BANK D     Relay 08 - IN8 - 43
      digitalWrite(BANCO_a, LOW);     // DENTRO KEYENCE = BANK a     Relay 01 - IN1 - 22
      digitalWrite(BANCO_b, LOW);    // DENTRO KEYENCE = BANK b     Relay 02 - IN2 - 24
      digitalWrite(BANCO_c, LOW);    // DENTRO KEYENCE = BANK c     Relay 03 - IN3 - 26
      digitalWrite(BANCO_d, LOW);    // DENTRO KEYENCE = BANK d     Relay 04 - IN4 - 28
      break;
  }

}
