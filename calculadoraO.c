/*      ejecutarlo gnu linux con gcc con el comando : gcc calculadoraO.c -lm -o calculadora    */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#define TAM 50

struct operador{

       char op;

       int prioridad;

       struct operador *sig,*ant;

};

struct operando{

       float num;

       struct operando *sig,*ant;

};

void menos(float *x,float *z);
void factorial(float *x,float *z);
void coseno(float *x,float *z);
void seno(float *x,float *z);
void raiz(float *x,float *z);
void suma(float *x,float *y,float *z);
void producto(float *x,float *y,float *z);
void division(float *x,float *y,float *z);
void resta(float *x,float *y,float *z);
void potencia(float *x,float *y,float *z);
void apilaroperando(struct operando **cab,float *c);
void sacaroperando(struct operando **cab,float *c);
void apilaroperador(struct operador **cab,char *car,int *u);
void sacaroperador(struct operador **cab,char *car,int *p);
void operar(float*x,float *y,float *z,char *l);
void operar2(float*x,float *z,char *l);
void evaluar(char *cadena,struct operador **cabI, struct operando **cabII);
void mostrar(struct operador *cab);
void mostrarII(struct operando *cab);
void verificarprioridad(char *car,int *pr);

int main(){

    char expresion[TAM];

    struct operador *operadores=NULL;
    struct operando *operandos=NULL;

    printf("\nExpresion:\n");
    scanf("%s", &expresion);
    printf("%s", expresion);
    evaluar(expresion,&operadores,&operandos);
    /*printf("\nMostrando pila de operadores: ");
    mostrar(operadores);
    printf("\nMostrando pila de operandos: ");
    mostrarII(operandos);*/
    //resolver(&operadores,&operandos);
    return 0;

}

void menos(float *x,float *z){
     
     float a,valor;
     
     a=*x;
     
     valor=a*(-1);
     
     *z=valor; 
     
     return;     

}

void factorial(float *x,float *z){
     
     int i,n;
     float factorial=1;
     
     n=*x;

     for(i=1;i<=n;i++){ 
         
         factorial=factorial*i; 
                        
     }
     
     *z=factorial;
     
     return;

}
void coseno(float *x,float *z){

     *z=cos(*x);

     return;

}
void seno(float *x,float *z){

     *z=sin(*x);

     return;

}
void raiz(float *x,float *z){

     *z=sqrt(*x);

     return;

}
void suma(float *x,float *y,float *z){

     *z=*x+*y;

     return;

}
void producto(float *x,float *y,float *z){

     *z=(*x)*(*y);

     return;

}
void division(float *x,float *y,float *z){

     *z=(*x)/(*y);

     return;

}
void resta(float *x,float *y,float *z){

     *z=*x-*y;

     return;

}
void potencia(float *x,float *y,float *z){

     *z=pow(*x,*y);

     return;

}
void apilaroperando(struct operando **cab,float *c){

     struct operando *nuevo;

     nuevo=(struct operando*) malloc(sizeof(struct operando));
     nuevo->num=*c;

     if(!(*cab)){
        nuevo->sig=*cab;
        nuevo->ant=*cab;
        *cab=nuevo;
     }else{

        (*cab)->ant=nuevo;
        nuevo->sig=*cab;
        nuevo->ant=NULL;
        *cab=nuevo;
     }

     return;

}

void sacaroperando(struct operando **cab,float *c){
     
     struct operando *s;
     
     *c=(*cab)->num;
     s=*cab;     
     *cab=(*cab)->sig;     
     free(s);
     if(*cab!=NULL)(*cab)->ant=NULL;

     return;
}

void apilaroperador(struct operador **cab,char *car, int *u){
     
     struct operador *nuevo;
     int unario=*u;
     
     nuevo=(struct operador*) malloc(sizeof(struct operador));
     nuevo->op=*car;   
     
     if(*car=='+'||*car=='-')
        if(*car=='-' && unario)nuevo->prioridad=3; 
        else 
          nuevo->prioridad=1;
     
     if(*car=='/'||*car=='*') nuevo->prioridad=2;
     if(*car=='^') nuevo->prioridad=4;
     if(*car=='!') nuevo->prioridad=5;
     if(*car=='s'||*car=='r'||*car=='c')nuevo->prioridad=6; 
     if(*car=='(') nuevo->prioridad=7;
     if(*car==')') nuevo->prioridad=0;

     if(!(*cab)){
        nuevo->sig=*cab;
        nuevo->ant=*cab;
        *cab=nuevo;
     }else{

        (*cab)->ant=nuevo;
        nuevo->sig=*cab;
        nuevo->ant=NULL;
        *cab=nuevo;

     }

     return;
}

void sacaroperador(struct operador **cab,char *car,int *p){
     
     struct operador *s;
     
     *car=(*cab)->op;
     *p=(*cab)->prioridad;
     s=*cab;
     *cab=(*cab)->sig;
     free(s); 
     if(*cab!=NULL)(*cab)->ant=NULL;     

     return;

}

void operar(float*x,float *y,float *z,char *l){ 
     
     float a,b,valor;
     
     a=*x;
     b=*y;
     
     if(*l=='*')producto(&a,&b,&valor);

     if(*l=='-')resta(&a,&b,&valor);

     if(*l=='+')suma(&a,&b,&valor);

     if(*l=='/')division(&a,&b,&valor);

     if(*l=='^')potencia(&a,&b,&valor);    
     
     *z=valor;

     return;
      
}

