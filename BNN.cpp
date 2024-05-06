/*
1)
    Конструкторы 1, 2 и 3 можно реализовать в одном или двух конструкторах
2)
    16-ый ввод и вывод
3)
    сравнение БЧ:
    ==,
    !=,
    >,
    >=,
    <,
    <=
4)
    operator +,
    operator +=
5)
    operator -,
    operator -=
6)
    operator * (BASE)
    operator *,
    operator *=
7)
    operator / (BASE)
    operator % (BASE)
    10-ый ввод и вывод
8)
    operator /
    operator %
9)
    Тест
 */
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef unsigned short BASE;
#define BASE_SIZE (sizeof(BASE)*8)

class BN { // Объявление класса BN

private: // Секция приватных членов класса

    int maxLen; // Максимальная длина числа
    int *digits; // Указатель на массив цифр
    int len; // Длина числа

public: // Секция публичных членов класса

    BN (int len = 1, bool random = false) { // Обновление параметров конструктора

        maxLen = len;
        digits = new int[len];

        if (random) {
            for (int i = 0; i< len; i++) {
                digits[i] = rand() << 16 | rand();
            }
            while (digits[len - 1] == 0 && len > 1) {
                len--;
            }
        }else { // Если random равно false
            for (int i = 0; i < len; i++) {
                digits[i] = 0;
            }
            len = 1;
        }
        this->len = len; // Присваивание длины числа
    }

    BN (const BN &x) { // Определение конструктора копирования
        maxLen = x.maxLen; // Копирование максимальной длины числа
        len = x.len; // Копирование длины числа
        digits = new int[x.maxLen]; // Выделение памяти для хранения цифр числа копируемого объекта
        for (int i = 0; i < maxLen; i++) {
            digits[i] = x.digits[i]; // Копирование цифр числа
        }
    }

    ~BN() { // Деструктор класса
        delete[] digits; // Освобождение выделенной памяти для массива цифр
        digits = NULL; // Указатель на массив коэффициентов присваивается нулевому значению
        maxLen = 0;
    }

    // =
    BN &operator = (const BN &x) {
        if (this != &x) {
            delete[] digits;
            maxLen = x.maxLen;
            len = x.len;
            digits = new int[maxLen];
            for (int i = 0; i < maxLen; i++) {
                digits[i] = x.digits[i];
            }
        }
        return *this;
    }

    // ==
    bool operator == (const BN &x) {
        if (len != x.len) {
            return false;
        }
        for (int i = 0; i < len; i++) {
            if (digits[i] != x.digits[i]) {
                return false;
            }
        }
        return true;
    }

    // !=
    bool operator != (const BN &x) {
        if (len != x.len) {
            return true;
        }
        for (int i = 0; i < len; i++) {
            if (digits[i] != x.digits[i]) {
                return true;
            }
        }
        return false;
    }

    // <
    bool operator < (const BN &x){
        if (len < x.len) {
            return true;
        }
        if (len > x.len) {
            return false;
        }
        for (int i = len-1; i>-1; i--) {
            if (digits[i] > x.digits[i]){
                return false;
            }
            if (digits[i] < x.digits[i]) {
                return true;
            }
        }
        return false;
    }

    // >
    bool operator > (const BN &x){
        if (len > x.len) {
            return true;
        }
        if (len < x.len) {
            return false;
        }
        for (int i = len-1; i>-1; i--) {
            if (digits[i] < x.digits[i]) {
                return false;
            }
            if (digits[i] > x.digits[i]) {
                return true;
            }
        }
        return false;
    }


    // >=
    bool operator >= (const BN &x){
        if (len > x.len) {
            return true;
        }
        if(len < x.len) {
            return false;
        }
        for (int i = len-1; i>-1; i--) {
            if (digits[i] < x.digits[i]) {
                return false;
            }
            if (digits[i] > x.digits[i]) {
                return true;
            }
        }
        return true;
    }

    // <=
    bool operator <= (const BN &x){
        if (len < x.len) {
            return true;
        }
        else if (len > x.len) {
            return false;
        }
        for (int i = len-1; i>-1; i--) {
            if (digits[i] > x.digits[i]){
                return false;
            }
            else if (digits[i] < x.digits[i]){
                return true;
            }
        }
        return true;
    }

    // <<
    friend ostream &operator << (ostream &os, const BN &bi) {
        for (int i = bi.maxLen - 1; i >= 0; i--) {
            os << bi.digits[i] << " ";
        }
        return os;
    }
};


int main() {

    srand(time(nullptr));

    int len;
    cout << "Enter the length of the number: ";
    cin >> len;
    cout << endl;

    BN num1(len, false);
    BN num2(len, true);
    BN num3(len, true);

    cout << "num 1: " << num1 << endl;
    cout << "num 2: " << num2 << endl;
    cout << "num 3: " << num3 << endl;

    if (num1 < num2) {
        cout << "num1 < num2" << endl;
    } else {
        cout << "num1 >= num2" << endl;
    }

    if (num1 == num2) {
        cout << "num1 == num2" << endl;
    } else {
        cout << "num1 != num2" << endl;
    }

    return 0;

}