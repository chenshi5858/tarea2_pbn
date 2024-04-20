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
    FILE *file = fopen("prueba.csv", "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    Place place;

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
            save_data(&place, fields);

            // Imprimir los datos para verificar que se hayan guardado correctamente
            printf("ID: %d\n", place.ID);
            printf("Geoname ID: %d\n", place.Geoname_ID);
            printf("Name: %s\n", place.Name);
            printf("Country Code: %s\n", place.Country_Code);
            printf("Country Name: %s\n", place.Country_name);
            printf("Population: %d\n", place.Population);
            printf("Elevation: %d\n", place.Elevation);
            printf("Timezone: %s\n", place.Timezone);
            printf("Coordinates: %s\n", place.Coordinates);
            printf("\n");
        }
    }

    fclose(file);
    return 0;
}