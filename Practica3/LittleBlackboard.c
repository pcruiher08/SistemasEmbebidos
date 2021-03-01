#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

int main(int argc, char *argv[]){

    int cuantosNombres = 0;
    cuantosNombres = atoi(argv[2]);
    char nombre[100];
    char id[100];
    bool addMore = true;
    char lectura;

    FILE *f = fopen("Datalog.txt", "w");
    
    if(f == NULL){
        fprintf(stderr,"Error opening file!\n");
        exit(1);
    }

    while(cuantosNombres-- && addMore){
        printf("Enter Name:\n[give name][Enter]\n");
        scanf("%s",nombre);
        printf("Enter ID:\n[give ID][Enter]\n");
        scanf("%s",id);
        fprintf(f, "%s %s\n", nombre, id);
        printf("Do you wish to add more [Y/n]:\n[give n][Enter]\n");
        scanf("%s", &lectura);
        if(lectura != 'Y'){
            addMore = false;
        }

    }

    printf("Students information stored in Datalog.txt\n");


    fclose(f);

    return 0;
}