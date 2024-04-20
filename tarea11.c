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
} Lugar;

// Estructura de la lista para almacenar los lugares
typedef struct nodo {
    Lugar lugar;
    struct nodo *siguiente;
} Nodo;

// Función para guardar los datos en un struct Lugar
void save_data(Lugar *lugar, char *fields[]) {
    lugar->ID = atoi(fields[0]);
    lugar->Geoname_ID = atoi(fields[1]);
    strcpy(lugar->Name, strlen(fields[2]) ? fields[2] : "N/A");
    strcpy(lugar->Country_Code, strlen(fields[3]) ? fields[3] : "N/A");
    strcpy(lugar->Country_name, strlen(fields[4]) ? fields[4] : "N/A");
    lugar->Population = strlen(fields[5]) ? atoi(fields[5]) : -1;
    lugar->Elevation = strlen(fields[6]) ? atoi(fields[6]) : -1;
    strcpy(lugar->Timezone, strlen(fields[7]) ? fields[7] : "N/A");
    strcpy(lugar->Coordinates, strlen(fields[8]) ? fields[8] : "N/A");
}

// Función para agregar un lugar a la lista
void agregar_lugar(Nodo **lista, Lugar lugar) {
    Nodo *nuevo_nodo = malloc(sizeof(Nodo));
    if (nuevo_nodo == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el nuevo nodo.\n");
        exit(1);
    }
    nuevo_nodo->lugar = lugar;
    nuevo_nodo->siguiente = *lista;
    *lista = nuevo_nodo;
}

int main() {
    FILE *file = fopen("prueba.csv", "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    Nodo *lista = NULL;

    // Leer la primera línea para ignorar los encabezados
    fgets(line, MAX_LINE_LENGTH, file);

    // Leer y guardar los datos de cada línea del archivo
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char *fields[9];
        char *token = strtok(line, ";"); // Cambio a strtok ya que está definida al principio
        int count = 0;
        while (token != NULL && count < 9) {
            fields[count++] = token;
            token = strtok(NULL, ";");
        }
        if (count == 9) {
            Lugar lugar;
            save_data(&lugar, fields);
            agregar_lugar(&lista, lugar);
        }
    }

    // Imprimir los datos almacenados en la lista
    Nodo *actual = lista;
    while (actual != NULL) {
        printf("ID: %d\n", actual->lugar.ID);
        printf("Geoname ID: %d\n", actual->lugar.Geoname_ID);
        printf("Name: %s\n", actual->lugar.Name);
        printf("Country Code: %s\n", actual->lugar.Country_Code);
        printf("Country Name: %s\n", actual->lugar.Country_name);
        printf("Population: %d\n", actual->lugar.Population);
        printf("Elevation: %d\n", actual->lugar.Elevation);
        printf("Timezone: %s\n", actual->lugar.Timezone);
        printf("Coordinates: %s\n", actual->lugar.Coordinates);
        printf("\n");
        actual = actual->siguiente;
    }

    // Liberar memoria de la lista
    while (lista != NULL) {
        Nodo *temp = lista;
        lista = lista->siguiente;
        free(temp);
    }

    fclose(file);
    return 0;
}