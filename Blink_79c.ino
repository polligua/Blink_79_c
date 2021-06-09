//------------------------------------------------------------------------------------------------------
// Bibliotecas
//------------------------------------------------------------------------------------------------------
#include <AVRUtils.h>

#include <Wire.h>
#include <ModbusMaster.h>
//#include <Modbusino.h>

//#include <SPI.h>
//#include <MFRC522.h>
#include <Wiegand.h>

#include <ArduinoJson.h>
#include <stdio.h>
#include <stdlib.h>

#include <FastLED.h>

#include <SoftwareSerial.h>

#include <PID_v1.h>
//#include <ElipseMobile.h>

//#include <VarSpeedServo.h>

//#include <ESP8266.h>
//#include <WiFiEsp.h>
//------------------------------------------------------------------------------------------------------
// Instanciando Objetos
//------------------------------------------------------------------------------------------------------
ModbusMaster node;

SoftwareSerial XBee1(19, 18); // RXD1 & TXD1

// Cria uma serial nas portas 0 (RX) e 1 (TX)
//SoftwareSerial WIFI(15 , 14);

//------------------------------------------------------------------------------------------------------
// DADOS CONEXAO WIFI - RX3 - TX3
//------------------------------------------------------------------------------------------------------

// Define que o modulo ira utilizar a serial WIFI
//ESP8266 wifi(WIFI);

// Configuracao ID e senha da rede Wireless
#define SSID        "Movixpro"
#define PASSWORD    "MoviXpro@01"

//------------------------------------------------------------------------------------------------------
// DADOS CONEXAO ELIPSE SCADA
//------------------------------------------------------------------------------------------------------

//ElipseMobile elipse;

// Inicializando ID do dispositivo...
//ModbusinoSlave modbusino_slave(1);

// Alocando numero de registradores - Numero de TAGs...
//uint16_t tab_reg[20];
float tab_reg[20];

//-------------------------------------------------------------------------------------------------------------------------
// DEFINICAO - NUMERACAO DAS PORTAS - Pinos para ARDUINO MEGA 2560 (EMBED)
//-------------------------------------------------------------------------------------------------------------------------

// |LED 24v|              |  FEED BATTERY  |                                                         |cooler 24v|
//                        | 24v 12v 5v GND |     |5v ARD|                                                       |cooler 12v|
// |LED 12v|                                                          |relays|               |IO1-TXD RXD-IO0|
//
// |LED  5v|
//                                                                               |USB Port|
//
//
// |Lant ESQ|                             |------------------------------------------------------------------|
//                                        |9v 9v|
// |Lant DIR|                             | Gnd |
//                                        |5v 5v|
//                                        | 3v3 |
//                                        |Rst A|
//                                     IO1|Tx Rx|IO0   
// CURTIS             PWM CURTIS M1    IO3|     |IO2   LUZ DIR                  (Ok)
// CURTIS             PWM CURTIS M2    IO5|     |IO4   LUZ ESQ                  (Ok)
//                    RESET KEYENCE    IO7|     |IO6   REV CURTIS M2            (Ok)
//                                     IO9|     |IO8   REV CURTIS M1            (Ok)
//                                    IO11|     |IO10  JUNCTION PULSE           (Ok)
//                                    IO13|     |IO12  
//     WIFI ESP8266             RXD3  IO15|Rx Tx|IO14  WIFI ESP8266             WIFI
//                              RXD2  IO17|Rx Tx|IO16  TXD2 
//                              RXD1  IO19|Rx Tx|IO18  TXD1 
//                    RFID D1         IO21|     |IO20  RFID D0
// KEYENCE  (Ok)      LASER 01        IO23|     |IO22  BANCO a                  (Ok)
// KEYENCE  (Ok)      LASER 02        IO25|     |IO24  BANCO b                  (Ok)
// KEYENCE  (Ok)      LASER 03        IO27|     |IO26  BANCO c                  (Ok)
// KEYENCE  (Ok)      LASER 04        IO29|     |IO28  BANCO d                  (Ok)
//          (Ok)     SWITCH BOTTOM    IO31|     |IO30  SWITCH TOP               (Ok)


//                    LSA08 PERCURSO   AD1|     |AD0   JOYSTICK VRX             (Ok)
//                                     AD3|     |AD2   JOYSTICK VRY             (Ok)
//                                     AD5|     |AD4    
//                                     AD7|     |AD6    
//                                     AD9|     |AD8                   
//                                    AD11|     |AD10  
//                                    AD13|     |AD12  
//                                    AD15|     |AD14  
//                      PIN BUZZER    IO33|     |IO32  BOTAO AUTO               (Ok)
//          (Ok)      RELAY BANK B    IO35|     |IO34  BOTAO MANUAL             (Ok)
//          (Ok)      BANCO A         IO37|     |IO36  BOTAO LIBERAR            (Ok)
//          (Ok)      BANCO B         IO39|     |IO38  BOTAO EMERGENCIA         (Ok)
//          (Ok)      BANCO C         IO41|     |IO40  
//          (Ok)      BANCO D         IO43|     |IO42  
//          (Ok)    L_MOTOR PWM       IO45|     |IO44  R_MOTOR ENABLED          (Ok)
//          (Ok)    L_MOTOR ENABLED   IO47|     |IO46  R_MOTOR PWM              (Ok)


