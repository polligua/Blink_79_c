////------------------------------------------------------------------------------------------------------
//// FUNCOES - Controle PID
////------------------------------------------------------------------------------------------------------
//
//#include <PID_v1.h>
//
//double PID_Input, PID_Output, PID_Setpoint;
//
////Specify the links and initial tuning parameters
////double PID_kp;
////double PID_ki;
////double PID_kd;
//
//PID myPID(&PID_Input, &PID_Output, &PID_Setpoint, PID_kp, PID_ki, PID_kd, DIRECT);
////PID myPID(&PID_Input, &PID_Output, &PID_Setpoint, PID_kp, PID_ki, PID_kd, REVERSE);
//
//void PID_setup()
//{
////  PID_kp=15;
////  PID_ki=0;
////  PID_kd=25;
//  PID_Setpoint = 4500;
//
//  //turn the PID on
//  myPID.SetMode(AUTOMATIC);
//}
//
//double PID_loop(double posicao, double set_point){
//  PID_Input = posicao;
//  PID_Setpoint = set_point;
//  myPID.SetTunings(PID_kp, PID_ki, PID_kd);
//  myPID.Compute();
//  return PID_Output;
//}
//void PID_SetAuto(){
//  myPID.SetMode(AUTOMATIC);
//}
//void PID_SetMan(){
//  myPID.SetMode(MANUAL);
//}
//
//void PID_tunning_set_kp(double _kp){
//  PID_kp = _kp;
//}
//void PID_tunning_set_ki(double _ki){
//  PID_ki = _ki;
//}
//void PID_tunning_set_kd(double _kd){
//  PID_kd = _kd;
//}
//
//double PID_tunning_get_kp(){
//  return PID_kp;
//}
//double PID_tunning_get_ki(){
//  return PID_ki;
//}
//double PID_tunning_get_kd(){
//  return PID_kd;
//}
//
//void PID_output_motors(int* vel_mot_dir, int* vel_mot_esq, int vel_mot_nominal, int vel_mot_max){
//  int i_PID_Output;
//  int dif_vel;
//  //vel_mot_nominal = 180;
//  //vel_mot_max = 215;
//  i_PID_Output = (int)PID_Output;
//  dif_vel = vel_mot_max - vel_mot_nominal;
//  if (i_PID_Output > (dif_vel)) {
//    i_PID_Output = dif_vel;
//  }
//  if (i_PID_Output < (dif_vel * -1)) {
//    i_PID_Output = dif_vel * -1;
//  }
//  vel_mot_dir = vel_mot_nominal - i_PID_Output;
//  vel_mot_esq = vel_mot_nominal + i_PID_Output;
//}
//
//double PID_nominal_curva(double raio, double dist_entre_rodas){
//  return dist_entre_rodas/2/raio;
//}