void operar2(float*x,float *z,char *l){ 
     
     float a,valor;
          
     a=*x;
        
     if(*l=='c')coseno(&a,&valor);

     if(*l=='s')seno(&a,&valor);

     if(*l=='r')raiz(&a,&valor);   
     
     if(*l=='!')factorial(&a,&valor);   
     
     *z=valor;
        
     return;

}

void evaluar(char *cadena,struct operador **cabI, struct operando **cabII){

     struct operador *operadores;
     struct operando *operandos;
     int largo,i,j=0,c,prioridad,unario,prioridadactual,operandoA,operandoB;
     float numero,a,b,valor;
     char car,carII,cantidad[TAM];

     operadores=*cabI;
     operandos=*cabII;

     largo=strlen(cadena);
     
     //Hey aquí me quedó desvergue otra vez XD pero le cambie los nombres a las variables para que se entienda más
     
     for(i=0;i<=largo;i++){

         car=cadena[i];

         if(car>=48 && car<=57 || car=='.'){
            cantidad[j]=car;
            j++;

            if(cadena[i+1]=='+'||cadena[i+1]=='-'||cadena[i+1]=='*'||cadena[i+1]=='/'||cadena[i+1]=='('||cadena[i+1]==')'||cadena[i+1]=='\0'||cadena[i+1]=='^'||cadena[i+1]=='!'||cadena[i+1]=='r'||cadena[i+1]=='s'||cadena[i+1]=='c'){
               cantidad[j]='\0';
               j=0;
               numero=atof(cantidad);
               apilaroperando(&operandos,&numero);

            }

         }

         if(car=='+'||car=='/'||car=='*'||car=='-'||car=='('||car==')'||car=='^'||car=='!'||car=='s'||car=='c'||car=='r'||car=='\0'){
            
            if(car=='-' && i==0)unario=1;
            else
              if(car=='-' && (cadena[i-1]=='-'||cadena[i-1]=='+'||cadena[i-1]=='*'||cadena[i-1]=='/'||cadena[i-1]=='('||cadena[i-1]=='^'))
                 unario=1;
              else
                 unario=0;
                 
            if(unario && car=='-'){ 
                        
               apilaroperador(&operadores,&car,&unario);
               unario=0;
               continue;
            }     
            
            verificarprioridad(&car,&prioridadactual);
            if(!operadores)apilaroperador(&operadores,&car,&unario);
            else
              if(car=='(' ||car=='r'|| car=='c'|| car=='s' )apilaroperador(&operadores,&car,&unario);
              else
                if(operadores->prioridad < prioridadactual)apilaroperador(&operadores,&car,&unario);
                else{ 
                  //Aqui se hace el despije para evaluar    
                  while(prioridadactual<=operadores->prioridad && operadores->op!='('){
                                                                
                        if(operadores)sacaroperador(&operadores,&carII,&prioridad);
                        
                        if(carII=='-' && prioridad==3){ 
                                      
                           if(operandos)sacaroperando(&operandos,&b); 
                           menos(&b,&valor);  
                           apilaroperando(&operandos,&valor);
                           if(!operadores)break;
                           else
                             continue;           
                        
                        }  
                  
                        if(carII=='!'||carII=='s'||carII=='r'||carII=='c'){ 
                           
                           if(operandos)sacaroperando(&operandos,&b); 
                           operar2(&b,&valor,&carII);   
                           apilaroperando(&operandos,&valor);
                           if(!operadores)break;
                           else
                             continue;                                    
                        
                        }
                        
                        if(operandos)sacaroperando(&operandos,&b);                                                                
                        if(operandos)sacaroperando(&operandos,&a);
                        
                        operar(&a,&b,&valor,&carII); 
                       
                        apilaroperando(&operandos,&valor);                        
                        if(!operadores)break;
                                                           
                  }  
                  
                  if(operadores)
                     if(operadores->op=='(' && car==')')
                        sacaroperador(&operadores,&carII,&prioridad); 
                        
                  if(prioridadactual==0 && !operadores && car=='\0') break;
                  if(car!=')')apilaroperador(&operadores,&car,&unario);                        
                
                }            

         }

     }
     
     printf("\nEl resultado es %f",operandos->num);
          
     return;

}

void mostrar(struct operador *cab){

     struct operador *s;

     s=cab;

     while(cab){

           printf("%c ", cab->op);
           //if(cab->sig == NULL ) break;
           cab=cab->sig;

     }
     //printf("\n");

    /* while(cab){

           //printf("%c ", cab->op);
           //if(cab->ant == NULL ) break;
          // cab=cab->ant;

     }*/

     return;

}

void mostrarII(struct operando *cab){

     struct operando *s;

     s=cab;

     while(cab){

           printf("%f ", cab->num);
           //if(cab->sig == NULL ) break;
           cab=cab->sig;

     }
     //printf("\n");

      //while(cab){

           //printf("%f ", cab->num);
           //if(cab->ant == NULL ) break;
          // cab=cab->ant;

   //  }

     return;

}

void verificarprioridad(char *car,int *pr){
     
     if(*car=='+'||*car=='-') *pr=1;
     if(*car=='/'||*car=='*') *pr=2;
     if(*car=='^') *pr=4;
     if(*car=='!') *pr=5;
     if(*car=='(') *pr=7;
     if(*car==')') *pr=0;
     if(*car=='\0')*pr=0;
     if(*car=='s'||*car=='r'||*car=='c')*pr=6;     
     
     return;     

}


