#include <iostream>
#include <chrono>

using namespace std;

class Array {

    int *a; // указатель на массив
    int n; //его размер

public:

    Array(int len = 1, int type = 1, int range = 10) {

        a = new int[len];
        n = len;

        /// если type = 1, генерируется неупорядоченный массив
        if (type == 1) {
            for (int i = 0; i < n; i++) {
                a[i] = rand() % range;
            }

            /// если type = 2, генерируется массив, упорядоченный по невозрастанию
        } else if (type == 2) {
            a[0] = rand() % (range - 1);
            for (int i = 1; i < n; i++) {
                a[i] = a[i - 1] - rand() % (range - 1); // Changed '-' to '+' for non-increasing order
            }

            /// если type = 3, генерируется массив, упорядоченный по неубыванию
        } else if (type == 3) {
            a[n - 1] = rand() % (range + 1);
            for (int i = n - 2; i >= 0; i--) {
                a[i] = a[i + 1] + rand() % (range + 1);
            }

            /// если значение type не соответствует ни одному из предложенных, программа завершается с ошибкой
        } else {
            exit(1);
        }
    };

    /// конструктор  копирования
    Array(const Array &x) {
        a = new int[x.n];
        n = x.n;
        for (int i = 0; i < n; i++) {
            a[i] = x.a[i];
        }
    };

    /// конструктор
    Array(int *x, int len) {
        a = new int[len];
        n = len;
        for (int i = 0; i < n; i++) {
            a[i] = x[i];
        }
    };

    /// деструктор
    ~Array() { // деструктор
        if (a) delete[] a; // освобождение памяти, если массив был выделен
        a = NULL; // обнуление указателя на массив
    }


    Array &operator=(const Array &);

    int &operator[](int);

    int getSize();

    friend istream &operator>>(istream &, Array &);

    friend ostream &operator<<(ostream &, Array &);

    bool operator==(Array &x);

    bool Test();

    void ShellSort();

    void QS(int first, int last);

    int partition(int p, int r);

    void heapify(int n, int i);

    void Heapsort();

    void Bit_Sort();
};

Array &Array::operator=(const Array &x) {

    if (this != &x) {
        delete[] a;
        n = x.n;
        a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = x.a[i];
        }
    }
    return *this;
}

int Array::getSize() {
    return n;
}

/// возвращается элемент массива по указанному индексу
int &Array::operator[](int x) {
    if (x < 0 || x >= n) { // Changed '>' to '>=' for correct bounds checking
        cout << "Error: index is out of bounds";
        exit(1);
    }
    return a[x];
}

/// оператор ввода
istream &operator>>(istream &in, Array &obj) {
    int len;
    cout << "len: ";
    in >> len; // ввод размера массива
    cout << "\n array: ";
    int *arr;
    arr = new int[len]; // выделение памяти под массив
    for (int i = 0; i < len; i++) {
        in >> arr[i]; // ввод элементов массива
    }
    obj = Array(arr, len); // создание объекта Array на основе введенного массива
    delete[] arr; // освобождение памяти, занимаемой временным массивом
    return in;
}

/// оператор вывода
ostream &operator<<(ostream &out, Array &a) {
    out << "[";
    for (int i = 0; i < a.n; i++) {
        out << a[i] << " "; // вывод элементов массива
    }
    out << "]";
    return out;
}


bool Array::operator==(Array &x) {
    if (n != x.n) {
        return false;
    }
    int len = n;
    for (int i = 0; i < n; i++) {
        bool ch = false;
        for (int j = 0; j < len; j++) {
            if (a[i] == x.a[j]) {
                ch = true;
                x.a[j] = x.a[len - 1];
                len--;
                break;
            }
        }
        if (!ch) {
            return true;
        }
    }
    return false;
}

bool Array::Test() {
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) return false;
    }
    return true;
}

// ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ShellSort ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀
void Array::ShellSort() {
    int size = getSize();
    for (int step = size / 2; step > 0; step = step / 2) {
        for (int i = step; i < size; i += 1) {
            int temp = a[i];
            int j;
            for (j = i; j >= step && a[j - step] > temp; j -= step) {
                a[j] = a[j - step];// Сдвигаем элементы вправо
            }
            a[j] = temp;
        }
    }
}

// ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ Heapsort ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡ ♡
void Array::heapify(int n, int i)
{
    int j = 2*i + 1;
    int x = a[i];
    bool f = true;

    while (j < n && f == 1)
    {
        if (j + 1 < n && a[j + 1] > a[j]) j++;
        if (a[j] > x)
        {
            a[i] = a[j];
            i = j;
            j = 2 * i + 1;
        }
        else f = false;
    }
    a[i] = x;
}
void Array::Heapsort()
{
    int tmp;
    for (int i = n/2 - 1; i >= 0; i--)  this->heapify(n, i);
    for (int i = n - 1; i > 0; i--)
    {
        tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;
        this->heapify(i, 0);
    }
}

//☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ QS ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆
void Array::QS(int right1, int left1) {
    int right = right1,
            left = left1,
            pivot = a[(right + left) / 2];
    while (right <= left) {
        while (a[right] < pivot) {
            right++;
        }
        while (a[left] > pivot) {
            left--;
        }
        if (right <= left) {
            int tmp = a[right];
            a[right] = a[left];
            a[left] = tmp;
            right++;
            left--;
        }
    }
    // Рекурсивно сортируем правую часть
    if (right < left1) {
        QS(right, left1);
    }
    // Рекурсивно сортируем левую часть
    if (right1 < left) {
        QS(right1, left);
    }
}

// ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ BitSort ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫ ♫
void BitSort(int a[], int left, int right, int k) {
    if (left >= right || k < 0) {
        return;
    }
    int i = left, j = right;
    while (i <= j) {
        while (i <= j && ((a[i] >> k) & 1) == 0) {
            i++;
        }
        while (i <= j && ((a[j] >> k) & 1) == 1) {
            j--;
        }
        if (i < j) {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }
    // Рекурсивная сортировка подмассива [l, j] по (k-1)-ому биту
    BitSort(a, left, j, k - 1);
    // Рекурсивная сортировка подмассива [i, r] по (k-1)-ому биту
    BitSort(a, i, right, k - 1);
}

void Array::Bit_Sort() {
    BitSort(a, 0, getSize() - 1, sizeof(int) * 8 - 1);
}
//☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ test ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺ ☺
void test() {

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    Array array1(100000, 1, 100000);
    Array array2 = array1;
    Array array3 = array1;
    Array array4 = array1;

    auto beg1 = std::chrono::steady_clock::now();
    array1.ShellSort();
    auto etime1 = std::chrono::steady_clock::now();
    auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(etime1 - beg1);
    cout << array1.Test() << endl;


    auto beg2 = std::chrono::steady_clock::now();
    array2.QS(0, array2.getSize());
    auto etime2 = std::chrono::steady_clock::now();
    auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(etime2 - beg2);
    array2.Test();


    auto beg3 = std::chrono::steady_clock::now();
    array3.Heapsort();
    auto etime3 = std::chrono::steady_clock::now();
    auto time3 = std::chrono::duration_cast<std::chrono::milliseconds>(etime3 - beg3);
    array3.Test();


    auto beg4 = std::chrono::steady_clock::now();
    array4.Bit_Sort();
    auto etime4 = std::chrono::steady_clock::now();
    auto time4 = std::chrono::duration_cast<std::chrono::milliseconds>(etime4 - beg4);
    array4.Test();


    cout << endl;

    cout << "The time for Hoar Sort: " << time2.count() << " ms\n";
    cout << array1.Test() << endl;
    cout << "The time for Bit Sort: " << time4.count() << " ms\n";
    cout << array2.Test() << endl;
    cout << "The time for HeapSort: " << time3.count() << " ms\n";
    cout << array3.Test() << endl;
    cout << "The time for Shell Sort: " << time1.count() << " ms\n";
    cout << array4.Test() << endl;

    cout << "==:"  << endl;
    cout << "array1 == array2: " << (array1 == array2) << endl;
    cout << "array3 == array2: " << (array3 == array2) << endl;
    cout << "array4 == array2: " << (array4 == array2) << endl;

}

int main() {

    srand(time(NULL));



    Array a1(7, 1, 100);
    cout << "Array a1: " << a1 << "\n" << endl;
    Array a2(7, 1, 100);
    cout << "Array a2: " << a2 << "\n" << endl;
    Array a3(7, 1, 100);
    cout << "Array a3: " << a3 << "\n" << endl;
    Array a4(7, 1, 100);
    cout << "Array a4: " << a4 << "\n" << endl;

    /*Array b1(10, 2, 100);
    cout << "(type = 2) Array b1: " << b1 << "\n" << endl;

    Array b2(10, 3, 100);
    cout << "(type = 3) Array b2: " << b2 << "\n" << endl;*/

    a1.ShellSort();
    cout << "Sorted Array a1: " << a1 << endl;
    a1.Test();

    a2.Heapsort();
    cout << "Sorted Array a2: " << a2 << endl;
    a2.Test();

    a3.QS(0, a3.getSize() - 1);
    cout << "Sorted Array a3: " << a3 << endl;
    a3.Test();

    a4.Bit_Sort();
    cout << "Sorted Array a4: " << a4 << endl;
    a4.Test();

    test();

    return 0;

}