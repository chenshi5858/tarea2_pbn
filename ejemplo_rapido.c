#include <stdio.h>

typedef struct{
    char nombre[1000];
    int poblacion;
    float altura;
 } Ciudad;


int main(){

    Ciudad ciudades[100];
    ciudades[80].poblacion = 500000;
    printf("%d", ciudades[80].poblacion); 
    return 0;

}