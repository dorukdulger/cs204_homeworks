#include "SparseMatrix.h"

int main(){
    // reads the matrix stored in m1.txt
    SparseMatrix lhs("m5.txt");
    // reads the matrix stored in m2.txt
    SparseMatrix rhs("m6.txt");
    // Stores in the SparseMatrix "result" the result of the following operation
    // lhs * rhs
    SparseMatrix result = lhs.mat_mul(rhs);
    cout << result;
    return 0;
}
