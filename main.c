//
// Created by Sol Coltman on 23/08/2023
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct element{
    char name[16];
    char symbol[3];
    int number;
    float mass;
};

char* getCSVField(char *line, int num);
void loadNames(FILE *fp);
void loadSymbols(FILE *fp);
void loadNumber(FILE *fp);
void loadMass(FILE *fp);
FILE* loadFile();
int displayMenu();
struct element e[118];

int main(){
    FILE *fp;
    char *name;
    char *symbol;
    int number;
    float mass;
    int check;

    fp = loadFile();
    loadNames(fp);
    fclose(fp);

    fp = loadFile();
    loadSymbols(fp);
    fclose(fp);

    fp = loadFile();
    loadNumber(fp);
    fclose(fp);

    fp = loadFile();
    loadMass(fp);
    fclose(fp);

    displayMenu();

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

FILE* loadFile(){
    int check;
    FILE *fp;
    char *file="index.csv";

    if (!(fp=fopen(file, "r"))){
        fprintf(stderr, "error: unable to open/locate index.csv\n");
        exit(EXIT_FAILURE);
    }
    if (check=fgetc(fp) == EOF)
        exit(1);

    return fp;
}

void loadNames(FILE *fp){
    char line[256];
    int count = 0;

    while(fgets(line, 256, fp)){
        char * tmp = strdup(line);
        if (count>0){
            strcpy(e[count-1].name, getCSVField(tmp, 1));
        }
        free(tmp);
        count++;
    }

}

void loadSymbols(FILE *fp){
    char line[256];
    int count = 0;

    while(fgets(line, 256, fp)){
        char * tmp = strdup(line);
        if (count>0){
            strcpy(e[count-1].symbol, getCSVField(tmp, 2));
        }
        free(tmp);
        count++;
    }

}

void loadNumber(FILE *fp){
    char line[256];
    int count = 0;

    while(fgets(line, 256, fp)){
        char * tmp = strdup(line);
        if (count>0){
            e[count-1].number = atoi(getCSVField(tmp, 3));
        }
        free(tmp);
        count++;
    }
}

void loadMass(FILE *fp){
    char line[256];
    int count = 0;

    while(fgets(line, 256, fp)){
        char * tmp = strdup(line);
        if (count>0){
            e[count-1].mass = atof(getCSVField(tmp, 4));
        }
        free(tmp);
        count++;
    }
}

int displayMenu(){
    int c = 0;
    int t = 1;
    int n;

    printf("Atomic Number  Symbol  Name  Mass\n");
        for (int i=c; i<c+5; i++){
            printf("%d  %s  %s  %f\n", e[i].number, e[i].symbol, e[i].name, e[i].mass);
        }
    printf("\n");
    printf("    1. Next     2. Back     3. Exit\n");

    while(1){
        scanf("%d", &n);
        if (n == 1)
            c=c+5;
        else
            if (n == 2)
                c=c-5;
            else
                if (n == 3)
                    return 0;

        printf("Atomic Number  Symbol  Name  Mass\n");
        for (int i=c; i<c+5; i++){
            printf("%d  %s  %s  %f\n", e[i].number, e[i].symbol, e[i].name, e[i].mass);
        }
        printf("\n");
        printf("    1. Next     2. Back     3. Exit\n");
    }
}