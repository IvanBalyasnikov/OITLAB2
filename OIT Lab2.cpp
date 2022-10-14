#include <iostream>
#include <string>
#include <math.h>
#include <locale>
using namespace std;

char forChas(string str, string str1, int x) {
    int temp = 0;
    for (int i = 0; i < size(str1); i++) {
        if (i == x) {
            return str[i];
            temp++;
        }
    }
    if (temp == 0) {
        return '0';
    }
}

char subtractionForOne(char first, char second) {
    if (first == '1' && second == '1') {
        return '0';
    }
    if (first == '1' && second == '0') {
        return '1';
    }
    if (first == '0' && second == '1') {
        return 'e';
    }
}

string subtraction(string bin1, string bin2) {
    int flag = 0;
    string ifNull = "0";
    string result, temp, temp2, bin11, bin22;
    bin11 = bin1;
    bin22 = bin2;
    if (bin1 == bin2) {
        temp2 += '0';
    }
    if (stoi(bin1) < stoi(bin2)) {
        bin1 = bin22;
        bin2 = bin11;
        temp2 += '-';
    }

    int size1 = size(bin1);
    int size2 = size(bin2);
    int bin2Pos = size2 - 1;

    for (int bin1Pos = size1 - 1; bin1Pos >= 0; bin1Pos--) {
        char u = forChas(bin2, bin1, bin2Pos);
        if (subtractionForOne(bin1[bin1Pos], forChas(bin2, bin1, bin2Pos)) == 'e') {
            int n = 1;
            if (bin1[bin1Pos - 1] == '0') {
                while (bin1[bin1Pos - n] != '1') {
                    bin1[bin1Pos - n] = '1';
                    n++;
                }
                bin1[bin1Pos - n] = '0';
                temp += '1';
                bin2Pos--;
                continue;
            }
            if (bin1[bin1Pos - 1] == '1') {
                temp += '1';
                bin1[bin1Pos - 1] = '0';
            }
        }
        else {
            temp += subtractionForOne(bin1[bin1Pos], forChas(bin2, bin1, bin2Pos));
        }
        bin2Pos--;
    }
    for (int resultSize = size(temp); resultSize >= 0; resultSize--) {
        result += temp[resultSize];
    }
    int k = 0;
    temp.clear();
    for (int resultSize = 0; resultSize < size(result); resultSize++) {
        if (result[resultSize] == '1') {
            k = resultSize;
            break;
        }
    }
    for (int resultSize = k; resultSize < size(result); resultSize++) {
        temp2 += result[resultSize];
    }
    
    
    return temp2;
}

string ToTwo(int tenToTwo) {
    string twoToChasTemp, twoToChas;
    while (tenToTwo != 1) {
        if (tenToTwo % 2 == 0) {
            twoToChasTemp += "0";
        }
        else {
            twoToChasTemp += "1";
        }
        tenToTwo = tenToTwo / 2;
    }
    twoToChasTemp += "1";
    for (int pos = size(twoToChasTemp) - 1; pos >= 0; pos--) {
        twoToChas += twoToChasTemp[pos];
    }
    return twoToChas;
}

string toTwoForB(string tenToTwoStr) {
    int x = 200;
    string twoToChasTemp, twoToChas, twoToInt, twoToFloat;
    int tenToTwo;
    float forFloatTwo;
    int flagToСomma = 0;
    if (tenToTwoStr[0] == '-') {
        twoToChas += "-";
        tenToTwoStr.erase(0, 1);
    }
    for (int stringPos = 0; stringPos < size(tenToTwoStr); stringPos++) {
        if (tenToTwoStr[stringPos] == ',' || tenToTwoStr[stringPos] == '.') {
            flagToСomma = stringPos;
        }
    }
    for (int stringPos = 0; stringPos < flagToСomma; stringPos++) {
        twoToInt += tenToTwoStr;
    }

    twoToChas += ToTwo(stoi(twoToInt));

    for (int stringPos = flagToСomma + 1; stringPos < size(tenToTwoStr); stringPos++) {
        twoToFloat += tenToTwoStr[stringPos];
    }

    forFloatTwo = stof(twoToFloat);
    while (forFloatTwo > 1) {
        forFloatTwo = forFloatTwo / 10;
    }
    twoToFloat.clear();
    forFloatTwo = forFloatTwo * 2;
    for (int toComma = 0; toComma < x; toComma++) {
        if (forFloatTwo < 1) {
            twoToFloat += "0";
            forFloatTwo = forFloatTwo * 2;
        }
        else {
            twoToFloat += "1";
            forFloatTwo -= 1;
            forFloatTwo = forFloatTwo * 2;
        }
    }
    twoToChas += ".";
    int extraZero = 0;
    for (int twoToFloatPos = 0; twoToFloatPos < size(twoToFloat); twoToFloatPos++) {
        if (twoToFloat[twoToFloatPos] == '0' &&
            twoToFloat[twoToFloatPos + 1] == '0' &&
            twoToFloat[twoToFloatPos + 2] == '0' &&
            twoToFloat[twoToFloatPos + 3] == '0' &&
            twoToFloat[twoToFloatPos + 4] == '0' &&
            twoToFloat[twoToFloatPos + 5] == '0' &&
            twoToFloat[twoToFloatPos + 6] == '0' &&
            twoToFloat[twoToFloatPos + 7] == '0' &&
            twoToFloat[twoToFloatPos + 8] == '0' &&
            twoToFloat[twoToFloatPos + 9] == '0') {
            extraZero = twoToFloatPos;
            if (extraZero == 0) {
                extraZero = 10;
            }
            break;
        }
    }

    for (int twoToFloatPos = 0; twoToFloatPos < extraZero; twoToFloatPos++) {
        twoToChas += twoToFloat[twoToFloatPos];
    }
    return twoToChas;
}

