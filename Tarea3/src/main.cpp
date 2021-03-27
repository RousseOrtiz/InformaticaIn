#include <Arduino.h>
#define btnIN A0
#define LED 10  

enum funMode
{
  OFF,
  BLINK1,
  BLINK2,
  BLINK3,
  BLINK4,
  NBSTATE
};

int L_STD = LOW;
unsigned long pre_Millis, pas_Millis;
unsigned long lastDeTime = 0;       
int LstBSTD = HIGH;               
int btnSTD = 0;                     
int funcSTD = 0;                  
int BP1 = 50, BP2 = 100, BP3 = 200; 
int interB = 100;            

/** desvanecido**/
int brightness= 0; 
int fade = 5; 

unsigned long tiempo;
unsigned long time=0;
unsigned long retardado=100;

void setup()
{
  pinMode(btnIN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
   
}

void loop()
{
  func1(); //Boton de deteccion
  func2(); //Seleccion
  desvanecido();
}

void func1()
{
  int reading = digitalRead(btnIN);
  if (reading != LstBSTD)
  {                        //Ultima estado definido del buton
    lastDeTime = millis(); //ultimo tiempo d rebote
    if ((millis() - lastDeTime) > 100)
    {
      if (reading != btnSTD)
      {
        btnSTD = reading;
      }
      if (btnSTD == HIGH)
      {
        funcSTD += 1;
      }
    }
  }
  LstBSTD = reading;
  funcSTD = funcSTD % NBSTATE;
}

void func2()
{
  switch (funcSTD)
  {
  case OFF:
    //FuncionOFF - LED
    digitalWrite(LED, LOW);
    break;
  case BLINK1:
    //FuncionBlink1 - LED
    funcB1(BP1);
    break;
  case BLINK2:
    //FuncionBlink2 - LED
    funcB2(BP2);
    break;
  case BLINK3:
  //FuncionBlink3 - LED
    funcB3(BP3);
    break;
  //FuncionBlink4 - LED
  case BLINK4:
    funcB4(interB);
    break;
  }
}
void funcB1(int BP1)
{
  delay(BP1);
  digitalWrite(LED, LOW);
  delay(BP1);
  digitalWrite(LED, HIGH);
}
void funcB2(int BP2)
{
  delay(BP2);
  digitalWrite(LED, LOW);
  delay(BP2);
  digitalWrite(LED, HIGH);
}
void funcB3(int BP3)
{
  delay(BP3);
  digitalWrite(LED, LOW);
  delay(BP3);
  digitalWrite(LED, HIGH);
}
void funcB4(int interB) {
  pre_Millis = millis();
  if ((pre_Millis - pas_Millis) >= interB) {
    pas_Millis = pre_Millis;
    if(L_STD = LOW) {
      L_STD = HIGH;
    } else {
      L_STD = LOW;
    }
  }

}

void desvanecido(){
    tiempo = millis ();
  if(tiempo>time+retardado){
  time=tiempo;
  //brillo del pin 9: 
  analogWrite (LED, brightness);
  
 brightness = brightness + fade; 
 // invierte la direccion del fundido 
 if (brightness == 0 || brightness == 255) {
   fade = -fade;
    } 
 
 }
    }