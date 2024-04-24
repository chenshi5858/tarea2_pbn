#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LARGO_MAX 1000

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

char* Separador_de_str(char *str, const char *delim)
{
    static char *start = NULL;
    char *token = NULL;
    if (str) start = str;
    if (!start) return NULL;
    token = start;
    start = strpbrk(start, delim);
    if (start) *start++ = '\0';
    return token;
}

int Comparar_Nombre(const void* a, const void* b) {
    const Lugar* lugarA = (const Lugar*)a;
    const Lugar* lugarB = (const Lugar*)b;
    return strcasecmp(lugarA->Name, lugarB->Name);
}

int Comparar_Poblacion(const void* a, const void* b) {
    const Lugar* lugarA = (const Lugar*)a;
    const Lugar* lugarB = (const Lugar*)b;

    if (lugarA->Population < lugarB->Population) {
        return -1;
    } else if (lugarA->Population > lugarB->Population) {
        return 1;
    } else {
        return 0;
    }
}

int Comparar_Elevacion(const void* a, const void* b) {
    const Lugar* lugarA = (const Lugar*)a;
    const Lugar* lugarB = (const Lugar*)b;

    if (lugarA->Elevation < lugarB->Elevation) {
        return -1;
    } else if (lugarA->Elevation > lugarB->Elevation) {
        return 1;
    } else {
        return 0;
    }
}

int Comparar_Latitud(const void* a, const void* b) {
    const Lugar* lugarA = (const Lugar*)a;
    const Lugar* lugarB = (const Lugar*)b;

    char coordenadasA[30], coordenadasB[30];
    strcpy(coordenadasA, lugarA->Coordinates);
    strcpy(coordenadasB, lugarB->Coordinates);

    char *tokenA = strtok(coordenadasA, ",");
    char *tokenB = strtok(coordenadasB, ",");

    double latitudA = atof(tokenA);
    double latitudB = atof(tokenB);

    if (latitudA < latitudB) {
        return -1;
    } else if (latitudA > latitudB) {
        return 1;
    } else {
        return 0;
    }
}

void Guardar_Datos(Lugar *lugar, char *datos[]) {
    lugar->ID = atoi(datos[0]);
    lugar->Geoname_ID = atoi(datos[1]);
    strcpy(lugar->Name, strlen(datos[2]) ? datos[2] : "N/A");
    strcpy(lugar->Country_Code, strlen(datos[3]) ? datos[3] : "N/A");
    strcpy(lugar->Country_name, strlen(datos[4]) ? datos[4] : "N/A");
    lugar->Population = strlen(datos[5]) ? atoi(datos[5]) : -1;
    lugar->Elevation = strlen(datos[6]) ? atoi(datos[6]) : -1;
    strcpy(lugar->Timezone, strlen(datos[7]) ? datos[7] : "N/A");
    strcpy(lugar->Coordinates, strlen(datos[8]) ? datos[8] : "N/A");
}

