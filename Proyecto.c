/*
  Proyecto.c
  Didier Salazar. 15487
  Raul de Leon. 15112
  Michelle Morales. 15322
  Joseline Ortiz. 15039
  
  Programa principal que realiza el algoritmo Tremaux para resolver cualquier tipo de laberinto.
*/

#include "simpletools.h"    // Include simpletools header
#include "abdrive.h"        // Include abdrive header
#include "ping.h"           // Include ping header
#include "adcDCpropab.h"    // Include adcDCpropab
#include "stdlib.h "
#include "time.h" 

int turn=0;   // Variables necesarias para el control de sensores y tiempo
int tim=0;
int derecha=0;
int adelante=0;
int izquierda=0;
int atras=0;
int recorridoInverso[3000];
int cruces[50][4];
int numCruces=0;
int temporizador=700;
int distanciaMinima=14; //Distancia en centimetros que espera el robot para no topar con el sensor ultrasonico la parte delantera del mismo.
int contadorRecorrido=0;
int estado=1; //Estado del robot, 1 su norte, 2 su este, 3 su oeste, 4 el sur (todo relativo a el).
int cruceDerecha=0;
int cruceIzquierda=0;
int cruceAdelante=0;
int cruceAtras=0;
int contadorCrucesDisponibles=0;
int cruceAnterior[4];
int regreso=0;
int estadoCruce[200]; //Vector donde se guardan los cruces realizados
int retorno=0;
int irLeft, irRight, frente;      //Variables donde se guardan los datos obtenidos por los sensores en el frente, derecha e izquierda del robot.                     

// Funcion principal del 
int main()
{
  srand(time(NULL)); 
while(1){

//Aca se controla el voltaje de los sensores infrarrojos, para que solo detecten objetos a 12 centimetros de distancia.
  dac_ctr(1, 0, 460);                           // D/A ch 0 -> 2.5 V to D/A 0
  dac_ctr(11, 1, 460);                            // D/A ch 1 -> 1 V to D/A 1
                          
     
drive_setRampStep(10);      

//Se valida con los sensores el alrededor del robot.
validarIzquierda(); 
validarDerecha();
validarAdelante();

//Validaciones para diferentes tipos de cruces y encrucijadas
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

//Guarda los cruces realizados hechos en el vector, luego se suma 1 a la cantidad de cruces en el vector (numCruces). 

cruces[numCruces][0]=cruceAdelante;
cruces[numCruces][1]=cruceDerecha;
cruces[numCruces][2]=cruceIzquierda;
cruces[numCruces][3]=cruceAtras;
numCruces=numCruces+1;
}
else{
  //Si el robot viene de regreso, al llegar a un cruce de este tipo, llama a la funcion que valida para los lugares a donde no ha ido del laberinto.
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

//Guarda los cruces realizados hechos en el vector, luego se suma 1 a la cantidad de cruces en el vector (numCruces). 
cruces[numCruces][0]=cruceAdelante;
cruces[numCruces][1]=cruceDerecha;
cruces[numCruces][2]=cruceIzquierda;
cruces[numCruces][3]=cruceAtras;
numCruces=numCruces+1;  
}
else{
  //Si el robot viene de regreso, al llegar a un cruce de este tipo, llama a la funcion que valida para los lugares a donde no ha ido del laberinto.
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

//Guarda los cruces realizados hechos en el vector numCruces
cruces[numCruces][0]=cruceAdelante;
cruces[numCruces][1]=cruceDerecha;
cruces[numCruces][2]=cruceIzquierda;
cruces[numCruces][3]=cruceAtras;
numCruces=numCruces+1;
}
else{
  //Si el robot viene de regreso, al llegar a un cruce de este tipo, llama a la funcion que valida para los lugares a donde no ha ido del laberinto.
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

//Guarda los cruces realizados hechos en el vector, luego se suma 1 a la cantidad de cruces en el vector (numCruces). 
cruces[numCruces][0]=cruceAdelante;
cruces[numCruces][1]=cruceDerecha;
cruces[numCruces][2]=cruceIzquierda;
cruces[numCruces][3]=cruceAtras;
  numCruces=numCruces+1;
  }
else{
  //Si el robot viene de regreso, al llegar a un cruce de este tipo, llama a la funcion que valida para los lugares a donde no ha ido del laberinto.
  retorno=0;
  cruce();
} 
} 
else if((irRight==0)&&(irLeft==0)&&(frente==0)){
  //Al llegar a un "punto muerto" el robot da la vuelta y comienza a buscar al cruce de donde vino.
  retorno=1;
retornarCamino();     
}
}
}

//Funcion que valida si hay un cruce en T, relativo a como se encuentre el robot
void interDerIzq(){
  //Realiza un random para saber cual camino tomar.
    turn = rand()%2;                          // Random val, odd = 1, even = 0
  if(turn==1){
    giraDerechaAvanza();
  } 
  else if(turn==0){
    giraIzquierdaAvanza();
  } 
}  

//Funcion que valida si hay un cruce en L, relativo a como se encuentre el robot
void interDerAdel(){
  //Realiza un random para saber cual camino tomar.
    turn = rand()%2;                          // Random val, odd = 1, even = 0
  if(turn==1){
    giraDerechaAvanza();
  } 
  else if(turn==0){
    avanzaAdelante();
  } 
}  

//Funcion que valida si hay un cruce en L invertida, relativo a como se encuentre el robot
void interIzqAdel(){
  //Realiza un random para saber cual camino tomar.
    turn = rand()%2;                          // Random val, odd = 1, even = 0
  if(turn==1){
    giraIzquierdaAvanza();
  } 
  else if(turn==0){
    avanzaAdelante();
  }  
} 

