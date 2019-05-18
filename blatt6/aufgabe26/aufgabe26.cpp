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

/// @brief Compressed Row Storage handler
///
/// @class SparseMatrix
/// Check https://de.wikipedia.org/wiki/Compressed_Row_Storage
class SparseMatrix
{
    int *i_rel{};
    int *j_rel{};
    double* rel;
    bool isInitialized;
    int dim;
    int nnz;
public:
    SparseMatrix() : rel{}, isInitialized{}, dim{}, nnz{} {}
    SparseMatrix(int size, int capacity) : SparseMatrix() { }
    int initFromFile(const char* filePath)
    {
        return initFromFile(std::string(filePath));
    }
    int initFromFile(std::string&& filePath)
    {
        std::vector<int> rowA, colA;
        std::vector<double> valA;
        parseFile(filePath + "/row_A.txt", rowA);
        parseFile(filePath + "/val_A.txt", valA);
        parseFile(filePath + "/col_A.txt", colA);
        nnz = valA.size();
        isInitialized = true;

        j_rel = rowA.data();
        i_rel = colA.data();
        assert(rowA.size() == valA.size());
        return nnz;
    }
    template <typename T>
    static inline void parseFile(const std::string& fileName, std::vector<T>& container)
    {
        static std::ifstream fileIn;
        static char buffer[512];
        fileIn.open(fileName);
        if (!fileIn.is_open()) throw std::invalid_argument(fileName + " could not be opened!");
        while (!fileIn.eof())
        {
            fileIn.getline(buffer, 512);
            container.emplace_back(std::stod(buffer));
            if (fileIn.peek() == std::char_traits<char>::eof())
                break;
        }
        fileIn.close();
    }


    inline bool isInit() const  noexcept { return isInitialized; }
    inline int notNull() const noexcept { return nnz; }
    ~SparseMatrix()
    {
        auto deleter = [](int* ptr) -> void {if (ptr) delete(ptr);};
        deleter(j_rel);
        deleter(i_rel);
    }
};



int main()
{
    SparseMatrix sparseMatrix;
    std::clog << "Nicht-null Elemente: " << sparseMatrix.initFromFile("../../blatt6/assets") << '\n';

    return EXIT_SUCCESS;
}

