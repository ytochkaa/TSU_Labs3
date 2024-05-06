#include <iostream> // Подключаем библиотеку для ввода-вывода через стандартные потоки.
#include <fstream> // Подключаем библиотеку для работы с файлами.
#include <vector> // Подключаем библиотеку для использования векторов.
#include <map> // Подключаем библиотеку для использования ассоциативных массивов (словарей).
#include <list> // Подключаем библиотеку для использования списков.

using namespace std; // Используем пространство имен std.

struct Range { // Определяем структуру Range.
    char s; // Поле для символа.
    int numb; // Поле для количества символов.
    int lb; // Поле для нижней границы.
    int rb; // Поле для верхней границы.
};

struct Sort { // Определяем структуру Sort для сравнения объектов Range.
    bool operator() (Range l, Range r) { // Перегрузка оператора () для сравнения Range.
        return l.numb > r.numb; // Сравниваем по количеству символов (убывающий порядок).
    }
};

double encode(ifstream& f, ofstream& g){ // Функция кодирования, принимает входящий и исходящий потоки файлов.
    int count=0; // Переменная для общего количества символов.
    map <char, int> m; // Ассоциативный массив для подсчета количества каждого символа.
    map <char, int> ::iterator ii; // Итератор для работы с ассоциативным массивом.
    list<Range> L; // Список объектов структуры Range.

    // Считываем символы из файла и увеличиваем счетчики символов.
    while(!f.eof()) {
        char c=f.get();
        m[c]++;
        count++;
    }

    // Заполняем список L объектами Range из ассоциативного массива m.
    for(ii=m.begin(); ii!=m.end(); ii++) {
        Range p;
        p.s=ii->first;
        p.numb=ii->second;
        L.push_back(p);
    }

    // Сортируем список L по убыванию количества символов.
    L.sort(Sort());

    // Инициализируем нижнюю и верхнюю границы для первого элемента списка.
    L.begin()->rb=L.begin()->numb;
    L.begin()->lb=0;

    // Вычисляем границы для остальных элементов списка.
    list<Range>::iterator it=L.begin(), i2;
    i2=it;
    it++;
    for(; it!=L.end(); it++) {
        it->lb=i2->rb;
        it->rb=it->lb+it->numb;
        i2++;
    }

    // Вычисляем длину закодированных данных.
    int ik=0;
    for (ii = m.begin(); ii != m.end(); ii++) {
        if (ii->second != 0) ik += 40;
    }

    // Записываем длину закодированных данных в исходящий файл.
    g.write((char*)(&ik), sizeof(ik));

    // Записываем символы и их количества в исходящий файл.
    for (int k=0; k<256; k++) {
        if (m[char(k)]>0) {
            char c=char(k);
            g.write((char*)(&c), sizeof(c));
            g.write((char*)(&m[char(k)]), sizeof(m[char(k)]));
        }
    }

    // Подготовка к адаптивному арифметическому кодированию.
    f.clear();
    f.seekg(0);
    int l=0, h=65535, i=0, delitel=L.back().rb;
    int F_q=(h+1)/4, Half=F_q*2, T_q=F_q*3, bits_to_follow=0;
    char tx=0;
    count=0;

    // Здесь начинается обработка данных для адаптивного арифметического кодирования.
    // Не хватает завершающих инструкций для корректного выполнения данной части кода.
    // Необходимо дописать соответствующий код для корректной работы функции encode.

    while(!f.eof()) { // Цикл выполняется, пока не достигнут конец файла
        char c=f.get(); i++; // Читаем символ из файла и увеличиваем счетчик i
        for(it=L.begin(); it!=L.end(); it++) { // Цикл по всем элементам в списке L
            if(c==it->s) break; // Если символ c равен символу в текущем элементе списка, выходим из цикла
        }
        if(c!=it->s) { // Если символ c не равен символу в текущем элементе списка
            cout<<"Error!"<<endl; // Выводим сообщение об ошибке
            break; // Завершаем выполнение цикла
        }
        int l2=l; // Запоминаем предыдущее значение переменной l
        l=l+it->lb*(h-l+1)/delitel; // Вычисляем новое значение l
        h=l2+it->rb*(h-l2+1)/delitel-1; // Вычисляем новое значение h
        for(;;) { // Бесконечный цикл
            if(h<Half) { // Если h меньше половины диапазона
                count++; // Увеличиваем переменную count
                if(count==8) { // Если count равно 8
                    count = 0; // Обнуляем count
                    g << tx; // Записываем tx в поток вывода
                    tx = 0; // Обнуляем tx
                }
                for(; bits_to_follow>0; bits_to_follow--) { // Цикл, выполняющийся bits_to_follow раз
                    tx=tx | (1<<(7-count)); // Устанавливаем бит в tx
                    count++; // Увеличиваем count
                    if(count==8) { // Если count равно 8
                        count = 0; // Обнуляем count
                        g << tx; // Записываем tx в поток вывода
                        tx = 0; // Обнуляем tx
                    }
                }
            }
            else if(l>=Half) { // Иначе, если l больше или равно половине диапазона
                tx=tx | (1<<(7-count)); // Устанавливаем бит в tx
                count++; // Увеличиваем count
                if(count==8) { // Если count равно 8
                    count = 0; // Обнуляем count
                    g << tx; // Записываем tx в поток вывода
                    tx = 0; // Обнуляем tx
                }
                for(; bits_to_follow>0; bits_to_follow--) { // Цикл, выполняющийся bits_to_follow раз
                    count++; // Увеличиваем count
                    if(count==8) { // Если count равно 8
                        count = 0; // Обнуляем count
                        g << tx; // Записываем tx в поток вывода
                        tx = 0; // Обнуляем tx
                    }
                }
                l-=Half; // Уменьшаем l на половину диапазона
                h-=Half; // Уменьшаем h на половину диапазона
            }
            else if((l>=F_q) && (h<T_q)) { // Иначе, если l больше или равен F_q и h меньше T_q
                bits_to_follow++;
                l-=F_q;
                h-=F_q;
            }
            else break;
            l+=l;
            h+=h+1;
        }
    }
    g<<tx;
    f.clear();
    f.seekg(0, std::ios::end);
    g.seekp(0, std::ios::end);
    double sizeF = f.tellg();
    double sizeG = g.tellp();
    f.close();
    g.close();
    return sizeG / sizeF;
}

