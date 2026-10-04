#include <iostream>
#include <new>
int** newmat(int m, int n) {
    int** mat = new (std::nothrow) int*[m];
    if (mat == nullptr) return nullptr;

    for (int i = 0; i < m; ++i) {
        mat[i] = new (std::nothrow) int[n];
        if (mat[i] == nullptr) {
            for (int j = 0; j < i; ++i ) {
                delete[] mat[j];
            } 
            delete[] mat;
            return nullptr;
        }
    }
    return mat;
}

void frmatr(int** mat, int m) {
    if (mat == nullptr) return;
    for (int i = 0; i < m; ++i) {
        delete[] mat[i];
    }
    delete[] mat;
}

int main() {
    int m, n;
    std::cout<<"Ввод размера";
    if (!(std::cin>>m>>n)) {
        return 1;
    }
    if (m <= 0 || n <= 0) {
        return 1;
    }

    int** matrix = newmat(m, n);
    if (matrix == nullptr) {
        return 2;
    }

    std::cout <<"элементы матрицы: (" << m << "x" << n << "):\n";
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(std::cin >> matrix[i][j])) {
                frmatr( matrix, m);
                return 1;
            }
        } 
    }

    std::cout <<"(" << n << "x" << m <<"):\n";
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m; ++i) {
            std::cout <<matrix[i][j];
            if (i < m - 1) std::cout <<" ";
        }
        std::cout << "\n";
    }

    frmatr(matrix, m);
    return 0;
}