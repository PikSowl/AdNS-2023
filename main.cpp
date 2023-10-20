#define WrongInput wcout << L"Неверная команда" << endl;

/*колекция лабораторных работ по Алгоритмам и структурам данных
 + -> выполнено
 №1 + Задача о скобках
 №2   Задача об арифметическом выражении
 №3   Задача о простых множителях
 №4 + Сортировка методом прочесывания
 №5 + Вставками
 №6 + Посредством выбора
 №7   Шелла
 №8   Поразрядная
 №9   Пирамидальная (heap sort)
 №10  Слиянием
 №11  Быстрая
 №12  Внешняя многофазная
 №13  Хеш-таблица “с наложением”
 №14  Хеш-таблица “со списками”
 №15  Рекурсивные обходы (прямой, центральный, концевой)
 №16  Не рекурсивный прямой обход
 №17  Операции над БНП: поиск, добавление, удаление
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <io.h>
#include <fcntl.h>

using std::wcin;
using std::wcout;
using std::swap;
using std::endl;
using std::string;
using std::vector;


struct Dot {
    double x;
    double y;
    double z;
};

class Vector {

private:
    Dot XYZ = {0, 0, 0};

public:
    Vector(Dot a, Dot b){
        XYZ.x = b.x - a.x;
        XYZ.y = b.y - a.y;
        XYZ.z = b.z - a.z;
    }

    Vector(){}
    Vector(double i, double j, double k){
        XYZ = {i,j,k};
    }
    Vector(const Vector& other){
        XYZ = other.XYZ;
    }
    double GetX(){
        return XYZ.x;
    }
    double GetY(){
        return XYZ.y;
    }
    double GetZ(){
        return XYZ.z;
    }
    double Len(){
        double len = pow(pow(XYZ.x, 2) + pow(XYZ.y, 2) + pow(XYZ.z, 2), 0.5);
        return len;
    }

    Vector& operator = (const Vector& other){
        XYZ = other.XYZ;
        return *this;
    }
    Vector& operator += (const Vector& other)
    {
        XYZ.x += other.XYZ.x;
        XYZ.y += other.XYZ.y;
        XYZ.z += other.XYZ.z;
        return *this;
    }
    Vector operator + (const Vector& other){
        Vector temp = *this;
        temp += other;
        return temp;
    }
    Vector& operator -= (const Vector& other){
        XYZ.x -= other.XYZ.x;
        XYZ.y -= other.XYZ.y;
        XYZ.z -= other.XYZ.z;
        return *this;
    }
    Vector operator - (const Vector& other){
        Vector temp = *this;
        temp -= other;
        return temp;
    }
    Vector& operator *= (const double& k){
        XYZ.x *= k;
        XYZ.y *= k;
        XYZ.z *= k;
        return *this;
    }
    Vector operator * (const double& k){
        Vector temp = *this;
        temp *= k;
        return temp;
    }
    double operator * (const Vector& other){
        return XYZ.x * other.XYZ.x + XYZ.y * other.XYZ.y + XYZ.z * other.XYZ.z;
    }
    Vector VecProd(const Vector& other){
        Vector ans;
        ans.XYZ.x = this->XYZ.y * other.XYZ.z - this->XYZ.z * other.XYZ.y;
        ans.XYZ.y = -1 * (this->XYZ.x * other.XYZ.z - this->XYZ.z * other.XYZ.x);
        ans.XYZ.z = this->XYZ.x * other.XYZ.y - this->XYZ.y * other.XYZ.x;
        return ans;
    }
    double MixProd(const Vector& other1, const Vector& other2){
        return (*this).VecProd(other1) * other2;
    }

    bool operator > (Vector& other){
        return (*this).Len() > other.Len();
    }
    bool operator < (Vector& other){
        return (*this).Len() < other.Len();
    }
    bool operator == (Vector& other){
        return (*this).Len() == other.Len();
    }

    bool Colinear(const Vector& other){
        Vector Null;
        return ((*this).VecProd(other) == Null);
    }
    bool Complanar(const Vector& other1, const Vector& other2){
        return (*this).MixProd(other1, other2) == 0;
    }

    double Angle(Vector& other){
        return std::cos((*this * other) / ((*this).Len() * other.Len()));
    }
    Vector Norm(){
        Vector temp = *this;
        double k = (*this).Len();
        if (k != 0)
            temp *= 1/k;
        return temp;
    }

    friend std::ostream& operator << (std::ostream& out, Vector& other);
    friend std::istream& operator >> (std::istream& in, Vector& other);

    ~Vector() {}
};

std::wostream& operator << (std::wostream& out, Vector& other)
{
    return out << other.GetX() << " " << other.GetY() << " " << other.GetZ();
}

std::wistream& operator >> (std::wistream& in, Vector& other)
{
    double x, y, z;
    in >> x >> y >> z;
    other = { x,y,z };
    return in;
}

void VecInput(Vector& x, char name,const int & style) {

    if (style == 1){
        Dot A,Z{0,0,0};
        wcout << L"Введите компоненты вектора "<< name << endl;
        wcin >> A.x >> A.y >> A.z;
        x=Vector(Z,A);
    }
    else{
        Dot A,B;
        wcout << L"Введите координаты 1 точки вектора "<< name << endl;
        wcin >> A.x >> A.y >> A.z;
        wcout << L"Введите координаты 2 точки вектора "<< name << endl;
        wcin >> B.x >> B.y >> B.z;
        x=Vector(A,B);
    }
}

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin),  _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    int lab_num;
    wcout << L"Выберете лабораторную" << endl;
    wcin >> lab_num;
    switch (lab_num) {
        case(1): {
            wcout << L"Не тот файл";
        }
        case(4): {
            int n, step, temp;
            std::random_device rd;

            wcout << L"Введите длинну масива:" ;
            wcin >> n;
            std::uniform_int_distribution<int> dist(1,n);
            step = n - 1;

            vector<int> v(n);
            wcout << L"Случайный масив:" <<endl;
            for(int i = 0; i <n;i++){
                v[i] = dist(rd);
                wcout << v[i] << " ";
            }
            wcout << endl;

            while (step > 0){
                for (int i =0; i + step < n; i++)
                    if (v[i] > v[i+step]){
                        temp = v[i+step];
                        v[i+step] = v[i];
                        v[i] = temp;
                    }
                step /= 1.3; //один раз не сработало, почему не понятно
            }

            wcout << L"Сортированный масив:" <<endl;
            for(int i = 0; i <n;i++){
                wcout << v[i] << " ";
            }
            return 0;
        }
        case(5): {
            int n;
            std::random_device rd;

            wcout << L"Введите длинну масива:" ;
            wcin >> n;
            std::uniform_int_distribution<int> dist(1,n);

            vector<int> v(n);
            wcout << L"Случайный масив:" <<endl;
            for(int i = 0; i <n;i++){
                v[i] = dist(rd);
                wcout << v[i] << " ";
            }
            wcout << endl;

            for(int i=1;i<n;i++)
                for(int j=i;j>0 && v[j-1]>v[j];j--)
                    swap(v[j-1],v[j]);

            wcout << L"Сортированный масив:" <<endl;
            for(int i = 0; i <n;i++)
                wcout << v[i] << " ";
            return 0;
        }
        case(6): {
            int mini, n;
            std::random_device rd;

            wcout << L"Введите длинну масива:" ;
            wcin >> n;
            std::uniform_int_distribution<int> dist(1,n);

            vector<int> v(n);
            wcout << L"Случайный масив:" <<endl;
            for(int i = 0; i <n;i++){
                v[i] = dist(rd);
                wcout << v[i] << " ";
            }
            wcout << endl;

            for (int i=0; i<n-1; i++){
                mini=i;
                for (int j=i+1; j<n; j++){
                    if (v[mini]>v[j])
                        mini=j;
                }
                if (mini!=i)
                    swap(v[i],v[mini]);
            }

            wcout << L"Сортированный масив:" <<endl;
            for(int i = 0; i <n;i++)
                wcout << v[i] << " ";
            return 0;
        }
        default: WrongInput break;
    }
    return 0;
}
