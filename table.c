#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int BUFFER_SIZE = 256;

char *string_copy(char *string);
FILE *build_file(char **arr, int arr_size);

int main() {
    FILE *read_file = fopen("ignore/cities.txt", "r");
    if (read_file == NULL) {
        perror("Não foi possivel abrir o arquivo.");
    }

    char buffer[BUFFER_SIZE];
    char **cities = (char **) malloc(sizeof(char**));
    int i, array_size;
    i = array_size = 0;
    while(fgets(buffer, sizeof(buffer), read_file) != NULL) {
        if (i == 0) {
            cities[i] = string_copy(buffer);
            i++;
            continue;
        }
        // alocar memoria para o array com uma posição a mais
        char **temp = cities;
        array_size = i + 1;
        cities = (char**) malloc((array_size) * sizeof(char *));
        
        memmove(cities, temp, (array_size - 1) * sizeof(char *));
        
        // copiar nova string para a ultima posição do array
        cities[i] = string_copy(buffer);
        i++;
        free(temp);
    }
    fclose(read_file);

    FILE *write_file = build_file(cities, array_size);
    fclose(write_file);
}


FILE *build_file(char **arr, int arr_size) {
    FILE *write_file = fopen("ignore/table.txt", "w");
    if (write_file == NULL) {
        perror("Não foi possivel abrir o arquivo.");
    }

    srand(time(NULL));
    for(int i = 0; i < 1e3; i++) {
        int r = rand() % arr_size;
        fprintf(write_file, "%s", arr[r]);
    }
    return write_file;
}

char *string_copy(char *string) {
    char *return_string = malloc(strlen (string) + 1);
    if (return_string == NULL) return NULL;
    strcpy(return_string, string);
    return return_string;
}