#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int ID, Geoname_ID, Population, Elevation;
    double Coordinates_latitude, Coordinates_longitude;
    char Name[100], Country_code[3], Country_name[100], Timezone[1000];
} Lugar;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s archivo.csv\n", argv[0]);
        return 1;
    }

    FILE* archivo = fopen(argv[1], "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    char line[1000];
    int indice = 0;
    Lugar lugares[100]; // Suponiendo un máximo de 100 lugares

    fgets(line, sizeof(line), archivo); // Ignorar la primera línea del archivo CSV
    
    while (fgets(line, sizeof(line), archivo) != NULL) {
        char* token = strtok(line, ";");

        // ID
        lugares[indice].ID = token ? atoi(token) : 0;

        // Geoname ID
        token = strtok(NULL, ";");
        lugares[indice].Geoname_ID = token ? atoi(token) : 0;

        // Name
        token = strtok(NULL, ";");
        strncpy(lugares[indice].Name, token ? token : "N/A", sizeof(lugares[indice].Name) - 1);
        lugares[indice].Name[sizeof(lugares[indice].Name) - 1] = '\0';

        // Country Code
        token = strtok(NULL, ";");
        strncpy(lugares[indice].Country_code, token ? token : "N/A", sizeof(lugares[indice].Country_code) - 1);
        lugares[indice].Country_code[sizeof(lugares[indice].Country_code) - 1] = '\0';

        // Country Name
        token = strtok(NULL, ";");
        strncpy(lugares[indice].Country_name, token ? token : "N/A", sizeof(lugares[indice].Country_name) - 1);
        lugares[indice].Country_name[sizeof(lugares[indice].Country_name) - 1] = '\0';

        // Population
        token = strtok(NULL, ";");
        lugares[indice].Population = token ? atoi(token) : 0;

        // Elevation
        token = strtok(NULL, ";");
        lugares[indice].Elevation = token ? atoi(token) : 0;

        // Timezone
        token = strtok(NULL, ";");
        strncpy(lugares[indice].Timezone, token ? token : "N/A", sizeof(lugares[indice].Timezone) - 1);
        lugares[indice].Timezone[sizeof(lugares[indice].Timezone) - 1] = '\0';

        // Coordinates Latitude
        token = strtok(NULL, ",");
        lugares[indice].Coordinates_latitude = token ? atof(token) : 0;

        // Coordinates Longitude
        token = strtok(NULL, ";");
        lugares[indice].Coordinates_longitude = token ? atof(token) : 0;

        indice++;
    }

    // Imprimir información del décimo lugar como prueba
    printf("ID: %d\n", lugares[10].ID);
    printf("Geoname ID: %d\n", lugares[10].Geoname_ID);
    printf("Name: %s\n", lugares[10].Name);
    printf("Country Code: %s\n", lugares[10].Country_code);
    printf("Country Name: %s\n", lugares[10].Country_name);
    printf("Population: %d\n", lugares[10].Population);
    printf("Elevation: %d\n", lugares[10].Elevation);
    printf("Timezone: %s\n", lugares[10].Timezone);
    printf("Coordinates Latitude: %lf\n", lugares[10].Coordinates_latitude);
    printf("Coordinates Longitude: %lf\n", lugares[10].Coordinates_longitude);

    fclose(archivo);
    return 0;
}