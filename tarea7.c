#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int ID, Geoname_ID, Population, Elevation;
    char Name[100], Country_code[3], Country_name[100], Timezone[1000], Coordinates[1000];
} Lugar;
int main(int argc, char* argv[]){

    FILE * archivo = fopen(argv[1], "r");
    char c;
    Lugar *lugares=malloc(500000*sizeof(int));
    char palabra[500];
    int i = 0;
    int cont_var = 0;
    int CONTADOR = 0;
    char basura[1000];
    fgets(basura, 999, archivo);//saltar primera paopaoepoe linea :)))
    while((c=fgetc(archivo)) != EOF){
        if (c==';'|| c=='\n'){
            palabra[i++] = '\0';
            if (i==0){
                switch (cont_var){
                    case 0:
                        lugares[CONTADOR].ID = -1;
                        cont_var++;
                        break;
                    case 1:
                        lugares[CONTADOR].Geoname_ID = -1;
                        cont_var++;
                        break;
                    case 2:
                        strcpy(lugares[CONTADOR].Name, "N/A");
                        cont_var++;
                        break;
                    case 3:
                        strcpy(lugares[CONTADOR].Country_code, "N/A");
                        cont_var++;
                        break;
                    case 4:
                        strcpy(lugares[CONTADOR].Country_name, "N/A");
                        cont_var++;
                        break;
                    case 5:
                        lugares[CONTADOR].Population = -1;
                        cont_var++;
                        break;
                    case 6:
                        lugares[CONTADOR].Elevation = -1;
                        cont_var++;
                        break;
                    case 7:
                        strcpy(lugares[CONTADOR].Timezone, "N/A");
                        cont_var++;
                        break;
                    case 8:
                        strcpy(lugares[CONTADOR].Coordinates, "N/A");
                        cont_var++;
                        CONTADOR++;
                        break;
                }
                //imprime NA en esa posicion
            }
            else{
                switch (cont_var){
                    case 0:
                        lugares[CONTADOR].ID = atoi(palabra);
                        cont_var++;
                        break;
                    case 1:
                        lugares[CONTADOR].Geoname_ID = atoi(palabra);
                        cont_var++;
                        break;
                    case 2:
                        strcpy(lugares[CONTADOR].Name, palabra);
                        cont_var++;
                        break;
                    case 3:
                        strcpy(lugares[CONTADOR].Country_code, palabra);
                        cont_var++;
                        break;
                    case 4:
                        strcpy(lugares[CONTADOR].Country_name, palabra);
                        cont_var++;
                        break;
                    case 5:
                        lugares[CONTADOR].Population = atoi(palabra);
                        cont_var++;
                        break;
                    case 6:
                        lugares[CONTADOR].Elevation = atoi(palabra);
                        cont_var++;
                        break;
                    case 7:
                        strcpy(lugares[CONTADOR].Timezone, palabra);
                        cont_var++;
                        break;
                    case 8:
                        strcpy(lugares[CONTADOR].Coordinates, palabra);
                        cont_var++;
                        CONTADOR++;
                        break;
                }
            }
            i=0;
            if (c=='\n') {
                cont_var=0;
            }
        }
        else{
            palabra[i] = c;
            i++;
        }
    }
    for (int i = 0; i < CONTADOR; i++) {
        printf("ID: %d\n", lugares[i].ID);
        printf("Geoname ID: %d\n", lugares[i].Geoname_ID);
        printf("Name: %s\n", lugares[i].Name);
        printf("Country Code: %s\n", lugares[i].Country_code);
        printf("Country Name: %s\n", lugares[i].Country_name);
        printf("Population: %d\n", lugares[i].Population);
        printf("Elevation: %d\n", lugares[i].Elevation);
        printf("Timezone: %s\n", lugares[i].Timezone);
        printf("Coordinates: %s\n", lugares[i].Coordinates);
        printf("\n");
    }
    fclose(archivo);
    free(lugares);
    return 0;
}