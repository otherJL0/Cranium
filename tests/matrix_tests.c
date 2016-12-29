#include "../src/matrix.c"
#include <stdio.h>

int main(){
    double** A_data = (double**)malloc(sizeof(double*) * 3);
    int i, j;
    for (i = 0; i < 3; i++){
        A_data[i] = (double*)malloc(sizeof(double) * 3);
        for (j = 0; j < 3; j++){
            A_data[i][j] = i + j;
        }
    }

    double** B_data = (double**)malloc(sizeof(double*) * 3);
    for (i = 0; i < 3; i++){
        B_data[i] = (double*)malloc(sizeof(double) * 4);
        for (j = 0; j < 4; j++){
            B_data[i][j] = i + j;
        }
    }

    // test creation
    Matrix* A = createMatrix(3, 3, A_data);
    Matrix* B = createMatrix(3, 4, B_data);

    // test addition
    Matrix* sum = add(A, A);
    assert(sum != NULL);
    assert(sum->rows == A->rows);
    assert(sum->cols == A->cols);
    assert(sum->data[0][0] == 0);
    assert(sum->data[2][2] == 8);

    // test multiplication
    Matrix* product = multiply(A, B);
    assert(product != NULL);
    assert(product->rows == A->rows);
    assert(product->cols == B->cols);
    assert(product->data[0][0] == 5);
    assert(product->data[2][3] == 38);

    // test hadamard
    Matrix* hadamardProduct = hadamard(A, A);
    assert(hadamardProduct->data[1][2] == A->data[1][2] * A->data[1][2]);

    // test copy
    Matrix* copied = copy(A);
    for (i = 0; i < A->rows; i++){
        for (j = 0; j < A->rows; j++){
            assert(copied->data[i][j] == A->data[i][j]);
        }
    }

    // test destroy
    destroyMatrix(sum);
    destroyMatrix(product);
    destroyMatrix(hadamardProduct);
    destroyMatrix(copied);

    return 0;
}