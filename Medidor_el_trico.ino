#include <LiquidCrystal.h>
//#include "EmonLib.h"

const int rs = PB11, en = PB10, d4 = PA7, d5 = PA6, d6 = PC13, d7 = PC14; //mention the pin names to with LCD is connected to
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //Initialize the LCD
float Tensao;
float Corrente;
float Potencia;
float Energia=0;
float EnergiaAux;
int T_sample;
int Fase;
const int PinTensao1=PB0;
const int PinCorrente1=PA0;
const int PinTensao2=PB1;
const int PinCorrente2=PA1;
const int PinTensao3=PA5;
const int PinCorrente3=PA4;
const int PinbotaoMode=PA11;
const int PinbotaoZerar=PA12;
//EnergyMonitor SCT1;
//EnergyMonitor SCT2;
//EnergyMonitor SCT3;
int botaoMode=0;
int estado1;
int estado2;
int estadoAux;
int ZeroTP1;
int ZeroTP2;
int ZeroTP3;
int ZeroTC1;
int ZeroTC2;
int ZeroTC3;
int PotFase1;
int PotFase2;
int PotFase3;
int Potfin;
int i1;
int i2;
int i3;
int v1;
int v2;
int v3;
unsigned long Tempo1;
unsigned long Tempo2;
unsigned long Tempo3;

void setup() {
  
  
  Serial1.begin(9600);
  lcd.begin(16, 2);//We are using a 16*2 LCD
  analogReadResolution(12); 
  pinMode(PinTensao1, INPUT);
  pinMode(PinCorrente1, INPUT);
  pinMode(PinTensao2, INPUT);
  pinMode(PinCorrente2, INPUT);
  pinMode(PinTensao3, INPUT);
  pinMode(PinCorrente3, INPUT);
  pinMode(PinbotaoMode, INPUT);
  pinMode(PinbotaoZerar, INPUT);
  Fase=0;
  T_sample=10;
  estado1=LOW;
  estado2=HIGH;
  estadoAux=0;
  lcd.setCursor(0, 0);
  lcd.print("Aguarde a config");
  lcd.setCursor(0, 1);
  lcd.print("A Vazio");
  delay(2000);
  
  ZeroTP1=ZeroADC(PinTensao1);
  ZeroTP2=ZeroADC(PinTensao2);
  ZeroTP3=ZeroADC(PinTensao3);
  ZeroTC1=ZeroADC(PinCorrente1);
  ZeroTC2=ZeroADC(PinCorrente2);
  ZeroTC3=ZeroADC(PinCorrente3);
  //ZeroTP1=100;
  //ZeroTP2=0;
  //ZeroTP3=0;
  //ZeroTC1=100;
  //ZeroTC2=100;
  //ZeroTC3=100;
  lcd.clear();
  lcd.setCursor(0, 0);
  delay(1500);
  lcd.print("Configurado!");
  delay(1500);
  
}


