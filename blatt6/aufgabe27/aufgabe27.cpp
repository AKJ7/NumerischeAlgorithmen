//
// Created by hp on 16.05.19.
//

#include <iostream>
#include <string>
#include <utility>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstring>
#include <cassert>
#include <limits>
#include <algorithm>


/// @brief Compressed Row Storage handler
///
/// @class SparseMatrix
/// Check https://de.wikipedia.org/wiki/Compressed_Row_Storage
class SparseMatrix {
    int *i_rel{};
    int *j_rel{};
    double *rel;
    bool isInitialized;
    int dim;
    int nnz;
public:
    SparseMatrix() : rel{}, isInitialized{}, dim{}, nnz{} {}
    SparseMatrix(int size, int capacity) : SparseMatrix() { dim = size; }
    int initFromFile(const char *filePath) {
        return initFromFile(std::string(filePath));
    }
    int initFromFile(std::string &&filePath) {
        std::vector<int> rowA, colA;
        std::vector<double> valA;
        parseFile(filePath + "/row_A.txt", rowA);
        parseFile(filePath + "/val_A.txt", valA);
        parseFile(filePath + "/col_A.txt", colA);
        nnz = valA.size();
        isInitialized = true;
        j_rel = rowA.data();
        i_rel = colA.data();
        rel = valA.data();
        assert(valA.size() == colA.size());
        return nnz;
    }
    template<typename T>
    static inline void parseFile(const std::string &fileName, std::vector<T> &container) {
        static std::ifstream fileIn;
        static char buffer[512];
        fileIn.open(fileName);
        if (!fileIn.is_open()) throw std::invalid_argument(fileName + " could not be opened!");
        while (!fileIn.eof()) {
            fileIn.getline(buffer, 512);
            container.emplace_back(std::stod(buffer));
            if (fileIn.peek() == std::char_traits<char>::eof())
                break;
        }
        fileIn.close();
    }
    inline bool isInit() const noexcept { return isInitialized; }
    inline int notNull() const noexcept { return nnz; }
    // Richtige Daten??? rowA richtig??

    //int sum(SparseMatrix &MB, SparseMatrix &MC) {
    //}
    //void print()
    //{
    //    for (int i = 0; i < dim; i++)
    //    {
    //    }
    //}
    ~SparseMatrix()
    {
        auto deleter = [](int* ptr) -> void {if (ptr) delete(ptr);};
        deleter(j_rel);
        deleter(i_rel);
    }
};


class SparseMatrix2 final {
public:
    std::vector<double> val;
    std::vector<int> colInd, rowPtr;
    std::pair<int, int> size;
public:
    SparseMatrix2(int numRow, int numCol) : size{numRow, numCol} { rowPtr.resize(numCol + 1); }

    void parse(double matrix[], size_t numbElements) {
        rowPtr.resize(0);
        rowPtr.clear();
        colInd.resize(0);
        val.resize(0);
        int row{}, currentRow{std::numeric_limits<int>::max()}, notNull{}, counter;
        for (int i = 0; i < numbElements; i++) {
            if (matrix[i] != 0) {
                val.emplace_back(matrix[i]);
                colInd.emplace_back(i % size.second);
                if (row != currentRow) {
                    currentRow = row;
                    rowPtr.emplace_back(notNull);
                }
                notNull++;
            }
            row = static_cast<int>(i / size.second);
        }
        rowPtr.emplace_back(notNull);
    }

    void print() {
        static int available{};
        static int someCounter{};
        someCounter = 0;
        available = 0;
        auto pr = [](double a) -> void { std::cout << a << ' '; };
        for (int i = 0; i < size.first; i++) {
            available = rowPtr[i + 1] - rowPtr[i];
            for (int j = 0; j < size.second; j++) {
                if (available && j == colInd[someCounter]) {
                    pr(val[someCounter]);
                    someCounter++;
                    available--;
                } else {
                    pr(0);
                }
            }
            std::cout << '\n';
        }
    }

    SparseMatrix2 operator+(SparseMatrix2 &rhs)
    {
        assert(rhs.size.second == size.second && rhs.size.first == size.first);
        double matrix[rhs.size.first * rhs.size.second];
        static int row{};
        for (int counter = 0; counter < sizeof(matrix)/8; counter++)
        {
            row = static_cast<int>(counter / size.second);
            matrix[counter] = fetch(row, counter % size.second) + rhs.fetch(row, counter % size.second);
        }
        SparseMatrix2 sparseMatrix2(rhs.size.first, rhs.size.second);
        sparseMatrix2.parse(matrix, sizeof(matrix)/8);
        return sparseMatrix2;
    }

    void transp()
    {
        double matrix[size.first * size.second];
        double mmatrix[size.first * size.second];
        int row = 0;
        int count = 0;
        auto matrixTransp = [&](double* mat)
        {
            for (int j = 1; j <= size.second; j++)
            {
                for (int i = 1; i <= size.first; i++)
                {
                    mmatrix[count] = *access(matrix, 4, 5, i, j);
                    count++;
                }
            }
        };
        for (int counter = 0; counter < size.first * size.second; counter++)
        {
            row = static_cast<int>(counter / size.second);
            matrix[counter] = fetch(row, counter % size.second);
        }

        matrixTransp(matrix);
        std::swap(size.first, size.second);
        parse(mmatrix, size.first * size.second);
    }

    static double* access(double* container, int m, int n, int x, int y)
    {
        for (int a = 1; a <= m; a++)
        {
            for (int b = 1; b <= n; b++) {
                if (x == a && y == b)
                {
                    return container;
                }
                container++;
            }
        }
        return nullptr;
    }

    void parseFromFile(std::string &&path) {

    }

    double fetch(int m, int n)
    {
        int available = 0;
        int someCounter = 0;
        for (int i = 0; i < size.first; i++) {
            available = rowPtr[i + 1] - rowPtr[i];
            for (int j = 0; j < size.second; j++) {
                if (available && j == colInd[someCounter]) {
                    if (i == m && j == n){
                        return val[someCounter];
                    }
                    someCounter++;
                    available--;

                } else {
                    if (i == m && j == n){
                        return 0;
                    }
                }
            }
        }
        return 0;
    }
    ~SparseMatrix2() = default;
};



int main()
{
    //SparseMatrix sparseMatrix(10, 20);
    //sparseMatrix.initFromFile("../../blatt6/assets");
    //sparseMatrix.print();

    // Beispielmatrix aus Wikipedia

    SparseMatrix2 sparseMatrix2(4, 5);
    double matrix[] = {10, 0, 0, 12, 0, 0, 0, 11, 0, 13, 0, 16, 0, 0, 0, 0, 0, 11, 0, 13};

    sparseMatrix2.parse(matrix, sizeof(matrix) / 8);
    sparseMatrix2.print();
    std::cout << '\n';

    SparseMatrix2 sparseMatrix3(4, 5);
    sparseMatrix3.parse(matrix, sizeof(matrix) / 8);

    auto B = sparseMatrix2 + sparseMatrix3;
    B.print();

    B.transp();
    std::cout << '\n';
    B.print();

    return EXIT_SUCCESS;
}

