/*
  Detect and Turn from Obstacle.c

  Detect obstacles in the ActivityBot's path, and turn a random direction to avoid them.

  http://learn.parallax.com/activitybot/roaming-ultrasound
*/

#include "simpletools.h"                      // Include simpletools header
#include "abdrive.h"                          // Include abdrive header
#include "ping.h"                             // Include ping header
#include "adcDCpropab.h"                         // Include adcDCpropab
#include "stdlib.h "
#include "time.h" 

int turn=0;                                     // Navigation variable
int tim=0;
int derecha=0;
int adelante=0;
int izquierda=0;
int atras=0;
int recorridoInverso[3000];
int cruces[50][4];
int numCruces=0;
int temporizador=700;
int distanciaMinima=14;
int contadorRecorrido=0;
int estado=1;
int cruceDerecha=0;
int cruceIzquierda=0;
int cruceAdelante=0;
int cruceAtras=0;
int contadorCrucesDisponibles=0;
int cruceAnterior[4];
int regreso=0;
int estadoCruce[200];
int retorno=0;
int irLeft, irRight, frente;                            // Global variables

int main()                                    // main function
{
  srand(time(NULL)); 
while(1){

  dac_ctr(1, 0, 460);                           // D/A ch 0 -> 2.5 V to D/A 0
  dac_ctr(11, 1, 460);                            // D/A ch 1 -> 1 V to D/A 1
                          
     
drive_setRampStep(10);

validarIzquierda();
validarDerecha();
validarAdelante();

if((irRight==0)&&(irLeft==0)&&(frente==1)){
  avanzaAdelante();
} 
else if((irRight==1)&&(irLeft==0)&&(frente==0)){
  giraDerechaAvanza();
} 
else if((irRight==0)&&(irLeft==1)&&(frente==0)){
  giraIzquierdaAvanza();
}
else if((irRight==1)&&(irLeft==1)&&(frente==0)){
recorridoInverso[contadorRecorrido]=5; 
contadorRecorrido=contadorRecorrido+1;

if(retorno==0){
  estadoCruce[numCruces]=estado;
    interDerIzq();
  cruceAdelante=1;
  cruceAtras=1;
if(turn==1){
  cruceIzquierda=0;
  cruceDerecha=1;
}
else if(turn==0){
  cruceIzquierda=1;
  cruceDerecha=0;
}  

cruces[numCruces][0]=cruceAdelante;
cruces[numCruces][1]=cruceDerecha;
cruces[numCruces][2]=cruceIzquierda;
cruces[numCruces][3]=cruceAtras;
numCruces=numCruces+1;
}
else{
  retorno=0;
  cruce();
}  
}  
else if((irRight==1)&&(irLeft==0)&&(frente==1)){
recorridoInverso[contadorRecorrido]=5; 
contadorRecorrido=contadorRecorrido+1;
  if(retorno==0){
    estadoCruce[numCruces]=estado;
      interDerAdel();
  cruceIzquierda=1;
cruceAtras=1;
if(turn==1){
  cruceAdelante=0;
  cruceDerecha=1;
}
else if(turn==0){
  cruceAdelante=1;
  cruceDerecha=0;
}  

cruces[numCruces][0]=cruceAdelante;
cruces[numCruces][1]=cruceDerecha;
cruces[numCruces][2]=cruceIzquierda;
cruces[numCruces][3]=cruceAtras;
numCruces=numCruces+1;  
}
else{
  retorno=0;
  cruce();
} 
} 
else if((irRight==0)&&(irLeft==1)&&(frente==1)){
recorridoInverso[contadorRecorrido]=5; 
contadorRecorrido=contadorRecorrido+1;
if(retorno==0){
  estadoCruce[numCruces]=estado;
  interIzqAdel();
 
  cruceDerecha=1;
cruceAtras=1;
if(turn==1){
  cruceIzquierda=1;
  cruceAdelante=0;
}
else if(turn==0){
  cruceIzquierda=0;
  cruceAdelante=1;
}  

cruces[numCruces][0]=cruceAdelante;
cruces[numCruces][1]=cruceDerecha;
cruces[numCruces][2]=cruceIzquierda;
cruces[numCruces][3]=cruceAtras;
numCruces=numCruces+1;
}
else{
  retorno=0;
  cruce();
} 
} 
else if((irRight==1)&&(irLeft==1)&&(frente==1)){
recorridoInverso[contadorRecorrido]=5; 
contadorRecorrido=contadorRecorrido+1;
if (retorno==0){
  estadoCruce[numCruces]=estado;
  interIzqDerAdel();
  cruceAtras=1;
  if(turn==0){
    cruceIzquierda=1;
    cruceDerecha=0;
    cruceAdelante=0;
  }
  else if(turn==1){
    cruceIzquierda=0;
    cruceDerecha=0;
    cruceAdelante=1;
  } 
  else if(turn==2){
    cruceIzquierda=0;
    cruceDerecha=1;
    cruceAdelante=0;
  } 
cruces[numCruces][0]=cruceAdelante;
cruces[numCruces][1]=cruceDerecha;
cruces[numCruces][2]=cruceIzquierda;
cruces[numCruces][3]=cruceAtras;
  numCruces=numCruces+1;
  }
else{
  retorno=0;
  cruce();
} 
} 
else if((irRight==0)&&(irLeft==0)&&(frente==0)){
  retorno=1;
retornarCamino();     
}
}
}
