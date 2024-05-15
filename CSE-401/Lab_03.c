#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// int main(){
//     printf("My Process Id : %d\n", (int) getpid());
//     exit(0);
// }

// int main(){
//     printf("My Process Id : %d\n", (int) getpid());
//     printf("My Parent Process Id : %d\n", (int) getppid());
//     exit(0);
// }

// int main(){
//     fork();
//     printf("Process ID: %d\n", getpid());
//     exit(0);
// }

// int main(){
//     printf("Program Execution start here.\n");

//     int r = fork();

//     printf(
//         "Process ID is %d, I am %s process\n",
//         getpid(), 
//         r==0 ? "child" : "parent"
//     );

//     exit(0);
// }

// int main(){
//     int pid;
//     switch (pid = fork()){
//        case 0:
//            printf("I am the child process: pid = %d\n", getpid());
//            break;
//        default:
//            printf("I am the parent process: pid = %d, child pid = %d\n", getpid(), pid);
//            break;
//        case -1:
//            perror("fork");
//            exit(1);
//     }

//     exit(0);
// }

// // execution of execve - eta "file path + commands as arguments + environment variables" parameter hisebe input ney
// int main(){
//     char *args[] = {"./p.out", 0};
//     char *env[] = {0};

//     printf("About to run demo.c\n");
//     execve("/mnt/d/University/LAB-2-2/CSE - 401/p.out", args, env);
    
//     printf("This line will not be executed\n");

//     perror("execve");
//     exit(1);
// }

// // execution of execlp - eta "file name + commands as arguments" parameter hisebe input ney ar path just "PATH" namer environment variable theke niye ney. Jeta amader input deya lage na.
// int main(){
//     printf("About to run ls\n");
//     execlp("ls", "ls", "-l", (char *)0);
//     perror("execlp");
//     exit(1);
// }

// // execution of execvp - works same as execlp.
// // The primary difference is in how they handle command-line arguments: execlp takes variable arguments directly, while execvp expects an array of pointers to command-line arguments. The choice between them depends on the convenience and flexibility you need for handling command-line arguments in your specific use case
// int main(){
//     char *args[] = {"ls", "-l", (char *)0};
//     printf("About to run ls\n");
//     execvp("ls", args);
//     perror("execvp");
//     exit(1);
// }

// Spawning a new program with fork + exec
void runit(){
    char *args[] = {"ls", "-l", (char *)0};
    printf("About to run ls\n");
    execvp("ls", args);
    perror("execvp");
    exit(1);
}

int main(){
    int pid;

    switch (pid = fork()){
        case 0:
            runit();
            break;
        default:
            sleep(5);
            printf("Parent is still here!\n");
            break;
        case -1:
            perror("fork");
            exit(1);
    }
    exit(0);
}