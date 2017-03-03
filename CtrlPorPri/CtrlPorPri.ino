#include <SPI.h>
//#include "nRF24L01.h"
//#include "RF24.h"
#include "printf.h"

//Primeira versao
/*23022017 - Retirado codigo de envio via interface nRF24L01 */
//RF24 radio(9, 10);


//const uint64_t pipe = 0xF0F0F0F0E1LL;

int inClosed = 7;
int inOpened = 6;
int outAct   = 5;
int pinState = 4;


/*struct
{
  int iOpened;
  int iClosed;
  int iOutAct;
}
Dados;*/



String inputString = "";
bool bIniciou = false;

void setup()
{
  pinMode(inClosed, INPUT_PULLUP);
  pinMode(inOpened, INPUT_PULLUP);
  pinMode(outAct, OUTPUT);
  pinMode(pinState,OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(inClosed), Action, CHANGE);
  attachInterrupt(digitalPinToInterrupt(inOpened), Action, CHANGE);
  digitalWrite(outAct, LOW);
  digitalWrite(pinState, LOW);
  /*radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();*/
  Serial1.begin(9600);
  //Serial.begin(9600);
  //printf_begin();

  /*if (Serial)
    printf("Iniciando versao 1.0.0 \r\n");*/

  while (!Serial1);

  inputString.reserve(200);
  warning(20);
}

void loop()
{
  //Indicar inicialização
  if (!bIniciou)
  {
    bIniciou = true;
    digitalWrite(pinState, HIGH);
  }
  
  while (Serial1.available())
  {
    char inChar = (char)Serial1.read();
    if (inChar != '\n')
      inputString += inChar;

    if (inChar == '\n')
    {

      if (inputString == "Act")
      {

        /*if (Serial)
          printf("Comando de acionamento do portao recebido do linux...\r\n");*/
        AcionarPortao();
        warning(2);
        digitalWrite(pinState, HIGH);
        //Dados.iOutAct = 1;
        //radio.stopListening();
        //radio.openWritingPipe(pipe);
        //bool ok = radio.write(&Dados,sizeof(Dados));

        //if(!ok && Serial)
          //printf("Falhou envio...\r\n");

        //radio.openReadingPipe(1,pipe);
        //radio.startListening();
      }
      else if ( inputString == "version"){
        Serial1.println("version 1.0.0");   
      }
      else if (inputString == "getState"){
            
      }
      

      inputString = "";
    }
  }
 /*if (radio.available())
  {

    if(Serial)
      printf("radio disponivel\r\n");
    bool done = false;
    while (!done)
    {      
      done = radio.read(&Dados, sizeof(Dados));
      if(done)
      {
        if(Serial)
          printf("dados recebidos iOutAct: %d\r\n",Dados.iOutAct);
        
      }
    }
  }*/
  
  
    
     
    
  

}
void Action()
{
  
}

void AcionarPortao(){
   digitalWrite(outAct, HIGH);
   delay(1000);
   digitalWrite(outAct, LOW);
}

void warning(int pulses)
{
  for (int i=0;i<pulses;i++)
  {
   digitalWrite(pinState, HIGH);
   delay(50);
   digitalWrite(pinState, LOW);
   delay(50);
  }
  
}






