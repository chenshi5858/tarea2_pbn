#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int ID, Geoname_ID, Population, Elevation, Timezone;
    double Coordinates_latitude, Coordinates_longitude;
    char Name[100], Country_code[3], Country_name[100];
}Lugar;


int main(int argc, char* argv[]){

    FILE* archivo = fopen(argv[1], "r");


    if (archivo == NULL){
        printf("El archivo ingresado no existe");
        return 1;
    }

    int numero_de_filas = 0;
    // char c;
    // for (c = getc(archivo); c != EOF; c = getc(archivo)){
    //     if (c == '\n') numero_de_filas++;
    // }
    char string[1000];
    while (fgets(string, 999, archivo) != NULL)numero_de_filas++;

    printf("numero total de filas en csv: %d\n", numero_de_filas);
    printf("checkpoint\n");
    //Lugar lugares[numero_de_filas-1]; //la cantidad de lugares es igual a la cantidad total de filas menos la primera fila del csv

    Lugar* lugares = malloc((numero_de_filas-1)*sizeof(Lugar));

    if (lugares == NULL){
        printf("Error al asignar memoria \n");
        return 1;
    }
    

    rewind(archivo);

    int read = 0; // en cada iteracion al leer el csv, se guardaran 10 datos, read se encarga de leer la cantidad de datos guardados. Si no es 10, muestra un error.
    int indice_lugares = 0; //determina la posicion del array "lugares" donde se guarda cada linea de datos del csv 

    // char primera_linea[300]; //guarda la primera linea del csv: "ID;Geoname_ID;Name;Country_Code;Country_name;Population;Elevation;Timezone;Coordinates"

    // fgets(primera_linea, 200, archivo);
    fscanf(archivo, "%*[^\n]"); // Ignorar la primera línea del archivo
    

    do{
        read = fscanf(archivo, 
                    "%d;%d;%99[^;];%2[^;];%99[^;];%d;%d;%99[^;];%lf, %lf", 
                    &lugares[indice_lugares].ID, 
                    &lugares[indice_lugares].Geoname_ID,
                    lugares[indice_lugares].Name,
                    lugares[indice_lugares].Country_code,
                    lugares[indice_lugares].Country_name,
                    &lugares[indice_lugares].Population,
                    &lugares[indice_lugares].Elevation,
                    &lugares[indice_lugares].Timezone,
                    &lugares[indice_lugares].Coordinates_latitude,
                    &lugares[indice_lugares].Coordinates_longitude);
        
        if (read == 10) indice_lugares++; //si las 10 variables se guardaron, se suma el indice para la siguiente iteracion
        
        if ((read != 10) && !feof(archivo)){
            printf("Formato del archivo incorrecto \n");
            return 1;
        }

        if (ferror(archivo)){ //si hay algun error al leer el archivo, se detiene el programa
            printf("Error al leer el archivo \n");
            return 1;
        }
    } while (!feof(archivo));

    //ahora cada dato esta guardado en una variable, ordenados en estructuras

    //afirmate a la silla porque acá se viene lo enfermo

    //qsort(lugares, sizeof(lugares)/sizeof(lugares[0]), sizeof(lugares[0]), );

    printf("tamano de la lista: %d\n", sizeof(lugares)/sizeof(Lugar));

    printf("%s\n", lugares[504].Name);
    printf("%d", indice_lugares);
    fclose(archivo);
    free(lugares);
    return 0;
}