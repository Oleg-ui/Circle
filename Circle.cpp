#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace std;

ifstream file("Circle.txt");

double Convert(string Str)
{
    double result = 0.0;
    int i = 0;
    string st = "";

    while (Str[i] != '.')
    {
        st.push_back(Str[i]);
        i++;
    }
    result = stoi(st);
    while (!st.empty())
        st.pop_back();
    i++;
    while (i < Str.length())
    {
        st.push_back(Str[i]);
        i++;
    }

    double t = stoi(st);
    for(int j = 0; j < st.length(); j++)
        t /= 10;

    result += t;
    return result;
}

class Circle
{
public:

    int Number;
    double X;
    double Y;
    double R;

    Circle()
    {
        Number = 0;
        X = 0.0;
        Y = 0.0;
        R = 0.0;
    }

    void FindCircle()
    {
        int count = 0;
        char ch;
        string str;

        while (file.get(ch))
        {
            if (ch == ',')
            {
                count++;
                switch (count)
                {
                case 1:
                    this->Number = stoi(str);
                    str.clear();
                    break;
                case 2:
                {
                    this->X = Convert(str);
                    str.clear();
                    break;
                }
                case 3:
                    this->Y = Convert(str);
                    str.clear();
                    break;
                }

            }
            else
            {
                str += ch;
            }

            if (ch == '\n')
            {
                this->R = Convert(str);
                str.clear();
                break;
            }

        }
    }

    bool ComparingCircles(const Circle& SecondCircle)
    {
        return sqrt(sqrt(this->X - SecondCircle.X) + sqrt(this->Y - SecondCircle.Y)) < this->R + SecondCircle.R;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    int comparison;                   // Номер круга, который нужно сравнить
    bool flag = true;

    Circle FirstCircle;
    Circle SecondCircle;

    if (!file.is_open())
    {
        cout << "Файл не найден";
    }
    else
    {
        while (!file.eof())
        {
            FirstCircle.FindCircle();          // Ищу номер последнего круга
        }

        file.clear();
        file.seekg(0, ios_base::beg);

        int* List = new int[FirstCircle.Number + 1];    //Создаю динамический массив (список проверенных кругов)
        int maxList = FirstCircle.Number + 1;           //Размер массива - максимальное количество кругов, указанных в файле

        for (int i = 0; i < maxList; i++)
        {
            List[i] = -1;
        }

        while (flag)
        {
            for (int i = 0; i < maxList; i++)           //Поиск номера круга, который еще не сравнивали
            {
                if (List[i] != i)
                {
                    comparison = i;
                    break;
                }
            }


            while (!file.eof())
            {
                FirstCircle.FindCircle();
                if (FirstCircle.Number == comparison)
                {
                    break;
                }
            }

            file.clear();
            file.seekg(0, ios_base::beg);                  //Перенаправляет в начало файла

            while (!file.eof())
            {
                SecondCircle.FindCircle();
                if (FirstCircle.Number == SecondCircle.Number)
                {
                    continue;
                }
                if (FirstCircle.ComparingCircles(SecondCircle))
                {
                    List[FirstCircle.Number] = FirstCircle.Number;
                    List[SecondCircle.Number] = SecondCircle.Number;
                    break;
                }
            }
            if (file.eof())
            {
                cout << "Заданный круг найден:" << endl;
                cout << "Номер круга - " << FirstCircle.Number << endl;
                cout << "Координаты круга - X: " << setprecision(10) << FirstCircle.X << " Y: " << setprecision(10) << FirstCircle.Y << endl;
                cout << "Радиус круга - " << setprecision(10) << FirstCircle.R << endl;
                flag = false;
            }
            file.clear();
            file.seekg(0, ios_base::beg);

        }

        file.close();
    }
}
