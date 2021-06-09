////------------------------------------------------------------------------------------------------------
//// FUNCOES - Lê valor númerico de string
////------------------------------------------------------------------------------------------------------
//bool SerialGetDouble(String s, double* value){
//  if (s.compareTo("0") == 0 or s.compareTo("0.0") == 0){
//    *value = 0.0;
//    return true;
//  }
//  if (s.toDouble() != 0.0){
//    *value = s.toDouble();
//    return true;
//  } else {
//    *value = 0.0;
//    return false;
//  }
//}
//bool SerialGetInt(String s, int* value){
//  if (s.compareTo("0") == 0){
//    *value = 0;
//    return true;
//  }
//  if (s.toInt() != 0){
//    *value = s.toInt();
//    return true;
//  } else {
//    *value = 0;
//    return false;
//  }
//}
////------------------------------------------------------------------------------------------------------
//// FUNCOES - Linha de comando pela Serial
////------------------------------------------------------------------------------------------------------
//#define SerialWiFi Serial1
////#define SerialWiFi Serial
//
//int send_pid_output_ms;
//int send_pid_input_ms;
//int send_pid_analog_ms;
//
//void Serial_setup() {
//  SerialWiFi.begin(115200);
//  SerialWiFi.println("");
//  SerialWiFi.println("SerialWiFi Ok");
//  Serial.println("SerialWiFi Ok");
//}
//
//void Serial_loop() {
//  //SerialWiFi.println("Serial_loop");
//  bool pulse_50ms;
//  static unsigned long previousMillis;
//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis >= 50) {
//    previousMillis = currentMillis;
//    pulse_50ms = true;
//  } else {
//    pulse_50ms = false;
//  }
//
//  //Serial --------------------------------------------------------------
//  PID_send_output(send_pid_output_ms);
//  PID_send_input(send_pid_input_ms);
//  PID_send_analog(send_pid_analog_ms, inChar);
//  
//  if (SerialWiFi.available() > 0){
//    static char ser_buffer[32];
//    static int ser_buffer_index = 0;
//    char buf[32];
//    int serial_len_rev = SerialWiFi.available();
//    //SerialWiFi.println(serial_len_rev);
//    SerialWiFi.readBytes(buf, serial_len_rev);
//    
//    for (int i = 0; i < serial_len_rev; i++){
//      ser_buffer[ser_buffer_index] = buf[i];
//      ser_buffer_index++;
//      if (ser_buffer_index >= ser_buffer){
//        ser_buffer_index = 0;
//        i = serial_len_rev;
//      }
//    }
//    
//    if (buf[serial_len_rev - 1] == 13 or buf[serial_len_rev - 1] == 10){ //Enter or New line
//      buf[serial_len_rev - 1] = '/0';
//      String ser_string = String(ser_buffer);
//      ser_string = ser_string.substring(0, ser_buffer_index);
//      ser_buffer_index = 0;
//      for (int i = 0; i < 32; i++){
//        ser_buffer[i] = 0;
//      }    
//      ser_string.toUpperCase();
//      SerialWiFi.println(ser_string);
//      
//      if (ser_string.charAt(3) == '='){ //Command format = XXX=NN...NN
//        //SerialWiFi.println("= ok");
//        //Command
//        String cmd = ser_string.substring(0, 3);
//        String cmd_data = ser_string.substring(4, ser_string.length()-1);
//        cmd_data.replace(",", ".");
//        if (cmd.compareTo("KPP") == 0){
//          //kp
//          double value;
//          if (SerialGetDouble(cmd_data, &value)){
//            PID_tunning_set_kp(value);
//            SerialWiFi.println("Ok");
//          } else {
//            SerialWiFi.println("Comando com dado invalido");
//            SerialWiFi.println(ser_string);
//          }
//        } else if (cmd.compareTo("KII") == 0){
//          //ki
//          double value;
//          if (SerialGetDouble(cmd_data, &value)){
//            PID_tunning_set_ki(value);
//            SerialWiFi.println("Ok");
//          } else {
//            SerialWiFi.println("Comando com dado invalido");
//            SerialWiFi.println(ser_string);
//          }
//        } else if (cmd.compareTo("KDD") == 0){
//          //kd
//          double value;
//          if (SerialGetDouble(cmd_data, &value)){
//            PID_tunning_set_kd(value);
//            SerialWiFi.println("Ok");
//          } else {
//            SerialWiFi.println("Comando com dado invalido");
//            SerialWiFi.println(ser_string);
//          }
//
//        } else if (cmd.compareTo("OUT") == 0){
//          int value;
//          if (SerialGetInt(cmd_data, &value)){
//            send_pid_output_ms = value;
//            SerialWiFi.println("Ok");
//          } else {
//            SerialWiFi.println("Comando com dado invalido");
//            SerialWiFi.println(ser_string);
//          }
//        } else if (cmd.compareTo("INP") == 0){
//          int value;
//          if (SerialGetInt(cmd_data, &value)){
//            send_pid_input_ms = value;
//            SerialWiFi.println("Ok");
//          } else {
//            SerialWiFi.println("Comando com dado invalido");
//            SerialWiFi.println(ser_string);
//          }
//        } else if (cmd.compareTo("ANA") == 0){
//          int value;
//          if (SerialGetInt(cmd_data, &value)){
//            send_pid_analog_ms = value;
//            SerialWiFi.println("Ok");
//          } else {
//            SerialWiFi.println("Comando com dado invalido");
//            SerialWiFi.println(ser_string);
//          }
//        //correcao_motor
//        } else if (cmd.compareTo("CMD") == 0){
//          double value;
//          if (SerialGetDouble(cmd_data, &value)){
//            correcao_motor_dir = value;
//            SerialWiFi.println("Ok");
//          } else {
//            SerialWiFi.println("Comando com dado invalido");
//            SerialWiFi.println(ser_string);
//          }
//        } else if (cmd.compareTo("CME") == 0){
//          double value;
//          if (SerialGetDouble(cmd_data, &value)){
//            correcao_motor_esq = value;
//            SerialWiFi.println("Ok");
//          } else {
//            SerialWiFi.println("Comando com dado invalido");
//            SerialWiFi.println(ser_string);
//          }
//        } else if (cmd.compareTo("CAL") == 0){
//          int value;
//          if (SerialGetInt(cmd_data, &value)){
//            calibracao_motor_en = value;
//            SerialWiFi.println("Ok");
//          } else {
//            SerialWiFi.println("Comando com dado invalido");
//            SerialWiFi.println(ser_string);
//          }
//        } else if (cmd.compareTo("VMA") == 0){
//          //Velocidade manual joystick
//          int value;
//          if (SerialGetInt(cmd_data, &value)){
//            if (value > 215) {
//              value = 215;
//            } else if (value < 20) {
//              value = 20;
//            }
//            velocidade_manual = value;
//            SerialWiFi.println("Ok");
//          } else {
//            SerialWiFi.println("Comando com dado invalido");
//            SerialWiFi.println(ser_string);
//          }
//        } else {
//          SerialWiFi.println("Comando desconhecido:");
//          SerialWiFi.println(cmd);
//        }
//      } else if (ser_string.charAt(3) == '?'){ //Read format = XXX?
//        //SerialWiFi.println("? ok");
//        //Read
//        String rd = ser_string.substring(0, 3);
//        if (rd.compareTo("KPP") == 0){
//          //kp
//          SerialWiFi.print(rd + "=");
//          SerialWiFi.println(PID_tunning_get_kp());
//        }
//        else if (rd.compareTo("KII") == 0){
//          //ki
//          SerialWiFi.print(rd + "=");
//          SerialWiFi.println(PID_tunning_get_ki());
//        }
//        else if (rd.compareTo("KDD") == 0){
//          //kd
//          SerialWiFi.print(rd + "=");
//          SerialWiFi.println(PID_tunning_get_kd());
//        }
//        else if (rd.compareTo("CMD") == 0){
//          //Correção motor direito
//          SerialWiFi.print(rd + "=");
//          SerialWiFi.println(correcao_motor_dir);
//        }
//        else if (rd.compareTo("CME") == 0){
//          //Correção motor esquerdo
//          SerialWiFi.print(rd + "=");
//          SerialWiFi.println(correcao_motor_esq);
//        }
//        else if (rd.compareTo("CAL") == 0){
//          //Modo de calibração dos motores, movimento apenas longitudinal
//          SerialWiFi.print(rd + "=");
//          SerialWiFi.println(calibracao_motor_en);
//        }
//        else if (rd.compareTo("VMA") == 0){
//          //Velocidade manual
//          SerialWiFi.print(rd + "=");
//          SerialWiFi.println(velocidade_manual);
//
//        //Leitura desconhecida
//        } else {
//          SerialWiFi.println("Leitura desconhecida:");
//          SerialWiFi.println(rd);
//        }
//      } else {
//        //discard
//        SerialWiFi.println("Comando invalido");
//        SerialWiFi.println(ser_string);
//      }
//    }
//  }
//  //Serial end ----------------------------------------------------------
//}
//
//void PID_send_output(int time_ms){
//  if (time_ms == 0) {
//    return;
//  }
//  static unsigned long previousMillis;
//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis >= (unsigned long)time_ms) {
//    previousMillis = currentMillis;
//    //pulse_ms = true;
//    int i_PID_Output;
//    i_PID_Output = (int)PID_Output;
//    SerialWiFi.print("Out=");
//    SerialWiFi.println(i_PID_Output);
//  } else {
//    //pulse_ms = false;
//  }
//}
//
//void PID_send_input(int time_ms){
//  if (time_ms == 0) {
//    return;
//  }
//  static unsigned long previousMillis;
//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis >= (unsigned long)time_ms) {
//    previousMillis = currentMillis;
//    //pulse_ms = true;
//    int i_PID_Input;
//    PID_Input = (int)PID_Input;
//    SerialWiFi.print("Inp=");
//    SerialWiFi.println(i_PID_Input);
//  } else {
//    //pulse_ms = false;
//  }
//}
//
//void PID_send_analog(int time_ms, int analog){
//  if (time_ms == 0) {
//    return;
//  }
//  static unsigned long previousMillis;
//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis >= (unsigned long)time_ms) {
//    previousMillis = currentMillis;
//    //pulse_ms = true;
//    SerialWiFi.print("Ana=");
//    SerialWiFi.println(analog);
//  } else {
//    //pulse_ms = false;
//  }
//}