//                                    IO49|     |IO48  
//                                    IO51|     |IO50  
//                                    IO53|     |IO52  

//-------------------------------------------------------------------------------------------------------------------------
// JOYSTICK - 2 portas analogicas (0 / 2)
//-------------------------------------------------------------------------------------------------------------------------

#define Y_Joy                                A0  // Pino Analog Movimento Y Joystick    //  14 = Porta Analogica   -  A14
#define X_Joy                                A2  // Pino Analog Movimento X Joystick    //  12 = Porta Analogica   -  A12

//-------------------------------------------------------------------------------------------------------------------------
// OK // MONITORAR VARIAVEIS ANALOGICA - SENSOR DE PERCURSO
//-------------------------------------------------------------------------------------------------------------------------

#define PIN_Sensor_Percurso_Optico           A1  // Leitura Analog Sensor Percurso     //  01 = Porta Analog     -   AD1

//-------------------------------------------------------------------------------------------------------------------------
// lANTERNAS - POSSUEM 3 FIOS PARA CONEXAO - | +5V / Gnd / Signal |
//-------------------------------------------------------------------------------------------------------------------------

#define LED_PIN_DIR                           2 // IO2
#define LED_PIN_ESQ                           4  // IO4

//-------------------------------------------------------------------------------------------------------------------------
// AVISOS DE OPERACAO - Saidas para Relays | 10 RELAYS - 2 UTILIZADOS - 4 DISPONIVEIS - 4 DESABILITADOS |
//-------------------------------------------------------------------------------------------------------------------------

#define PIN_Buzzer                           33 // Pino Porta Relay - Buzzer
// #define Luz_Piloto                           35  // Pino Porta Relay - Luz Piloto

//-------------------------------------------------------------------------------------------------------------------------
// CONTROLE MOTORES - CURTIS
//-------------------------------------------------------------------------------------------------------------------------

//#define KSI_Curtis_M1                         7   Ligado na chave geral
//#define KSI_Curtis_M2                        11   Ligado na chave geral

#define PWM_M1_Curtis                         5   //Motor esq
#define PWM_M2_Curtis                         3   //Motor dir

#define Reverse_M1_Curtis                     8
#define Reverse_M2_Curtis                     6

//-------------------------------------------------------------------------------------------------------------------------
// MONITORAR VARIAVEIS ANALOGICA - TENSAO DA BATERIA
//-------------------------------------------------------------------------------------------------------------------------

#define PIN_Tensao_Bateria                   A8  // Leitura 24v - Nao poder ser < 23,5v //  15 = Porta Analog     -   A15
#define PIN_Temperatura_M1                   40  // Leitura 24v - Nao poder ser < 23,5v //  15 = Porta Analog     -   A15

//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

#define JPulse_Percurso_Optico               10  // Leitura Digital JUNCTION PULSE     //  10 = Porta Digital    -   D10

//#define TxEnablePin                          12

//-------------------------------------------------------------------------------------------------------------------------
// OK // SCANNER DE SEGURANCA LASER - Portas Digitais e Auxiliares
//-------------------------------------------------------------------------------------------------------------------------

#define PIN_Keyence_AUX1_INTERNA             23    // AUX1 - LARANJA 
#define PIN_Keyence_AUX2_INTERMED            25    // AUX2 - LARANJA/PRETO
#define PIN_Keyence_AUX3_EXTERNA             27    // AUX3 - AMARELO/PRETO
#define PIN_Keyence_AUX4                     29    // AUX4 - VERMELHO/PRETO

#define PIN_Keyence_Reset                    12    //Reset Bancos Keyence

//-------------------------------------------------------------------------------------------------------------------------
// SWITCHES - Chave Fim de Curso - Pinos de Indexacao ==> APENAS O PINO 01 ESTA SENDO UTILIZADO <==
//-------------------------------------------------------------------------------------------------------------------------

#define SW_P1_PMS                            30  // Fim de Curso Pino1 Superior        //  32 = Porta Digital    -     
#define SW_P1_PMI                            31  // Fim de Curso Pino1 Inferior        //  34 = Porta Digital    -     D34 - Brown

//---------------------------------------------------------------------------------------------------------------------------------------
// BOTOES - TODOS OS BOTOES ESTAO CONECTADOS COMO ENTRADA PULL-UP, PORTANTO SUAS PORTAS ESTAO EM HIGH, QDO ACIONADOS A PORTA VAI PARA LOW
//---------------------------------------------------------------------------------------------------------------------------------------

#define PIN_Chave_Seletora_Auto              32  // P20SLR4B2A - Chave Seletora AUTOM   //  pino 01 Mike
#define PIN_Chave_Seletora_Manual            34  // P20SLR4B2A - Chave Seletora Manual  //  pino 02 Mike
#define PIN_Botao_Libera_AGV                 36  // P20SLR4B2A - Chave Liberar AGV      //  pino 04 Mike
#define PIN_Botao_Emergencia                 38  // Botao 20AKRR1C - Botao Emergencia   //  pino 05 Mike

