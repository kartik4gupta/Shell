//cat command
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char **args){
  int flag=0;
    if(argc==3) {
        int check_1=0;
        int check_2=0;
        // int check_3=0;
        size_t length = 0;
        chdir("/");
        FILE *f_ptr;
        chdir(*(args+2));
        char *ln = NULL;
        if ((f_ptr = fopen(*(args + 1), "r")) == NULL) {
            printf("No such File or Directory found.\n");
            check_1=1;
            // Program will exit if file pointer returns NULL value.
            exit(1);
        }

        // reads text until newline is encountered
        while (getline(&ln, &length, f_ptr) != -1) {
            printf("%s", ln);
        }
        check_2=1;
        fclose(f_ptr);
    }
    else if(argc==4){
        if(strcmp(*(args+1),"-n")==0){
            chdir("/");
            int check_3=0;
            chdir(*(args+3));
            char *ln = NULL;
            FILE *f_ptr;
            size_t length = 0;
            if ((f_ptr = fopen(*(args + 2), "r")) == NULL) {
                printf("No such file or directory\n");
                check_3=1;
                // Program will exit if file pointer returns NULL value.
                exit(1);
            }

            // reads text until newline is encountered
            int count = 1;
            while (getline(&ln, &length, f_ptr) != -1) {
                count++;
                printf("%d %s", count, ln);
            }
            fclose(f_ptr);
        }
        else if(strcmp("-e",*(args+1))==0){
            chdir("/");
            int chk_1=0;
            chdir(*(args+3));
            char *ln = NULL;
            FILE *f_ptr;
            size_t length = 0;
            if ((f_ptr = fopen(*(args + 2), "r")) == NULL) {
                printf("No such file or directory\n");
                chk_1++;
                // Program exits if file pointer returns NULL.
                exit(1);
            }

            // reads text until newline is encountered
            while (getline(&ln, &length, f_ptr) != -1) {
                printf("%s$", ln);
                
            }
            fclose(f_ptr);

        }
        else{
            flag=-1;
            printf("Please enter a valid Command.\n");
        }
    }
    exit(0);
}
