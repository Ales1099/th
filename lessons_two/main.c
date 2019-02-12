#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void child_process();

static int count_of_process = 0;

int main() {

    pid_t pid;
    int status;

    if(count_of_process == 0){
        ++count_of_process;
        pid = fork();
    } else{
        return(1);
    }

    if(pid == -1){
        fprintf(stderr,"Cannot fork!\n");
        return(2);
    }

    if(pid == 0){
        execlp("../lessons_two","../lessons_two",NULL);
        fprintf(stderr,"Cannot exec!!!\n");
        return(3);
    }

    child_process();

    if(waitpid(pid,&status,0) <= 0){
        fprintf(stderr,"Cannot waitpid!!!\n");
        return(4);
    }

    if(!WIFEXITED(status)){
        fprintf(stderr,"Cannot finished abnormally, terminating...\n");
        return(5);
    }

    if(WEXITSTATUS(status)){
        fprintf(stderr,"Child procees return non-zero argument, terminating...\n");
        return(6);
    }

    return 0;
}

void child_process(){
    fprintf(stderr,"Hello from child process of %d!!!\n",count_of_process);
    sleep(5);
    return;
}