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
  attachInterrupt(digitalPinToInterrupt(inClosed), Action, CHANGE);
  attachInterrupt(digitalPinToInterrupt(inOpened), Action, CHANGE);
  digitalWrite(outAct, LOW);
  /*radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();*/
  Serial1.begin(9600);
  Serial.begin(9600);
  printf_begin();

  if (Serial)
    printf("Iniciando versao 1.0.0 \r\n");

  while (!Serial1);

  inputString.reserve(200);
}

void loop()
{
  if (Serial && !bIniciou)
  {
    bIniciou = true;
    printf("Comunicacao com Linux iniciada!...Aguardando comando...\r\n");
    //printf("Status do radio\r\n");
    //radio.printDetails();
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

        if (Serial)
          printf("Comando de acionamento do portao recebido do linux...\r\n");
        AcionarPortao();

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
        Serial.println("version 1.0.0");   
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





