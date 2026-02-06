#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const long BUFFER_SIZE = 1000;
const int NUMBER_CITIES = 10;
typedef struct {
    char *city;
    int counter;
} city_counter;

void set_array_cities_zero(city_counter *arr, int size);
int verify_city(char *city, city_counter *array_cities) ;
int add_to_counter(city_counter *arr, int size ,char *string);
int get_empty_index(city_counter *arr, int size);;

int main() {
    char buffer[BUFFER_SIZE];
    // city_counter *cities = (city_counter *) malloc(NUMBER_CITIES * sizeof(city_counter));
    city_counter cities[NUMBER_CITIES];
    set_array_cities_zero(cities, NUMBER_CITIES);
    
    FILE *read_file = fopen("ignore/cidades.txt", "r");
    if (read_file == NULL) {
        perror("Erro ao abrir o arquivo de leitura.");
        return 1;
    }
    
    int current = 0;
    char current_string[20];

    size_t bytes_read;
    while((bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, read_file)) > 0) {
        int first = 0;
        for (int j = 0; current < bytes_read; j++) {
            // limpar string temporaria
            memset(current_string, 0, sizeof(current_string));

            // passa o valor da linha atual para a string temporaria
            while(buffer[current] != '\n') {
                if(current >= bytes_read) {
                    break;
                }
                current++;
            }
            memmove(current_string, &buffer[first], (current - first) * sizeof(char));
            first = current + 1;
             //comparar se a cidade esta ou nao no array
            if (verify_city(current_string, cities) != -1) {
                // ja foi contada pelo menos uma vez
                int index = add_to_counter(cities, NUMBER_CITIES, current_string);
            } else {
                // primeiro vez q a cidade aparece
                int empty_index = get_empty_index(cities, NUMBER_CITIES );
                cities[empty_index].city = (char*) malloc((strlen(current_string) + 1) * sizeof(char));
                strcpy(cities[empty_index].city, current_string);
                cities[empty_index].counter++; 
            }
            current++;
        }
    }
    for (int i = 0; i < NUMBER_CITIES; i++){
        printf("Cidade: %s -> Contador: %d\n", cities[i].city, cities[i].counter);
    }
    return 0;
}

int get_empty_index(city_counter *arr, int size) {
    for(int i = 0; i < size; i++) {
        if(arr[i].counter == 0) {
            return i;
        }
    }
    return -1;
}

int add_to_counter(city_counter *arr, int size ,char *string) {
    for (int i = 0; i < size; i++) {
        if(strcmp(arr[i].city, string) == 0) {
            arr[i].counter++;
            return i;
        }
    }
}

void set_array_cities_zero(city_counter *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i].city = "";
        arr[i].counter = 0;
    }
}

int verify_city(char *city, city_counter *array_cities) {

    for (int i = 0; i < NUMBER_CITIES; i++) {
        if(strcmp(city, array_cities[i].city) == 0) {
            // ja esta no array
            return i;
        }
    }
    // nao esta no array
    return -1;
}