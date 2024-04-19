#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{

    int ID, Geoname_ID, Population, Elevation, Timezone;
    double Coordinates_latitude, Coordinates_longitude;
    char Name[100], Country_code[3], Country_name[100];

}Lugar;

int main(int argc, char* argv[]){

    FILE* archivo = fopen(argv[1], "r");
    char line[1000];
    int numero_lugares = 0;
    while(fgets(line, 999, archivo)) numero_lugares++;
    Lugar lugares[numero_lugares-1];
    rewind(archivo);
    fgets(line, 999, archivo);//ignora la primera linea del csv

    fgets(line, 999, archivo);

    char* token = strtok(line, ";");

    int contador = 0; //contador llega a 10
    int indice = 0;
    lugares[indice].ID = atoi(token);
    token = strtok(NULL, ";");
    contador++;    
    //primera linea del archivo csv: ";Geoname_ID;Name;Country_Code;Country_name;Population;Elevation;Timezone;Coordinates"
    //segunda linea del archivo csv: "0;3112388;Rabade;ES;Spain;1635;398;Europe/Madrid;43.117, -7.61714"
    while (token!=NULL){
        
        switch(contador){
            case 0: 
                //printf("contador en ID: %d\n", contador);
                lugares[indice].ID = atoi(token);
                token = strtok(NULL, ";");
                break;
            
            case 1:
                //printf("contador en Geoname_ID: %d\n", contador);
                lugares[indice].Geoname_ID = atoi(token);
                token = strtok(NULL, ";");
                break;

            case 2:
                //printf("contador en Name: %d\n", contador);
                strcpy(lugares[indice].Name, token);
                token = strtok(NULL, ";");
                break;
            
            case 3:
                //printf("contador en Country_code: %d\n", contador);
                strcpy(lugares[indice].Country_code, token);
                token = strtok(NULL, ";");
                break;
            
            case 4:
                //printf("contador en Country_name: %d\n", contador);
                strcpy(lugares[indice].Country_name, token);
                token = strtok(NULL, ";");
                break;

            case 5:
                //printf("contador en Population: %d\n", contador);
                lugares[indice].Population = atoi(token);
                token = strtok(NULL, ";");
                break;
            
            case 6:
                //printf("contador en Elevation: %d\n", contador);
                lugares[indice].Elevation = atoi(token);
                token = strtok(NULL, ";");
                break;

            case 7:
                //printf("contador en Timezone: %d\n", contador);
                lugares[indice].Timezone = atoi(token);
                token = strtok(NULL, ";");
                break;
            
            case 8:
                //printf("contador en Coordinates_latitude: %d\n", contador);
                lugares[indice].Coordinates_latitude = atof(token);
                token = strtok(NULL, ",");
                printf("TOKEN: %s\n", token);
                break;

            case 9:
                //printf("contador en Coordinates_longitude: %d\n", contador);
                lugares[indice].Coordinates_longitude = atof(token);
                token = strtok(NULL, ";");
                break;
        }
            
        if (contador==10){
            contador = 0;
            indice++;
        }
        contador++;
        //printf("TOKEN: %s\n", token);
        
        

    }
    //primera linea del archivo csv: "ID;Geoname_ID;Name;Country_Code;Country_name;Population;Elevation;Timezone;Coordinates"
    //segunda linea del archivo csv: 319;1625084;Tangerang;ID;Indonesia;1911914;18;Asia/Jakarta;-6.17806, 106.63
    //printf("contador: %d\n", contador);
    printf("lugares[0].Name: %lf\n", lugares[0].Coordinates_longitude);
    fclose(archivo);
    return 0;

}