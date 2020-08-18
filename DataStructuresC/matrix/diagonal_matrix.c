#include <stdio.h>

typedef struct intMatrix
{
    int array[255];
    int n;
} intMatrix;

void matrixSet(intMatrix *tmp, int row, int col, int value)
{
    if (row == col) {
        tmp->array[row - 1] = value;
    }
}

int matrixGet(intMatrix *tmp, int row, int col)
{
    if (row == col) {
        return tmp->array[row - 1];
    }

    return 0;
}

void matrixDisplay(intMatrix *tmp)
{
    int i, j;

    for (i = 0; i < tmp->n; i++) {

        for (j = 0; j < tmp->n; j++) {

            if (i == j) {
                printf("%d ", tmp->array[i]);
            }
            else {
                printf("0 ");
            }
        }

        printf("\n");
    }
}

/**
 * Main.
 */
int main () {

    // array rapresent the diagonal matrix
    intMatrix matrix;
    matrix.n = 4;

    matrixSet(&matrix, 1, 1, 5);
    matrixSet(&matrix, 2, 2, 8);
    matrixSet(&matrix, 3, 3, 9);
    matrixSet(&matrix, 4, 4, 12);

    matrixDisplay(&matrix);

}