string goToInternal(string tenToTwoStr, int bytes) {
    tenToTwoStr = toTwoForB(tenToTwoStr);
    string result;
    int bias, sizeMantis, commaPos;
    if (bytes == 4) {
        bias = 127;
        sizeMantis = 23;
    }
    else if (bytes == 8) {
        bias = 1023;
        sizeMantis = 52;
    }
    if (tenToTwoStr[0] == '-') {
        result += '1';
        tenToTwoStr.erase(0, 1);
    }
    else {
        result += '0';
    }
    result += ' ';
    for (int stringPos = 0; stringPos < size(tenToTwoStr); stringPos++) {
        if (tenToTwoStr[stringPos] == ',' || tenToTwoStr[stringPos] == '.') {
            commaPos = stringPos;
            break;
        }
    }
    tenToTwoStr.erase(commaPos, 1);
    tenToTwoStr.erase(0, 1);
    result += ToTwo((commaPos - 1) + bias);
    result += ' ';

    while (size(tenToTwoStr) < sizeMantis) {
        tenToTwoStr += '0';
    }

    for (int stringPos = 0; stringPos < sizeMantis; stringPos++) {
        result += tenToTwoStr[stringPos];
    }
    return result;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Здравствуйте, дорогой пользователь, добро пожаловать в мою программу." << endl;
    cout << "Выберите, пожалуйста, пункт из лабораторной работы, который нужно выполнить." << endl;
    while (1) {
        cout << "Напишите 1, если нужно выполнить задание под буквой А." << endl;
        cout << "Напишите 2, если нужно выполнить задание под буквой Б." << endl;
        cout << "Напишите 3, если нужно остановить работу программы." << endl;

        int tenToTwo, tenToTwo1, flag;
        int chas = 0;
        cin >> flag;
        if (flag == 1) {
            string bin1, bin2;
            cout << "Введите числа в десятичной системе счисления, которые нужно поделить в двоичной." << endl;
            cin >> tenToTwo >> tenToTwo1;
            bin1 = ToTwo(tenToTwo);
            bin2 = ToTwo(tenToTwo1);
            cout << "Ваши числа в двоичной системе счисления:" << endl;
            cout << bin1 << endl << bin2 << endl;
            while (stoi(bin1) > 0) {
                bin1 = subtraction(bin1, bin2);
                chas++;
            }

            cout << "Результат деления в двоичной системе счисления:" << endl;
            cout << ToTwo(chas) << endl << endl;
            continue;
        }
        else if (flag == 2) {
            string toTwo;
            int bytes;
            cout << "Пожалуйста, введите число, которое нужно представить:" << endl;
            cin >> toTwo;
            cout << "Теперь введите количество байт, которое должно занимать число:" << endl;
            cin >> bytes;
            cout << "Ваше число в двоичной системе:" << endl;
            cout << toTwoForB(toTwo) << endl;
            cout << "Ваше число вo внутреннем представлении с размером " << bytes << " байта:" << endl;
            cout << goToInternal(toTwo, bytes) << endl << endl;
            continue;
        }
        else if (flag == 3) {
            return 0;
        }
        else {
            cout << "Пожалуйста, введите либо цифру 1, либо цифру 2." << endl;
            cout << "Если необходиимо закрыть программу, напишите 3." << endl << endl;
        }
    }
}