//-------------------------------------------------------------------------------------------------------------------------
// OK // SCANNER DE SEGURANCA LASER - BANCOS PARA ÁREAS
//-------------------------------------------------------------------------------------------------------------------------

#define BANCO_a                              22  // 
#define BANCO_b                              24  // 
#define BANCO_c                              26  // 
#define BANCO_d                              28  // 34 - Brown

#define BANCO_A                              37  // 
#define BANCO_B                              39  // 
#define BANCO_C                              41  // 
#define BANCO_D                              43  // 

//-------------------------------------------------------------------------------------------------------------------------
// MOTOR CONTROLLER - Placa de Controle do Motor do PINO  ==> APENAS O MOTOR 01 ESTA SENDO UTILIZADO <== IN11 IN12
//-------------------------------------------------------------------------------------------------------------------------

#define PIN_Right_Enabled                    44  // Controle Motor Pino Dianteiro IN21  //  44 = Porta Digital  -      D44 - Green
#define PIN_Left_PWM                         45  // Controle Motor Pino Dianteiro IN21  //  44 = Porta Digital  -      D44 - Green
#define PIN_Right_PWM                        46  // Controle Motor Pino Dianteiro IN21  //  44 = Porta Digital  -      D44 - Green
#define PIN_Left_Enabled                     47  // Controle Motor Pino Dianteiro IN21  //  44 = Porta Digital  -      D44 - Green

//-------------------------------------------------------------------------------------------------------------------------
// ANTENA RFID - MFRC522 - Antena MFRC522 (D49-Rst D50-MISO D51-MOSI D52-Sck D53-SS/Sda)
//-------------------------------------------------------------------------------------------------------------------------
//#define RST_PIN                              49   //MFRC522                            //  49 = Reset Pin RFID  -      D49
//#define MISO_PIN                             50   //MFRC522                            //  50 = Miso Pin RFID   -      D50
//#define MOSI_PIN                             51   //MFRC522                            //  51 = Mosi Pin RFID   -      D51
//#define SCK_PIN                              52   //MFRC522                            //  52 = Sck Pin  RFID   -      D52
//#define SS_PIN                               53   //MFRC522                            //  53 = SS Pin   RFID   -      D53
//
//#define DEBUG true
//
//MFRC522 mfrc522(53, 49);   // Create MFRC522 instance.
//
//MFRC522::MIFARE_Key key;

WIEGAND RFID_reader;

//------------------------------------------------------------------------------------------------------
// Variaveis Globais
//------------------------------------------------------------------------------------------------------
double correcao_motor_dir = 0.77;   // 70->1
double correcao_motor_esq = 1.00;     // 70-> 0.88
int calibracao_motor_en = 0;
int velocidade_manual = 215;

String content = "";
String tag_Destino = "";

String comando;  //recebe a mensagem do Supervisorio

String data_atual = "";
String data_old = "";
String conteudo = "";
boolean isReceberRota = true;

String msg_telemetria = "";
int ult_codigo_lido = 0;
int modo_operacao = 0;
int bif_count = 0;

//------------------------------------------------------------------------------------------------------
// Alertas Visuais
//------------------------------------------------------------------------------------------------------

int alertaVisual = 0;
int alertaVisualOn = 0;
int aux_aV = 0;

//------------------------------------------------------------------------------------------------------
// Variaveis dos Pinos Atuador
//------------------------------------------------------------------------------------------------------

int estado_atuador = 0;
int aux_atuador = 0;

int ponto_temporizado = 0;
int ponto_retardo_vel = 0;
int aux_pt = 0;
int aux_rv = 0;

int aux_t1 = 0;


//------------------------------------------------------------------------------------------------------
// ESTADO SWITCHES - PINO ATUADOR
//------------------------------------------------------------------------------------------------------

int SW1_Sup = 0;
int SW1_Inf = 0;

//------------------------------------------------------------------------------------------------------
// Variaveis de Tempo
//------------------------------------------------------------------------------------------------------

int t1 = 0; // Variaveis de Tempo para Movimento Cego
int t2 = 0;

int ponto_bif = 0;
int aux_bif = 0;
int gatilho = 0;
int gatilho100 = 0;

//------------------------------------------------------------------------------------------------------
// Variaveis de Comunicacao
//------------------------------------------------------------------------------------------------------

char buffer[10];
char valor[7];
int a = 0;
int i = 0;
int aux_com = 0;

//------------------------------------------------------------------------------------------------------
// Variaveis WIFI
//------------------------------------------------------------------------------------------------------

