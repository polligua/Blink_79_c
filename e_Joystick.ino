//------------------------------------------------------------------------------------------------------
// FUNCOES - JOYSTICK
//------------------------------------------------------------------------------------------------------

void joystick() {

  xPosition = analogRead(X_Joy);
  yPosition = analogRead(Y_Joy);
  // Y-axis used for forward and backward control
  if (yPosition <= 420) {
    // Set Motor 1 backward
    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    Valor_Y1max = map(yPosition, 530, 0, 0, 230);
    Valor_Y2max = map(yPosition, 530, 0, 0, 230);
    aux_reverse = -1;
  }
  else if (yPosition >= 580) {
    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    Valor_Y1max = map(yPosition, 580, 1023, 0, 230);
    Valor_Y2max = map(yPosition, 580, 1023, 0, 230);
    aux_reverse = 1;
  }
  // If joystick stays in middle the motors are not moving
  else {
    Valor_Y1max = 0;
    Valor_Y2max = 0;
  }
  // X-axis used for left and right control
  if (xPosition <= 420) {
    // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
    int xMapped = map(xPosition, 530, 0, 0, 230);
    // Move to left - decrease left motor speed, increase right motor speed
    //Serial.println(xMapped);
    //Serial.println(Valor_Y1max);
    Valor_Y1max = Valor_Y1max + xMapped / 2;
    Valor_Y2max = Valor_Y2max - xMapped / 2;
    //Serial.println(Valor_Y1max);
    //Serial.println(Valor_Y2max);
    //delay(1500);
    // Confine the range from 0 to 255
    //    if (Valor_Y1max > 160) {
    //      Valor_Y1max = 160;
    //    }
  }
  if (xPosition >= 580) {
    // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
    int xMapped = map(xPosition, 580, 1023, 0, 230);
    // Move right - decrease right motor speed, increase left motor speed
    Valor_Y1max = Valor_Y1max - xMapped / 2;
    Valor_Y2max = Valor_Y2max + xMapped / 2;
    // Confine the range from 0 to 255
    //     if (Valor_Y2max > 160) {
    //      Valor_Y2max = 160;
    //    }
  }
  
  Acionamento_M1_Curtis_Manual(Valor_Y1max * aux_reverse);
  Acionamento_M2_Curtis_Manual(Valor_Y2max * aux_reverse);

  //Atraso para o próximo passo:
  //delay(25);

}
