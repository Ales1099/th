#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void child_process();

int main() {

    pid_t pid;

    pid = fork();

    if(pid == -1){
        fprintf(stderr,"Cannot fork!\n");
        return(1);
    }

    else if(pid == 0){
        return(0);
    }

    pid = fork();

    if(pid == -1){
        fprintf(stderr,"Cannot fork!\n");
        return(1);
    }
    else if(pid == 0){
        return(0);
    }

    child_process();

    return 0;
}

void child_process() {

    FILE * file = fopen("../input.txt","r+");

    while(1){

        int i = 0;
        int err;
        err = fscanf(file, "%d\n", &i);

        if(err == EOF){
            break;
        }

        i *= 2;

        fprintf(file,"%d\n",i);

        sleep(2);

    }

    fclose(file);

}