void loop() {
  Tempo1=micros();  
  if(Fase==0){
    
    //Bloco para teste de valor maximo digital, tempo para realização do analog read.
    //lcd.setCursor(0, 0); //elemento 1x1
    //Tempo1=micros();
    //Tensao = analogRead(PinTensao1);
    //Tempo2=micros();
    //lcd.print(Tensao);
    //lcd.setCursor(0, 1);
    //Tempo3=Tempo2-Tempo1;
    //lcd.print(Tempo2-Tempo1);   
    
    Potencia=LCDMode(botaoMode,Fase,PinCorrente1,PinTensao1,Energia,ZeroTP1,ZeroTC1);
    PotFase1=arredonda(Potencia);
    i1=arredonda(RMS(42.16,PinCorrente1,1000,ZeroTC1));
    v1=arredonda(RMS(1,PinTensao1,1000,ZeroTP1));
    
                                  
  }
  if(Fase==1){
    Potencia=LCDMode(botaoMode,Fase,PinCorrente2,PinTensao2,Energia,ZeroTP2,ZeroTC2);
    PotFase2=arredonda(Potencia);
    i2=arredonda(RMS(42.16,PinCorrente2,1000,ZeroTC2));
    v2=arredonda(RMS(1,PinTensao2,1000,ZeroTP2)); 
  }
  if(Fase==2){
    Potencia=LCDMode(botaoMode,Fase,PinCorrente3,PinTensao3,Energia,ZeroTP3,ZeroTC3);
    PotFase3=arredonda(Potencia);
    i3=arredonda(RMS(54.54,PinCorrente3,1000,ZeroTC3));
    v3=arredonda(RMS(1,PinTensao3,1000,ZeroTP3));
  }

        

          
        if(Serial1.available()>0)      // comunicação serial com o ESP8266
                                       //Cada letra tem um feature sendo enviado
            {
             
             Serial1.write('A');
             if(Serial1.available()>0)
            {
             Serial1.write(PotFase1);}
             
             Serial1.write('B');
             if(Serial1.available()>0)
            {
             Serial1.write(PotFase2);}
             
           
             Serial1.write('C');
             if(Serial1.available()>0)
            {
             Serial1.write(PotFase3);}

             Serial1.write('D');
             if(Serial1.available()>0)
            {
             Serial1.write(i1);}

             Serial1.write('E');
             if(Serial1.available()>0)
            {
             Serial1.write(v1);}


             Serial1.write('F');
             if(Serial1.available()>0)
            {
             Serial1.write(i2);}

             Serial1.write('G');
             if(Serial1.available()>0)
            {
             Serial1.write(v2);}


             Serial1.write('H');
             if(Serial1.available()>0)
            {
             Serial1.write(i3);}


             Serial1.write('I');
             if(Serial1.available()>0)
            {
             Serial1.write(v3);}

             Serial1.write('J');
             if(Serial1.available()>0)
            {
             Serial1.write(arredonda(Energia));}


              }
      


  
        estado1=digitalRead(PinbotaoMode);// Lógica para mudar a variavel botaomode de acordo com o apertar do botao. isso mudara o que o LCD enxergará
        if((estado1==LOW)  and (estadoAux==HIGH)){
          
          if(botaoMode<3){
            botaoMode++;
            lcd.clear();
          }
          else{
            botaoMode=0;
            lcd.clear();
          }
          estadoAux=estado1;
        }
        else{
          estadoAux=estado1;
        }
        
        
        estado2=digitalRead(PinbotaoZerar);  //Lógica para zerar energia.
        if(estado2==HIGH){
          Energia=0;
        }
        



  
        if(Fase<2){       // Mudar de fase a cada loop
          Fase++;
          }
        else {
          Fase=0;
        }

  delay(200);
  Tempo2=micros();
  
  EnergiaAux=(Tempo2-Tempo1)/10000;
  EnergiaAux=EnergiaAux/100;
  EnergiaAux=Potencia*3*EnergiaAux; // Não esta em kw hora
  Energia=EnergiaAux+Energia;
  

  
}


float RMS(float constante, const int pinEntrada, int samples,int zero){

       int i;     // Calculo de RMS discreto para uma só variável. Usar constante para fazer a tranformação na medição elétrica
       float Valor;
       float Result=0;
       for(i=0;i<samples;i++){
           Valor = analogRead(pinEntrada)-zero; // 
           Result=Valor*Valor+Result; 
       }
       Result=Result/samples;
       Result=sqrt(Result);
       Result=constante*Result;   // para o sensor de corrente = (3.3/4096)*(2000/Resistencia)


       return Result;
}
float RMS_simultaneo(float constante1,float constante2,const int pinEntrada1,const int pinEntrada2,int samples,int mode,int zero1, int zero2){

       int i;     // Calculo de RMS discreto ; constante1 e constante2 para transformação da tensao e corrente em valores reais
       float Valor1;
       float Valor2;
       float Result1=0;
       float Result2=0;
       float Resultfinal;
       unsigned long Tempo1;
       unsigned long Tempo2;

       Tempo1=micros();
       for(i=0;i<samples;i++){
       
       Valor1 = analogRead(pinEntrada1)-zero1;   // usar constantes aqui, para transformar em valores reais.
       Valor2 = analogRead(pinEntrada2)-zero2;  // mudar de acordo com o ADC 
       Result1=Valor1*Valor1+Result1; 
       Result2=Valor2*Valor2+Result2;
       }
       Result1=Result1/samples;
       Result2=Result2/samples;
       Result1=sqrt(Result1);
       Result2=sqrt(Result2);
       Result1=constante1*Result1; //para o sensor de corrente = (3.3/4096)*(2000/Resistencia) 
       Result2=constante2*Result2;// para o de tensão é impirico
       Resultfinal=Result1*Result2;
       Tempo2=micros();

       if(mode==0){
        Resultfinal=Resultfinal*(Tempo2-Tempo1)/1000000;   // definir mode=0 para medir a energia.  Converter para unidade de tempo certa
       }
       

       return Resultfinal;
}

