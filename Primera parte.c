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
void interDerIzq(){
    turn = rand()%2;                          // Random val, odd = 1, even = 0
  if(turn==1){
    giraDerechaAvanza();
  } 
  else if(turn==0){
    giraIzquierdaAvanza();
  } 
}  
void interDerAdel(){
    turn = rand()%2;                          // Random val, odd = 1, even = 0
  if(turn==1){
    giraDerechaAvanza();
  } 
  else if(turn==0){
    avanzaAdelante();
  } 
}  
void interIzqAdel(){
    turn = rand()%2;                          // Random val, odd = 1, even = 0
  if(turn==1){
    giraIzquierdaAvanza();
  } 
  else if(turn==0){
    avanzaAdelante();
  }  
} 
void interIzqDerAdel(){
    turn = rand()%3;                          // Random val, odd = 1, even = 0
  if(turn==0){
    giraIzquierdaAvanza();
  } 
  else if(turn==1){
    avanzaAdelante();
  }
  else if(turn==2){
    giraDerechaAvanza();
  }    
}
void retornarCamino(){
  int tramoRegreso=0;
  giraAtras();
  
/*  for(int x=contadorRecorrido-1;x>=0;x--){
    if(recorridoInverso[x]!=5){
    if(recorridoInverso[x]==4){
      regreso=1;
      avanzaAdelante(); 
    } 
    else if(recorridoInverso[x]==3){
      regreso=1;
      avanzaAdelante();
      giraDerecha();
    } 
    else if(recorridoInverso[x]==2){
      regreso=1;
      avanzaAdelante();
      giraIzquierda();
    } 
   contadorRecorrido=contadorRecorrido-1;
   recorridoInverso[x]=0; 
   tramoRegreso=tramoRegreso+1;
   } 
   else if(recorridoInverso[x]==5){
    recorridoInverso[x]=0;
    tramoRegreso=tramoRegreso+1; 
    break;
  }       
  } 
  regreso=0;*/
  
}  
void cruce(){
  for(int i=0;i<=3;i++){
    if(cruces[numCruces-1][i]==0){
     contadorCrucesDisponibles= contadorCrucesDisponibles+1;
     if(i==0){
       cruceAnterior[0]=1;
     }   
     else if(i==1){
       cruceAnterior[1]=1;
     } 
     else if(i==2){
       cruceAnterior[2]=1;
     } 
     else if(i==3){
       cruceAnterior[3]=1;
     }     
    }
    }
    
    
     if(contadorCrucesDisponibles==2){
       int cruce1=0;
       int cruce2=0;
       int segundoCruce=0;
       
      for(int z=0;z<=3;z++){
    if(cruceAnterior[z]==1){
     if(z==0){
       if(segundoCruce==0){
       cruce1=1;
       segundoCruce=1;
     } 
     else{
       cruce2=1;
     }             
     }
     if(z==1){
       if(segundoCruce==0){
       cruce1=2;
       segundoCruce=1;
     } 
     else{
       cruce2=2;
     }             
     }
     if(z==2){
       if(segundoCruce==0){
       cruce1=3;
       segundoCruce=1;
     } 
     else{
       cruce2=3;
     }             
     }
     if(z==3){
       if(segundoCruce==0){
       cruce1=4;
       segundoCruce=1;
     } 
     else{
       cruce2=4;
     }             
     }
   }
 }
 segundoCruce=0;
 
 if((estadoCruce[numCruces-1]==1)&&(estado==3)){
interDerAdel();     
if (turn==1){
  cruces[numCruces-1][1]=1;
}  
else{
  cruces[numCruces-1][0]=1;
}      
       }   
       else if((estadoCruce[numCruces-1]==1)&&(estado==2)){
interIzqAdel(); 
if (turn==1){
  cruces[numCruces-1][2]=1;
}  
else{
  cruces[numCruces-1][0]=1;
} 
       } 
       else if((estadoCruce[numCruces-1]==1)&&(estado==4)){
interDerIzq(); 
if (turn==1){
  cruces[numCruces-1][1]=1;
}  
else{
  cruces[numCruces-1][2]=1;
} 
       }      
       
       
 if((estadoCruce[numCruces-1]==2)&&(estado==3)){
interDerIzq(); 
if (turn==1){
  cruces[numCruces-1][0]=1;
}  
else{
  cruces[numCruces-1][3]=1;
}             
       }   
       else if((estadoCruce[numCruces-1]==2)&&(estado==1)){
interDerAdel();  
if (turn==1){
  cruces[numCruces-1][1]=1;
}  
else{
  cruces[numCruces-1][0]=1;
}  
       } 
       else if((estadoCruce[numCruces-1]==2)&&(estado==4)){
interIzqAdel();   
if (turn==1){
  cruces[numCruces-1][2]=1;
}  
else{
  cruces[numCruces-1][3]=1;
}  
       } 
       
       else if((estadoCruce[numCruces-1]==3)&&(estado==2)){
         interDerIzq();  
         if (turn==1){
  cruces[numCruces-1][3]=1;
}  
else{
  cruces[numCruces-1][0]=1;
} 
       }
       else if((estadoCruce[numCruces-1]==3)&&(estado==1)){
         interIzqAdel(); 
         if (turn==1){
  cruces[numCruces-1][2]=1;
}  
else{
  cruces[numCruces-1][0]=1;
} 
       }
       else if((estadoCruce[numCruces-1]==3)&&(estado==4)){
        interDerAdel(); 
        if (turn==1){
  cruces[numCruces-1][2]=1;
}  
else{
  cruces[numCruces-1][3]=1;
} 
       }
       else if((estadoCruce[numCruces-1]==4)&&(estado==2)){
         interDerAdel(); 
         if (turn==1){
  cruces[numCruces-1][3]=1;
}  
else{
  cruces[numCruces-1][1]=1;
} 
       }
       else if((estadoCruce[numCruces-1]==4)&&(estado==1)){
         interDerIzq(); 
         if (turn==1){
  cruces[numCruces-1][1]=1;
}  
else{
  cruces[numCruces-1][2]=1;
} 
       }
       else if((estadoCruce[numCruces-1]==4)&&(estado==3)){
         interIzqAdel();
         if (turn==1){
  cruces[numCruces-1][3]=1;
}  
else{
  cruces[numCruces-1][2]=1;
}  
       }
 }               
    if(contadorCrucesDisponibles==1){
      for(int z=0;z<=3;z++){
    if(cruceAnterior[z]==1){
     if(z==0){
       cruces[numCruces-1][0]=1;
       if((estadoCruce[numCruces-1]==1)&&(estado==3)){
         giraDerechaAvanza();
       }   
       else if((estadoCruce[numCruces-1]==1)&&(estado==2)){
         giraIzquierdaAvanza();
       }    
       else if((estadoCruce[numCruces-1]==2)&&(estado==3)){
         giraDerechaAvanza();
       }
       else if((estadoCruce[numCruces-1]==2)&&(estado==1)){
         avanzaAdelante();
       } 
       else if((estadoCruce[numCruces-1]==3)&&(estado==2)){
         giraIzquierdaAvanza();
       }
       else if((estadoCruce[numCruces-1]==3)&&(estado==1)){
         avanzaAdelante();
       }
               
     }   
     else if(z==1){
       cruces[numCruces-1][1]=1;
       if((estadoCruce[numCruces-1]==1)&&(estado==4)){
         giraIzquierdaAvanza();
       }   
       else if((estadoCruce[numCruces-1]==1)&&(estado==2)){
         avanzaAdelante();
       }    
       else if((estadoCruce[numCruces-1]==4)&&(estado==2)){
         avanzaAdelante();
       }
       else if((estadoCruce[numCruces-1]==4)&&(estado==1)){
         giraDerechaAvanza();
       } 
       else if((estadoCruce[numCruces-1]==3)&&(estado==4)){
         giraIzquierdaAvanza();
       }
       else if((estadoCruce[numCruces-1]==3)&&(estado==1)){
         giraDerechaAvanza();
       }
     } 
     else if(z==2){
       cruces[numCruces-1][2]=1;
       if((estadoCruce[numCruces-1]==1)&&(estado==4)){
         giraDerechaAvanza();
       }   
       else if((estadoCruce[numCruces-1]==1)&&(estado==3)){
         avanzaAdelante();
       }    
       else if((estadoCruce[numCruces-1]==4)&&(estado==3)){
         avanzaAdelante();
       }
       else if((estadoCruce[numCruces-1]==4)&&(estado==1)){
         giraIzquierdaAvanza();
       } 
       else if((estadoCruce[numCruces-1]==3)&&(estado==4)){
         giraDerechaAvanza();
       }
       else if((estadoCruce[numCruces-1]==3)&&(estado==1)){
         giraIzquierdaAvanza();
       } 
     }     
    }
    
  }     
              
  }
  else if(contadorCrucesDisponibles==0){
    retorno=1;
    if((estadoCruce[numCruces-1]==1)&&(estado==4)){
         avanzaAdelante();
       }   
       else if((estadoCruce[numCruces-1]==1)&&(estado==2)){
         giraDerechaAvanza();
       }    
       else if((estadoCruce[numCruces-1]==1)&&(estado==3)){
         giraIzquierdaAvanza();
       }  
       else if((estadoCruce[numCruces-1]==4)&&(estado==2)){
         giraIzquierdaAvanza();
       }
       else if((estadoCruce[numCruces-1]==4)&&(estado==1)){
         avanzaAdelante();
       } 
       else if((estadoCruce[numCruces-1]==4)&&(estado==3)){
         giraDerechaAvanza();
       }
       else if((estadoCruce[numCruces-1]==3)&&(estado==4)){
         giraIzquierdaAvanza();
       }
       else if((estadoCruce[numCruces-1]==3)&&(estado==1)){
         giraDerechaAvanza();
       }
       else if((estadoCruce[numCruces-1]==3)&&(estado==2)){
         avanzaAdelante();
       }
       else if((estadoCruce[numCruces-1]==2)&&(estado==4)){
         giraDerechaAvanza();

       }
       else if((estadoCruce[numCruces-1]==2)&&(estado==1)){
             giraIzquierdaAvanza();
       }
       else if((estadoCruce[numCruces-1]==2)&&(estado==3)){
         avanzaAdelante();
       }
  }    
  contadorCrucesDisponibles=0;  
numCruces=numCruces-1;
}    
void giraIzquierda(){
   drive_ramp(0, 0);
 pause(100); 
     drive_speed(-52,70);
    while(1){ 
  pause(1);           // Wait until object in range
  tim=tim+1;
  if(tim==425){
    tim=0;
    break;
  }    
}
tim=0;
 drive_speed(0,0);
 if(estado==1){
      estado=3;
    } 
    else if(estado==2){
      estado=1;
    } 
    else if(estado==3){
      estado=4;
    }
    else if(estado==4){
      estado=2;
    }  
}  
void giraDerecha(){
   drive_ramp(0, 0);
 pause(100); 
     drive_speed(52,-70);
    while(1){ 
  pause(1);           // Wait until object in range
  tim=tim+1;
  if(tim==425){
    tim=0;
    break;
  }    
}
tim=0;
  drive_speed(0,0);
if(estado==1){
      estado=2;
    } 
    else if(estado==2){
      estado=4;
    } 
    else if(estado==3){
      estado=1;
    }
    else if(estado==4){
      estado=3;
    }   
} 
void avanzaAdelante(){
    drive_ramp(64, 64);                       // Forward 2 RPS
    if(regreso==0){
    recorridoInverso[contadorRecorrido]=4;
}  
      
  // While disatance greater than or equal
  // to 20 cm, wait 5 ms & recheck.
  while(ping_cm(8) >= distanciaMinima){ 
  pause(5);           // Wait until object in range
  tim=tim+5;
  if(tim==temporizador){
    tim=0;
    break;
  }    
}
tim=0;
drive_ramp(0,0);
}  
void giraDerechaAvanza(){
  drive_ramp(0,0); 
    
 pause(100); 
     drive_speed(52,-70);
    while(1){ 
  pause(1);           // Wait until object in range
  tim=tim+1;
  if(tim==425){
    tim=0;
    break;
  }    
}
tim=0;
  drive_speed(0,0);
      drive_ramp(64, 64);                       // Forward 2 RPS
       if(regreso==0){
    recorridoInverso[contadorRecorrido]=3;
  }    
      if(estado==1){
      estado=2;
    } 
    else if(estado==2){
      estado=4;
    } 
    else if(estado==3){
      estado=1;
    }
    else if(estado==4){
      estado=3;
    }   
    
  // While disatance greater than or equal
  // to 20 cm, wait 5 ms & recheck.
  while(ping_cm(8) >= distanciaMinima){ 
  pause(5);           // Wait until object in range
  tim=tim+5;
  if(tim==temporizador){
    tim=0;
    break;
  }    
}
tim=0;
drive_ramp(0,0);
} 
void giraIzquierdaAvanza(){
    drive_ramp(0, 0);
 pause(100); 
     drive_speed(-52,70);
    while(1){ 
  pause(1);           // Wait until object in range
  tim=tim+1;
  if(tim==425){
    tim=0;
    break;
  }    
}
tim=0;
  drive_speed(0,0);
      drive_ramp(64, 64);                       // Forward 2 RPS
       if(regreso==0){
    recorridoInverso[contadorRecorrido]=2;
    }      
    if(estado==1){
      estado=3;
    } 
    else if(estado==2){
      estado=1;
    } 
    else if(estado==3){
      estado=4;
    }
    else if(estado==4){
      estado=2;
    }  
  // While disatance greater than or equal
  // to 20 cm, wait 5 ms & recheck.
  while(ping_cm(8) >= distanciaMinima){ 
  pause(5);           // Wait until object in range
  tim=tim+5;
  if(tim==temporizador){
    tim=0;
    break;
  }    
}
tim=0;
drive_ramp(0,0);
}  
void giraAtras(){
  drive_ramp(0,0);
    
 pause(100); 
     drive_speed(-52,70);
    while(1){ 
  pause(1);           // Wait until object in range
  tim=tim+1;
  if(tim==425){
    tim=0;
    break;
  }    
}
tim=0;
drive_speed(0,0);
pause(100); 
     drive_speed(-52,70);
    while(1){ 
  pause(1);           // Wait until object in range
  tim=tim+1;
  if(tim==425){
    tim=0;
    break;
  }    
}
tim=0;
drive_speed(0,0);
  if(estado==1){
      estado=4;
    } 
    else if(estado==2){
      estado=3;
    } 
    else if(estado==3){
      estado=2;
    }
    else if(estado==4){
      estado=1;
    }
}   
void validarIzquierda(){
  freqout(11, 1, 38000);                      // Left IR LED light
    irLeft = input(10);                         // Check left IR detector
}  
void validarAdelante(){
  if(ping_cm(8)<=distanciaMinima){
    frente=0;
}
  else{
    frente=1;
  }
}  
void validarDerecha(){
  freqout(1, 1, 38000);                       // Repeat for right detector
    irRight = input(2);
}  

