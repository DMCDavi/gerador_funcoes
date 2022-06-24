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


void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
//  Complex c1(10.0, -2.0);
//  Complex c2(3, 0);
//  c2 = c1.c_sin();
//  Complex c5(0, 0);
   //c5 = e.c_pow(c1);

//   int w0 = 5;
//   int n = 2;
//   Complex a1(0,w0*n);
//  Serial.println(c2);
}

void loop() {
  int offset = 225;
  int A = 6;
  int N = 50;
  int N1 = ((N/2)-1)/2;
  for (int n = offset%N; n < N; n+=1) 
  {

//  Serial.println(A*seno(N,n));
  Serial.println(A*quadrado(N,N1,n));
//  Serial.println(A*triangulo(N,n));
  
  }
  // put your main code here, to run repeatedly:

}
