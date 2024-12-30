#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>

using namespace std;

vector<vector<int>> keyToMatrix(const string& key, int n) {
    if (key.size() != n * n) {
        throw runtime_error("Invalid key length: Must be exactly " + to_string(n * n) + " characters for matrix of size " + to_string(n) + "x" + to_string(n));
    }

    vector<vector<int>> matrix(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = static_cast<unsigned char>(key[i * n + j]); // Преобразование символа в код Unicode
        }
    }

    return matrix;
}

std::string getGoodKey(std::string key)
{
    int i = 2, n = key.length();
    while (i * i != n){

        if (n > i*i) i+=1;
        key += " ";
        n+=1;
        std::cout << i << "\n";
    }
    return key;
}
// Функция для вычисления обратного по модулю
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    throw runtime_error("Inverse does not exist");
}

// Функция для нахождения детерминанта матрицы
int determinant(vector<vector<int>> matrix, int mod) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0] + mod) % mod;
}

// Функция для нахождения обратной матрицы
vector<vector<int>> inverseMatrix(vector<vector<int>> keyMatrix, int mod) {
    int det = determinant(keyMatrix, mod);
    int detInv = modInverse(det, mod);

    vector<vector<int>> inverse = {
            {keyMatrix[1][1], -keyMatrix[0][1]},
            {-keyMatrix[1][0], keyMatrix[0][0]}
    };

    for (auto& row : inverse) {
        for (auto& elem : row) {
            elem = ((elem % mod) + mod) % mod; // Приведение к положительному модулю
            elem = (elem * detInv) % mod;
        }
    }
    return inverse;
}

// Функция для дешифрования текста
string hillDecrypt(string ciphertext, std::string key) {
    vector<vector<int>> keyMatrix = keyToMatrix(key, key.length());
    int n = keyMatrix.size();
    vector<vector<int>> inverseKeyMatrix = inverseMatrix(keyMatrix, 227);

    string plaintext = "";
    for (size_t i = 0; i < ciphertext.size(); i += n) {
        vector<int> chunk(n, 0);
        for (int j = 0; j < n && i + j < ciphertext.size(); j++) {
            chunk[j] = static_cast<unsigned char>(ciphertext[i + j]); // Unicode код символа
        }

        vector<int> decryptedChunk(n, 0);
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                decryptedChunk[row] += inverseKeyMatrix[row][col] * chunk[col];
            }
            decryptedChunk[row] = ((decryptedChunk[row] % 227) + 227) % 227; // Модуль 227
            plaintext += static_cast<char>(decryptedChunk[row]); // Интерпретация через Windows-1251
        }
    }
    return plaintext;
}
