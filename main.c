//
// Created by Sol Coltman on 23/08/2023
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

char* getCSVField(char *line, int num);
void loadData(FILE *fp);
struct element e[118];

int main(){
    FILE *fp;
    char *file="index.csv";
    char *name;
    char *symbol;
    int number;
    float mass;
    int check;

    if (!(fp=fopen(file, "r"))){
        fprintf(stderr, "error: unable to open/locate index.csv\n");
        exit(EXIT_FAILURE);
    }

    if (check=fgetc(fp) == EOF)
        exit(1);

    loadData(fp);

    printf("%s\n", e[0].symbol);

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

void loadData(FILE *fp){
    char line[256];
    int count = 0;

    while(fgets(line, 256, fp)){
        char * tmp = strdup(line);
        if (count>0)
            printf("Field 1 would be %s\n", getCSVField(tmp, 1));
        free(tmp);
        count++;
    }

    strcpy(e[0].name, "Hello");
    strcpy(e[0].symbol, "Pn");
    e[0].number = 1;
    e[0].mass = 1.0;

    fclose(fp);
}