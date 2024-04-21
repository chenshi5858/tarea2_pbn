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
    Place *place = malloc(500000 * sizeof(Place)); // Esto debería ser suficiente para almacenar los datos

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
        }
    }
    rewind(file);
    fgets(line, MAX_LINE_LENGTH - 1, file);
    int num_lugares = 0;
    while (fgets(line, MAX_LINE_LENGTH - 1, file) != NULL) num_lugares++;
    qsort(place, i, sizeof(Place), compareByName);

    // printf("numero de lugares: %d\n", num_lugares);
    // for (int j = 0; j < num_lugares; j++) {
    //     printf("Country Name: %s\n", place[j].Name);
    //     printf("%d\n", j);
    // }

    qsort(place, i, sizeof(Place), compareByPopulation);
    for (int j = 0; j < num_lugares; j++) {
        printf("Country Name: %s\n", place[j].Name);
        printf("Population: %d\n", place[j].Population);
        printf("%d\n", j);
    }

    free(place);
    fclose(file);
    return 0;
}