int main(int argc, char **argv) {
    FILE *archivo = fopen(argv[1], "r");
    if (argc != 2){
        printf("Cantidad de argumentos invalida");
        return 1;
    }
    if (archivo == NULL) {
        printf("Error al abrir el archivo");
        return 1;
    }

    char linea[LARGO_MAX];
    fgets(linea, LARGO_MAX-1, archivo);
    int num_lugares = 0;
    while (fgets(linea, LARGO_MAX-1, archivo)!=NULL) num_lugares++;
    rewind(archivo);
    int i = 0;
    Lugar *lugar = malloc(num_lugares*sizeof(Lugar));

    fgets(linea, LARGO_MAX, archivo);

    while (fgets(linea, LARGO_MAX, archivo) != NULL) {
        char *datos[9];
        char *token = Separador_de_str(linea, ";");
        int count = 0;
        while (token != NULL && count < 9) {
            datos[count++] = token;
            token = Separador_de_str(NULL, ";");
        }
        if (count == 9) {
            Guardar_Datos(&lugar[i], datos);
            i++;

            // printf("ID: %d\n", lugar[i-1].ID);
            // printf("Geoname ID: %d\n", lugar[i-1].Geoname_ID);
            // printf("Name: %s\n", lugar[i-1].Name);
            // printf("Country Code: %s\n", lugar[i-1].Country_Code);
            // printf("Country Name: %s\n", lugar[i-1].Country_name);
            // printf("Population: %d\n", lugar[i-1].Population);
            // printf("Elevation: %d\n", lugar[i-1].Elevation);
            // printf("Timezone: %s\n", lugar[i-1].Timezone);
            // printf("Coordinates: %s\n", lugar[i-1].Coordinates);
            // printf("\n");
        }
    }

    //qsort(lugar, i, sizeof(lugar), Comparar_Nombre);

    // printf("numero de lugares: %d\n", num_lugares);
    // for (int i = 0; i<num_lugares; i++){
    //     printf("Country Name: %s\n", lugar[i].Name);
    //     printf("%d\n", i);
    // }
    // qsort(lugar, i, sizeof(lugar), Comparar_Poblacion);
    // for (int i = 0; i<num_lugares; i++){
    //     printf("Country Name: %d\n", lugar[i].Population);
    //     printf("%d\n", i);
    // }

    printf("Numero de lugares: %d\n", num_lugares);
    char input_usuario[50]="vacio";
    char nombre_ciudad[50];
    while (strcmp(input_usuario, "SALIR") != 0){
        printf("Ingrese orden junto al indice (POBL, ELEV, LAT, nombre de la ciudad y SALIR si desea terminar): ");
        fgets(input_usuario, 49, stdin);
        input_usuario[strcspn(input_usuario, "\n")] = '\0';
        strcpy(nombre_ciudad, input_usuario);
        printf("%s\n", input_usuario);
        char* token_input = strtok(input_usuario, " ");
        int respuesta_valida = 0;
        if(strcmp(token_input, "POBL") == 0){
            qsort(lugar, i, sizeof(Lugar), Comparar_Poblacion);
            // for (int i = 0; i<num_lugares; i++){
            //     printf("Country Name: %s\n", lugar[i].Name);
            //     printf("Country Population: %d\n", lugar[i].Population);
            //     printf("%d\n", i);
            // }
            token_input=strtok(NULL, " ");
            if(token_input[0]=='-'){
                token_input = strtok(token_input, "-");
                printf("Poblacion de %s, %s: %d habitantes\n", lugar[num_lugares-atoi(token_input)].Name, lugar[num_lugares-atoi(token_input)].Country_name, lugar[num_lugares-atoi(token_input)].Population);
            }
            else printf("Poblacion de %s, %s: %d habitantes\n", lugar[atoi(token_input)].Name, lugar[atoi(token_input)].Country_name, lugar[atoi(token_input)].Population);
            respuesta_valida = 1;

        }
        else if(strcmp(token_input, "ELEV") == 0){
            qsort(lugar, i, sizeof(Lugar), Comparar_Elevacion);
            // for (int i = 0; i<num_lugares; i++){
            //     printf("Country Name: %s\n", lugar[i].Name);
            //     printf("Country Elevation: %d\n", lugar[i].Elevation);
            //     printf("%d\n", i);
            // }
            token_input=strtok(NULL, " ");
            if(token_input[0]=='-'){
                token_input = strtok(token_input, "-");
                printf("Elevacion de %s, %s: %d m.s.n.m\n", lugar[num_lugares-atoi(token_input)].Name, lugar[num_lugares-atoi(token_input)].Country_name, lugar[num_lugares-atoi(token_input)].Elevation);
            }
            else printf("Elevacion de %s, %s: %d m.s.n.m\n", lugar[atoi(token_input)].Name, lugar[atoi(token_input)].Country_name, lugar[atoi(token_input)].Elevation);
            respuesta_valida = 1;

        }
        else if(strcmp(token_input, "LAT") == 0){
            token_input=strtok(NULL, " ");
            qsort(lugar, i, sizeof(Lugar), Comparar_Latitud);
            if(token_input[0]=='-'){
                token_input = strtok(token_input, "-");
                printf("Coordenadas de %s, %s: %s\n", lugar[num_lugares-atoi(token_input)].Name, lugar[num_lugares-atoi(token_input)].Country_name, lugar[num_lugares-atoi(token_input)].Coordinates);
            }
            else printf("Coordenadas de %s, %s: %s\n", lugar[atoi(token_input)].Name, lugar[atoi(token_input)].Country_name, lugar[atoi(token_input)].Coordinates);
            respuesta_valida = 1;

        }
        else{
            for (int z = 0; z<num_lugares; z++){
                if (strcmp(nombre_ciudad, lugar[z].Name) == 0){
                    printf("Datos de la ciudad %s: \n", nombre_ciudad);
                    printf("    ID: %d\n", lugar[z].ID);
                    printf("    Geoname ID: %d\n", lugar[z].Geoname_ID);
                    printf("    Name: %s\n", lugar[z].Name);
                    printf("    Country code: %s\n", lugar[z].Country_Code);
                    printf("    Country name: %s\n", lugar[z].Country_name);
                    printf("    Population: %d\n", lugar[z].Population);
                    printf("    Elevation: %d\n", lugar[z].Elevation);
                    printf("    Timezone: %s\n", lugar[z].Timezone);
                    printf("    Coordinates: %s\n", lugar[z].Coordinates);
                    respuesta_valida = 1;
                    break;
                }
            }
            
        }
         
    if (respuesta_valida == 0 && (strcmp(input_usuario, "SALIR") != 0)) printf("No se encontro el nombre de ciudad ingresado\n\n");

    }
    free(lugar);
    fclose(archivo);
    return 0;
}