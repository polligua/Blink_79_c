

//------------------------------------------------------------------------------------------------------
// FUNCOES - Leitura de Inputs
//------------------------------------------------------------------------------------------------------
void Ler_Inputs() {

  bot_emergencia = digitalRead(PIN_Botao_Emergencia);
  aux_lib_AGV = digitalRead(PIN_Botao_Libera_AGV);
  estado_manual = digitalRead(PIN_Chave_Seletora_Manual);
  estado_automatico = digitalRead(PIN_Chave_Seletora_Auto);
  SW1_Sup = digitalRead(SW_P1_PMS);
  SW1_Inf = digitalRead(SW_P1_PMI);

  if (aux_lib_AGV != last_aux_lib_AGV) {
    if (aux_lib_AGV == 1) {
      if (estado_automatico == 1) {
        if (bot_lib_AGV == 0)bot_lib_AGV = 1;
        else bot_lib_AGV = 0;
      }
    }
  }
  last_aux_lib_AGV = aux_lib_AGV;
  //Serial.println("6");
    RFID();   
}
