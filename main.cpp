#include <algorithm>
#include <complex>
#include <iostream>
#include <map>
#include <windows.h>

using namespace std;


string getUnique(string s)
{
    string unique;
    map<char, int> check;
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

string sort(string s)
{
    for (int i = s.length()-1; i >= 0; i--)
    {
        int maxInd = i;
        char max = s[i];
        for (int j = 0; j < i; j++)
        {
            if (s[j] > max)
            {
                max = s[j];
                maxInd = j;
            }
        }
        swap(s[i], s[maxInd]);
    }
    return s;
}

string getMatrix(string text, string key)
{
    int kl = key.length(), tl = text.length();
    int rows = tl/kl +(tl%kl != 0), columns = kl;
    string matrix[rows][columns];
    int k = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (k >= tl)
            {
                matrix[i][j] += char(11);
                continue;
            }
            matrix[i][j] += text[k++];
        }
    }
    string sKey = sort(key), res;
    for (char c:sKey)
    {
        for (int j = 0; j < rows; j++)
        {
            res += matrix[j][key.find(c)];
        }
    }
    return res;
}

map<int, int> sortIn(int *s, int n)
{
    map<int, int> mp;
    for (int i = n-1; i >= 0; i--)
    {
        int maxInd = i, max = s[i];
        for (int j = 0; j < i; j++)
        {
            if (s[j] > max)
            {
                max = s[j];
                maxInd = j;
            }
        }
        mp[s[maxInd]] = i;
        swap(s[i], s[maxInd]);
    }
    return mp;
}


string cleanString(string s)
{
    string ns;
    for (char c:s)
    {
        if (c == char(11)) continue;
        ns += c;
    }
    return ns;
}


string verticalEncode(string s, string key)
{
    key = getUnique(key);
    int kl = key.length(), tl = s.length();
    int rows = tl/kl +(tl%kl != 0), columns = kl;
    string matrix[rows][columns];
    string sKey = sort(key);
    int k = 0;
    for (char c:sKey)
    {
        for (int j = 0; j < rows; j++)
        {
            matrix[j][key.find(c)] = s[k++];
        }
    }
    string res;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            res += matrix[i][j];
        }
    }
    return cleanString(res);
}


int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string s = "”пфс ку юеллеасвееытвн«е€во афйснуе афрс  о автлод,кнспхилвасцитыикруаринв€агасща е ыеетцоц,тнисцсзвеод.пн авмсбтннл се  и€мсерсюро пиамадаимппнни нсооинн  ,мд€иисдр ончжкнь тб.бии и ежзиизфхустапетиооа ешвоалд жеиивеоикчќеп»гнрунйлхкоизи-л,отнеп урррскмрс  прраихиннсс,оции ыа,  нма-соеео,ниус  ти€веваа наны   рприцкрнхчйоипе иудтиоувнта ра« еелаааыестзоатсррсемв  нои о  ам-м,нпнказ ис фоарь нбех  €нтм   онлйоонмыйопиноокюосн,рих«р  йнсжеме:тоиннмул€аарыееиасо,,йсаеонрсрбет   нз ииреып ы о)сиееапрбиснлоьрсолрреныынрркййордтннон и гиишоишмеатжнати(лиа е ноотт ,ин их, идоев уйсбв ы ат гаоодотк,ньинцулм хн.ф»ктлбвсо топсклоепдхбпнннеха ооке нье";
    string encoded = getMatrix(s, "јшурмалаевич");
     verticalEncode("123", "јшурмалаевич");
    return 0;


    string str = "gwestafcxb";
    auto pairs = sort(str);
    // for (pair<int, int>c:pairs)
    // {
        // cout << char(c.first) << " " << c.second << "\n";
    // }

    // return 0;
    // int a[10]{3,5,2,63,55,62,654,72,323,143};
    // auto pairs = sortIn(a, 10);
    // for (int i = 0; i < 10; i++) cout << sort_in[i] <<" ";

    return 0;

    getMatrix("my very good text", "imomali");
    return 0;


    map<char, int> mp;
    mp['a'] = 1;
    cout << mp.find('a')->first;
    bool s1 =  mp.find('b') == mp.end();
    cout << s1;
    return 0;

    for (int i = 0; i < 256; ++i)
    {
        cout << char(i) << " ";
    }

}