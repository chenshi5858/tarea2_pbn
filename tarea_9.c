#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1000

// Definición del struct para almacenar los datos
typedef struct {
    int ID;
    int Geoname_ID;
    char Name[50];
    char Country_Code[3];
    char Country_name[50];
    int Population;
    int Elevation;
    char Timezone[50];
    char Coordinates[30];
} Place;

char* strtoke(char *str, const char *delim)
{
    static char *start = NULL; /* stores string str for consecutive calls */
    char *token = NULL; /* found token */
    /* assign new start in case */
    if (str) start = str;
    /* check whether text to parse left */
    if (!start) return NULL;
    /* remember current start as found token */
    token = start;
    /* find next occurrence of delim */
    start = strpbrk(start, delim);
    /* replace delim with terminator and move start to follower */
    if (start) *start++ = '\0';
    /* done */
    return token;
}

int compareByName(const void* a, const void* b) {
    const Place* placeA = (const Place*)a;
    const Place* placeB = (const Place*)b;
    return strcasecmp(placeA->Name, placeB->Name);
}

int compareByPopulation(const void* a, const void* b) {
    const Place* placeA = (const Place*)a;
    const Place* placeB = (const Place*)b;

    if (placeA->Population < placeB->Population) {
        return -1;
    } else if (placeA->Population > placeB->Population) {
        return 1;
    } else {
        return 0;
    }
}

int compareByElevation(const void* a, const void* b) {
    const Place* placeA = (const Place*)a;
    const Place* placeB = (const Place*)b;

    if (placeA->Elevation < placeB->Elevation) {
        return -1;
    } else if (placeA->Elevation > placeB->Elevation) {
        return 1;
    } else {
        return 0;
    }
}

int compareByLatitude(const void* a, const void* b) {
    const Place* placeA = (const Place*)a;
    const Place* placeB = (const Place*)b;

    // Copiar las coordenadas para no modificar la original
    char coordinatesA[30], coordinatesB[30];
    strcpy(coordinatesA, placeA->Coordinates);
    strcpy(coordinatesB, placeB->Coordinates);

    // Obtener la latitud del primer número en las coordenadas
    char *tokenA = strtok(coordinatesA, ",");
    char *tokenB = strtok(coordinatesB, ",");

    double latitudeA = atof(tokenA);
    double latitudeB = atof(tokenB);

    if (latitudeA < latitudeB) {
        return -1;
    } else if (latitudeA > latitudeB) {
        return 1;
    } else {
        return 0;
    }
}

// Función para guardar los datos en un struct Place
void save_data(Place *place, char *fields[]) {
    place->ID = atoi(fields[0]);
    place->Geoname_ID = atoi(fields[1]);
    strcpy(place->Name, strlen(fields[2]) ? fields[2] : "N/A");
    strcpy(place->Country_Code, strlen(fields[3]) ? fields[3] : "N/A");
    strcpy(place->Country_name, strlen(fields[4]) ? fields[4] : "N/A");
    place->Population = strlen(fields[5]) ? atoi(fields[5]) : -1;
    place->Elevation = strlen(fields[6]) ? atoi(fields[6]) : -1;
    strcpy(place->Timezone, strlen(fields[7]) ? fields[7] : "N/A");
    strcpy(place->Coordinates, strlen(fields[8]) ? fields[8] : "N/A");
}