//int status = WL_IDLE_STATUS; //STATUS TEMPORÁRIO ATRIBUÍDO QUANDO O WIFI É INICIALIZADO E PERMANECE ATIVO
////ATÉ QUE O NÚMERO DE TENTATIVAS EXPIRE (RESULTANDO EM WL_NO_SHIELD) OU QUE UMA CONEXÃO SEJA ESTABELECIDA
////(RESULTANDO EM WL_CONNECTED)
//
//WiFiEspServer server(80); //CONEXÃO REALIZADA NA PORTA 80
//
//RingBuffer buf(8); //BUFFER PARA AUMENTAR A VELOCIDADE E REDUZIR A ALOCAÇÃO DE MEMÓRIA
//
//int statusLed = LOW; //VARIÁVEL QUE ARMAZENA O ESTADO ATUAL DO AGV (LIGADO / DESLIGADO)

//-------------------------------------------------------------------------------------------------------------------------
// Comandos VARIAVEIS para JOYSTICK
//-------------------------------------------------------------------------------------------------------------------------

int mSpeed_Dir = 0;
int mSpeed_Esq = 0;

int xPosition = 0;
int yPosition = 0;

int Joy_State = 0;

unsigned int pwm1;
unsigned int pwm2;

//Variáveis dos valores máximos e mínimos para os cálculos da função fixar:
int Valor_Xmax = 1023;
int Valor_Xmin = 0;
int Valor_Ymax = 1023;
int Valor_Ymin = 0;
int Valor_Y1max = 0;
int Valor_Y2max = 0;
int aux_reverse = 1;
//-------------------------------------------------------------------------------------------------------------------------
// Comandos VARIAVEIS CRUZAMENTO DE ROTAS
//-------------------------------------------------------------------------------------------------------------------------

int cruzamento_1 = 0;
int espera_C_1 = 0;
int cruzamento_2 = 0;
int espera_C_2 = 0;

//------------------------------------------------------------------------------------------------------
// Variaveis para Sensor de Percurso
//------------------------------------------------------------------------------------------------------

double inChar = 0;
double posicao = 0;
double posicao_old = 0;
double delta_posicao = 0;
int aux_posicao = 1000;
int seg_opt_fre = 1; // define navegacao optica ou frequencia
int vgirar = 0;
int fugaPerc = 0;
int aux_jpulse = 0;
int JBifurcacao = 0;       // Variavel leitura Junction Pulse - Sensor de Percurso

int readVal, positionVal;   // Variables to store analog and line position value
unsigned int junctionCount = 0;   // Variable to store junction count value

//------------------------------------------------------------------------------------------------------
// Variaveis de Velocidade dos Motores
//------------------------------------------------------------------------------------------------------

float vel_M1 = 0;
float vel_M2 = 0;
float vel_maxima = 200;
float cv1 = 1; // variavel para alterar a velocidade pela serial
float cv2 = 1; // variavel para alterar a velocidade de arranque
float cv3 = 1; // variavel para alterar a velocidade quando existir obstaculo na area 2
float aux_cv3 = 1;
float aux_giro = 0;
float aux_vel_M2 = 0;
double aux_vel_M = 0;
double compensacao_M1 = 0;
double compensacao_M2 = 0;
double saida_M1 = 0;
double saida_M2 = 0;

//------------------------------------------------------------------------------------------------------
// Variaveis de Controle PID
//------------------------------------------------------------------------------------------------------
// Target – It is the position you want the line follower to always be(or try to be),that is, the center 
// of the robot. Current Position – It is the current position of the robot with respect to the line.

double set_point = 4500 ;
float aux_set_point;

double PID_kp = 12;  // 180 -> 12 70 -> 5
double PID_ki =  0.0001; //0.002
double PID_kd = 50;  // 180 -> 30 70 -> 30

double kp = PID_kp;     //3->50  5->100    15 ->180 
double ki = PID_ki;     //0->0   0->100     0 -> 180
double kd = PID_kd;     //0->50   10->100  25 -> 180

double correction = 0;
double Error = 0;
double Error_old = 0;
double Proporcional = 0;
double Integral = 0;
double Derivativo = 0;

double delta = 0;
double t_old = 0;
double t_now = 0;


//------------------------------------------------------------------------------------------------------
// Variaveis dos BOTOES
//------------------------------------------------------------------------------------------------------

int bot_lib_AGV = 0;
int aux_lib_AGV = 0;
int last_aux_lib_AGV = 0;
int bot_emergencia = 0;
int estado_automatico = 0;
int estado_manual = 0;
int ligado;
int aux_bot;
int aux_bot_lib = 0;

//------------------------------------------------------------------------------------------------------
// Variaveis de SEGURANCA
//------------------------------------------------------------------------------------------------------

int emergencia = 0;
int auxEmergencia = 0;
int liberado = 0;
int aux_liberado = 0;

int Keyence_Area_Interna;
int Keyence_Area_Intermediaria;
int Keyence_Area_Externa;
int Keyence_Area_AUX4;
int aux_Keyence = 0;

int Estado_Key_a;
int Estado_Key_b;
int Estado_Key_c;
int Estado_Key_d;
int Estado_Key_A;
int Estado_Key_B;
int Estado_Key_C;
int Estado_Key_D;
int aux_bancos = 0 ;

int luz_som = 0;
int aux_luz_som = 0;
int luz_som_2 = 0;
int aux_luz_som_2 = 0;

