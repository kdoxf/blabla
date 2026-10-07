#include <iostream>
#include <cstddef>
#include <new>

void freeMat(int **m, size_t r) {
    for (size_t i = 0; i < r; ++i) {
        delete[] m[i];
    }
    delete[] m;

}

int ** createMat(size_t r, size_t c) {
    int ** m = nullptr;
    try {
        m = new int*[r];
        for (size_t i = 0; i < r; ++i) {
            m[i] = new int[c];
        }
    }
    catch (const std::bad_alloc& e) {
        freeMat(m, r);
        return nullptr;
    }
    return m;
}

bool readMat(int ** m, size_t r, size_t c) {
    for (size_t i = 0; i < r; ++i) {
        for (size_t j = 0; j < c; ++j) {
            if (!(std::cin >> m[i][j])) {
                return false;
            }

        }
    }
    return true;
}

int ** Trans(int ** m, size_t r, size_t c) {
    int ** t = createMat(c, r);
    if (t == nullptr) {
        return nullptr;
    }
    for (size_t i = 0; i < r; ++ i) {
        for (size_t j = 0; j < c; ++j) {
            t[j][i] = m[i][j];
        }
    }
    return t;
}

void printMat(int **m, size_t r, size_t c) {
    for (size_t i = 0; i < r; ++i) {
        for (size_t j = 0; j < c; ++j) {
            std::cout << m[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    size_t r = 0, c = 0;
    std::cout << "Ввод размера";
    std::cin >> r >> c;

    if (!std::cin) {
        std::cerr << "ошибка\n";
        return 1;
    }

    if (r == 0 || c ==0) {
        return 0;
    }

    int ** m = createMat(r, c);
    if (m == nullptr) {
        std::cerr << "ошибка\n";
        return 2;
    }

    std::cout << "Ввод элементов\n";

    if (!readMat(m, r, c)) {
        std::cerr << "ошибка\n";
        return 1;
    }

    int ** t = Trans(m, r, c);
    if (t == nullptr) {
        std::cerr << "ошибка\n";
        freeMat(m, r);
        return 2;
    }

    printMat(t, c, r);

    freeMat(t, c);
    freeMat(m, r);
    return 0;
}