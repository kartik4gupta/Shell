//mkdir command
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **args){
int chk=0;
  int chk_2=0;
  int chk_3=0;
    if(argc==3){
        chdir("/");
        chdir(*(args+2));
        char *direc = *(args+1);
        mkdir(direc,0777);
    }
    else if(argc==4){
        if(strcmp("-v",*(args+1))==0){
          chk_2=1;
            chdir("/");
            chdir(*(args+3));
            char *direc = *(args+2);
            int flag = mkdir(direc,0777);
            if (flag==0) {
                printf("Directory has been created\n");
            }
            else {
                printf("Unable to create Directory\n");
            }
        }
          
        else if(strcmp("-p",*(args+1))==0){
          chk=1;
            chdir("/");
            chdir(*(args+3));
            char *direcPath = *(args+2);
            char *currDirec = strtok(direcPath,"/");
            while(currDirec!=NULL){
                mkdir(currDirec,0777);
                chdir(currDirec);
                currDirec = strtok(NULL,"/");
            }
        }
        else{
          chk_3=1;
            printf("Please enter a valid Command\n");
        }
    }
  // printf("%d %d %d ",chk,chk_2,chk_3);
    exit(0);
}