//
// Created by Manaki ITO on 2021/12/07.
// Edited by Manaki ITO on 2022/01/11.
//

#include <stdio.h>
#include <stdlib.h>

#define N 8
#define FILE_NAME "graph_2.txt"

#define print_green(...) {printf("\x1b[32m"); printf(__VA_ARGS__); printf("\x1b[39m\n");}
#define print_error(...) {fprintf(stderr, "\x1b[31m"); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\x1b[39m\n");}
#define fatal(exit_code, ...) {print_error(__VA_ARGS__); exit(exit_code);}
#define blank() {printf("\n");}

int a[N + 1][N + 1];
int v[N + 1];

void visit(int);

void load_file(char *file_name);


int main(void) {
    int i;

    for (i = 1; i <= N; i++) {
        v[i] = 0;
    }

    load_file(FILE_NAME);

    visit(1);

    printf("\n");
}

void visit(int i) {
    int j;

    v[i] = 1;
    for (j = 1; j <= N; j++) {
        if (a[i][j] == 1 && v[j] == 0) {
            printf("%d->%d ", i, j);
            visit(j);
        }
    }
}


void load_file(char *file_name) {
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        fatal(-1, "[X] Unknown error: Failed to open '%s'.", file_name)
    }

    for (int i = 0; i < N + 1; i++) {
        fscanf(fp, "%d, %d, %d, %d, %d, %d, %d, %d, %d",
               &a[i][0], &a[i][1], &a[i][2], &a[i][3], &a[i][4],
               &a[i][5], &a[i][6], &a[i][7], &a[i][8]);
    }


    fclose(fp);
}