int agv_cego = 0;
int auxUS = 0;

//------------------------------------------------------------------------------------------------------
// Variaveis de Leitura da Tensao da Bateria
//------------------------------------------------------------------------------------------------------

float tensaoEntrada = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DE TENSÃO DE ENTRADA DO SENSOR
float tensaoMedida = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DA TENSÃO MEDIDA PELO SENSOR

String Min_Bat = "23.5";
String tensaoBateria = "";
String tensaoBateriaTelemetria = "";

float valorR1 = 30000.0; // VALOR DO RESISTOR 1 DO DIVISOR DE TENSÃO
float valorR2 = 7500.0;  // VALOR DO RESISTOR 2 DO DIVISOR DE TENSÃO
float Leitura_Sensor = 0;   // VARIÁVEL PARA ARMAZENAR A LEITURA DO PINO ANALÓGICO




// DECLARAÇÃO DA VARIÁVEL AUXILIAR
int sensorValue_aux = 0;

// DECLARAÇÃO DA VARIÁVEL DA CONSTANTE DO ADC 5/1023
float VoltsporUnidade = 0.00488;// 5v/1023

//DECLARAÇÃO DA VARIÁVEL DE SENSIBILIDADE DO ACS712
float sensibilidade = 0.100;

//------------------------------------------------------------------------------------------------------
// DECLARACOES PARA MODBUS
//------------------------------------------------------------------------------------------------------
#define baud 9600
#define timeout 1000
#define polling 200 // the scan rate

#define retry_count 10

// This is the easiest way to create new packets
// Add as many as you want. TOTAL_NO_OF_PACKETS
// is automatically updated.

enum
{
  PACKET1,
  PACKET2,
  TOTAL_NO_OF_PACKETS // leave this last entry
};


// Data read from the arduino slave will be stored in this array
// if the array is initialized to the packet.
float readRegs[1];

// Data to be written to the arduino slave
float writeRegs[1];

//------------------------------------------------------------------------------------------------------
// FUNCOES Auxiliares
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
// LEDS RGB
//------------------------------------------------------------------------------------------------------

// How many leds in your strip?
#define NUM_LEDS 44

// Define the array of leds
CRGB leds[NUM_LEDS];

//------------------------------------------------------------------------------------------------------
// PROGRAMA - CONFIGURACOES
//------------------------------------------------------------------------------------------------------

void setup() {

  //------------------------------------------------------------------------------------------------------
  // PROGRAMA - ANTENAS E REAL TIME CLOCK
  //------------------------------------------------------------------------------------------------------

  //VALOR REFERENCIAL
  analogReference(DEFAULT);

  //------------------------------------------------------------------------------------------------------
  // PROGRAMA - INICIALIZACAO SABERTOOTH E DEMAIS SERIAIS
  //------------------------------------------------------------------------------------------------------

  Serial.begin(115200);

  //  Wire.begin();                                     // Inicia I2C
  //
  //SPI.begin();                                      // Inicia SPI bus
  
  //
  //mfrc522.PCD_Init();                               // Inicia MFRC522 RFID AZUL
  //mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);   // Increase Antenna Power

  RFID_reader.D0PinA = 20;  
  RFID_reader.D1PinA = 21; 

  // RFID Reader enable
  RFID_reader.begin(1, 0, 0);  // RFID_reader.begin(GateA , GateB, GateC)
  
  //
  //  XBee1.begin(9600);                                            // Inicia Serial 1 Antena Xbee   - D18 (TxD1) & D19 (RxD1)
  //
  //  WIFI.begin(9600);
  //
  //Serial.println("Inicializando Comunicacao WIFI...");
  //
  //  WiFi.init(&WIFI); //INICIALIZA A COMUNICAÇÃO SERIAL COM O ESP8266
  //  WiFi.config(IPAddress(192,168,100,150)); //COLOQUE UMA FAIXA DE IP DISPONÍVEL DO SEU ROTEADOR
  //
  //   //INÍCIO - VERIFICA SE O ESP8266 ESTÁ CONECTADO AO ARDUINO, CONECTA A REDE SEM FIO E INICIA O WEBSERVER
  //  if(WiFi.status() == WL_NO_SHIELD){
  //    while (true);
  //  }
  //  status = WiFi.begin(SSID, PASSWORD);
  //  server.begin();
  //  //FIM - VERIFICA SE O ESP8266 ESTÁ CONECTADO AO ARDUINO, CONECTA A REDE SEM FIO E INICIA O WEBSERVER

  //------------------------------------------------------------------------------------------------------
  // PROGRAMA - CONECTANDO A REDE WIRELESS
  //------------------------------------------------------------------------------------------------------

  Serial.println("Inicializando Lanternas e Avisos...");
  
  pinMode(PIN_Buzzer, OUTPUT);                       // 08
    
  digitalWrite(PIN_Buzzer, LOW);                       // Buzzer
  delay(3000);
  digitalWrite(PIN_Buzzer, HIGH);                       // Buzzer

  FastLED.addLeds<WS2811, LED_PIN_DIR, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2811, LED_PIN_ESQ, RGB>(leds, NUM_LEDS);

  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
    // Turn our current led on to white, then show the leds
    leds[whiteLed] = CRGB::White;

    // Show the leds (only one of which is set to white, from above)
    
  }
  FastLED.show();
  //------------------------------------------------------------------------------------------------------
  // PROGRAMA - LEITURA DAS SAIDAS E ENTRADAS DIGITAIS (CHAVES - BOTOES - SENSORES)
  //------------------------------------------------------------------------------------------------------

  pinMode(Y_Joy, INPUT);                             // 00
  pinMode(X_Joy, INPUT);                             // 02


  pinMode(PIN_Sensor_Percurso_Optico, INPUT);        // 01

  pinMode(LED_PIN_DIR, OUTPUT);                      // 02
  pinMode(LED_PIN_ESQ, OUTPUT);                      // 04

