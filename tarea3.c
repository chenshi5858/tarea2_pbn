#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{

    int ID, Geoname_ID, Population, Elevation;
    double Coordinates_latitude, Coordinates_longitude;
    char Name[100], Country_code[3], Country_name[100], Timezone[1000];

}Lugar;

int main(int argc, char* argv[]){
    
    FILE* archivo = fopen(argv[1], "r");
    char line[1000];
    int numero_lugares = 0;
    
    while(fgets(line, 999, archivo)) numero_lugares++;
    
    Lugar lugares[numero_lugares-1];
    
    
    rewind(archivo);
    
    fgets(line, 999, archivo);//ignora la primera linea del csv
    int indice = 0;
    
    //319;1625084;Tangerang;ID;Indonesia;1911914;18;Asia/Jakarta;-6.17806, 106.63
    
    while(fgets(line, 999, archivo) != NULL){

        char* token = strtok(line, ";");
        if (token == NULL)
            lugares[indice].ID = 0;
        else
            lugares[indice].ID = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL)
            lugares[indice].Geoname_ID = 0;
        else
            lugares[indice].Geoname_ID = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL)
            strcpy(lugares[indice].Name, "N/A");
        else
            strcpy(lugares[indice].Name, token);

        token = strtok(NULL, ";");
        
        if (token == NULL) // Verificar si el Country_Code no está vacío
            strcpy(lugares[indice].Country_code, "N/A"); 
        else
            strcpy(lugares[indice].Country_code, token);
        
        token = strtok(NULL, ";");

        if (token == NULL)
            strcpy(lugares[indice].Country_name, "N/A");
        else
            strcpy(lugares[indice].Country_name, token);

        token = strtok(NULL, ";");
        if (token == NULL)
            lugares[indice].Population = 0;
        else
            lugares[indice].Population = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL)
            lugares[indice].Elevation = 0;
        else
            lugares[indice].Elevation = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL)
            strcpy(lugares[indice].Timezone, "N/A");
        else
            strcpy(lugares[indice].Timezone, token);

        token = strtok(NULL, ",");

        if (token == NULL)
            lugares[indice].Coordinates_latitude = 0;
        else
            lugares[indice].Coordinates_latitude = atof(token);

        token = strtok(NULL, ";");

        if (token == NULL)
            lugares[indice].Coordinates_longitude = 0;
        else
            lugares[indice].Coordinates_longitude = atof(token);

        indice++;

    }
    printf("ID: %d\n", lugares[10].ID);
    printf("Geoname ID: %d\n", lugares[10].Geoname_ID);
    printf("Name: %s\n", lugares[10].Name);
    printf("Country Code: %s\n", lugares[10].Country_code);
    printf("Country Name: %s\n", lugares[10].Country_name);
    printf("Population: %d\n", lugares[10].Population);
    printf("Elevation: %d\n", lugares[10].Elevation);
    printf("Timezone: %s\n", lugares[10].Timezone);
    printf("Coordinates Latitude: %lf\n", lugares[10].Coordinates_latitude);
    printf("Coordinates Longitude: %lf\n\n", lugares[10].Coordinates_longitude);
    fclose(archivo);
    return 0;

}