bool decode(ifstream& fg, ofstream& gf){
    if (!fg.is_open()) {
        return false;
    }
    int count=0;
    int x1, x2;
    char s;
    map<char, int> m;
    map <char, int> ::iterator ii;
    fg.read((char*)&x1, sizeof(x1));
    while (x1>0) {
        fg.read((char*)&s, sizeof(s));
        fg.read((char*)&x2, sizeof(x2));
        x1-=40;
        m[s]=x2;
    }
    list<Range> L;
    for(ii=m.begin(); ii!=m.end(); ii++) {
        Range p;
        p.s=ii->first;
        p.numb=ii->second;
        L.push_back(p);
    }
    L.sort(Sort());
    L.begin()->rb=L.begin()->numb;
    L.begin()->lb=0;
    list<Range>::iterator it=L.begin(), i2;
    i2=it;
    it++;
    for(; it!=L.end(); it++) {
        it->lb=i2->rb;
        it->rb=it->lb+it->numb;
        i2++;
    }
    count=0;
    int l=0, h=65535, delitel=L.back().rb;
    int F_q=(h+1)/4, Half=F_q*2, T_q=F_q*3;
    int value=(fg.get()<<8) | fg.get();
    char symbl=fg.get();
    while(!fg.eof()) {
        int freq = ((value - l + 1) * delitel - 1) / (h - l + 1);
        for (it = L.begin(); it->rb <= freq; it++);
        int l2 = l;
        l = l + (it->lb) * (h - l + 1) / delitel;
        h = l2 + (it->rb) * (h - l2 + 1) / delitel - 1;
        for (;;) {
            if (h < Half);
            else if (l >= Half) {
                l -= Half;
                h -= Half;
                value -= Half;
            }
            else if ((l >= F_q) && (h < T_q)) {
                l -= F_q;
                h -= F_q;
                value -= F_q;
            }
            else break;
            l += l;
            h += h + 1;
            value += value + (((short) symbl >> (7 - count)) & 1);
            count++;
            if (count == 8) {
                symbl = fg.get();
                count = 0;
            }
        }
        gf << it->s;
    }
    fg.close();
    gf.close();
    return true;
}

int main() {
    ifstream f("text.txt", ios::out | ios::binary);
    ofstream g("code.txt", ios::out | ios::binary);
    double coef = encode(f, g);
    cout << coef << endl;
    ifstream fg("code.txt", ios::out | ios::binary);
    ofstream gf("output.txt", ios::out | ios::binary);
    if (decode(fg,gf))
        std::cout << "decode" << std::endl;
    else
        std::cout << "didnt decode" << std::endl;
    return 0;
}