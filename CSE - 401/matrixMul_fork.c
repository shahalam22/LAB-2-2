
// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <unistd.h>

// void multiply_row(long long int matrix1[][10], long long int matrix2[][10], long long int result[][10], int row, int col) {
//     for (int i = 0; i < col; i++) {
//         long long int product = 0;
//         for (int j = 0; j < col; j++) {
//             if (matrix1[row][j] < 0 || matrix2[j][i] < 0) {
//                 product -= matrix1[row][j] * matrix2[j][i];  // Handle negative numbers separately
//             } else {
//                 product += matrix1[row][j] * matrix2[j][i];
//             }
//         }
//         result[row][i] = product;
//     }
// }

// int main() {
//     int m, n, p, q;

//     printf("Enter dimensions of matrix 1: ");
//     scanf("%d %d", &m, &n);
//     printf("Enter dimensions of matrix 2: ");
//     scanf("%d %d", &p, &q);

//     if (n != p) {
//         printf("Matrices cannot be multiplied!\n");
//         return 1;
//     }

//     long long int matrix1[10][10], matrix2[10][10], result[10][10] = {
//         {0,0,0,0,0,0,0,0,0,0},
//         {0,0,0,0,0,0,0,0,0,0},
//         {0,0,0,0,0,0,0,0,0,0},
//         {0,0,0,0,0,0,0,0,0,0},
//         {0,0,0,0,0,0,0,0,0,0},
//         {0,0,0,0,0,0,0,0,0,0},
//         {0,0,0,0,0,0,0,0,0,0},
//         {0,0,0,0,0,0,0,0,0,0},
//         {0,0,0,0,0,0,0,0,0,0},
//         {0,0,0,0,0,0,0,0,0,0},
//     };

//     // Input matrices
//     printf("Enter elements of matrix 1:\n");
//     for (int i = 0; i < m; i++) {
//         for (int j = 0; j < n; j++) {
//             scanf("%lld", &matrix1[i][j]); // Use %lld for long long int
//         }
//     }
//     printf("Enter elements of matrix 2:\n");
//     for (int i = 0; i < p; i++) {
//         for (int j = 0; j < q; j++) {
//             scanf("%lld", &matrix2[i][j]); // Use %lld for long long int
//         }
//     }

//     // Perform multiplication using fork for each row
//     for (int i = 0; i < m; i++) {
//         pid_t pid = fork();

//         if (pid < 0) {
//             // Fork failed
//             printf("Fork failed!\n");
//             return 1;
//         } else if (pid == 0) {
//             // Child process
//             multiply_row(matrix1, matrix2, result, i, q);
//             exit(0);  // Child process exits
//         } else {
//             // Parent process
//             wait(NULL);  // Wait for child process to finish
//         }
//     }

//     // Print the result matrix
//     printf("\nResultant matrix:\n");
//     for (int i = 0; i < m; i++) {
//         for (int j = 0; j < q; j++) {
//             printf("%lld ", result[i][j]);
//         }
//         printf("\n");
//     }

//     return 0;
// }



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
        }else{
            wait(NULL);
        }
    }
}