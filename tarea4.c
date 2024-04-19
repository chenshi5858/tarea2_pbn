#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char* argv[]){

    FILE* archivo = fopen(argv[1], "r");
    int numero_lugares = 0;
    char c;
    while((c = fgetc(archivo)) != EOF){
        printf("%c", c);
        if (c == ';' || c == ',' || c == '\n'){
            numero_lugares++;
        }
    }
    printf("%d", numero_lugares);
    rewind(archivo);
    fclose(archivo);
    return 0;

}