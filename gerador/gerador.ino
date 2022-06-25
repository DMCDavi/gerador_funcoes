//lib para valores complexos https://www.arduino.cc/reference/en/libraries/complex/
#include "Complex.h"

#define pi 3.1415
Complex e=2.7182;
//funcao para o seno


double seno(int N, int n)
{
 double val = 0;
 double w0 = (2 * pi) / N; //frequencia natural
 
 Complex y(0,0); //inicia saida vazia 
 
 Complex a1(0,w0*n); //termo do primeiro coeficiente
 
 Complex a2(0,-w0*n); //termo do segundo coeficiente
 
 Complex d1(0,-2); //termo da divisao
 //eq em python  y = np.exp( w0*1j*n)/2j - np.exp( w0*-1j*n)/2j

  y = (e.c_pow( a1 )/d1) - (e.c_pow( a2 )/d1);


  val = y.real();
  return val;
 //return 25 + (51 * val) / 2 ;
}
//funcao para a quadrada



double quadrado(int N,int N1, int n)
{
 double val = 0;
 double w0 = (2 * pi) / N; //frequencia natural

 Complex y(0,0); //inicia saida vazia 
 Complex complexN(N,0);


 for(int k=0;k<N ;k++){
  if (k == 0){
    y = y + ((2.0*float(N1)+1.0)/float(N));
    }
  else{
    Complex coef(0,w0*n*k);
    float sen1termo = (float(N1)+1.0/2.0);
    Complex coefsen1(k*w0*sen1termo, 0);
    Complex coefsen2(k*w0/2, 0);

    y = y+ ( coefsen1.c_sin() / (complexN*coefsen2.c_sin())) * e.c_pow( coef );

    //--y = y+ ( sin(k*w0*(N1+1/2))  / (N*sin(k*w0/2))) * e.c_pow( coef );
    //x+(np.sin(k*w0*(N1+1/2))/(N*np.sin(k*w0/2)))*np.exp(1j*k*w0*n)
    }  
  }

  val = y.real();
  return val;
 //return 25 + (51 * val) / 2 ;
}
//funcao para triangular


double triangulo(int N, int n)
{
 double val = 0;
 double w0 = (2 * pi) / N; //frequencia natural

 Complex y(0,0); //inicia saida vazia 
 Complex complexN(N,0);

    Complex Ncplx(float(N),0);
    Complex twoCplx(2.0,0);
    Complex fourCplx(4.0,0);
    Complex oneCplx(1.0,0);
    Complex minusOneCplx(-1.0,0);

 for(int k=1;k<=N ;k++){
    Complex coef(0,w0*n*k);
    Complex kpi(0,k*pi);
    
     y = y + (fourCplx/kpi.c_pow(2))*(oneCplx-e.c_pow( (minusOneCplx)*kpi ))*e.c_pow( coef );
  }

  val = y.real();
  return val;
 //return 25 + (51 * val) / 2 ;
}

 //Configurando potenciometros
int potAmplitude = A0; //pino do potenciometro da amplitude
int potFreq = A1; //pino do potenciometro da amplitude
int potOffset = A2; //pino do potenciometro do offset
int potFase = A3; //pino do potenciometro da fase

int pushbutton = 2;
void setup() {
 pinMode(pushbutton, INPUT_PULLUP);
 Serial.begin(9600);

 
}

int sig = 0;
void loop() {


 //controle do sinal pelo botao
 //0 - sin, 1 - quadrado, 2 - triangulo
  if (digitalRead(pushbutton) == LOW){
    sig +=1;
    sig = sig%3;
    delay(200);  
    }

  int offset =int(map(analogRead(potOffset), 0, 1000, -10, 10));
//  Serial.println(analogRead(potFase)); // 
  //Amplitude
  int A = int(map(analogRead(potAmplitude), 0, 1000, 0, 5));
  //Frequencia
  int N = int(map(analogRead(potFreq), 0, 1000, 1, 100));
  int N1 = ((N/2)-1)/2;
  // Controle de Fase, Fase varia de 0 a 360, pegamos o percentual e multiplicamos por N, depois soma o valor de atraso em N
  int fase = int(map(analogRead(potFase), 0, 1000, 0, 360));
  int ControleFase = 0;
  
  ControleFase = fase*N/360;
  
  for (int n = 0; n < N; n+=1) 
  {
  
  if (sig == 0){
  Serial.print(seno(N,n));
  Serial.print(",");
  Serial.println(A*seno(N,n + ControleFase)+offset );
  }
  if (sig == 1){
    Serial.print(quadrado(N,N1,n));
    Serial.print(",");
    Serial.println(A*quadrado(N,N1,n + ControleFase)+offset );
  }
  if (sig == 2){
    Serial.print(triangulo(N,n));
    Serial.print(",");
    Serial.println(A*triangulo(N,n + ControleFase)+offset );
  }
  //  Serial.println(A*quadrado(N,N1,n));
  //  Serial.println(A*triangulo(N,n));
  }

  
  }
  // put your main code here, to run repeatedly:
