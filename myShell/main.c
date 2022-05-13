#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 256
#define MAX_ARG_LEN 32
#define MAX_NR_ARGS 8
#define MAX_LINE_LEN 256

void copy_files(FILE* src, FILE* dest) {
    int c;
    
    while ((c = getc(src)) != EOF) {
        fprintf(dest, "%c", c);
    }
}

void cat(FILE* name) {
    int c;
    while ((c = getc(name)) != EOF) {
       printf("%c", c);
   }
}

void touch(char* file_name) {
    FILE* new = fopen(file_name, "w");
    
    fclose(new);
}

void _echo(char parsed_input[][MAX_ARG_LEN], int args_cnt) {
    for (int i = 1; i < args_cnt; i++) {
        printf("%s", parsed_input[i]);
        if (i != args_cnt - 1)
            printf(" ");
    }
    printf("\n");
}

// break input into words
int parse_input(char* input, char parsed_input[][MAX_ARG_LEN]) {
    int nrWords = 0;

    char* token = strtok(input, " ");

    while (token != NULL) {
        strcpy(parsed_input[nrWords++], token);
        token = strtok(NULL, " ");
    }

    parsed_input[nrWords][0] = '\0';

    return nrWords;

}

void start(void) {
    
    bool finished = false;
    do {
        printf("shell-> ");
        char input[MAX_INPUT_SIZE]; // initial input
        char parsed_input[MAX_NR_ARGS][MAX_ARG_LEN]; // used to store arguments
        fgets(input, 256, stdin);

        int args_cnt = parse_input(input, parsed_input);

        for (int i = 0; i < args_cnt; i++) {
            parsed_input[i][strcspn(parsed_input[i], "\n")] = '\0';
        }

        char *function = parsed_input[0];

        if (!strcmp(function, "echo")) {
            _echo(parsed_input, args_cnt);
        }

        if (!strcmp(function, "cat")) {
            for (int i = 1; i < args_cnt; i++) {
                FILE* src  = fopen(parsed_input[i], "r");
                cat(src);
                fclose(src);
            }
        }
        
        // find out why this doesn't work
        if (!strcmp(function, "touch")) {
            for (int i = 1; i < args_cnt; i++) {
                touch(parsed_input[i]);
            }
        }
        
        if (!strcmp(function, "cp")) {
            FILE* src = fopen(parsed_input[1], "r");
            FILE* dest = fopen(parsed_input[2], "a+");
            
            copy_files(src, dest);
            
            fclose(src);
            fclose(dest);
        }

        if (!strcmp(function, "exit")) {
            finished = true;
        }

    } while(!finished);
}

int main(void) {

    start();

    return 0;
}
