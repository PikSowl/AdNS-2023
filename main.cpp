#define WrongInput wcout << L"Неверная команда" << endl
#define Output wcout << L"Сортированный масив:" <<endl;for(int i = 0; i <n;i++) wcout << mas[i] << " "; break

/*колекция лабораторных работ по Алгоритмам и структурам данных
 + -> выполнено
 №1 + Задача о скобках
 №2   Задача об арифметическом выражении
 №3   Задача о простых множителях
 №4 + Методом прочесывания
 №5 + Вставками
 №6 + Посредством выбора
 №7 + Шелла
 №8 + Поразрядная
 №9 + Пирамидальная (heap sort)
 №10+ Слиянием
 №11  Быстрая
 №12  Внешняя многофазная
 №13  Хеш-таблица “с наложением”
 №14  Хеш-таблица “со списками”
 №15  Рекурсивные обходы (прямой, центральный, концевой)
 №16  Не рекурсивный прямой обход
 №17  Операции над БНП: поиск, добавление, удаление
*/
#include <iostream>
#include <math.h>
#include <algorithm>
#include <random>
#include <io.h>
#include <fcntl.h>

using std::wcin;
using std::wcout;
using std::swap;
using std::endl;
using std::string;
using std::vector;

namespace seven {
    int d[] = {1,4,10,23,57,132,301,701,1750};
    void CiuraSort(int mas[], int n) {
        int sNum = 8;
        while (d[sNum] > n) sNum--;

        for (; sNum != 0; sNum--) {
            for (int i = sNum; i != n; ++i)
                for (int j = i - sNum; j >= 0; j -= sNum)
                    if (mas[j] > mas[j + sNum]) swap(mas[j], mas[j + sNum]);
        }
    }
    void SedgewickSort(int mas[], int n) {
        int f[100];
        int sNum = 0;
        for(; f[sNum] < n; sNum++)
            f[sNum] = pow(4,sNum)+ 3*pow(2,sNum - 1) + 1;


        for (; sNum != 0; sNum--) {
            for (int i = sNum; i != n; ++i)
                for (int j = i - sNum; j >= 0; j -= sNum)
                    if (mas[j] > mas[j + sNum]) swap(mas[j], mas[j + sNum]);
        }
    }
}
namespace eight {
    void countingSort(int mas[], int n, int place) {
        const int intLen = 10;
        int output[n];
        int count[intLen];

        for (int i = 0; i < intLen; ++i) count[i] = 0;

        for (int i = 0; i < n; i++) count[(mas[i] / place) % 10]++;

        for (int i =0; i < intLen; i++) wcout << count[i] << " ";
        wcout << endl;

        for (int i = 1; i < intLen; i++) count[i] += count[i - 1];

        for (int i =0; i < intLen; i++) wcout << count[i] << " ";
        wcout << endl;

        for (int i = n - 1; i >= 0; i--) {
            output[count[(mas[i] / place) % 10] - 1] = mas[i];
            count[(mas[i] / place) % 10]--;
        }

        /*
        wcout << L"Проход" << endl;
        for (int i =0; i < n; i++)
            wcout << output[i] << " ";
        wcout << endl;
        */
        for (int i = 0; i < n; i++)
            mas[i] = output[i];
    }

    void radixsort(int mas[], int n) {
        int max = mas[0];
        for (int i = 1; i < n; i++)
            if (mas[i] > max)
                max = mas[i];

        for (int place = 1; max / place > 0; place *= 10)
            countingSort(mas, n, place);
    }
}
namespace nine {
    void heapify(int mas[], int n, int i){
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && mas[left] > mas[largest])
            largest = left;
        if (right < n && mas[right] > mas[largest])
            largest = right;

        if (largest != i) {
            swap(mas[i], mas[largest]);
            heapify(mas, n, largest);
        }
    }

    void heapSort(int mas[], int n)
    {
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(mas, n, i);
        }

        for (int i = n - 1; i > 0; i--) {
            swap(mas[0], mas[i]);
            heapify(mas, i, 0);
        }
    }
}
namespace ten {
    void merge(int mas[], int first, int cut, int last) {
        int n1 = cut - first + 1;
        int n2 = last - cut;
        int L[n1], M[n2];

        for (int i = 0; i < n1; i++)
            L[i] = mas[first + i];
        for (int j = 0; j < n2; j++)
            M[j] = mas[cut + 1 + j];

        int i = 0, j = 0, k = first;
        while (i < n1 && j < n2) {
            if (L[i] <= M[j]) {
                mas[k] = L[i];
                i++;
            } else {
                mas[k] = M[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            mas[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            mas[k] = M[j];
            j++;
            k++;
        }
    }

    void mergeSort(int mas[], int left, int right) {
        if (left < right) {
            int midle = left + (right - left) / 2;

            mergeSort(mas, left, midle);
            mergeSort(mas, midle + 1, right);

            merge(mas, left, midle, right);
        }
    }
}
int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin),  _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    int n, lab_num;
    wcout << L"Введите длинну масива:" ;
    wcin >> n;
    std::random_device rd;
    std::uniform_int_distribution<int> dist(1,n);

    int mas[n];
    wcout << L"Случайный масив:" <<endl;
    for(int i = 0; i <n;i++){
        mas[i] = dist(rd);
        wcout << mas[i] << " ";
    }
    wcout << endl;
    wcout << L"Выберете сортировку" << endl;
    wcin >> lab_num;
    switch (lab_num) {
        case(1): {
            wcout << L"Не тот файл" << endl;
            break;
        }
        case(4): {
            wcout << L"Методом прочесывания" << endl;
            for (int step = n - 1;step > 0;step /= 1.3)
                for (int i = 0; i + step < n; i++)
                    if (mas[i] > mas[i + step]) swap(mas[i], mas[i + step]);
            Output;
        }
        case(5): {
            wcout << L"Вставками" << endl;

            for(int i=1;i<n;i++)
                for(int j=i;j>0 && mas[j - 1] > mas[j]; j--)
                    swap(mas[j - 1], mas[j]);
            Output;
        }
        case(6): {
            wcout << L"Посредством выбора" << endl;
            int mini;
            for (int i=0; i<n-1; i++){
                mini=i;
                for (int j=i+1; j<n; j++){
                    if (mas[mini] > mas[j])
                        mini=j;
                }
                if (mini!=i)
                    swap(mas[i], mas[mini]);
            }
            Output;
        }
        case(7): {
            wcout << L"Шелла" << endl;
            if(n >4000) seven::SedgewickSort(mas, n);
            else seven::CiuraSort(mas, n);
            Output;
        }
        case(8): {
            wcout << L"Поразрядная" << endl;
            eight::radixsort(mas, n);
            Output;
        }
        case(9): {
            wcout << L"Пирамидальная" << endl;
            nine::heapSort(mas, n);
            Output;
        }
        case(10): {
            wcout << L"Слиянием" << endl;
            ten::mergeSort(mas, 0, n-1);
            Output;
        }
        default:
            WrongInput;
            break;
    }
    return 0;
}
