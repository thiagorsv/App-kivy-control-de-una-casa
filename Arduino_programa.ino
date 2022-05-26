#include <Servo.h>   //Librerias para los servomotores

//------------------------------------------
//----------Definir Pines-------------------

const int foco_cocina = 8;
const int foco_sala = 9;
const int foco_cuarto = 10;
const int foco_banio = 11;
const int cerradura_puerta = 5;
const int cerradura_sala = 6;
const int cerradura_cuarto = 7;
const int sirena_puerta = 2;
const int sirena_sala = 3;
const int sirena_cuarto = 4;
const int entrada_s_puerta = A0;
const int entrada_s_sala = A1;
const int entrada_s_cuarto = A2;


//--------Nombrar los servomotores--------------

Servo servo_puerta;
Servo servo_sala;
Servo servo_cuarto;


//-------------------------------------------
//-----------Funciones------------------------

//void checar_sirenas();

//-------------------------------------------

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);//Baudios en la comunicaion serial
  //Colocar pines como salida para los focos
  pinMode(foco_cocina, OUTPUT);
  pinMode(foco_sala, OUTPUT);
  pinMode(foco_cuarto, OUTPUT);
  pinMode(foco_banio, OUTPUT);
  
  //Colocar los pines como conexiones a los servomotores
  servo_puerta.attach(cerradura_puerta);
  servo_sala.attach(cerradura_sala);
  servo_cuarto.attach(cerradura_cuarto);
  //Iniciar las cerraduras abiertas
  servo_puerta.write(180);
  servo_sala.write(180);
  servo_cuarto.write(180);
  delay(1000);

  //Las entradas analogicas no son necesarias en setup(),
  //las entradas de los sensores de mov. estan en A0,A1 y A2.
  //
  //Colocar pines como salida para activar las sirenas
  pinMode(sirena_puerta, INPUT);
  pinMode(sirena_sala, INPUT);
  pinMode(sirena_cuarto, INPUT);
}


//-----------------------------------------
//----------Iniciar varisbles------------

String recibido = "";
int lectura_analogica0,lectura_analogica1,lectura_analogica2;

//------------------------------------------
//----------Codigo principal----------------

void loop() {
  if(Serial.available()){
    recibido = Serial.readString(); //leer el primer dato enviado por la app
    delay(3);       //Delay para mantener la estabilidad
    if(recibido == "FC1") digitalWrite(foco_cocina, HIGH);
    else if(recibido == "FC0") digitalWrite(foco_cocina, LOW); 
    else if(recibido== "FS1") digitalWrite(foco_sala, HIGH);
    else if(recibido == "FS0") digitalWrite(foco_sala, LOW); 
    else if(recibido== "FR1") digitalWrite(foco_cuarto, HIGH);
    else if(recibido == "FR0") digitalWrite(foco_cuarto, LOW); 
    else if(recibido== "FB1") digitalWrite(foco_banio, HIGH);
    else if(recibido == "FB0") digitalWrite(foco_banio, LOW); 
    else if(recibido == "CP1") {servo_puerta.write(180); delay(1000);}
    else if(recibido == "CP0") {servo_puerta.write(0); delay(1000);}
    else if(recibido == "CS1") {servo_sala.write(180); delay(1000);}
    else if(recibido == "CS0") {servo_sala.write(0); delay(1000);}
    else if(recibido == "CC1") {servo_cuarto.write(180); delay(1000);}
    else if(recibido == "CC0") {servo_cuarto.write(0); delay(1000);}
    else if(recibido == "FB0") digitalWrite(foco_banio, LOW);
    else if(recibido == "FB0") digitalWrite(foco_banio, LOW);
    else if(recibido == "FB0") digitalWrite(foco_banio, LOW);
    else if(recibido == "SP1") digitalWrite(sirena_puerta, HIGH);
    else if(recibido == "SP0") digitalWrite(sirena_puerta, LOW); 
    else if(recibido == "SS1") digitalWrite(sirena_sala, HIGH);
    else if(recibido == "SS0") digitalWrite(sirena_sala, LOW); 
    else if(recibido == "SC1") digitalWrite(sirena_cuarto, HIGH);
    else if(recibido == "SC0") digitalWrite(sirena_cuarto, LOW);
    delay(1);
    recibido = ""; 
  }
  else{
  lectura_analogica0 = analogRead(A0);
  lectura_analogica1 = analogRead(A1);
  lectura_analogica2 = analogRead(A2);
  if(lectura_analogica0 >= 635) Serial.write('P');
  if(lectura_analogica1 >= 635) Serial.write('S');
  if(lectura_analogica2 >= 635) Serial.write('C');
  delay(100);
  }
}
