#include <iostream>

using namespace std;

class DiagonalMatrix
{
    private:
        int *tmp;
        int n;
    
    public:
        DiagonalMatrix(int n)
        {
            tmp = new int[n];
            this->n = n;
        }

        void set(int row, int col, int value);
        int get(int row, int col);
        void display();

        ~DiagonalMatrix()
        {
            delete []tmp;
        }
};

void DiagonalMatrix::set(int row, int col, int value)
{
    if (row == col) {
        tmp[row - 1] = value;
    }
};

int DiagonalMatrix::get(int row, int col)
{
    if (row == col) {
        return tmp[row - 1];
    }

    return 0;
};

void DiagonalMatrix::display()
{
    int i, j;

    for (i = 0; i < n; i++) {

        for (j = 0; j < n; j++) {

            if (i == j) {
                cout << tmp[i] << " ";
            }
            else {
                cout << "0 ";
            }
        }

        cout << endl;
    }
};

/**
 * Main.
 */
int main () {

    // class rapresent the diagonal matrix
    DiagonalMatrix matrix(4);

    matrix.set(1, 1, 5);
    matrix.set(2, 2, 8);
    matrix.set(3, 3, 9);
    matrix.set(4, 4, 12);

    matrix.display();
}