int main() {
    FILE *file = fopen("bd_final.csv", "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int i = 0; // Cambiar a 0 ya que los índices de arreglo comienzan en 0
    Place *place = malloc(500000*sizeof(Place)); // Esto debería ser suficiente para almacenar los datos

    // Leer la primera línea para ignorar los encabezados
    fgets(line, MAX_LINE_LENGTH, file);

    // Leer y guardar los datos de cada línea del archivo
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char *fields[9];
        char *token = strtoke(line, ";");
        int count = 0;
        while (token != NULL && count < 9) {
            fields[count++] = token;
            token = strtoke(NULL, ";");
        }
        if (count == 9) {
            save_data(&place[i], fields);
            i++;

            // Imprimir los datos para verificar que se hayan guardado correctamente
            // printf("ID: %d\n", place[i - 1].ID); // Aquí debes imprimir place[i - 1] en lugar de place[i]
            // printf("Geoname ID: %d\n", place[i - 1].Geoname_ID);
            // printf("Name: %s\n", place[i - 1].Name);
            // printf("Country Code: %s\n", place[i - 1].Country_Code);
            // printf("Country Name: %s\n", place[i - 1].Country_name);
            // printf("Population: %d\n", place[i - 1].Population);
            // printf("Elevation: %d\n", place[i - 1].Elevation);
            // printf("Timezone: %s\n", place[i - 1].Timezone);
            // printf("Coordinates: %s\n", place[i - 1].Coordinates);
            // printf("\n");
        }
    }
    rewind(file);
    fgets(line, MAX_LINE_LENGTH-1, file);
    int num_lugares = 0;
    while (fgets(line, MAX_LINE_LENGTH-1, file)!=NULL) num_lugares++;
    //qsort(place, i, sizeof(Place), compareByName);

    // printf("numero de lugares: %d\n", num_lugares);
    // for (int i = 0; i<num_lugares; i++){
    //     printf("Country Name: %s\n", place[i].Name);
    //     printf("%d\n", i);
    // }
    // qsort(place, i, sizeof(Place), compareByPopulation);
    // for (int i = 0; i<num_lugares; i++){
    //     printf("Country Name: %d\n", place[i].Population);
    //     printf("%d\n", i);
    // }

    printf("Numero de lugares: %d\n", num_lugares);
    char input_usuario[50]="vacio";
    while (strcmp(input_usuario, "SALIR") != 0){
        printf("Ingrese orden junto al indice (POBL, ELEV, LAT, nombre de la ciudad): ");
        fgets(input_usuario, 49, stdin);
        input_usuario[strcspn(input_usuario, "\n")] = '\0'; //elimina salto de linea
        printf("%s\n", input_usuario);
        char* token_input = strtok(input_usuario, " ");
        if(strcmp(token_input, "POBL") == 0){
            qsort(place, i, sizeof(Place), compareByPopulation);
            // for (int i = 0; i<num_lugares; i++){
            //     printf("Country Name: %s\n", place[i].Name);
            //     printf("Country Population: %d\n", place[i].Population);
            //     printf("%d\n", i);
            // }
            token_input=strtok(NULL, " ");
            if(token_input[0]=='-'){
                token_input = strtok(token_input, "-");
                printf("%s, %s\n", place[num_lugares-atoi(token_input)].Name, place[num_lugares-atoi(token_input)].Country_name);
            }
            else printf("%s, %s\n", place[atoi(token_input)].Name, place[atoi(token_input)].Country_name);

        }
        if(strcmp(token_input, "ELEV") == 0){
            qsort(place, i, sizeof(Place), compareByElevation);
            // for (int i = 0; i<num_lugares; i++){
            //     printf("Country Name: %s\n", place[i].Name);
            //     printf("Country Elevation: %d\n", place[i].Elevation);
            //     printf("%d\n", i);
            // }
            token_input=strtok(NULL, " ");
            if(token_input[0]=='-'){
                token_input = strtok(token_input, "-");
                printf("%s, %s\n", place[num_lugares-atoi(token_input)].Name, place[num_lugares-atoi(token_input)].Country_name);
            }
            else printf("%s, %s\n", place[atoi(token_input)].Name, place[atoi(token_input)].Country_name);

        }
        if(strcmp(token_input, "LAT") == 0){
            qsort(place, i, sizeof(Place), compareByLatitude);
            
            // for (int i = 0; i < num_lugares; i++) {
            //     printf("City Name: %s\n", place[i].Name);

            //     // Extrayendo solo la latitud de las coordenadas
            //     char coordinates[30];
            //     strcpy(coordinates, place[i].Coordinates);
            //     char *latitude = strtok(coordinates, ",");
            //     printf("Latitude: %s\n", latitude);

            //     printf("%d\n", i);
            // }
            token_input=strtok(NULL, " ");
            if(token_input[0]=='-'){
                token_input = strtok(token_input, "-");
                printf("%s, %s\n", place[num_lugares-atoi(token_input)].Name, place[num_lugares-atoi(token_input)].Country_name);
            }
            else printf("%s, %s\n", place[atoi(token_input)].Name, place[atoi(token_input)].Country_name);
           
            

        }
        

    }


    free(place);
    fclose(file);
    return 0;
}