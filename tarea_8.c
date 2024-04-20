#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int ID, Geoname_ID, Population, Elevation;
    double Coordinates_latitude, Coordinates_longitude;
    char Name[100], Country_code[3], Country_name[100], Timezone[1000];
} Lugar;

int main(int argc, char* argv[]){
    FILE* archivo= fopen(argv[1], "r");
    char c;
    while ((c=fgetc(archivo))!=EOF){

        printf("%c", c);
        
    }
    return 0;
}