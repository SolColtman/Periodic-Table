//
// Created by SolColtman on 06/08/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct element{
    char name[16];
    char symbol[2];
    int number;
    float mass;
};

struct element elements[118];
char* getCSVField(char *line, int num);

int main(int argc, char **argv){
    FILE *fp;
    char line[256];
    char *item;
    char *file="index.csv";

    if (!(fp=fopen(file, "r"))){
        fprintf(stderr, "error unable to read file %s\n", "index.csv");
        exit(EXIT_FAILURE);
    }

    int check=fgetc(fp);
    if(check==EOF)
        exit(EXIT_FAILURE);

    while(fgets(line, 256, fp)){
        char* temp = strdup(line);
        item=getCSVField(temp, 1);
        printf("%s\n", item);
        free(temp);
    }

    return 0;
}

char* getCSVField(char *line, int num){

    char* token;
    for (token = strtok(line, ",");
            token && *token;
            token = strtok(NULL, ",/n"))
    {
        if (!--num)
            return token;
    }

    return NULL;
}