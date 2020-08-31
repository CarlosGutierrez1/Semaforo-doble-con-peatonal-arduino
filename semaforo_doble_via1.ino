/*
Inicializacion de pins para semaforo 1
*/
int LEDRED1 = 2;
int LEDYE1 = 3;
int LEDBLU1 = 4;


/*
Inicializacion de pins para switches
*/
int Switch1 = 5;
int Switch2 = 11;

/*
Inicializacion de pins para semaforo peatonal 1
*/
int LEDREDP1 = 7;
int LEDGREENP1 = 6;

/*
Variables para proceso de validacion de cual secuencia usar
*/

int EstadoSW1;
int EstadoSW2;
int chk; //contador usado en for
boolean flag1 = false;
boolean flag2 = false;
boolean SaberEtapa=true;

int timedelayNS = 3000; //Time delay para la secuencia normal
int timedelayCS=1000; //Time delay para el cambio de secuencia
int timedelaymid=500; //Time Delay comun(usado en los ciclos for)



void setup()
{
  /*
  	Se hace set de los pins de los leds en salidas y
    los switches en entradas
  */
  pinMode(LEDRED1,OUTPUT);
  pinMode(LEDYE1,OUTPUT);
  pinMode(LEDBLU1,OUTPUT);
  
  pinMode(LEDREDP1,OUTPUT);
  pinMode(LEDGREENP1,OUTPUT);
  
  pinMode(Switch1,INPUT);
  pinMode(Switch2,INPUT); 
  
  digitalWrite(LEDBLU1,HIGH);
  digitalWrite(LEDREDP1,HIGH);
  
  
  
  
  
}

void loop()
{
  
  
  flag1 = false;
  flag2 = false;
  SaberEtapa =false;
  /*
  Proceso logico -> Se comienza haciendo una espera de 10 segundos
  para saber si se presiona el switch1*/
  
  for(chk=0;chk<10;chk++){
  	EstadoSW1 = digitalRead(Switch1);
    if(EstadoSW1==HIGH){
     flag1=true;//si se presiona el switch1 flag1 determinara si iniciar cambiodesecuencia1()
      break;
    }
    delay(timedelaymid);
  }
  /*
  Despues de esperar los 10 segundos se evalua si se presiono el switch1*/
  if(flag1){
    
    /*cambiodesecuencia iniciara el proceso para habilitar el paso
    peatonal, del semaforo 1(protoboard parte de arriba)*/
    
   	CambiodeSecuencia1();
    
  }else{
    
    /*
    Si no se presiona, inicia secencia normal pero saberetapa=false
    esto para saber que secuencia debe usar. Como es la primera parte
    la secuencia sera verde,amarillo,rojo. pausando en rojo*/
    
    SecuenciaNormal(SaberEtapa);
    
  }
  
  /*
  como ya paso la etapa 1 colocamos saberetapa=true para
  avisar que se necesita la secuencianormal 2*/
  
  SaberEtapa=true;
  
  /*
  Esperamos en la finalizacion de la etapa 1(rojo), para saber si se
  presiona el switch2*/
  
  for(chk=0;chk<10;chk++){
    EstadoSW2 = digitalRead(Switch2);
    if(EstadoSW2==HIGH){
      flag2=true;
      break;
    }
    delay(timedelaymid);
    
  }
  if(flag2){
    
     /*cambiodesecuencia iniciara el proceso para habilitar el paso
    peatonal, del semaforo 2(protoboard parte de abajo)*/
    
   	CambiodeSecuencia2(); 
  }else{
    SecuenciaNormal(SaberEtapa);
  }
  
  
  
  
  
  
 
}

/*Proceso para cambiar secuencia del semaforo 1 y habilitar al peaton,
apaga verde, llega a rojo el semaforo vehicular*/

