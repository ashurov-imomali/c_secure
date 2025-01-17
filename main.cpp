#include"cesar.h"
#include "plaifor.h"
#include "vertical.h"
#include "veginer.h"
#include "hill.h"
#include "algebra.h"
#include "keys.h"
#include <windows.h>
#include <fstream>
#include <map>
#include <functional>


std::string getClearString(std::string s) {
    //     Л±s -> сис
    // ћ+а -> ема
    // НOь -> дан
    // Ь≈< -> адм
    std::map<std::string, std::string> mp{{"RvA","ез "},{"}Ту", "» т"},{"F,Ї", "ерн"},{"Л±s","сис"}, {"ћ+а","ема"}, {"НOь","дан"}, {"Ь≈<", "адм"}};
    for (std::pair<std::string, std::string> p:mp) {
        while (s.find(p.first,0) != std::string::npos) {
            s.replace(s.find(p.first), 3, p.second);
        }
    }
    return s;
}



std::string readFile(std::string fileName) {
    std::ifstream f(fileName);
    if (!f) {
        std::cerr << "couln't open file";
    }
    std::string line, full;
    while (std::getline(f, line )) full+=line+"\n";
    full = full.substr(0, full.length() -1);
    f.close();
    return full;
}

std::map<int, std::function<std::string(std::string, std::string)>> getFuncMaps() {
    std::map<int, std::function<std::string(std::string,std::string)>> mp;
    mp[0] = cesarDecode;
    mp[1] = veginerDecode;
    mp[2] = verticalDecode;
    mp[3] = plaiforDecode;
    mp[4] = decodeHill;
    mp[5] = decodeAlgebra;
    return mp;
}

std::map<int, std::function<std::string(std::string, std::string)>> getFuncEncMaps() {
    std::map<int, std::function<std::string(std::string,std::string)>> mp;
    mp[0] = cesarEncode;
    mp[1] = veginerEncode;
    mp[2] = verticalEncode;
    mp[3] = plaiforEncode;
    mp[4] = hillEncode;
    mp[5] = encodeAlgebra;
    return mp;
}


void writeToFile(std::string stream, std::string fileName) {
    std::ofstream f(fileName);
    f << stream;
    f.close();
}

std::map<int, std::string>getMethNames() {
    std::map<int, std::string> mp;
    mp[0] = "Cesar";
    mp[1] = "Veginer";
    mp[2] = "Vertical";
    mp[3] = "Plaifor";
    mp[4] = "Hill";
    mp[5] = "Algebra";
    return mp;
}


int PrintMethods() {
    std::cout << "1-Cesar\n2-Veginer\n3-Vertical\n4-Plaifor\n5-Hill\n6-Algebra\n";
    int check;
    std::cin >> check;
    return check;
}


void PrintEncode(int meth, std::string txt, std::string key) {
    std::map<int, std::string> meth_names = getMethNames();
    auto pairs = getFuncEncMaps();
    std::cout << meth_names[meth]  << "\t" << key << "\n" << pairs[meth](txt, key) << "\n–езультат сохранЄн в input.txt\n";
    writeToFile(pairs[meth](txt, key), "../input.txt");
}

void PrintDecode(int meth, std::string txt, std::string key) {
    std::map<int, std::string> meth_names = getMethNames();
    auto pairs = getFuncMaps();
    std::cout << meth_names[meth]  << "\t" << key << "\n" << getClearString(pairs[meth](txt, key)) << "\n–езультат сохранЄн в output.txt\n";
    writeToFile(getClearString(pairs[meth](txt, key)), "../output.txt");

}

std::string ChooseFile() {
    std::cout << "ChooseFile:\n1-input.txt\n2-output.txt\n";
    int s;
    std::cin >> s;
    switch (s) {
        case 1: return "../input.txt";
        case 2: return "../output.txt";
    }
    return "";
}


void Interface() {
    std::cout << "1-Encode\n2-Decode\n3-Exit\n";
    int check, meth;
    std::cin >> check;
    std::string file = ChooseFile();
    std::string key = readFile("../key.txt");
    std::string s = readFile(file);
    meth = PrintMethods();
    switch (check) {
        case 1:
            PrintEncode(meth-1, s,key);
            Interface();
            return;
        case 2:
            PrintDecode(meth - 1, s, key);
            Interface();
    }
}


int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Interface();
    // std::string vertical_encode = verticalEncode(imomali, test);
    // std::cout << verticalDecode(vertical_encode, test);
    // return 0;
    std::map<int, std::function<std::string(std::string, std::string)>> pairs = getFuncMaps();
    std::map<int, std::function<std::string(std::string, std::string)>> pairsEnc = getFuncEncMaps();
    std::map<int, std::string> mp;
    mp[0] = "Cesar";
    mp[1] = "Veginer";
    mp[2] = "Vertical";
    mp[3] = "Plaifor";
    mp[4] = "Hill";
    std::vector<std::string> keys = getKeys();
    std::string stream;
    std::string file = readFile("../input.txt");
    std::cout << decodeAlgebra(file, "keyboard");
    return 0;
    for (std::string key: keys) {
    // std::string key = "structure";
    for (int i = 0; i < 5; ++i) {
            // std::string dec = pairs[i](file, key);
            std::cout << key << "\t" << mp[i] << "\n" << pairs[i](file, key) << "\n\n";
            // std::string enc = pairsEnc[i](dec, key);
            // std::cout << key << "\t" << mp[i] << "\n" << pairs[i](enc, key) << "\n\n";
        }
    }
}
