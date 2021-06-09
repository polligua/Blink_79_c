//------------------------------------------------------------------------------------------------------
// FUNCOES - Pino Atuador
//------------------------------------------------------------------------------------------------------
unsigned long millis_CurAtuador;
unsigned long millis_OldAtuador;
const unsigned long Pino_timeout = 10000;


void atuador() {

  digitalWrite(PIN_Right_Enabled, HIGH);
  digitalWrite(PIN_Left_Enabled, HIGH);
  millis_OldAtuador = millis();
    if (SW1_Inf == 1 && SW1_Sup != 1) {
      //Serial.println("Atuador Subindo");
      digitalWrite(PIN_Right_PWM, HIGH);
      digitalWrite(PIN_Left_PWM, LOW);
  
    digitalWrite(PIN_Buzzer, LOW); 
    //delay(3500);
    digitalWrite(PIN_Buzzer, HIGH); 
    
      while (SW1_Sup != 1) {
        SW1_Sup = digitalRead(SW_P1_PMS);
        SW1_Inf = digitalRead(SW_P1_PMI);
        millis_CurAtuador = millis();
        if(estado_manual == HIGH || aux_vel_M == 0){
          if((millis_CurAtuador - millis_OldAtuador) > Pino_timeout){
            digitalWrite(PIN_Right_PWM, HIGH);
            digitalWrite(PIN_Left_PWM, HIGH);
            Serial.println("Timeout");
            bot_lib_AGV = 0;
            Acionamento_M1_Curtis_Manual(0);
            Acionamento_M2_Curtis_Manual(0);
            return;
          }
          Acionamento_M1_Curtis_Manual(0);
          Acionamento_M2_Curtis_Manual(0);
          modo_operacao = 0;
          bot_lib_AGV = 1;
        } 
        else {
          millis_CurAtuador = millis();
          if((millis_CurAtuador - millis_OldAtuador) > Pino_timeout){
            digitalWrite(PIN_Right_PWM, HIGH);
            digitalWrite(PIN_Left_PWM, HIGH);
            Serial.println("Timeout");
            bot_lib_AGV = 0;
            Acionamento_M1_Curtis_Manual(0);
            Acionamento_M2_Curtis_Manual(0);
            return;
          }
          Ler_Inputs();
          controle();
          saida_M1 = vel_maxima + compensacao_M1;    //CALCULO DO SINAL DE SAIDA MOTOR M1 (MOTOR DIREITO)
          saida_M2 = vel_maxima + compensacao_M2;    //CALCULO DO SINAL DE SAIDA MOTOR M2 (MOTOR ESQUERDO)
  
          Acionamento_M1_Curtis_Manual(saida_M1);   //ACIONAMENTO DE RESPOSTA RAPIDA DE M1 (MOTOR DIREITO)
          Acionamento_M2_Curtis_Manual(saida_M2);   //ACIONAMENTO DE RESPOSTA RAPIDA DE M2 (MOTOR ESQUERDO)
        
        }
      }
      digitalWrite(PIN_Right_PWM, HIGH);
      digitalWrite(PIN_Left_PWM, HIGH);
      //return;
      kp = 55;       //40
      kd = 75;       //65 
      ki = 0.00001;    //0.0001
      correcao_motor_dir = 0.80;
    }
    else {
      //Serial.println("Atuador descendo");
      digitalWrite(PIN_Right_PWM, LOW);
      digitalWrite(PIN_Left_PWM, HIGH);
  
    digitalWrite(PIN_Buzzer, LOW); 
    //delay(4500);
    digitalWrite(PIN_Buzzer, HIGH); 
      while (SW1_Inf != 1) {
        SW1_Sup = digitalRead(SW_P1_PMS);
        SW1_Inf = digitalRead(SW_P1_PMI);
        millis_CurAtuador = millis();
        if(estado_manual == HIGH || aux_vel_M == 0){
          if((millis_CurAtuador - millis_OldAtuador) > Pino_timeout){
            digitalWrite(PIN_Right_PWM, HIGH);
            digitalWrite(PIN_Left_PWM, HIGH);
            Serial.println("Timeout");
            bot_lib_AGV = 0;
            Acionamento_M1_Curtis_Manual(0);
            Acionamento_M2_Curtis_Manual(0);
            return;
          }
          Acionamento_M1_Curtis_Manual(0);
          Acionamento_M2_Curtis_Manual(0);
          modo_operacao = 0;
          bot_lib_AGV = 1;
        } 
        else {
          millis_CurAtuador = millis();
          if((millis_CurAtuador - millis_OldAtuador) > Pino_timeout){
            digitalWrite(PIN_Right_PWM, HIGH);
            digitalWrite(PIN_Left_PWM, HIGH);
            Serial.println("Timeout");
            bot_lib_AGV = 0;
            Acionamento_M1_Curtis_Manual(0);
            Acionamento_M2_Curtis_Manual(0);
            return;
          }
          Ler_Inputs();
          controle();
          saida_M1 = vel_maxima + compensacao_M1;    //CALCULO DO SINAL DE SAIDA MOTOR M1 (MOTOR DIREITO)
          saida_M2 = vel_maxima + compensacao_M2;    //CALCULO DO SINAL DE SAIDA MOTOR M2 (MOTOR ESQUERDO)
  
          Acionamento_M1_Curtis_Manual(saida_M1);   //ACIONAMENTO DE RESPOSTA RAPIDA DE M1 (MOTOR DIREITO)
          Acionamento_M2_Curtis_Manual(saida_M2);   //ACIONAMENTO DE RESPOSTA RAPIDA DE M2 (MOTOR ESQUERDO)
        
        }   
      }
      digitalWrite(PIN_Right_PWM, HIGH);
      digitalWrite(PIN_Left_PWM, HIGH);
      kp = 12;
      kd = 50;
      ki = 0.0001;
      correcao_motor_dir = 0.77;
    }

}
