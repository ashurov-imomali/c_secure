#include <cmath>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <locale>
#include <map>
#include <regex>
#include <windows.h>

std::map<int, char> keyToCode;
std::map<char, int> codeToKey;


void createKeyToCode() {
    keyToCode[1] = 9;
    keyToCode[2] = 10;
    keyToCode[3] = 13;
    int j = 32;
    for (int i = 4; i < 228; ++i) {
        keyToCode[i] = j++;
    }

}

void createCodeToKey() {
    codeToKey[9] = 1;
    codeToKey[10] = 2;
    codeToKey[13] = 3;
    int j = 32;
    for (int i = 4; i < 228; ++i) {
        codeToKey[j++] = i;
    }
}



std::string modifyString(std::string key, int m) {
    int n = key.length();
    while (n%m != 0) {
        key += " ";
        n++;
    }
    return key;
}


int** getKeyMrx(std::string key, int n)
{
    int **a = new int*[n];
    for (int i = 0; i < n; ++i) {
        a[i] = new int[n];
    }
    key = modifyString(key, n*n);
    int k = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = codeToKey[key[k++]];
        }
    }
    return a;
}

int **createEncVectors(std::string txt, int cols) {
    int rows = txt.length() / cols + (txt.length() %3 != 0);
    txt = modifyString(txt, cols);
    int ** a = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        a[i] = new int[cols];
    }
    for (int i = 0,k = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j, k++)
        {
            int tmp = codeToKey[txt[k]];
            a[i][j] = tmp;
        }
    }
    return a;
}

int** createDecVectors(const std::string& txt, int cols) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    std::u32string utf32String = converter.from_bytes(txt);
    int rows = utf32String.length() / cols + (utf32String.length() % cols != 0);
    int** a = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        a[i] = new int[cols];
    }
    int i = 0, j = 0;
    for (char32_t c : utf32String) {
        int ab = static_cast<int>(c);
        // std::cout << "Unicode code: " << static_cast<int>(c) <<"\t" << a <<std::endl;
        a[i][j++] = ab;
        i += j%cols == 0;
        j = j % cols;
    }
    // for (int kn = 0; kn < rows; ++kn) {
    //     for (int sb = 0; sb < cols; ++sb) {
    //         std::cout << a[kn][sb] << " ";
    //     }
    //     std::cout << "\n";
    // }
    // for (int i = 0; i < rows; ++i) {
    //     for (int j = 0; j < cols; ++j) {
    //        a[i][j] = static_cast<int>(utf32String[k]);
    //     }
    // }
    return a;
}

// void PrintMrxI(int ** mrx,  int row, int col) {
//     for (int i = 0; i < row; ++i) {
//         for (int j = 0; j < col; ++j) {
//             std::cout << mrx[i][j] << " ";
//         }
//         std::cout << "\n";
//     }
// }
int **getDropedMrx(int **a, int row, int col, int n) {
    int **newA = new int *[n - 1];
    for (int j = 0; j < n; ++j) {
        newA[j] = new int[n - 1];
    }
    for (int i = 0, ni = 0; i < n; ++i) {
        if (i == row) continue;
        for (int j = 0, nj = 0; j < n; ++j) {
            if (j == col) continue;
            newA[ni][nj++] = a[i][j];
        }
        ni++;
    }
    return newA;
}

int determinant(int **a, int n) {
    if (n == 2) {
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
        res += std::pow(-1, i)*a[0][i] * determinant(getDropedMrx(a,0,i,n),n - 1);
    }
    return res;
}




int ** transportMrx(int **mrx, int n) {
    int ** na = new int *[n];
    for (int i = 0; i < n; ++i) {
        na[i] = new int[n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            na[i][j] = mrx[j][i];
        }
    }
    return na;
}


int mod(int n, int mod) {
    if (n >= 0) {
        return n % mod;
    }
    return mod + n % mod;
}


int **getMinors(int **mrx, int n){
    int **nMrx = new int *[n];
    for (int i = 0; i < n; ++i) {
        nMrx[i] = new int[n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int **na = getDropedMrx(mrx,i,j,n);
            int k = i+j;
            int determ = determinant(na, n-1);

            int res = pow(-1, k) * determ;
            nMrx[i][j] = res;
        }
    }

    return nMrx;

}



