#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    int n = 10;

    int r = fork();
    
    if(r==0){
        int oddSum = 0;
        for(int i=0; i<=n; i++){
            if(i%2==1){
                oddSum += i;
            }
        }
        printf("Odd numbers sum upto %d is %d.\n", n, oddSum);
    }else{
        int evenSum = 0;
        for(int i=0; i<=n; i++){
            if(i%2==0){
                evenSum += i;
            }
        }
        printf("even numbers sum upto %d is %d.\n", n, evenSum);
    }
}