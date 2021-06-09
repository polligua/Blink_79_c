//------------------------------------------------------------------------------------------------------
// FUNCOES - Parada Emergencia
//------------------------------------------------------------------------------------------------------

void parar_emergencia() {
      analogWrite(PWM_M1_Curtis, 0);
      analogWrite(PWM_M2_Curtis, 0);
      
      ALL_RED();
     }


//------------------------------------------------------------------------------------------------------
// FUNCOES - Acionamento M1 Curtis Manual
//------------------------------------------------------------------------------------------------------

void Acionamento_M1_Curtis_Manual(float vel_m1_manual) {
  if (vel_m1_manual > 255) vel_m1_manual = 255;
  if (vel_m1_manual < -255) vel_m1_manual = -255; 
  if (vel_m1_manual < 0) {
    digitalWrite(Reverse_M1_Curtis, HIGH);
    analogWrite(PWM_M1_Curtis, (vel_m1_manual * -1 * cv1 * cv2 * cv3) * correcao_motor_dir);
  }
  else {
    digitalWrite(Reverse_M1_Curtis, LOW);
    analogWrite(PWM_M1_Curtis, (vel_m1_manual * cv1 * cv2 * cv3) * correcao_motor_dir);
  }
}

//------------------------------------------------------------------------------------------------------
// FUNCOES - Acionamento M2 Curtis Manual
//------------------------------------------------------------------------------------------------------

void Acionamento_M2_Curtis_Manual(float vel_m2_manual) {
  if (vel_m2_manual > 255) vel_m2_manual = 255;
  if (vel_m2_manual < -255) vel_m2_manual = -255;
  if (vel_m2_manual < 0) {
    digitalWrite(Reverse_M2_Curtis, LOW);
    analogWrite(PWM_M2_Curtis, (vel_m2_manual * -1 * cv1 * cv2 * cv3) * correcao_motor_esq);
  }
  else {
    digitalWrite(Reverse_M2_Curtis, HIGH);
    analogWrite(PWM_M2_Curtis, (vel_m2_manual * cv1 * cv2 * cv3) * correcao_motor_esq);
  }
}

