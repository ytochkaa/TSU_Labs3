#include <iostream>
#include <math.h>

using namespace std;

class complex{
private:
    double re, im;
public:
    complex(double Re = 0, double Im = 0) {
        re = Re;
        im = Im;
    }

    double getRe();                     //получить                                                                                                                                                  double getIm();
    double getIm();

    void setIm(double);                 //установить значение
    void setRe(double);
    double mod();

    bool operator==(complex);
    bool operator!=(complex);

    complex operator+(const complex &);
    complex operator-(const complex &);
    complex operator*(const complex &);
    complex operator/(const complex &);

    friend ostream& operator<<(ostream& out, const complex &x);
    friend istream& operator>>(istream& inp, complex &x);
};

double complex::getRe() {
    return re;
}

double complex::getIm() {
    return im;
}

void complex::setIm(double x) {
    im = x;
}

void complex::setRe(double x) {
    re = x;
}

double complex::mod(){
    return sqrt(re*re + im*im);
}

bool complex::operator==(complex x) {
    if ((re == x.re) && (im == x.im)) {
        return true;
    }
    return false;
}

bool complex::operator!=(complex x) {
    if ((re != x.re) || (im != x.im)) {
        return true;
    }
    return false;
}

complex complex::operator+(const complex &x) {
    complex temp;
    temp.re = re + x.re;
    temp.im = im + x.im;
    return temp;
}

complex complex::operator-(const complex &x) {
    complex temp;
    temp.re = re - x.re;
    temp.im = im - x.im;
    return temp;
}

complex complex::operator*(const complex &x) {
    complex temp;
    temp.re = re * x.re - im * x.im;
    temp.im = im * x.re + re * x.im;
    return temp;
}

complex complex::operator/(const complex &x) {
    complex temp;
    if ((x.re == 0) && (x.im == 0)) {
        cout << "Error division";
    }else{
        temp.re = (re * x.re + im * x.im) / (x.re * x.re + x.im * x.im);
        temp.im = (im * x.re - re * x.im) / (x.re * x.re + x.im * x.im);
        return temp;
    }
}

ostream& operator<<(ostream& out, const complex &x) {
    out << x.re << " " << x.im << "i";
    return out;
}

istream& operator>>(istream& inp, complex &x) {
    inp >> x.re >> x.im;
    return inp;
}

int main() {
    complex c1, c2;
    cout << "Enter the real and imaginary parts of the first complex number: ";
    cin >> c1;
    cout << "Enter the real and imaginary parts of the second complex number: ";
    cin >> c2;
    cout << "==: " << (c1 == c2) << endl;
    cout << "!=: " << (c1 != c2) << endl;
    cout << "|c1|: " << (c1.mod()) << endl;
    cout << "|c2|: " << (c2.mod()) << endl;
    cout << "+: " << (c1 + c2) << endl;
    cout << "-: " << (c1 - c2) << endl;
    cout << "*: " << (c1 * c2) << endl;
    cout << "/: " << (c1 / c2) << endl;
    cout << "";
}



