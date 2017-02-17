
#include <LiquidCrystal.h>
//#include <VirtualWire.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
String inputString = "";

void setup() 
{
  pinMode(13, OUTPUT);
  Serial.begin(9600); 
  while (!Serial);
  lcd.begin(16, 2);
  lcd.print("Connectado!");
  inputString.reserve(200);
//  vw_set_tx_pin(8);
 // vw_setup(2000);   // Bits per sec
}

void loop() 
{
  lcd.setCursor(0,1);
  while (Serial.available()) 
  {
    char inChar = (char)Serial.read(); 
    
    if (inChar != '\n') 
      inputString += inChar;
    
    if (inChar == '\n') 
    {
      lcd.setCursor(0, 1);
      lcd.print("                ");
      if(inputString == "Act")
      {
        lcd.setCursor(0,1);
        lcd.print("Acionando Portao");
        digitalWrite(13, HIGH);  
        delay(1000);
        digitalWrite(13, LOW);
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print("Portao Acionado");
        delay(1000);
        lcd.setCursor(0,1);
        lcd.print("                ");
        //send((char*)"Act");
      }
      else if(inputString.substring(0,4) == "Hour") 
      {
        lcd.setCursor(0, 1);
        inputString.remove(0,4);
        lcd.print(inputString);        
      }
      else
      {
        lcd.setCursor(0, 1);
        lcd.print(inputString);
      }
      inputString = "";
    } 
  }
  
  //lcd.setCursor(0, 1);
  //lcd.print(millis()/1000); 
}
/*void send (char *message)
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Aguarda o envio de dados
}*/





