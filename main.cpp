#include"cesar.h"
#include "vertical.h"
#include "veginer.h"
#include <windows.h>
#include <fstream>

std::string readFile(std::string fileName) {
    std::ifstream f(fileName);
    std::string line, full;
    while (std::getline(f, line )) full+=line;
    f.close();
    return full;
}


int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string enc = readFile("../cesar.txt");
    std::string decode = cesarDecode(enc,"Ахлиллоев");
    std::cout << "CesarDecode: " << decode << "\n\n\n";
    enc = readFile("../veginer.txt");
    std::cout <<  "\nVeginer: ";
    std::cout << veginerDecode(enc, "Рустамзода");
    enc = readFile("../vertical.txt");
    std::cout << "\n\n\n\nVertical: ";
    std::cout << verticalDecode(enc, "Ашурмалаевич");
}