int **reverseMatrix(int **mrx, int n) {
    int ** minors = getMinors(mrx,n);
    int ** transpMrx = transportMrx(minors, n);
    return transpMrx;
 }


int *multiplyMrxtoVec(int **key, int *text, int n) {
    int *res = new int[n];
    for (int i = 0; i < n; ++i) {
        int tmp = 0;
        for (int j = 0; j < n; ++j) {
            tmp += key[i][j] * text[j];
        }
        res[i] = tmp;
    }
    return res;
}

int **multiplyKeyMrxToVectors(int **mrx, int **vectors, int rows, int cols) {
    int ** res = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        res[i] = new int[cols];
    }

    for (int i = 0; i < rows; ++i) {
        res[i] = multiplyMrxtoVec(mrx, vectors[i], cols);
    }
    return res;
}


std::string utf32CodeToString(int codePoint) {
    char32_t utf32Char = static_cast<char32_t>(codePoint);
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    return converter.to_bytes(utf32Char);
}

std::string decodeAlgebra(std::string s, std::string key) {
    createCodeToKey();
    createKeyToCode();
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>  convert;
    std::u32string u32txt = convert.from_bytes(s);
    int col = 3, rows = u32txt.length() / col + (u32txt.length() % col != 0);
    int ** mrx = getKeyMrx(key, col);
    int ** reverseMrx = reverseMatrix(mrx, col);
    int ** vectors = createDecVectors(s,col);
    int ** res = multiplyKeyMrxToVectors(reverseMrx, vectors, rows, col);
    int deter = determinant(mrx, col);
    std::string enc;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < col; ++j) {
            enc += keyToCode[res[i][j] / deter];
        }
    }
    return enc;
}

std::string encodeAlgebra(std::string s, std::string key) {
    int cols = 3, rows = s.length() / cols + (s.length() % cols != 0);
    int ** mrx = getKeyMrx(key, cols);
    int ** vectors = createEncVectors(s, cols);
    int ** res = multiplyKeyMrxToVectors(mrx, vectors, rows, cols);
    std::string enc;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            enc += utf32CodeToString(res[i][j]);
        }
    }
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    return enc;
}

// int main(){
//     createAlphaBet();
//     createBetaAl();
//     std::string words[] = {
//         "applied",
//         "client",
//         "computer",
//         "decrypt",
//         "display",
//         "encrypt",
//         "keyboard",
//         "matrix",
//         "memory",
//         "model",
//         "monitor",
//         "mouse",
//         "program",
//         "result",
//         "save",
//         "system",
//         "value"
//     };
//     std::string str = readFile("../input.txt"), key = "keyboard";
//         int ** keyMrx = getKeyMrx(key,3);
//         PrintMrxI(keyMrx,3,3);
//         int ** mrx = getReverseMrx(keyMrx, 3);
//         int determ = getDetermOfMrx(keyMrx, 3);
//         PrintMrxI(mrx, 3,3);
//         int ** vectors = createVectors(str, 3);
//         int ** res = multiplyMrxToVectors(mrx, vectors, 216, 3);
//         std::string sres;
//         for (int i = 0; i < 216; ++i) {
//             for (int s = 0; s < 3; ++s) {
//                 sres += alphaBet[getNumMod(res[i][s]/determ, 227)];
//             }
//         }
//         SetConsoleCP(1251);
//         SetConsoleOutputCP(1251);
//         std::cout << sres;
//     int ** vec = createSimpleVectors(sres, 3);
//     int ** resEnc = multiplyMrxToVectors(keyMrx, vec, 216,3);
//     std::string encRes;
//     for (int i = 0; i < 216; ++i) {
//         for (int j = 0; j < 3; ++j) {
//             encRes += utf32CodeToString( resEnc[i][j]);
//         }
//     }
//     SetConsoleCP(CP_UTF8);
//     SetConsoleOutputCP(CP_UTF8);
//     std::cout << "\n==================================================================\n";
//     std::cout << encRes;
// }