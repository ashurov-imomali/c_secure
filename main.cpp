#include"cesar.h"
#include "vertical.h"
#include "veginer.h"
#include <windows.h>
#include <fstream>
#include <map>
#include <vector>

std::string readFile(std::string fileName) {
    std::ifstream f(fileName);
    std::string line, full;
    while (std::getline(f, line )) full+=line;
    f.close();
    return full;
}

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

char** getMatrix(std::string key)
{
    std::map<char, int> alphabet;

    key = getUnique1(key);

    int row = 13, colum = 15;
    char** mrx = new char*[row];
    for (int i = 0; i < row; ++i)
    {
        mrx[i] = new char[colum];
    }
    int k  = 0, i = 0, j = 0;
    while (k < key.length())
    {
        alphabet[key[k]] = k;
        mrx[i][j++] = key[k++];
        i += j % colum == 0;
        j = j % colum;
    }
    // for (std::pair<char, int> c:alphabet) std::cout << c.first << "\t" << c.second << "\n";
    for (int l = 32; l < 256; ++l)
    {
        if (alphabet.find(char(l)) == alphabet.end())
        {
            std::cout << char(l);
            mrx[i][j++] = char(l);
            i += j % colum == 0;
            j = j % colum;
        }
    }
    for (int l = 0; l < row; l++)
    {
        for (int m = 0; m < colum; m++)
        {
            std::cout << mrx[l][m];
        }
        std::cout<<"\n";
    }
    // k = 0;
    // i = 0; j = 0;
    // while (k < key.length())
    // {
    //     std::cout << mrx[i][j];
    //     j++;
    //     k++;
    //     i += j % colum == 0;
    //     j = j % colum;
    // }
    // for (std::pair<int, char>c:alphabet)
    // {
    //
    // }
    return mrx;


}




int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string s[]{"answer","computer","department","display", "exercise", "informatic","information",
        "keyboard","language", "lesson", "mathematic", "mouse", "notebook", "program", "projector",
        "question", "structure", "student"};
    std::string enc = readFile("../vertical.txt");
    // std::cout << enc;
    // return 0;
    for (int i = 0; i < 18; i++)
    {
            // std::string decode = cesarDecode(enc,s[i]);
            // std::cout << "CesarDecode: "<< s[i] << "\n" << decode << "\n\n\n";
        // enc = readFile("../veginer.txt");
        // std::cout <<  "\nVeginer: " << s[i] << "\n";
        // std::cout << veginerDecode(enc, s[i]) << "\n\n";
        // enc = readFile("../vertical.txt");
        std::cout << "\n\n\n\nVertical: " << s[i] << "\n";
        std::cout << verticalDecode(enc, s[i]);
    }
}