void CambiodeSecuencia1(){
  delay(timedelayCS);
  digitalWrite(LEDBLU1,LOW);
  digitalWrite(LEDYE1,HIGH);
  
  
  delay(timedelayCS);
  digitalWrite(LEDYE1,LOW);
  digitalWrite(LEDRED1,HIGH);
  digitalWrite(LEDREDP1,LOW);
  digitalWrite(LEDBLU1,LOW);
  
   /* Hacemos parpadear la luz verde para dar aviso de habilitacion*/
  for(int i=0;i<10;i++){
    digitalWrite(LEDGREENP1,HIGH);
    
    delay(timedelaymid);
    digitalWrite(LEDGREENP1,LOW);
    
    delay(timedelayCS);
    
    /*Cuando llegamos a el ultimo parpadeo, apagamos y regresa
        a estado normal(Encendido solo rojo)*/
      if(i==14){
      	digitalWrite(LEDGREENP1,LOW);
      	digitalWrite(LEDREDP1,HIGH);
        
        
    }
    
  }
  
  delay(timedelayCS);
  digitalWrite(LEDYE1,HIGH);
  digitalWrite(LEDRED1,LOW);
  
  
  delay(timedelayCS);
  digitalWrite(LEDYE1,LOW);
  digitalWrite(LEDBLU1,HIGH);
  
  
 
  
   
  
  
}

/*Proceso para cambiar secuencia del semaforo 2 y habilitar al peaton,
apaga verde, llega a rojo el semaforo vehicular*/
          
          
void CambiodeSecuencia2(){
  
  delay(timedelayCS);  
  digitalWrite(LEDRED1,LOW);  
  digitalWrite(LEDYE1,HIGH);
  
  
  
  delay(timedelayCS);
  digitalWrite(LEDYE1,LOW);
  digitalWrite(LEDBLU1,HIGH);
  digitalWrite(LEDGREENP1,LOW);
  digitalWrite(LEDRED1,LOW);
  
  /* Hacemos parpadear la luz verde para dar aviso de habilitacion*/
  for(int i=0;i<10;i++){
    
    digitalWrite(LEDREDP1,HIGH);
    delay(timedelaymid);
    digitalWrite(LEDREDP1,LOW);
    delay(timedelayCS);
    	/*Cuando llegamos a el ultimo parpadeo, apagamos y regresa
        a estado normal(Encendido solo rojo)*/
      if(i==14){
      	digitalWrite(LEDREDP1,LOW);
        
      	digitalWrite(LEDGREENP1,HIGH);
        
        
    }
    
  }
  
  delay(timedelayCS);
  digitalWrite(LEDYE1,HIGH);
  digitalWrite(LEDBLU1,LOW);
  
  
  delay(timedelayCS);
  digitalWrite(LEDYE1,LOW);
  digitalWrite(LEDRED1,HIGH);
  
  
 
  
   
  
  
}
          
          
void SecuenciaNormal(bool SaberEnQueEtapa){
  /*En caso de que este en la etapa 2(rojo,amarillo,para en verde)*/
  if(SaberEnQueEtapa){
    
    digitalWrite(LEDRED1,LOW);
    digitalWrite(LEDGREENP1,LOW);
    digitalWrite(LEDREDP1,HIGH);
    digitalWrite(LEDYE1,HIGH);
    
    delay(timedelayNS);
    digitalWrite(LEDYE1,LOW);
    digitalWrite(LEDBLU1,HIGH);
    digitalWrite(LEDREDP1,HIGH);
    
    
    
    
  
     /*En caso de que este en la etapa 1(verde,amarillo,para en rojo)*/
  }else{
    
    delay(timedelayNS);
  digitalWrite(LEDBLU1,LOW);
  digitalWrite(LEDYE1,HIGH);
  
  
  delay(timedelayNS);
  digitalWrite(LEDREDP1,LOW);
  digitalWrite(LEDYE1,LOW);
  digitalWrite(LEDRED1,HIGH);
  digitalWrite(LEDGREENP1,HIGH);
  
  
  
  
  
  
  
  }
  
}
/*
	Some parts of the code were referenced from: 
    https://electronicaindustr28.wixsite.com/mec
    atronicabb/single-post/2016/11/15/Sem%C3%A1f
    oro-veh%C3%ADcular-y-peatonal-con-arduino
*/