float FatordePotencia(const int pinEntrada1,const int pinEntrada2){     // Falta definir quem é um e quem é dois para saber se a corrente esta atrasada ou adiantada
       int i;
       int samples;
       int flag=0;
       float Valor1;
       float Valor2;
       float FatPot;
       unsigned long Tempo1;
       unsigned long Tempo2;
       
       Valor1 = (3.3*analogRead(pinEntrada1))/1024;   
       Valor2 = (3.3*analogRead(pinEntrada2))/1024;

       for(i=0;i<samples;i++){

             if(Valor1==0){              // zero para a transformação de onda adotada. pode não ser zero de fato.
              Tempo1=micros();
              flag++;
             }
             if(Valor2==0){
              Tempo2=micros();
              flag++;
             }
             if(flag==2){
              break;
             }
       }

       FatPot=(Tempo1-Tempo2)/46.2;   //(46.2 é o quanto demora para a onda de 60hz andar um grau) resultado aqui é o numero de graus 
       FatPot=FatPot*(2*3.14159/360); // Passando pra radiano.
       FatPot=cos(FatPot);           //fator de potencia

       return FatPot;
       
       
}

int arredonda(float number)
{
    return (number >= 0) ? (int)(number + 0.5) : (int)(number - 0.5);
}

int ZeroADC(const int A){
      int i;
      int sum=0;
      for(i=0;i<10;i++){
        sum=analogRead(A)+sum;
      }
      sum= (int) sum/10;
      return sum;
}

float LCDMode(int botao,int fase, const int pinI,const int pinV,float E,int zeroV,int zeroI) {
      int a;
      int b;
      float preco=0.5;
      float precofinal;
      float V;
      float I;
      float P;
      P=RMS_simultaneo(1,60.6,pinV,pinI,1000,1,zeroV,zeroI); //Calculo da potencia.
      

      
      if(fase==0){     // setar cursor do LCD de acordo com a fase
        a=9;
        b=0;
      }
      if(fase==1){
        a=2;
        b=1;
      }
      if(fase==2){
        a=9;
        b=1;
      }

  
    if(botao==0){    //Tensão
       // Printando a tela do usuario.
      
       lcd.setCursor(0, 0); //elemento 1x1
       lcd.print("U(volt)A:"); //Print 
       lcd.setCursor(0, 1); //elemento 1x2
       lcd.print("B:"); //Print
       lcd.setCursor(7, 1);
       lcd.print("C:");
       
       V=RMS(1,pinV,1000,zeroV);
       lcd.setCursor(a,b);
       lcd.print(V,1); 
    }
    if(botao==1){  //Corrente

      
       lcd.setCursor(0, 0); //elemento 1x1
       lcd.print("I(Amp) A:"); //Print 
       lcd.setCursor(0, 1); //elemento 1x2
       lcd.print("B:"); //Print
       lcd.setCursor(7, 1);
       lcd.print("C:");
       I=RMS(1,pinI,1000,zeroI);
       lcd.setCursor(a,b);
       lcd.print(I,2); 
    }
    if(botao==2){ // Potencia instantanea
       
       lcd.setCursor(0, 0); //elemento 1x1
       lcd.print("Pot(kW)A:"); //Print 
       lcd.setCursor(0, 1); //elemento 1x2
       lcd.print("B:"); //Print
       lcd.setCursor(7, 1);
       lcd.print("C:");
       lcd.setCursor(a,b);
       lcd.print(P,2);  
    }
    if(botao==3){  // Energia
       
       
       lcd.setCursor(0, 0); //elemento 1x1
       lcd.print("E(kWh):"); //Print 
       lcd.setCursor(0, 1); //elemento 1x2
       lcd.print("Preco:"); //Print
       lcd.setCursor(6, 1);
       precofinal=preco*E;
       lcd.print(precofinal,2);
       
       lcd.setCursor(9,0);
       lcd.print(E,2);
         
    }

    return P;

}
