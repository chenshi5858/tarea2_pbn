#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

// Definición del struct para almacenar los datos
typedef struct Place {
    int ID;
    int Geoname_ID;
    char Name[50];
    char Country_Code[3];
    char Country_name[50];
    int Population;
    int Elevation;
    char Timezone[50];
    char Coordinates[30];
    struct Place *next;
} Place;

// Función para guardar los datos en un struct Place y agregarlo a la lista
void save_data(Place **head, char *fields[]) {
    Place *new_place = (Place *)malloc(sizeof(Place));
    if (new_place == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo lugar.\n");
        exit(1);
    }

    new_place->ID = atoi(fields[0]);
    new_place->Geoname_ID = atoi(fields[1]);
    strcpy(new_place->Name, strlen(fields[2]) ? fields[2] : "N/A");
    strcpy(new_place->Country_Code, strlen(fields[3]) ? fields[3] : "N/A");
    strcpy(new_place->Country_name, strlen(fields[4]) ? fields[4] : "N/A");
    new_place->Population = strlen(fields[5]) ? atoi(fields[5]) : -1;
    new_place->Elevation = strlen(fields[6]) ? atoi(fields[6]) : -1;
    strcpy(new_place->Timezone, strlen(fields[7]) ? fields[7] : "N/A");
    strcpy(new_place->Coordinates, strlen(fields[8]) ? fields[8] : "N/A");
    new_place->next = NULL;

    // Agregar el nuevo lugar al final de la lista
    if (*head == NULL) {
        *head = new_place;
    } else {
        Place *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_place;
    }
}

// Función para imprimir la lista de lugares
void print_list(Place *head) {
    Place *current = head;
    while (current != NULL) {
        printf("ID: %d\n", current->ID);
        printf("Geoname ID: %d\n", current->Geoname_ID);
        printf("Name: %s\n", current->Name);
        printf("Country Code: %s\n", current->Country_Code);
        printf("Country Name: %s\n", current->Country_name);
        printf("Population: %d\n", current->Population);
        printf("Elevation: %d\n", current->Elevation);
        printf("Timezone: %s\n", current->Timezone);
        printf("Coordinates: %s\n", current->Coordinates);
        printf("\n");
        current = current->next;
    }
}

// Función para liberar la memoria utilizada por la lista
void free_list(Place *head) {
    while (head != NULL) {
        Place *temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    FILE *file = fopen("prueba.csv", "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    Place *head = NULL;

    // Leer la primera línea para ignorar los encabezados
    fgets(line, MAX_LINE_LENGTH, file);

    // Leer y guardar los datos de cada línea del archivo
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char *fields[9];
        char *token = strtok(line, ";");
        int count = 0;
        while (token != NULL && count < 9) {
            fields[count++] = token;
            token = strtok(NULL, ";");
        }
        if (count == 9) {
            save_data(&head, fields);
        }
    }

    fclose(file);

    // Imprimir la lista de lugares
    print_list(head);

    // Liberar la memoria utilizada por la lista
    free_list(head);

    return 0;
}