////------------------------------------------------------------------------------------------------------
//// FUNCOES - Acionamento M1 Curtis
////------------------------------------------------------------------------------------------------------
//void Acionamento_M1_Curtis (float vel_M1) {
//  if (vel_M1 > 230) vel_M1 = 230;
//  if (vel_M1 < -230) vel_M1 = -230;
//  if (vel_M1 == aux_vel_M1) {
//    if ( aux_vel_M1 < 0) {
//      digitalWrite(Reverse_M1_Curtis, HIGH);
//      analogWrite(PWM_M1_Curtis, aux_vel_M1 * -1 * cv1 * cv2 * cv3 * correcao_motor_dir);
//    }
//    else {
//      analogWrite(PWM_M1_Curtis, aux_vel_M1 * cv1 * cv2 * cv3 * correcao_motor_dir);
//    }
//
//  }
//  else if (vel_M1 > aux_vel_M1) {
//    if (aux_vel_M1 < 0) {
//      digitalWrite(Reverse_M1_Curtis, HIGH);
//      analogWrite(PWM_M1_Curtis, aux_vel_M1 * -1 * cv1 * cv2 * cv3 * correcao_motor_dir);
//      aux_vel_M1 = aux_vel_M1 + 0.15 ;
//    }
//    else {
//      digitalWrite(Reverse_M1_Curtis, LOW);
//      analogWrite(PWM_M1_Curtis, aux_vel_M1 * cv1 * cv2 * cv3 * correcao_motor_dir);
//      aux_vel_M1 = aux_vel_M1 + 0.15 ;
//    }
//  }
//  else {
//    if (aux_vel_M1 < 0) {
//      digitalWrite(Reverse_M1_Curtis, HIGH);
//      analogWrite(PWM_M1_Curtis, aux_vel_M1 * -1 * cv1 * cv2 * cv3 * correcao_motor_dir);
//      aux_vel_M1 = aux_vel_M1 - 0.15 ;
//    }
//    else {
//      digitalWrite(Reverse_M1_Curtis, LOW);
//      analogWrite(PWM_M1_Curtis, aux_vel_M1 * cv1 * cv2 * cv3 * correcao_motor_dir);
//      aux_vel_M1 = aux_vel_M1 - 0.15 ;
//    }
//  }
//}
//
////------------------------------------------------------------------------------------------------------
//// FUNCOES - Acionamento M2 Curtis
////------------------------------------------------------------------------------------------------------
//
//void Acionamento_M2_Curtis (float vel_M2) {
//  if (vel_M2 > 215) vel_M2 = 230;
//  if (vel_M2 < -215) vel_M2 = -230;
//  if (vel_M2 == aux_vel_M2) {
//    if ( aux_vel_M2 < 0) {
//      digitalWrite(Reverse_M2_Curtis, LOW);
//      analogWrite(PWM_M2_Curtis, aux_vel_M2 * -1 * cv1 * cv2 * cv3 * correcao_motor_esq);
//    }
//    else {
//      analogWrite(PWM_M2_Curtis, aux_vel_M2 * cv1 * cv2 * cv3 * correcao_motor_esq);
//    }
//
//  }
//  else if (vel_M2 > aux_vel_M2) {
//    if (aux_vel_M2 < 0) {
//      digitalWrite(Reverse_M2_Curtis, LOW);
//      analogWrite(PWM_M2_Curtis, aux_vel_M2 * -1 * cv1 * cv2 * cv3 * correcao_motor_esq);
//      aux_vel_M2 = aux_vel_M2 + 0.15 ;
//    }
//    else {
//      digitalWrite(Reverse_M2_Curtis, HIGH);
//      analogWrite(PWM_M2_Curtis, aux_vel_M2 * cv1 * cv2 * cv3 * correcao_motor_esq);
//      aux_vel_M2 = aux_vel_M2 + 0.15 ;
//    }
//  }
//  else {
//    if (aux_vel_M2 < 0) {
//      digitalWrite(Reverse_M2_Curtis, LOW);
//      analogWrite(PWM_M2_Curtis, aux_vel_M2 * -1 * cv1 * cv2 * cv3 * correcao_motor_esq);
//      aux_vel_M2 = aux_vel_M2 - 0.15 ;
//    }
//    else {
//      digitalWrite(Reverse_M2_Curtis, HIGH);
//      analogWrite(PWM_M2_Curtis, aux_vel_M2 * cv1 * cv2 * cv3 * correcao_motor_esq);
//      aux_vel_M2 = aux_vel_M2 - 0.15 ;
//    }
//  }
//}
// 

////------------------------------------------------------------------------------------------------------
//// FUNCOES - Parar Suave
////------------------------------------------------------------------------------------------------------

void parar_suave(){
  while (aux_vel_M > 0){
    controle();  
    if (Keyence_Area_Interna == HIGH){    //PARADA DO AGV EM CASO DE ACIONAMENTO DA AREA MAIS INTERNA DO SCANNER DE SEGURANÇA
      parar_emergencia();
    }
    else{
      if (aux_vel_M > 0){
        saida_M1 = aux_vel_M + compensacao_M1;    //CALCULO DO SINAL DE SAIDA MOTOR M1 (MOTOR DIREITO)
        saida_M2 = aux_vel_M + compensacao_M2;    //CALCULO DO SINAL DE SAIDA MOTOR M2 (MOTOR ESQUERDO)
                
        Acionamento_M1_Curtis_Manual(saida_M1);  //PARADA SUAVE DE M1 (MOTOR DIREITO)
        Acionamento_M2_Curtis_Manual(saida_M2);  //PARADA SUAVE DE M2 (MOTOR ESQUUERDO)
        aux_vel_M = aux_vel_M - 0.06;
      }
    }
  }
  aux_vel_M = 0;
  modo_operacao = 0;
  bot_lib_AGV = 0;
}
