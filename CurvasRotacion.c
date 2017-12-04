#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define bb 0.2497
#define bd 5.16
#define ad 0.3105
#define ah 64.3
#define mgal 1.0
#define mgalR 2.325e7
#define total 301


FILE *arc;
int i;
int j;
int k;
int l;

double R0[total];
double V0[total];

double b= 0;
double d= 0;
double h= 0;
double V[total];

double bbest= 0;
double dbest= 0;
double hbest= 0;
double Vbest[total];

double bnext = 0;
double dnext = 0;
double hnext = 0;
double Vnext[total];


void cargarDatos();
double like(double arr1[], double arr2[]);
double funcion(double r, double aq, double bq, double cq);
void generarSiguiente();
void imprimirModelo(char s[]);


int main(){
    srand((unsigned) 3);
    cargarDatos();
    printf("Datos cargados\n");


 
    
    
 
    b = sqrt(mgalR/3.0);
    bbest = b;
    d = sqrt(mgal/3.0);
    dbest = d;
    h = sqrt(mgal/3.0);
    hbest = h;

    
    
    int iter = 10000;
    double y  = 0;
    double ynext = 0;

    double rate = 0;
    double ybest= 0;
    double ran2= 0;


          for(j = 1; j<total;j++){
                V[j] = funcion(R0[j], b,d,h);
                }
          y = like(V0, V);
          ybest = y;
          bbest = b;
          hbest = h;
          dbest = d;


//Así queda guardado el mejor inicial.
    k = 1;    

    while(k<iter){
          generarSiguiente();
          
          for(j = 1; j<total;j++){
                V[j] = funcion(R0[j], b,d,h);
                Vnext[j] = funcion(R0[j], bnext, dnext, hnext);
                }
          y = like(V0, V);
          ynext = like(V0,Vnext);
          
          rate = ynext/y;

//          printf("el rate es %f %f\n", y,ynext);
          if(rate>1){
          b = bnext;
          h = hnext;
          d = dnext;
          if(ynext > ybest){
                             ybest = ynext;
                             bbest = bnext;
                             hbest = hnext;
                             dbest = dnext;
                    for(j = 1; j<total;j++){
                      Vbest[j] = Vnext[j];
                }
                   }                    
                     }
          else{
               ran2 = (double)rand()/RAND_MAX;
               if(ran2>rate){
          b = bnext;
          h = hnext;
          d = dnext;                               
                             }
               }
          
          k +=1;
          
          
          }
          printf("Corrido el Monte Carlo\n");
          printf("La masa del bulbo es %.3f\n"  ,b*b);
          printf("La masa del disco estelar y de gas es %.3f\n"  ,d*d);
          printf("La masa de un halo de materia oscura es %.3f\n"  ,h*h);
         FILE *archivo    =fopen("rta.txt","w+");  
         fprintf(archivo,"%f %f %f", bbest,dbest,hbest);
         imprimirModelo("modelo.txt");
    
    

    
    
      
    
}//Fin main



void cargarDatos(){
     
        arc = fopen("RadialVelocities.dat", "r");
        i = 0;
        j = 0;
        if(arc){
                    const size_t lena = 1000;
                    char* linea = malloc(lena);

                while (fgets(linea, lena, arc) != NULL){ 

                    char *recorte = strtok(linea, " ");  
       				R0[i] = strtod(recorte,NULL); 
                    recorte = strtok(NULL, " ");  
					V0[i] = strtod(recorte,NULL);
                    recorte = strtok(NULL, " ");  
                    i += 1;
                          }
                                                    	free(linea); 
                            fclose(arc); 
                    }

     
     
}//Fin cargarDatos

void imprimirModelo(char s[]){
     FILE *acha    =fopen(s,"w+");  
     double pr = 0;
     double rfinal = 305;
     int elementos = 500;
         for(i = 1;i<elementos;i++){
               pr = funcion(i*rfinal/elementos, bbest,dbest,hbest);
               fprintf(acha,"%f %f\n ",i*rfinal/elementos, pr);
               }
      
     
}


double funcion(double r, double aq, double bq, double cq){
       double p1 = aq*r*pow( r*r + bb*bb ,-3.0/4.0);
       double p2 = bq *r * pow(r*r+(bd+ad)*(bd+ad),-3.0/4.0);
       double p3 = cq  * pow(r*r+ah*ah, -1.0/4.0);      
       return p1 + p2 + p3;
}//Fin de función.

double like(double arr1[], double arr2[]){
       double equix =0;
       for(i=1;i<total;i+=1){
        equix += pow((arr1[i]-arr2[i])/1e3,2);
        }
       return exp(-equix);
       
       
       
}//Fin like

void generarSiguiente(){
    double std = 15;

     double desv = (double)rand()/RAND_MAX;
          double desv1 = (double)rand()/RAND_MAX;
               double desv2 = (double)rand()/RAND_MAX;

     desv = desv*std;
     desv = desv-(std*0.5);
     desv = desv/100;
     
     desv1 = desv1*std;
     desv1 = desv1-(std*0.5);
     desv1 = desv1/100;
     
     desv2 = desv2*std;
     desv2 = desv2-(std*0.5);
     desv2 = desv2/100;
     
     
     bnext = b*desv+b;
     hnext = h*desv1 + h;
     dnext = d*desv2+d;


  
     
     
     
}//Fin generarSiguiente


