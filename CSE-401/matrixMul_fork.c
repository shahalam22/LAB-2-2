#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
    // int r1, r2, c1, c2;
    // printf("Enter row and column of matrix 1 -");
    // scanf("%d %d", &r1, &c1);
    // printf("Enter row and column of matrix 2 -");
    // scanf("%d %d", &r2, &c2);

    // printf("%d %d %d %d", r1, c1, r2, c2);

    // int mat1[r1][c1];
    // int mat2[r2][c2];
    
    // printf("Enter values of matrix 1 -");
    // for(int i=0; i<r1; i++){
    //     for(int j=0; j<c1; j++){
    //         scanf("%d", &mat1[r1][c1]);
    //     }
    // }

    // printf("Enter values of matrix 2 -");
    // for(int i=0; i<r2; i++){
    //     for(int j=0; j<c2; j++){
    //         scanf("%d", &mat2[r2][c2]);
    //     }
    // }

    int mat1[3][3] = {
            {1,2,3},
            {4,5,6},
            {7,8,9},
        };

    int mat2[3][3] = {
            {9,8,7},
            {6,5,4},
            {3,2,1},
        };

    int ans[3][3];

    for(int i=0; i<3; i++){
        int f = fork();
        if(f==0){
            for(int j=0; j<3; j++){
                ans[i][j] = 0;
                for(int k=0; k<3; k++){
                    ans[i][j] += (mat1[i][k]*mat2[k][j]);
                }
            }
            for(int j=0; j<3; j++){
                printf("%d ", ans[i][j]);
            }
            printf("\n");
            exit(0);
        }
    }
}