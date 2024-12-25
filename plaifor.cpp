#include<iostream>
#include<map>

std::string getUnique1(std::string s)
{
    std::string unique;
    std::map<char, int> check;
    for (char c:s)
    {
        if (check.find(c) == check.end())
        {
            unique += c;
            check[c] = 1;
        }
    }
    return unique;
}

int row = 14, colum = 16;
char** mrx = new char*[row];

std::map<char, int*> getMatrix(std::string key)
{
    key = getUnique1(key);
    std::map<char, int> alphabet;
    std::map<char, int*> mp;

    for (int i = 0; i < row; ++i)
    {
        mrx[i] = new char[colum];
    }

    int k  = 0, i = 0, j = 0;
    while (k < key.length())
    {
        alphabet[key[k]] = k;
        mp[key[k]] = new int[2]{i,j};
        mrx[i][j++] = key[k++];
        i += j % colum == 0;
        j = j % colum;
    }
    for (int l = 32; l < 256; ++l)
    {
        if (alphabet.find(char(l)) == alphabet.end()) {
            // std::cout <<  l << char(l);
            mp[char(l)] = new int[2]{i,j};
            mrx[i][j++] = char(l);
            i += j % colum == 0;
            j = j % colum;
        }
    }
    for (int l = 0; l < row; l++) {
        for (int m = 0; m < colum; m++) {
            std::cout << mrx[l][m] << " ";
        }
        std::cout << "\n";
    }
    return mp;
}

int* getFromMrx(int* a, int* b) {
    int rowA = a[0], colA = a[1], rowB = b[0], colB = b[1];
    int *indexes = new int[4];
    if (rowA == rowB) {
        // std::cout  << rowA ,colA % 16  << rowA, colB % 16;
        indexes[0] = rowA; indexes[1] = (colA+1) % 16; indexes[2] = rowA; indexes[3] = (colB+1) % 16;
        // std::cout << indexes;
        return indexes;
    }
    if (colA == colB) {
        // std::cout << rowA % 14, colA << rowB%14, colB;
        indexes[0] = (rowA+1) % 14; indexes[1] = colA; indexes[2] = (rowB+1)%14; indexes[3] = colB;
        // std::cout << indexes;
        return indexes;
    }
    // std::cout << rowA, colB, rowB, colA;
    indexes[0] = rowA; indexes[1] = colB; indexes[2] = rowB; indexes[3]= colA;
    return indexes;
}


std::string getCleanStr(std::string s) {
    if (s.length() % 2 == 0) return s;
    return s +=" ";
}
int *getDecFromMatrix(int *a, int *b) {
    int rowA = a[0], colA = a[1], rowB = b[0], colB = b[1];
    if (rowA == rowB) {
        return new int[4]{rowA, (colA - 1 + colum)%colum, rowB, (colB - 1 + colum)%colum};
        std::cout << "rowA" << rowA << "rowB" << rowB << "\n";
    }
    if (colA == colB) {
        return new int[4]{(rowA - 1 + row) % row, colA, (rowB - 1 + row) % row, colB};
    }
    // indexes[0] = rowA; indexes[1] = colB; indexes[2] = rowB; indexes[3]= colA;
    return new int[4]{rowA, colB, rowB, colA};
}



std::string  plaiforEncode(std::string key, std::string s) {
    std::map<char, int*> mp= getMatrix(key);
    // std::cout <<  mrx[4][12] << "\n";
    s = getCleanStr(s);
    std::string enc;
    for (int i = 0; i < s.length(); i+=2) {
        int * indexes = getFromMrx(mp[s[i]], mp[s[i+1]]);
        // std::cout << indexes[0] << " " << indexes[1] << " " << indexes[2] << " " << indexes[3] << "\n";
        enc += mrx[indexes[0]][indexes[1]];
        enc += mrx[indexes[2]][indexes[3]];
    }
    return enc;
}




std::string plaiforDecode(std::string key, std::string s) {
    std::map<char, int*> mp = getMatrix(key);
    std::string dec;
    for (int i = 0; i < s.length(); i+=2) {
        int * indxes = getDecFromMatrix(mp[s[i]], mp[s[i+1]]);
        std::cout << indxes[0] << " " << indxes[1] << " " << indxes[2] << " " << indxes[3] << "\n";
        dec += mrx[indxes[0]][indxes[1]];
        dec += mrx[indxes[2]][indxes[3]];
    }
    return dec;
}

