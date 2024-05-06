//2.2. Задача Коммивояжера.
//     Класс Маршрут. Полный перебор, используя алгоритм Дейкстры
#include <iostream>
#include <algorithm>

using namespace std;

class route {
    int *town;
    int number;

public:

    route(int num = 0); // первую
    route(const route &); // конструктор копирования
    route &operator=(const route &); // оператор присваивания
    ~route() {
        delete[] town;
    }

    int routePrice(int**);
    bool nextRoute();
    friend ostream &operator << (ostream&, const route&);
};

    //Конструктор
    route::route(int num){
        number = num;
        town = new int[number];
        for (int i = 0; i < number; i++) {
            town[i] = i;
        }
    }

    //Конструктор копирования
    route::route(const route &x):
    number(x.number) {
        town = new int[number];
        for (int i = 0; i < number; i++) {
            town[i] = x.town[i];
        }
    }

    //Оператор присваивания
    route &route::operator=(const route& x) {
        if (this == &x) { // является ли текущий объект объектом х
            return *this;
        }
        number = x.number;
        delete[] town;
        town = new int[number];
        for (int i = 0; i < number; i++) {
            town[i] = x.town[i];
        }
        return *this;
    }

    // стоимость
    int route::routePrice(int **arr) {
        int sum = 0;
        for (int i = 0; i < number; i++) {
            sum += arr[town[i]] [town[(i + 1) % number]];
        }
        return sum;
    }

    // Алгоритм Дейкстры
    bool route::nextRoute(){
        int i = -1;
       int j;
       int k;
       for ( k = number - 2; k >= 0; k--) { // итерация для поиска значения i
          if (town[k] < town[k + 1]) {
              i = k;
              break;
           }
       }

      // проверка на начало маршрута
       if (i < 0) {
           return false;  // если не найдено, возвращаем false
       }

      for ( k = number - 1; k >= i + 1; k--) { // итерация для поиска значения j
            if (town[i] < town[k]) { // поиск ближайшего города с бОльшим номером
                j = k;
                int tmp = town[j];
                town[j] = town[i];
                town[i] = tmp;
                break; // добавлен прерывание цикла, так как уже найден ближайший город
            }
        }


        //инвертируем порядок (упорядочиваем хвост по возрастанию)
        for ( j = i + 1, k = (number - 1); j < k; j++, k--){
            int tmp = town[j];
            town[j] = town[k];  // инверсия порядка
            town[k] = tmp;
        }
        return true;  // возвращаем true
    }
//вывод
ostream& operator << (ostream &out, const route &a) {
    for (int i = 0; i < a.number; i++) {
        out << a.town[i] << " ";
    }
    return out;
}
int main() {

    int numer;
    cout << "enter the numer of cities: ";
    cin >> numer;
    cout << "enter cost array:\n";

    // Создание начального маршрута
    route perm1(numer);

    // для стоимостей
    int **cost = new int *[numer];

    // сотимости
    for (int i = 0; i < numer; i++) {
        cost[i] = new int[numer];
        for (int j = 0; j < numer; j++) {
            if (i == j) {
                cost[i][j] = 0;
            } else {
                cout << i << "->" << j << ":";
                cin >> cost[i][j];
            }
        }
        cout  << endl;
    }

    // создание копии начального маршрута
    route perm2 = perm1;

    // начальный
    int price1 = perm1.routePrice(cost);
    cout << "Route: " << perm1 << "Price: " << price1 << endl;

    // оптимальный?
    while (perm2.nextRoute()) {
        int price2 = perm2.routePrice(cost);
        cout << "Route: " << perm2 << "Price: " << price2 << endl;

        if (price2 <= price1) {
            perm1 = perm2;
            price1 = price2;
        }
    }

    cout << "Optimal price: " << price1 << endl << "Optimal route: " << perm1;

    for (int i = 0; i < numer; i++) {
        delete[] cost[i];
    }

    delete[] cost;

    return 0;
}
