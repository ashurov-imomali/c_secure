#include <iostream>
#include <fstream>
#include <cmath>
#include <locale>
#include <codecvt>
#include <windows.h>

std::string readFile(std::string fileName){
    std::ifstream file(fileName);
    std::string res, line;
    while (std::getline(file,line)){
        res += line+ "\n";
    }
    res = res.substr(0, res.length() -1);
    file.close();
    return res;
}

bool isPrime(int n){
    for (int i = 2; i < int(std::pow(n,0.5) + 1); ++i) {
        if (n%i == 0) return false;
    }
    return true;
}

int modPow(int a, int d, int n){
    int res = 1;
    for (int i = 1; i <= d; ++i) {
        res *= a;
        res %= n;
    }
    return res;
}


long long modExp(long long base, long long exponent, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exponent >>= 1;
    }
    return result;
}

bool checkA(int a){
    int startCirilic = 1040;
    int endCirilic = 1103;
    if ((a <= endCirilic && a >= startCirilic) || a == 32){
        return true;
    }
    return false;
}

void writeToFile(std::string stream, std::string fileName) {
    std::ofstream f(fileName);
    f << stream;
    f.close();
}

std::string Decode(std::string fileName, int p, int q, int d, std::string fileToWrite){
    std::string utf8str = readFile(fileName);
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    std::u32string file = convert.from_bytes(utf8str);
    std::u32string res32;
    res32.reserve(file.size());
    for (int i = 0; i < file.length(); ++i) {
        auto codePoint = modExp(file[i], d, p*q);
        res32.push_back(static_cast<char32_t>(codePoint));
    }

    std::string utf8res = convert.to_bytes(res32);
    writeToFile(utf8res, fileToWrite);
    return utf8res;
}


std::string Encode(const std::string& fileName, int p, int q, int e, std::string fileToWrite) {
    std::string utf8Input = readFile(fileName);
    if (utf8Input.empty()) {
        return {};
    }

    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    std::u32string u32Input = convert.from_bytes(utf8Input);

    long long n = static_cast<long long>(p) * q;

    std::u32string u32Output;
    u32Output.reserve(u32Input.size());

    for (char32_t codePoint : u32Input) {
        long long m = static_cast<long long>(codePoint);
        long long c = modExp(m, e, n);
        u32Output.push_back(static_cast<char32_t>(c));
    }

    std::string encryptedUtf8 = convert.to_bytes(u32Output);
    writeToFile(encryptedUtf8, fileToWrite);
    return encryptedUtf8;
}

long long extendedEuclid(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = extendedEuclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

long long modInverse(long long a, long long m) {
    long long x, y;
    long long gcd = extendedEuclid(a, m, x, y);
    if (gcd != 1) {
        return -1;
    }
    return (x % m + m) % m;
}

long long findPublicExponent(long long p, long long q, long long d) {
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    long long e = modInverse(d, phi);
    return e;
}



void Interface()
{
    std::cout << "1.Encode\n2.Decode\n3.Exit\n";
    int choose;
    std::cin >> choose;
    switch (choose)
    {
    case 1:
        std::cout << "Choose file\n1.input.txt\n2.output.txt\n";
        int nc;
        std::cin >> nc;
        if (nc == 1)
        {
            std::cout << "P Q D (73 103 941):";
            int p, q, d;
            std::cin >> p >> q >> d;
            std::cout << Encode("../input.txt", p, q,d, "../output.txt") << "\nSave to output.txt\n\n";
        }else
        {
                std::cout << "P Q D (73 103 941):";
                int p, q, d;
                std::cin >> p >> q >> d;
                std::cout << Encode("../output.txt", p, q,d, "../input.txt") << "\nSave to input.txt\n\n";
        }
        Interface();
    case 2:
        std::cout << "Choose file\n1.input.txt\n2.output.txt\n";
        int ncc;
        std::cin >> ncc;
        if (ncc == 1)
        {
            std::cout << "P Q D (73 103 941):";
            int p, q, d;
            std::cin >> p >> q >> d;
            std::cout << Decode("../input.txt", p, q,d, "../output.txt") << "\nSave to output.txt\n\n";
        }else
        {
            std::cout << "P Q D (73 103 941):";
            int p, q, d;
            std::cin >> p >> q >> d;
            std::cout << Decode("../output.txt", p, q,d, "../input.txt") << "\nSave to input.txt\n\n";
        }
        Interface();
    default:
            Interface();
    }
}


int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    Interface();
    int p = 73, q = 103, d = 941;

    // std::cout << Decode("../input.txt", p,q,d);
    return 0;
    // std::cout << Decode("../input.txt", 73, 103, 941) << "\n\n";
    // int e = findPublicExponent(p,q,d);
    // std::cout << Encode("../output.txt", p, q, e) << "\n\n";
    // std::cout << Decode("../input1.txt",p,q,d);
    // return 0;
    // std::string fileName = "../input.txt";
    // std::string u32txt = readFile(fileName);
    // std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>  convert1;
    // std::u32string file = convert1.from_bytes(u32txt);
    // int k = 0, counter = 0;
    // int ps[100], ds[100], qs[100];
    // for (int p = 11; p < 101; p+=2) {
    //     if (!isPrime(p)) continue;
    //     for (int q = 101; q < 1000; q+=2) {
    //         if (!isPrime(q)) continue;
    //         for (int d = 10; d < p*q+1; ++d) {
    //             if (checkA(modExp(file[k],d,p*q)) && checkA(modExp(file[k+1],d,p*q)) && checkA(modExp(file[k+2],d,p*q))){
    //                 std::cout << "P: " << p << " Q: " << q << " D: " << d << "\n\n";
    //                 ps[counter] = p;
    //                 qs[counter] = q;
    //                 ds[counter++] = d;
    //             }
    //         }
    //     }
    // }
    // for (int j = 0; j < counter; ++j) {
    //     std::u32string res32;
    //     res32.reserve(file.size());
    //     for (int i = 0; i < file.length(); ++i) {
    //         auto codePoint = modExp(file[i], ds[j], ps[j]*qs[j]);
    //         res32.push_back(static_cast<char32_t>(codePoint));
    //     }
    //     std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    //     std::string utf8res = convert.to_bytes(res32);
    //     SetConsoleOutputCP(CP_UTF8);
    //     SetConsoleCP(CP_UTF8);
    //     std::cout << "p: " << ps[j] << " q: " << qs[j] << " d: " << ds[j] << "\n" << utf8res << "\n\n";
    // }


}