//Funcion que valida si hay una interseccion de 3 caminos, sin contar la parte trasera, relativo a como se encuentre el robot.
void interIzqDerAdel(){
  //Realiza un random para saber cual camino tomar.
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

//Funcion que verifica si esta en un camino sin salida y debe retornar
void retornarCamino(){
  int tramoRegreso=0;
  giraAtras();
  
}  

//Funcion que verifica que caminos no ha tomado el robot, dependiendo del cruce que tomo.
void cruce(){
  for(int i=0;i<=3;i++){
    //Verifica en la ultima posicion del vector de cruces, los caminos disponibles.
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
    
    //Si hay dos caminos que no ha tomado, hace un random para elegir cual tomar de los dos.
     if(contadorCrucesDisponibles==2){
       int cruce1=0;
       int cruce2=0;
       int segundoCruce=0;
       
      for(int z=0;z<=3;z++){
    if(cruceAnterior[z]==1){
      //Valida el camino a tomar, relativo al estado en que se encontraba el robot al tomar el cruce.
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
 
 //Aca realiza el random para decidir cual camino tomar.
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
 //Si solo le queda un camino por tomar, sigue ese camino de acuerdo al estado en el que inicio el cruce, y el estado en el que se encuentra luego de regresar del cruce.
    if(contadorCrucesDisponibles==1){
      for(int z=0;z<=3;z++){
    if(cruceAnterior[z]==1){
     if(z==0){
       //Si el camino que falta por tomar esta hacia su norte.
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
       //Si el camino que falta por tomar esta hacia su Este.
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
       //Si el camino que falta por tomar esta hacia su Oeste.
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
  //Si ya no le quedan caminos por tomar, regresa al otro cruce validando el camino de donde vino.
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
  //Se reinician contadores.
  contadorCrucesDisponibles=0;  
numCruces=numCruces-1;
}    

//Funcion que da la velocidad a la hora de girar a la izquierda
void giraIzquierda(){
   drive_ramp(0, 0);
 pause(100); 
     drive_speed(-52,70);
    while(1){ 
  pause(1);           
  tim=tim+1;
  if(tim==425){
    tim=0;
    break;
  }    
}
tim=0;
 drive_speed(0,0);
 //Cambia los estados al girar a la izquierda, dependiendo de su orientacion inicial.
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

//Funcion que da la velocidad a la hora de girar a la derecha
void giraDerecha(){
   drive_ramp(0, 0);
 pause(100); 
     drive_speed(52,-70);
    while(1){ 
  pause(1);           
  tim=tim+1;
  if(tim==425){
    tim=0;
    break;
  }    
}
tim=0;
  drive_speed(0,0);
  //Cambia los estados al girar a la derecha, dependiendo de su orientacion inicial.
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

//Funcion que da la velocidad a la hora de avanzar
void avanzaAdelante(){
    drive_ramp(64, 64);                       // Forward 1 RPS
    if(regreso==0){
    recorridoInverso[contadorRecorrido]=4;
}  
      
  // While disatance greater than or equal
  // to distanciaMinima, wait 5 ms & recheck.
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

//Funcion que hace girar a la derecha al robot, y luego avanzar hacia adelante.
void giraDerechaAvanza(){
  drive_ramp(0,0); 
    
 pause(100); 
     drive_speed(52,-70);
    while(1){ 
  pause(1);          
  tim=tim+1;
  if(tim==425){
    tim=0;
    break;
  }    
}
tim=0;
  drive_speed(0,0);
      drive_ramp(64, 64);                       // Forward 1 RPS
       if(regreso==0){
    recorridoInverso[contadorRecorrido]=3;
  }    
  //Cambia los estados al girar a la derecha, dependiendo de su orientacion inicial.
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
    
  // While distance greater than or equal
  // to distanciaMinima, wait 5 ms & recheck.
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
//Funcion que hace girar a la izquierda al robot, y luego avanzar hacia adelante.
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
      drive_ramp(64, 64);                       // Forward 1 RPS
       if(regreso==0){
    recorridoInverso[contadorRecorrido]=2;
    }   
    //Cambia los estados al girar a la derecha, dependiendo de su orientacion inicial.
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
  // to distanciaMinima, wait 5 ms & recheck.
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

//Funcion que da la velocidad a la hora de regresar, es decir, hace dos veces el giro hacia la izquierda para dar la vuelta hacia atras.
void giraAtras(){
  drive_ramp(0,0);
    
 pause(100); 
     drive_speed(-52,70);
    while(1){ 
  pause(1);           
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
  pause(1);           
  tim=tim+1;
  if(tim==425){
    tim=0;
    break;
  }    
}
tim=0;
drive_speed(0,0);
//Cambia el estado de la orientacion del robot, si estaba yendo hacia adelante, ahora va hacia atras, si iba a la derecha, ahora va hacia la izquierda, y asi viceversa.
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

//Funcion que verifica mediante los sensores IR si hay pared a la izquierda
void validarIzquierda(){
  freqout(11, 1, 38000);                      // Left IR LED light
    irLeft = input(10);                         // Check left IR detector
}  
//Funcion que valida si hay algun objeto adelante
void validarAdelante(){
  if(ping_cm(8)<=distanciaMinima){
    frente=0;
}
  else{
    frente=1;
  }
}  

//Funcion que verifica mediante los sensores IR si hay pared a la derecha
void validarDerecha(){
  freqout(1, 1, 38000);                       // Repeat for right detector
    irRight = input(2);
}  


