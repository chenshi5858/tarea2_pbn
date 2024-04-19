#include <stdio.h>
#include <string.h>

typedef struct{
    char ID[100], Geoname_ID[100], Population[100], Elevation[100], Timezone[100];
    char Coordinates_latitude[100], Coordinates_longitude[100];
    char Name[100], Country_code[3], Country_name[100];
}Lugar;

int main(int arg, char* argv[]){

    FILE* archivo = fopen(argv[1], "r");
    
    char line[1000];
    int numero_de_filas = 0;
    while (fgets(line, 999, archivo) != NULL)numero_de_filas++;
    fseek(archivo, 1, SEEK_SET);
    
    Lugar lugares[numero_de_filas-1];
    
//ID;Geoname_ID;Name;Country_Code;Country_name;Population;Elevation;Timezone;Coordinates


    fgets(line, 999, archivo);

    char* token = strtok(line, ";");
    printf("hola");
    printf("%s", line);
    
    // int indice_lugares=0;
    // while (fgets(line, 999, archivo) != NULL){

    //     char* ptr = strtok(line, ";");
    //     while (ptr!=NULL){
    //         printf("%s", ptr);
    //         ptr = strtok(NULL, ";");
    //     }

    // }
    // fclose(archivo);
    // return 0;
}