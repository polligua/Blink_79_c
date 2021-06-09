//------------------------------------------------------------------------------------------------------
// FUNCOES - Controle (chamada de funções
//------------------------------------------------------------------------------------------------------

void controle() {
    leitura_dos_sensores();
    Error = set_point - posicao;
    calculo_do_PID();  
    ajuste_erro();
}

//------------------------------------------------------------------------------------------------------
// FUNCOES - Leitura SENSORES
//------------------------------------------------------------------------------------------------------

void leitura_dos_sensores() {

  posicao_old = posicao;
  JBifurcacao = digitalRead(JPulse_Percurso_Optico);
  //Serial.print("valor lido sensor optico \t");  
  inChar = analogRead(PIN_Sensor_Percurso_Optico); 
  //Serial.println(inChar);  
  double resultado = (inChar * 5 * 70 / 4.5) / 1023 ;
  posicao = ((resultado + 10) * 100);
  //Serial.println(posicao);
  
  if ( posicao >= 1000 && posicao <= 8000){
    digitalWrite(PIN_Buzzer, LOW);
  }
  if(estado_manual != HIGH && aux_giro == 0){
  if (posicao > 8100 || posicao < 1000){
      if(aux_bif < 10){
        aux_bif++;
     //   Serial.print("aux bif: \t");
     //   Serial.println(aux_bif);
        posicao = posicao_old;
      }
      else{
        parar_emergencia();
        bot_lib_AGV = 0;
      }
  }
  else aux_bif = 0;
  }
  
}

//------------------------------------------------------------------------------------------------------
// FUNCOES - PID - Proporcional Integral Derivativo
//------------------------------------------------------------------------------------------------------

void calculo_do_PID() {

  //t_now=millis();
 
  //delta = t_now - t_old;
 
  Error = set_point - posicao ;
  
  Proporcional = Error;
  
  Integral = Integral + Error;
  
  Derivativo = (Error - Error_old);
    
  correction = Proporcional / 1000 * kp + Integral / 1000 * ki + Derivativo / 1000 * kd ;

  Error_old = Error;

//  if(correction > 50){
//    correction = 50;
//  }
//  if(correction < -50){
//    correction = -50;
//  }
  //t_old=t_now;
}

//------------------------------------------------------------------------------------------------------
// FUNCOES - Ajuste do Erro
//------------------------------------------------------------------------------------------------------

void ajuste_erro() {
//  if (correction >= 0){
//    compensacao_M1 = correction / 1;
//    compensacao_M2 = 0;  
//    Serial.println(compensacao_M1);
//    Serial.println(compensacao_M2);
//  }
//  else{
//    compensacao_M1 = 0;
//    compensacao_M2 = correction / -1;
//    Serial.println(compensacao_M1);
//    Serial.println(compensacao_M2);   
//  }  
//}
    compensacao_M1 = correction / 1;
    compensacao_M2 = correction / -1;
}
