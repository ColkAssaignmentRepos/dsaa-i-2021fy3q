//
// Created by Manaki ITO on 2022/01/11.
//
#include <stdio.h>
#include <stdlib.h>

#define print_green(...) {printf("\x1b[32m"); printf(__VA_ARGS__); printf("\x1b[39m\n");}
#define print_error(...) {fprintf(stderr, "\x1b[31m"); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\x1b[39m\n");}
#define fatal(exit_code, ...) {print_error(__VA_ARGS__); exit(exit_code);}
#define blank() {printf("\n");}

#define FILENAME "data.txt"
#define SIZE 10
#define NUM_OF_DATA 5
#define EMPTY 0
#define USED 1

typedef struct {
    int is_empty;
    int data;
} record;

void initialize_array_with(int target[], int initialize_with);

void load_data(char *path_to_file, int dist[]);

void initialize_hash_table(record hashtable[]);

int hash(int n);

void add(record hashtable[], int n);

void display(record hashtable[]);

void read_data(int raw[], record dist[]);


int main() {
    int raw_data[SIZE];
    record hashtable[SIZE];

    initialize_array_with(raw_data, 0);
    initialize_hash_table(hashtable);

    load_data(FILENAME, raw_data);
    read_data(raw_data, hashtable);

    printf("========== hashtable ==========\n");
    display(hashtable);
    printf("===============================\n");

    return 0;
}


void initialize_array_with(int target[], int initialize_with) {
    for (int i = 0; i < SIZE; i++) {
        target[i] = initialize_with;
    }
}


void load_data(char *path_to_file, int dist[]) {
    FILE *fp = fopen(path_to_file, "r");
    if (fp == NULL) {
        fatal(-1, "[X] Unknown error: Failed to open '%s'.", FILENAME)
    }

    int retval = fscanf(fp, "%d %d %d %d %d", &dist[0], &dist[1], &dist[2], &dist[3], &dist[4]);

    if (retval == -1) {
        fatal(-1, "[X] Unknown error: Failed read the file.\n"
                  "Make sure the format is correct and there is no new line.")
    }

    fclose(fp);
}


void initialize_hash_table(record hashtable[]) {
    for (int i = 0; i < SIZE; i++) {
        hashtable[i].data = 0;
        hashtable[i].is_empty = EMPTY;
    }
}


int hash(int n) {
    return n % SIZE;
}


void add(record hashtable[], int n) {
    int i = 0;
    int h = hash(n);

    while (hashtable[h].is_empty == USED) {
        i++;
        if (i >= SIZE) {
            fatal(-1, "[X] Runtime Exception: The hashtable is full.")
        }
        h = hash(h + 1);
    }

    hashtable[h].data = n;
    hashtable[h].is_empty = USED;
}


void display(record hashtable[]) {
    int i;
    for (i=0; i<SIZE; i++) {
        printf("%2d: VALUE: %2d STATUS %d\n", i, hashtable[i].data, hashtable[i].is_empty);
    }
}


// オープンアドレス法を用いて、raw[] のデータを全て dist[] に再配置する
void read_data(int raw[], record dist[]) {
    for (int i = 0; i < NUM_OF_DATA; i++) {
        add(dist, raw[i]);
    }
}
