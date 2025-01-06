#include <cmath>
#include <future>
#include <iostream>
#include <windows.h>
#include <map>

std::map<int, char> alphaBet;
std::map<char, int> betaAl;


void PrintMrxI(int ** mrx,  int row, int col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            std::cout << mrx[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void PrintMrx(double ** mrx,  int row, int col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            std::cout << mrx[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void createAlphaBet() {
    int s = 'A';
    for (int i = 0; i < 26; ++i) {
        alphaBet[i] = s++;
    }
    return;
    alphaBet[1] = 9;
    alphaBet[2] = 10;
    alphaBet[3] = 13;
    int j = 32;
    for (int i = 4; i < 228; ++i) {
        alphaBet[i] = j++;
    }
}
void createBetaAl() {
    // betaAl[9] = 1;
    // betaAl[10] = 2;
    // betaAl[13] = 3;
    // int j = 32;
    // for (int i = 4; i < 228; ++i) {
    //     betaAl[j++] = i;
    // }
    int s = 'A';
    // betaAl['A'] = 0;
    // std::cout << betaAl['A'];
    for (int i = 0; i < 26; ++i) {
        betaAl[s++] = i;
    }
    // for (int i = 0; i < 26; ++i)
        // std::cout << betaAl[i];
    // std::cout << "\n";
}

std::string getGoodString(std::string key, int m) {
    int n = key.length();
    while (n%m != 0) {
        key += " ";
        n++;
    }
    return key;
}

int** getMrx(std::string key, int n)
{
    int **a = new int*[n];
    for (int i = 0; i < n; ++i) {
        a[i] = new int[n];
    }
    key = getGoodString(key, n*n);
    int k = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = betaAl[key[k++]];
        }
    }
    return a;
}


int ** createVectors(std::string txt, int cols)
{
    txt = getGoodString(txt, cols);
    int rows = txt.length() / cols + txt.length()%cols;
    int ** a = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        a[i] = new int[cols];
    }
    for (int i = 0,k = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j, k++)
        {
            a[i][j] = betaAl[txt[k]];
        }
    }
    return a;
}


int *multiPly(int **key, int *text, int n) {
    int *res = new int[n];
    for (int i = 0; i < n; ++i) {
        int tmp = 0;
        for (int j = 0; j < n; ++j) {
            tmp += key[i][j] * text[j];
        }
        res[i] = tmp % betaAl.size();
    }
    return res;
}


int **multiplyMrxToVectors(int **mrx, int **vectors, int rows, int cols) {
    int ** res = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        res[i] = new int[cols];
    }

    for (int i = 0; i < rows; ++i) {
        res[i] = multiPly(mrx, vectors[i], cols);
    }
    return res;
}


std::string GetStrFromMrx(int **mrx, int rows, int cols) {
    std::string str;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            str += alphaBet[mrx[i][j]];
        }
    }
    return str;
}
std::string GetStrDecFromMrx(int **mrx, int rows, int cols) {
    std::string str;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            str += betaAl[mrx[i][j]];
        }
    }

    return str;
}

std::string hillEncode(std::string text, std::string key) {
    createAlphaBet();
    createBetaAl();
    int cols = 3, rows = text.length() / cols + text.length() % cols;
    int ** mrx = getMrx(key, cols);
    int ** vectors = createVectors(text, cols);
    int ** resMrx = multiplyMrxToVectors(mrx, vectors, rows, cols);
    return GetStrFromMrx(resMrx, rows, cols);
}

int **getNewA(int **a, int row, int col, int n) {
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

int getDetermOfMrx(int **a, int n) {
    if (n == 2) {
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
        res += pow(-1, i)*a[0][i] * getDetermOfMrx(getNewA(a,0,i,n),n - 1);
    }
    return res;
}




int ** getTranspMrx(int **mrx, int n) {
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


int **getMrxMinors(int **mrx, int n){
    int **nMrx = new int *[n];
    for (int i = 0; i < n; ++i) {
        nMrx[i] = new int[n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int **na = getNewA(mrx,i,j,n);
            int k = i+j;
            int determ = getDetermOfMrx(na, n-1);
            nMrx[i][j] = determ;
        }
    }

    return nMrx;

}

int **multiPlyMrxtoNum(int **mrx, int n, int num) {
    std::cout << num  << "\n";
    int **nMrx = new int *[n];
    for (int i = 0; i < n; ++i) {
        nMrx[i] = new int[n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            nMrx[i][j] = (mrx[i][j] * num) % betaAl.size();
        }
    }
    return nMrx;
}

int **getReverseMrx(int **mrx, int n) {
    PrintMrxI(mrx, n, n);
    int determ = getDetermOfMrx(mrx, n) % betaAl.size();
    int ** minors = getMrxMinors(mrx,n);
    PrintMrxI(minors, n, n);
    int ** transpMrx = getTranspMrx(minors, n);
    return multiPlyMrxtoNum(transpMrx,n,1);
}



std::string decodeHill(std::string txt, std::string key)
{
    int col = 3;
    int** vectors = createVectors(txt, col);
    int** mrx = getMrx(key, col);
    int **reverse = getReverseMrx(mrx, col);
    int row = txt.length() / col + txt.length()%col;
    int ** result = multiplyMrxToVectors(reverse, vectors, row, col);
    return GetStrDecFromMrx(result, row, col);
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    createBetaAl();
    return 0;
    // createAlphaBet();
    // int mapped = betaAl['V'];
    // std::cout << mapped << "\n";
    // return 0;
    std::string encode = hillEncode("ACT", "GYBNQKURP");
    std::cout << encode << "\n";
    decodeHill(encode, "GYBNQKURP");
}
