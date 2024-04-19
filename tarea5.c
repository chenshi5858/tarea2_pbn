#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
    int ID, Geoname_ID, Population, Elevation;
    double Coordinates_latitude, Coordinates_longitude;
    char Name[100], Country_code[3], Country_name[100], Timezone[50];
} Lugar;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s archivo.csv\n", argv[0]);
        return 1;
    }

    FILE* archivo = fopen(argv[1], "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    char linea[MAX_LINE_LENGTH];
    char line[1000];
    int numero_lugares = 0;
    
    while(fgets(line, 999, archivo)) numero_lugares++;
    
    Lugar lugares[numero_lugares+1];
    rewind(archivo);
    int num_lugares = 0;

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        Lugar lugar;
        char* token = strtok(linea, ";");
        lugar.ID = atoi(token);

        token = strtok(NULL, ";");
        lugar.Geoname_ID = atoi(token);

        token = strtok(NULL, ";");
        strcpy(lugar.Name, token);

        token = strtok(NULL, ";");
        if (token != NULL) {
            strcpy(lugar.Country_code, token);
        } else {
            strcpy(lugar.Country_code, "");
        }

        token = strtok(NULL, ";");
        strcpy(lugar.Country_name, token);

        token = strtok(NULL, ";");
        lugar.Population = atoi(token);

        token = strtok(NULL, ";");
        lugar.Elevation = atoi(token);

        token = strtok(NULL, ";");
        strcpy(lugar.Timezone, token);

        token = strtok(NULL, ",");
        lugar.Coordinates_latitude = atof(token);

        token = strtok(NULL, ",");
        lugar.Coordinates_longitude = atof(token);

        lugares[num_lugares++] = lugar;
    }

    fclose(archivo);

    // Imprimir los lugares leídos
    for (int i = 0; i < num_lugares; i++) {
        printf("ID: %d\n", lugares[i].ID);
        printf("Geoname ID: %d\n", lugares[i].Geoname_ID);
        printf("Name: %s\n", lugares[i].Name);
        printf("Country Code: %s\n", lugares[i].Country_code);
        printf("Country Name: %s\n", lugares[i].Country_name);
        printf("Population: %d\n", lugares[i].Population);
        printf("Elevation: %d\n", lugares[i].Elevation);
        printf("Timezone: %s\n", lugares[i].Timezone);
        printf("Coordinates Latitude: %lf\n", lugares[i].Coordinates_latitude);
        printf("Coordinates Longitude: %lf\n\n", lugares[i].Coordinates_longitude);
    }

    return 0;
}