//  pinMode(KSI_Curtis_M1, OUTPUT);                    // 07    Ligado na chave geral
//  pinMode(KSI_Curtis_M2, OUTPUT);                    // 11    Ligado na chave geral
  pinMode(PWM_M1_Curtis, OUTPUT);                    // 05
  pinMode(PWM_M2_Curtis, OUTPUT);                    // 03
  pinMode(Reverse_M1_Curtis, OUTPUT);                // 09
  pinMode(Reverse_M2_Curtis, OUTPUT);                // 13

  pinMode(PIN_Tensao_Bateria, INPUT);                // 08
  pinMode(PIN_Temperatura_M1, INPUT);                // 40

  pinMode(JPulse_Percurso_Optico, INPUT);            // 10

  pinMode(PIN_Keyence_AUX1_INTERNA, INPUT);          // 23
  pinMode(PIN_Keyence_AUX2_INTERMED, INPUT);         // 25
  pinMode(PIN_Keyence_AUX3_EXTERNA, INPUT);          // 27
  pinMode(PIN_Keyence_AUX4, INPUT);                  // 29
  pinMode(PIN_Keyence_Reset, OUTPUT);                // 12

  pinMode(SW_P1_PMI, INPUT);                         // 30
  pinMode(SW_P1_PMS, INPUT);                         // 31

  pinMode(PIN_Chave_Seletora_Auto, INPUT);           // 32
  pinMode(PIN_Chave_Seletora_Manual, INPUT);         // 34
  pinMode(PIN_Botao_Libera_AGV, INPUT);              // 36
  pinMode(PIN_Botao_Emergencia, INPUT);              // 38

  pinMode(BANCO_a, OUTPUT);                          // 22
  pinMode(BANCO_b, OUTPUT);                          // 24
  pinMode(BANCO_c, OUTPUT);                          // 26
  pinMode(BANCO_d, OUTPUT);                          // 28

  pinMode(BANCO_A, OUTPUT);                          // 37
  pinMode(BANCO_B, OUTPUT);                          // 39
  pinMode(BANCO_C, OUTPUT);                          // 41
  pinMode(BANCO_D, OUTPUT);                          // 43

  pinMode(PIN_Right_Enabled, OUTPUT);                // 44 - Controle Motor Pino Atuador
  pinMode(PIN_Left_PWM, OUTPUT);                     // 45 - Controle Motor Pino Atuador
  pinMode(PIN_Right_PWM, OUTPUT);                    // 46 -Controle Motor Pino Atuador
  pinMode(PIN_Left_Enabled, OUTPUT);                 // 47 - Controle Motor Pino Atuador

  //------------------------------------------------------------------------------------------------------
  // ESTADO DE INICIALIZACAO DAS VARIAVEIS
  //------------------------------------------------------------------------------------------------------
  
  
  digitalWrite(PIN_Buzzer, HIGH);                       // Buzzer

  // Inicia Parâmetros Curtis
  digitalWrite(Reverse_M1_Curtis, HIGH);
  digitalWrite(Reverse_M2_Curtis, HIGH);

  

  digitalWrite(PIN_Botao_Libera_AGV, LOW); //PINO 13 INICIA DESLIGADOr

  // Inicia Pino Comunicação


  // Inicia Parâmetros do Pino
  digitalWrite(PIN_Right_Enabled, HIGH);
  digitalWrite(PIN_Left_Enabled, LOW);
  digitalWrite(PIN_Right_PWM, LOW);
  digitalWrite(PIN_Left_PWM, LOW);
  SW1_Sup = digitalRead(SW_P1_PMS);
  SW1_Inf = digitalRead(SW_P1_PMI);
  
  analogWrite(PWM_M1_Curtis, 0);
  analogWrite(PWM_M2_Curtis, 0);
  Bancos_Keyence(0);
  digitalWrite(PIN_Keyence_Reset, LOW);

  saida_M1 = 0;
  saida_M2 = 0;

  delay(500);
  digitalWrite(PIN_Keyence_Reset, HIGH);
  digitalWrite(PIN_Keyence_Reset, LOW);
  delay(500);
  digitalWrite(PIN_Keyence_Reset, HIGH);
  
      

