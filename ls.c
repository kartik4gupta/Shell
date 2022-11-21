#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

//ls
int main(int argc, char **args) {
    // printf("reached");
  int chk_1=0;
  int chk_2=0;
  int chk_3=0;
  
    if(argc == 2) {
        chdir("/");
        chdir(*(args+1));
        struct dirent *Ent;
        DIR *dir = opendir(".");

        if (dir == NULL) {
            printf("Directory does not exist.\n");
        }

        Ent = readdir(dir);
        while (Ent != NULL) {
            printf("%s\t", Ent->d_name);
            Ent = readdir(dir);
        }
      printf("\n");
        closedir(dir);
    }
    if(argc == 3){
        if(strcmp("-Q",*(args+1))==0){
            chdir("/");
            chdir(*(args+2));
            struct dirent *Ent;
            DIR *dir = opendir(".");

            if (dir == NULL) {
                printf("Directory does not exist.\n");
            }

            Ent = readdir(dir);
            while (Ent != NULL) {
                printf("\"%s\"\t\t", Ent->d_name);
                Ent = readdir(dir);
            }
            closedir(dir);
            printf("\n");
        }//print the index number of each file
        else if(strcmp("-i",*(args+1))==0||strcmp("--inode",*(args+1))==0){
            chdir("/");
            chdir(*(args+2));
            struct dirent *Ent;
            DIR *dir = opendir(".");
        
            if (dir == NULL) {
                printf("Directory does not exist.\n");
            }

            Ent = readdir(dir);
            while (Ent != NULL) {
                printf("%lu %s\t\t", Ent->d_ino, Ent->d_name);
                Ent = readdir(dir);
            }
          printf("\n");
            closedir(dir);
            
        }
        else{
            printf("Please enter valid Command.\n");
        }
    }
    exit(0);
}
