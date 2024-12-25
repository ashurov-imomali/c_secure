#include"cesar.h"
#include "plaifor.h"
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


int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // std::string enc1 = plaiforEncode("key","imomali");
    // std::cout << enc1 << "\n";
    // std::cout << plaiforDecode("key",enc1);
    std::string enc2 = readFile("../plaifor.txt");
    std::cout << plaiforDecode("Ôàððóõøî", enc2);
    // getMatrix("key");
    return 0;
    // std::string test = "abagkerkl";
    // std::string str = sort1(test);
    // std::cout << str;
    // return 0;
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