//  if (SW1_Inf != 1) {
//    atuador();
//    Serial.println("atuador");
//    while (SW1_Inf != 1) {
//      atuador();
//    }
//  }

  
  // Inicia estado de operação
 modo_operacao = 0; // 0 = partida suave, 1 = em movimento, 2  = parada suave, 3 = parado

  //------------------------------------------------------------------------------------------------------                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           ------------------------------------------------------------------------
  // TAGS COM SISTEMA SUPERVISORIO
  //------------------------------------------------------------------------------------------------------
  //
  //  elipse.DigitalTags(10);
  //
  //  elipse.AnalogTags(10);
  //

  //Serial (Serial1)
  //Serial_setup();

  //PID
  //PID_setup();
  
}

//------------------------------------------------------------------------------------------------------
// PROGRAMA - LOOP
//------------------------------------------------------------------------------------------------------

void loop()
{

  //------------------------------------------------------------------------------------------------------
  // PROGRAMA - LOOP - LEITURA DE VARIAVEIS
  //------------------------------------------------------------------------------------------------------
  //Serial.println("inicio do loop");
  //Serial.println("0");
  Ler_Inputs();     //VERIFICA OS ESTADOS DOS BOTÕES E LEITURA DO RFID
  //Serial.println("1");
  Ler_Keyence();    //VERIFICA AREAS DO SCANNER DE SEGURANÇA


  //Leitura_Sensor = analogRead(PIN_Tensao_Bateria);
  //leitura_dos_sensores();

  kp = PID_kp;     //
  ki = PID_ki;     //
  kd = PID_kd;     // 

  gatilho = disparo25();      //USADO PARA DISPARO A CADA 25ms
  gatilho100 = disparo100();  //USADO PARA DISPARA A CADA 100ms
  
  // BOTÃO DE EMERGENCIA PRECIONADO
  if (bot_emergencia != LOW){
    bot_lib_AGV = 0;          //FORÇA O AGV PARA ESTADO NÃO LIBERADO 
    parar_emergencia();       //PARA O AGV
//    Serial.println("Botão de Emergência");
  }

  // MODO MANUAL
  if (bot_emergencia != HIGH && estado_manual == HIGH){
        leitura_dos_sensores();   //REALIZA A LEITURA DO SENSOR DE FAIXA
        ALL_YELLOW();             //COR INDICATIVA DO MODO MANUAL
        cv2 = 1;                  
        cv3 = 1;
        aux_bif = 0;
//      Serial.println(posicao);
        if (gatilho100 == 1){     //REALIZA A LEITURA DA POSICAO DO JOYSTICK E ACIONAMENTO DOS MOTORES A CADA 100ms
        joystick();
        }
        
        if (aux_lib_AGV == 1) {   //ACIONAMENTO DO ATUADOR VIA BOTÃO DE LIBERAÇÃO DO AGV
          atuador();
        }
        bot_lib_AGV = 0;          //FORÇA O AGV PARA ESTADO NÃO LIBERADO

//        Serial.println("manual");
//        Serial.print("X \t");
//        Serial.println(xPosition);
//        Serial.print("Y \t");
//        Serial.println(yPosition);
//        Serial.print("SW1 Sup \t");
//        Serial.println(SW1_Sup);
//        Serial.print("SW1 Inf \t");
//        Serial.println(SW1_Inf);
        
                  
  }


  //MODO AUTOMATICO E LIBERADO
  if (bot_emergencia != HIGH && estado_manual != HIGH && bot_lib_AGV == 1 ){

  // AGV MODO DE OPERACAO 0 - PARTIDA SUAVE ---------------------------------------------

    switch (modo_operacao) {
              
      case 0:   // partida suave
        
  //      if (gatilho == 1){    //CALCULO DE COMPENSACAO PARA SEGUIR A FAIXA A CADA 25ms
        controle();
  //      }
        if (Keyence_Area_Interna == HIGH){ //PARADA DO AGV EM CASO DE ACIONAMENTO DA AREA MAIS INTERNA DO SCANNER DE SEGURANÇA
          parar_emergencia();
        }
        else{
          if(aux_vel_M < vel_maxima){
          saida_M1 = aux_vel_M + compensacao_M1;    //CALCULO DO SINAL DE SAIDA MOTOR M1 (MOTOR DIREITO)
          saida_M2 = aux_vel_M + compensacao_M2;    //CALCULO DO SINAL DE SAIDA MOTOR M2 (MOTOR ESQUERDO)
          
          Acionamento_M1_Curtis_Manual(saida_M1);    //ACIONAMENTO SUAVE DE M1 (MOTOR DIREITO)
          Acionamento_M2_Curtis_Manual(saida_M2);    //ACIONAMENTO SUAVE DE M2 (MOTOR ESQUERDO)
          aux_vel_M = aux_vel_M + 0.05;
          
          ALL_BLUE();   // COR INDICATIVA DE AGV EM AUTOMATICO E LIBERADO
          }     
          else { // VERIFICAR LOGICA  //VERIFICAÇAO DO TERMINO DO ARRANQUE
            modo_operacao = 1;
            ALL_BLACK();      
            }
          }                                
        break;


// AGV MODO DE OPERACAO 1 - MOVIMENTACAO ---------------------------------------------

      case 1:    //Modo em movimentação
        
//        if (gatilho == 1){    //CALCULO DE COMPENSACAO PARA SEGUIR A FAIXA A CADA 25ms
        controle(); 
//        //Serial.println(posicao); 
//        }
        
        if (Keyence_Area_Interna == HIGH){ //PARADA DO AGV EM CASO DE ACIONAMENTO DA AREA MAIS INTERNA DO SCANNER DE SEGURANÇA
          parar_emergencia();
        }
        
        else{
          saida_M1 = vel_maxima + compensacao_M1;    //CALCULO DO SINAL DE SAIDA MOTOR M1 (MOTOR DIREITO)
          saida_M2 = vel_maxima + compensacao_M2;    //CALCULO DO SINAL DE SAIDA MOTOR M2 (MOTOR ESQUERDO)

          Acionamento_M1_Curtis_Manual(saida_M1);   //ACIONAMENTO DE RESPOSTA RAPIDA DE M1 (MOTOR DIREITO)
          Acionamento_M2_Curtis_Manual(saida_M2);   //ACIONAMENTO DE RESPOSTA RAPIDA DE M2 (MOTOR ESQUERDO)
          Serial.print(saida_M2 *  cv1 * cv2 * cv3 * correcao_motor_esq);
          Serial.print("\t ");
          Serial.println(saida_M1 *  cv1 * cv2 * cv3 * correcao_motor_dir);
        
          ALL_BLUE();     // COR INDICATIVA DE AGV EM AUTOMATICO E LIBERADO
        }
      break;
       
      }
    }

// ESTADO AUTOMÁTICO E NÃO LIBERADO  
  if (bot_emergencia != HIGH && estado_manual != HIGH && bot_lib_AGV == 0 ){
   
    Acionamento_M1_Curtis_Manual(0);      //PARA O AGV
    Acionamento_M2_Curtis_Manual(0);      //PARA O AGV

    //----------- REINICIA PARAMETROS DE CONTROLE DO MODO AUTOMATICO DO AGV
    
    aux_vel_M = 0; 
    
    //Serial.println("AGV automatico e  Nao liberado");
       
    modo_operacao = 0;

    correction = 0;
    Error = 0;
    Error_old = 0;
    Integral = 0;
    Derivativo = 0;
    set_point = 4500;
    aux_vel_M = 0;
    
    ALL_GREEN();  //COR INDICATIVA DO MODO DE OPERAÇÃO AUTOMATICO E NÃO LIBERADO
  }
  //PID --------------------------------------------------------------
 /*
  if (pulse_50ms) {
    int vel_mot_dir;
    int vel_mot_esq;
    PID_loop(posicao, set_point);
    PID_output_motors(vel_mot_dir, vel_mot_esq, 180, 215);
    Acionamento_M1_Curtis_Manual(vel_mot_dir);
    Acionamento_M2_Curtis_Manual(vel_mot_esq);
  }
 */
  //PID end ----------------------------------------------------------

  //Serial (Serial1)
  // Serial_loop();
  
  //Serial.println("Fim do Ciclo");
  //Serial.println("end");

  //Tempo ciclo e status --------------------------------------------------------------
  static unsigned long count_TemCic;
  static unsigned long lastMillis_TemCic;
  static unsigned long prevMillis_TemCic;
  unsigned long curMillis_TemCic = millis();

  if (curMillis_TemCic - lastMillis_TemCic > count_TemCic){
    count_TemCic = curMillis_TemCic - lastMillis_TemCic;
  }
  lastMillis_TemCic = curMillis_TemCic;
  
  if (curMillis_TemCic - prevMillis_TemCic >= 200) {
    prevMillis_TemCic = curMillis_TemCic;
    if (true){
      //Tempo ciclo máximo
      Serial.print("Máx: ");
      Serial.print(count_TemCic);
      Serial.println(" ms");
      count_TemCic = 0;
      
      //Status do AGV
      if (bot_emergencia != HIGH && estado_manual != HIGH && bot_lib_AGV == 0 ){
        Serial.println("AGV automatico e  Nao liberado");
      }
//      if (bot_emergencia != HIGH && estado_manual == HIGH){
//        Serial.println("manual");
//        Serial.print("X \t");
//        Serial.println(xPosition);
//        Serial.print("Y \t");
//        Serial.println(yPosition);
//        Serial.println(posicao);
//        Serial.print("SAIDA M1 \t");
//        Serial.println(Valor_Y1max * aux_reverse);
//        Serial.print("SAIDA M2 \t");
//        Serial.println(Valor_Y2max * aux_reverse);
//      }
    }
    //Serial_loop();
  } 
  //Fim Tempo ciclo e status ----------------------------------------------------------

}



//------------------------------------------------------------------------------------------------------
// Fim CODIGO - The End!
//------------------------------------------------------------------------------------------------------
