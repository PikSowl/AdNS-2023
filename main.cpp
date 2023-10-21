#define WrongInput wcout << L"Неверная команда" << endl

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
#include <io.h>
#include <fcntl.h>

using std::wcin;
using std::wcout;
using std::swap;
using std::endl;
using std::string;
using std::vector;

namespace eight {
    int getMax(int m[], int n) {
        int max = m[0];
        for (int i = 1; i < n; i++)
            if (m[i] > max)
                max = m[i];
        return max;
    }

    void countingSort(int m[], int n, int place) {
        const int iLen = 10;
        int output[n];
        int count[iLen];

        for (int i = 0; i < iLen; ++i)
            count[i] = 0;

        for (int i = 0; i < n; i++)
            count[(m[i] / place) % 10]++;
        for (int i =0; i < iLen; i++)
            wcout << count[i] << " ";
        wcout << endl;

        for (int i = 1; i < iLen; i++)
            count[i] += count[i - 1];
        for (int i =0; i < iLen; i++)
            wcout << count[i] << " ";
        wcout << endl;

        for (int i = n - 1; i >= 0; i--) {
            output[count[(m[i] / place) % 10] - 1] = m[i];
            count[(m[i] / place) % 10]--;
        }

        wcout << L"Проход" << endl;
        for (int i =0; i < n; i++)
            wcout << output[i] << " ";
        wcout << endl;

        for (int i = 0; i < n; i++)
            m[i] = output[i];
    }

    void radixsort(int m[], int n) {
        int max = getMax(m, n);
        for (int place = 1; max / place > 0; place *= 10)
            countingSort(m, n, place);
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

            int step, temp;

            while (step > 0){
                for (int i =0; i + step < n; i++)
                    if (mas[i] > mas[i + step]){
                        temp = mas[i + step];
                        mas[i + step] = mas[i];
                        mas[i] = temp;
                    }
                step /= 1.3; //один раз не сработало, почему не понятно
            }

            wcout << L"Сортированный масив:" <<endl;
            for(int i = 0; i <n;i++){
                wcout << mas[i] << " ";
            }
            break;
        }
        case(5): {
            wcout << L"Вставками" << endl;

            for(int i=1;i<n;i++)
                for(int j=i;j>0 && mas[j - 1] > mas[j]; j--)
                    swap(mas[j - 1], mas[j]);

            wcout << L"Сортированный масив:" <<endl;
            for(int i = 0; i <n;i++)
                wcout << mas[i] << " ";
            break;
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

            wcout << L"Сортированный масив:" <<endl;
            for(int i = 0; i <n;i++)
                wcout << mas[i] << " ";
            break;
        }
        case(7): {
            wcout << L"Шелла" << endl;
            vector d {1,4,10,23,57,132,301,701,1750};

            if(n >4000){
                for (int s = n / 2; s > 0; s /= 2)
                    for (int i = s; i != n; ++i)
                        for (int j = i - s; j >= 0 && mas[j] > mas[j + s]; j -= s)
                            swap(mas[j], mas[j + s]);
            }
            else {
                int step = d.size()-1;
                while (d[step] > n) step--;

                for (; step != 0; step--) {
                    for (int i = step; i != n; ++i)
                        for (int j = i - step; j >= 0; j -= step)
                            if (mas[j] > mas[j + step]) swap(mas[j], mas[j + step]);
                }
            }
            wcout << L"Сортированный масив:" <<endl;
            for(int i = 0; i <n;i++)
                wcout << mas[i] << " ";
            break;
        }
        case(8):{
            wcout << L"Поразрядная" << endl;
            eight::radixsort(mas, n);

            wcout << L"Сортированный масив:" <<endl;
            for(int i = 0; i <n;i++)
                wcout << mas[i] << " ";
            break;
        }
        default:
            WrongInput;
            break;
    }
    return 0;
}
