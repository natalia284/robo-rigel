// VARIÁVEIS PARA SENSORES DE FAIXA

int corE, corM, corD; 

int lim_pretoE = 1024;
int lim_brancoE = 140; 

int lim_pretoM = 1024;
int lim_brancoM = 140;

int lim_pretoD = 1024; 
int lim_brancoD = 200; 

int sensor_esquerda = A0;
int sensor_meio = A1;
int sensor_direita = A2; 

int valor_esquerda = 0;
int valor_meio = 0;
int valor_direita = 0; 

// VARIÁVEIS DOS MOTORES

int M11 = 4; 
int M12 = 6;
int M21 = 7; 
int M22 = 8;
int M1S = 11;
int M2S = 3;
int spd = 200;

// SHARP 

#define sharp A4 

int dist;
float tensao;

void setup() {
          
  pinMode(M11, OUTPUT); 
  pinMode(M12, OUTPUT); 
  pinMode(M21, OUTPUT); 
  pinMode(M22, OUTPUT);   
  pinMode(M1S, OUTPUT); 
  pinMode(M2S, OUTPUT); 
  Serial.begin(9600);

}

void loop() {
  
  corE = lerSensor(0);
  corM = lerSensor(1);
  corD = lerSensor(2);
  
  tabela();
  LerSharp();

  //Serial.print("CorE: ");
  //Serial.print(valor_esquerda);
  //Serial.print(" CorM: ");
  //Serial.println(valor_meio);
  //Serial.print("CorD:");
  //Serial.print(valor_direita);

   Serial.println(dist);

}

// TABELA VERDADE PARA OS 2 SENSORES 

void tabela() {

  if(corE == 0 && corM == 0 && corD == 0) {
  parar(spd); 
    
  }
  
  if(corE == 0 && corM == 0 && corD == 1) {
  esquerda90(spd);   
    
  }
  
  if(corE == 0 && corM == 1 && corD == 0) {
  frente(spd); 
    
  }
  
  if(corE == 0 && corM == 1 && corD == 1) {
  direita90(spd);

  }

  if(corE == 1 && corM == 0 && corD == 0){
  direita90(spd);
  
  }

  if(corE == 1 && corM == 0 && corD == 1){
  parar(spd);
  }

  if(corE == 1 && corM == 1 && corD == 0){
  esquerda90(spd);  
  }

  if(corE == 1 && corM == 1 && corD == 1){
  parar(spd);  
  }
}

int lerSensor(int sensor) {   
    
    if(sensor == 0){
      valor_esquerda = analogRead(sensor_esquerda);
      return classificaSensor(valor_esquerda);   
    }

    if(sensor == 1){
      valor_meio = analogRead(sensor_meio);
      return classificaSensor(valor_meio);      
    }

    if(sensor == 2){
      valor_direita = analogRead(sensor_direita);
      return classificaSensor(valor_direita);
    }
} 

int classificaSensor(int valor){

// CÓDIGO PARA LIMITAR SENSOR DA ESQUERDA  
  
  if(valor > 0 && valor < lim_brancoE){
    return 0;
  }
  else if(valor > lim_brancoE && valor < lim_pretoE){
    return 1;
  }

// CÓDIGO PARA LIMITAR SENSOR DO MEIO 

  if(valor > 0 && valor < lim_brancoM) {
    return 0;
    } 
  else if(valor > lim_brancoM && valor < lim_pretoM) {
    return 1;
  }

// CÓDIGO PARA LIMITAR SENSOR DA DIREITA

  if(valor > 0 && valor < lim_brancoD) {
    return 0;
    } 
  else if(valor > lim_brancoD && valor < lim_pretoD) {
    return 1;
  }
}

// MOTORES 

void parar(int spd) { // CONFERIDO 
  
  digitalWrite(M11,LOW);
  digitalWrite(M12,LOW);
  digitalWrite(M21,LOW);
  digitalWrite(M22,LOW);
  analogWrite(M1S,spd);
  analogWrite(M2S,spd);
}

void frente(int spd) { // CONFERIDO 
  
  digitalWrite(M11,HIGH);
  digitalWrite(M12,LOW);
  digitalWrite(M21,HIGH);
  digitalWrite(M22,LOW);
  analogWrite(M1S,spd);
  analogWrite(M2S,spd);
}

void tras(int spd) { // CONFERIDO 
  
  digitalWrite(M11,LOW);
  digitalWrite(M12,HIGH);
  digitalWrite(M21,LOW);
  digitalWrite(M22,HIGH);
  analogWrite(M1S,spd);
  analogWrite(M2S,spd);
}

void esquerda90(int spd) { // CONFERIDO 
  
  digitalWrite(M11,HIGH);
  digitalWrite(M12,LOW);
  digitalWrite(M21,LOW);
  digitalWrite(M22,HIGH);
  analogWrite(M1S,spd);
  analogWrite(M2S,spd);
}

void direita90(int spd) { // CONFERIDO 
 
  digitalWrite(M11,LOW);
  digitalWrite(M12,HIGH);
  digitalWrite(M21, HIGH);
  digitalWrite(M22,LOW);
  analogWrite(M1S,spd);
  analogWrite(M2S,spd);
}

void LerSharp(){
  
    float tensao = analogRead(sharp)*0.00048828125; // CALCULA TENSÃO 
    int dist = 2.6*pow(tensao, -1); 
  
  Serial.print(dist); 
  Serial.print("cm");
  
  delay(5); // DA UMA PAUSA NA LEITURA

}

