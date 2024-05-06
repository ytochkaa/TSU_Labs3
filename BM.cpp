// если передача не по ссылке, тогда срабатывает конструктор копрования, а нам надо просто взять значение
// для этого используем ссылку

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

class String {

    char *str;
    int len;

public:

    // Конструктор по умолчанию
    String(int l = 0) {
        str = new char[l + 1];
        len = l;
        str[0] = '\0';
    }

    // Конструктор для преобразования строки в объект String
    String(const char *x) {
        len = strlen(x);
        str = new char[len + 1];
        strcpy(str, x);
    }

    // Конструктор копирования
    String(const String &x) {
        len = x.len;
        str = new char[len + 1];
        strcpy(str, x.str);
    }

    // Деструктор
    ~String(){
        delete[] str;
    }

    // Функция возвращает длину строки
    int Len();

    // Перегрузка операторов
    String &operator = (const String&);
    char &operator [](int);
    bool operator == (const String&);
    bool operator != (const String&);
    String operator + (const String&);//+ для конкатенации строк
    String operator += (const String&);//+= для конкатенации строк и присваивания
    friend istream &operator >> (istream &inp, String &x);
    friend ostream &operator << (ostream &out, String &x);
    int BMSearch(String&);
};

// Функция возвращает длину строки
int String::Len() {
    return len;
}

// Перегрузка оператора присваивания
String &String::operator = (const String &x) {
    if (this != &x) {
        delete[] str;
        len = x.len;
        str = new char[len + 1];
        strcpy(str, x.str);
    }
    return *this;
}

// Перегрузка оператора []
char &String::operator [] (int x) {
    if (x < 0 || x > len) {
        cout << "Error: index is out of bounds";
        exit(1);
    }
    return str[x];
}

// Перегрузка оператора равенства
bool String::operator == (const String &x) {
    return strcmp(str, x.str) == 0;
}

bool String::operator != (const String &x) {
    return strcmp(str, x.str) != 0;
}

String String::operator + (const String &x) {

    int newLen = len + x.len;
    char *newStr = new char[newLen + 1];

    strcpy(newStr, str); // копирование текущей строки в новую строку
    strcat(newStr, x.str); // добавление строки x в конец новой строки

    // Возвращаем новый объект String, а не изменяем текущий объект
    String result(newStr);
    delete[] newStr;
    return result;
}

String String::operator += (const String &x) {

    int newLen = len + x.len;
    char *newStr = new char[newLen + 1];

    strcpy(newStr, str);
    strcat(newStr, x.str);

    delete[] str;
    str = newStr; // присваивание новой строки текущей строке
    len = newLen; // обновление длины строки

    return *this;
}

istream &operator >> (istream &inp, String &x) {

    const int massSize = 1000;
    char mass[massSize];

    inp.getline(mass, massSize);

    x.len = strlen(mass);

    delete[] x.str;
    x.str = new char[x.len + 1];
    strcpy(x.str, mass);

    return inp;
}

ostream &operator << (ostream &out, String &x) {
    out << x.str;
    return out;
}

int String::BMSearch(String &substring) {// подстрока

    int substringLen = substring.len;

    int text = len; // содержимое this
    int helper[256]; // массив кодов всех символов

    /*Заполнение массива символами подстроки*/
    fill_n(helper, 256, substringLen);

    for (int i = 0; i < substringLen - 1; i++){
        helper[substring.str[i]] = substringLen - 1 - i;
    }

    int i = substringLen - 1; // i в основном тексте, там где ищем
    int j = substringLen - 1; // j в подстроке, то что ищем

    // из схем на лекции
    while (i < text && j >= 0) { // пока не конец текста, пока не дошли до начала подстроки
        int k = i;
        j = substringLen - 1; // с конца подстроки
        while (j >= 0) { // пока не гранца подстроки, ищем первые не совпадающий символ
            if (str[k] != substring.str[j]) {
                i += helper[str[i]];
                j = substringLen - 1;
                break;
            }
            j--;
            k--;
        }
    }


    if (j >= 0) {
        return -1;
    } else {
        return i + 1 - substringLen;
    }

}

int main() {

    String s1, s2, s3;

    cout << "enter the string s1: ";
    cin >> s1; // Ввод строки
    cout << endl;

    cout << "enter a substring b: ";
    cin >> s2; // Ввод подстроки
    cout << endl;


    cout << "String: " << s1 << "\n" << "Substring: " << s2 << endl;
    cout << "Length of s1: " << s1.Len() << "\n" << "Length of s2: " << s2.Len() << endl;

    cout << "match at symbol number: " << s1.BMSearch(s2) << "\n";

    if (s1 == s2) {
        cout << "s1 == s2" << endl;
    } else {
        cout << "s1 != s3" << endl;
    }

    s3 = s1 + s2;
    cout << "s1 + s2: " << s3 << endl;

    s1 += s2;
    cout << "s3 += s2: " << s3 << endl;

    return 0;
}