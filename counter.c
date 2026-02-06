#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *city;
    int counter;
} city_counter;

const int BUFFER_SIZE = 256;

int verify_city(char *city, city_counter *array_cities, int array_size);
int add_to_counter(city_counter *arr, int size ,char *string);
int get_empty_index(city_counter *arr, int size);
char *string_copy(char *string);
city_counter* sort_cities(city_counter *src, int size);
int find_smallest(city_counter *arr, int size);
int find_highest(city_counter *arr, int size);
city_counter* remove_index(city_counter *src, int real_size, int index);

int main() {
    char buffer[BUFFER_SIZE];
    city_counter *cities = (city_counter *) malloc(sizeof(city_counter));
    memset(cities, 0, sizeof(city_counter));

    
    FILE *read_file = fopen("ignore/table.txt", "r");
    if (read_file == NULL) {
        perror("Erro ao abrir o arquivo de leitura.");
        return 1;
    }
    int array_size = 0;
    while(fgets(buffer, sizeof(buffer), read_file) != NULL) {
        // guarda a linha no buffer
        int buffer_length = strlen(buffer); 
        // remove o '\n'
        memset(&buffer[buffer_length - 1], 0, sizeof(char));

        char *current_string = string_copy(buffer);
        // verifica se a linha ja esta no array
        if(verify_city(current_string, cities, array_size) != -1) {
            //ja foi contada uma vez
            int index = add_to_counter(cities, array_size, current_string);
        } else {
            // ainda nao foi contada
            
            // aloca memoria com uma posição maior
            int empty_index = array_size;
            array_size++;
            city_counter *temp_city_array = cities;
            cities = (city_counter *) malloc(array_size * sizeof(city_counter));
            memmove(cities, temp_city_array, array_size * sizeof(city_counter));
            free(temp_city_array);

            // indexa os valores 
            cities[empty_index].city = (char*) malloc((strlen(current_string) + 1) * sizeof(char));
            strcpy(cities[empty_index].city, current_string);
            cities[empty_index].counter = 1;
        }
    }

    cities = sort_cities(cities, array_size);
    for (int i = 0; i < array_size; i++){
        printf("%s: %d\n", cities[i].city, cities[i].counter);
    }
    return 0;
}

int find_highest(city_counter *arr, int size) {
    int highest_index = 0;
    for (int i = 0; i < size; i++) {
        if(arr[highest_index].counter < arr[i].counter) {
            highest_index = i;
        }
    }
    return highest_index;
}

int find_smallest(city_counter *arr, int size) {
    int smallest_index = 0;
    for (int i = 0; i < size; i++) {
        if(arr[smallest_index].counter > arr[i].counter) {
            smallest_index = i;
        }
    }
    return smallest_index;
}

city_counter* sort_cities(city_counter *src, int src_size) {
    city_counter *dest = (city_counter *) malloc(src_size * sizeof(city_counter));
    int length = src_size;
    for(int i = 0; i < length; i++) {
        // find smallest index
        int smallest_index = find_highest(src, src_size);

        // add smallest index to a new array
        memmove(&dest[i], &src[smallest_index], sizeof(city_counter));

        // remove index from the array
        src_size--;
        src = remove_index(src, src_size, smallest_index);
    }
    return dest;
}

city_counter* remove_index(city_counter *src, int new_size, int index) {
    int new_index = 0;
    int old_size = new_size + 1;
    city_counter *temp = src;
    src = (city_counter *) malloc(new_size * sizeof(city_counter));
    for(int i = 0; i < old_size; i++) {
        if(i != index) {
            memmove(&src[new_index], &temp[i], sizeof(city_counter));
            new_index++;
        } else {

            continue;
        }
    }
    free(temp);
    return src;
}

int get_empty_index(city_counter *arr, int size) {
    if (size == 0) return 0;

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

int verify_city(char *city, city_counter *array_cities, int size) {
    // array vazio
    if (size == 0) return -1;

    for (int i = 0; i < size; i++) {
        if(strcmp(city, array_cities[i].city) == 0) {
            // ja esta no array
            return i;
        }
    }

    // nao esta no array
    return -1;
}

char *string_copy(char *string) {
    char *return_string = malloc(strlen (string) + 1);
    if (return_string == NULL) return NULL;
    strcpy(return_string, string);
    return return_string;
}
