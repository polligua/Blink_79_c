//------------------------------------------------------------------------------------------------------
// FUNCOES - Giro
//------------------------------------------------------------------------------------------------------

void girar(int dir_giro)                    //DOCUMENTAR
{
  if (dir_giro == 0){     // GIRO PARA ESQUERDA
    if (aux_vel_M == 0) {
      aux_giro = 1;
      digitalWrite(PIN_Buzzer, LOW);
      Acionamento_M1_Curtis_Manual(150);
      Acionamento_M2_Curtis_Manual(-150);
      t1 = millis();
      t2 = millis();
      while((t2 - t1) < 2000){
        Ler_Keyence();
        Ler_Inputs();
        t2 = millis();
      }
      leitura_dos_sensores();
      Serial.println(posicao);
      while (posicao > 8000) {
        Ler_Keyence();
        Acionamento_M1_Curtis_Manual(80);
        Acionamento_M2_Curtis_Manual(-80);
        leitura_dos_sensores();
        Ler_Inputs;
      }
          while (correction < -2 || correction > 2) {
        Ler_Keyence();
        leitura_dos_sensores();
        controle();
        saida_M1 = 40 + compensacao_M1;
        saida_M2 = 40 + compensacao_M2;
        Acionamento_M1_Curtis_Manual(saida_M1);
        Acionamento_M2_Curtis_Manual(saida_M2);
      }
      modo_operacao = 0;
      bot_lib_AGV = 1;
      aux_giro = 0;
      t1 = 0;
      t2 = 0;
    }
  }
  if (dir_giro == 1){     //Girar para Direita
    if (aux_vel_M == 0) {
      aux_giro = 1;
      digitalWrite(PIN_Buzzer, LOW);
      Acionamento_M1_Curtis_Manual(-150);
      Acionamento_M2_Curtis_Manual(150);
      t1 = millis();
      t2 = millis();
      while((t2 - t1) < 2000){
        Ler_Keyence();
        Ler_Inputs();
        t2 = millis();
      }
      leitura_dos_sensores();
      Serial.println(posicao);
      while (posicao > 8000) {
        Ler_Keyence();
        Acionamento_M1_Curtis_Manual(-80);
        Acionamento_M2_Curtis_Manual(80);
        leitura_dos_sensores();
        Ler_Inputs;
      }
          while (correction < -2 || correction > 2) {
        Ler_Keyence();
        leitura_dos_sensores();
        controle();
        saida_M1 = 40 + compensacao_M1;
        saida_M2 = 40 + compensacao_M2;
        Acionamento_M1_Curtis_Manual(saida_M1);
        Acionamento_M2_Curtis_Manual(saida_M2);
      }
      modo_operacao = 0;
      bot_lib_AGV = 1;
      aux_giro = 0;
      t1 = 0;
      t2 = 0;
    }  
  }
}

//------------------------------------------------------------------------------------------------------
// FUNCOES - Bifurcação
//------------------------------------------------------------------------------------------------------

void Bifurcacao(int aux_bifurcacao) {
  static unsigned long bif_count_start;
  static unsigned long bif_count_current;
  bif_count_start = millis();
  bif_count_current = millis();
  switch (aux_bifurcacao) {
    case 0:               //Bifurcação a esquerda
      while ((bif_count_current - bif_count_start) < 5000)  {
        set_point = 5300;
        Ler_Keyence();
        leitura_dos_sensores();
        controle();
        saida_M1 = aux_vel_M + compensacao_M1;
        saida_M2 = aux_vel_M + compensacao_M2;
        Acionamento_M1_Curtis_Manual(saida_M1);
        Acionamento_M2_Curtis_Manual(saida_M2);
        Ler_Inputs();
        bif_count_current = millis();
      }
      set_point = 4400;
      break;
    case 1:               //Bifurcação Segue reto
      while ((bif_count_current - bif_count_start) < 2500) {
        set_point = 4400;
        Ler_Keyence();
        controle();
        saida_M1 = aux_vel_M;
        saida_M2 = aux_vel_M;
        Acionamento_M1_Curtis_Manual(saida_M1);
        Acionamento_M2_Curtis_Manual(saida_M2);
        Ler_Inputs();
        bif_count_current = millis();
      }

      break;
    case 2:               //Bifurcação a Direita
      while ((bif_count_current - bif_count_start) < 5000) {
        set_point = 2700;
        Ler_Keyence();
        leitura_dos_sensores();
        controle();
        saida_M1 = aux_vel_M + compensacao_M1;
        saida_M2 = aux_vel_M + compensacao_M2;
        Acionamento_M1_Curtis_Manual(saida_M1);
        Acionamento_M2_Curtis_Manual(saida_M2);
        Ler_Inputs();
        bif_count_current = millis();
      }
      set_point = 4400;
      break;
  }
}
