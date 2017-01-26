#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(9, 10);

//Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xF0F0F0F0E1LL;

int inClosed = 7;
int inOpened = 3;
int outAct   = 13;
int inClosedAnt = -1;
int inOpenedAnt = -1;
int outActAnt   = -1;

struct
{
  int iOpened;
  int iClosed;
  int iOutAct;
}
Dados;


bool bIniciou = false;

void setup()
{
  pinMode(inClosed, INPUT);
  pinMode(inOpened, INPUT);
  pinMode(outAct, OUTPUT);
  //Serial.begin(9600);
  //printf_begin();

  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
 
  digitalWrite(outAct, LOW);
  //while(!Serial);
  /*if (Serial)
  {
    printf("Iniciando Sec\r\n");
  }*/
}

void loop()
{
  Dados.iOutAct = 0;
  /*if (Serial && !bIniciou)
  {
    bIniciou = true;

    printf("Status do radio\r\n");
    radio.printDetails();
  }*/
  if (radio.available())
  {
    /*if (Serial)
    {
      printf("radio.available()\r\n");
    }*/

    bool done = false;
    while (!done)
    {
      /*{
        printf("Data available\r\n");
      }*/
      done = radio.read(&Dados, sizeof(Dados));
      if ( Dados.iOutAct == 1)
      {
        /*if (Serial)
        {
          printf("Comando de acionamento do portao recebido\r\n");
        }*/
        //Ativar portao
        Dados.iOutAct = 0;
        digitalWrite(outAct, HIGH);
        delay(1000);
        digitalWrite(outAct, LOW);
        radio.openWritingPipe( pipe);
        radio.stopListening();
        radio.write(&Dados, sizeof(Dados));
        delay(500);
        radio.startListening();
      }
      else if (Dados.iOutAct == 2)
      {
        Dados.iOpened = digitalRead(inOpened);
        Dados.iClosed = digitalRead(inClosed);
        radio.openWritingPipe( pipe);
        radio.stopListening();
        radio.write(&Dados, sizeof(Dados));
        delay(500);
        radio.startListening();
      }
    }
  }
  
 

  
}




