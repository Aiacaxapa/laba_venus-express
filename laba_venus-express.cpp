#include <iostream>
#include <cmath>
#include <fstream>

# define PI           3.14159265358979323846 

using namespace std;

// метод итераций (метод неподвижной точки)
#include <cmath>

double fixed_point_iteration(double M, double e, double epsilon = 1e-6)
{
    double E = M;
    double E_next;

    for (int i = 0; i <= 30; i++)       //цикл для поиска кол-ва действий с вводными данными
    {
        E_next = e * sin(E) + M;   // обновляем значение E
        if (fabs(E_next - E) < epsilon)
            return E_next;

        E = E_next; // вычисляем значение E_next
    }

    return 0;
}

double bisection_method(double M, double e, double epsilon = 1e-6)
{
    double x = M - 5; // любое отрицательное значение
    double y = M + 5;  // любое положительное значение
    double z = 0;

    for (int i = 0; i <= 100; i++)
    {
        z = (x + y) / 2; // вычисляем новую середину отрезка
        if (fabs(y - x) < (2 * epsilon))
            return z;

        if (((x - e * sin(x) - M) * (y - e * sin(y) - M)) < 0)
        {
            y = z; // обновляем правую границу отрезка
        }
        else
        {
            x = z; // обновляем левую границу отрезка
        }
    }

    return z;
}

double golden_section_method(double M, double e, double epsilon = 1e-6)
{
    double x = M - 5; // любое отрицательное значение
    double y = M + 5; // любое положительное значение
    double z = 0;
    double phi = (sqrt(5) + 1) / 2; // золотое сечение

    for (int i = 0; i <= 30; i++)
    {
        z = x + (y - x) / phi; // вычисляем новую середину отрезка
        if (fabs(y - x) < 2 * epsilon)
            return z;

        if ((x - e * sin(x) - M) * (y - e * sin(y) - M) < 0)
        {
            y = z; // обновляем правую границу отрезка
        }
        else
        {
            x = z; // обновляем левую границу отрезка
        }
    }

    return z;
}

double newton_method(double M, double e, double epsilon = 1e-6)
{
    double E = M; // начальное приближение для E

    for (int i = 0; i < 40; i++)
    {
        double f = E - e * sin(E) - M; // значение функции
        double f_prime = 1 + e * cos(E); // значение производной функции

        E -= f / f_prime; // вычисление следующего приближения для E

        if (abs(f) < epsilon) // проверка условия сходимости
        {
            break;
        }
    }

    return abs(E);
}

int main() {
    // параметры орбиты
    double T = 64800;                        // период обращения КА в секундах
    double r_a = 63000;                   // м радиус апоцентра
    double r_p = 460;                    // м радиус перицентра 
    double epsilon = 1e-6;

    double n = 2 * PI / T;                 // средняя угловая скорость 

    /*Конечно можно было бы найти n через формулу n = sqrt(G*M_пл/(a^3)),
    
    но я нашел период обращения венеры-экспресс на википедии и решил упростить себе задачу

    */
    double a = (r_a + r_p) / 2;              // большая полуось 
    double e = ((r_a - r_p) / (2 * a));            // эксцентриситет орбиты 0.985503

    // создаем файл
    ofstream fout1;
    fout1.open("task_one.txt");

    // проверяем файл на успешное открытие
    if (!fout1) {
        cout << "ошибка, файл не открылся";
        return 0;
    }

    fout1 << "t, c\t";
    fout1 << "M(t), рад\t";
    fout1 << "E(t), рад\t";
    fout1 << "Theta(t), рад\t" << endl;

    // считаем и записываем значения аномалий в файл
    for (int t = 0; t <= T; t++) {
        fout1 << t << "\t";

        double M = n * t; // средняя аномалия
        double E = newton_method(M, e, epsilon); // эксцентрическая аномалия
        double true_anomaly = atan(sqrt((1 + e) / (1 - e)) * tan(E / 2)) * 2; // истинная аномалия

        if (true_anomaly < 0)
            true_anomaly += 2 * PI;

        fout1 << M << "\t";
        fout1 << E << "\t";
        fout1 << true_anomaly << endl;
    }

    fout1.close();
    cout << "данные были успешно внесены в файл task_one.txt " << endl;

    ofstream fout2;
    fout2.open("task_two.txt");

    if (!fout2) {
        cout << "ошибка, файл не открылся";
        return 0;
    }

    fout2 << "t, c\t";
    fout2 << "M(t), рад\t";
    fout2 << "E(t), рад\t";
    fout2 << "Theta(t), рад\t" << endl;

    // считаем и записываем значения аномалий в файл
    for (int t = 0; t <= T; t++) {
        fout2 << t << "\t";

        double M = n * t; // средняя аномалия
        double E = golden_section_method(M, e, epsilon); // эксцентрическая аномалия
        double true_anomaly = atan(sqrt((1 + e) / (1 - e)) * tan(E / 2)) * 2; // Истинная аномалия

        if (true_anomaly < 0)
            true_anomaly += 2 * PI;

        fout2 << M << "\t";
        fout2 << E << "\t";
        fout2 << true_anomaly << endl;
    }

    fout2.close();
    cout << "данные были успешно внесены в файл task_two.txt " << endl;

    ofstream fout3;
    fout3.open("task_three.txt");

    if (!fout3) {
        cout << "ошибка, файл не открылся";
        return 0;
    }

    fout3 << "t, c\t";
    fout3 << "M(t), рад\t";
    fout3 << "E(t), рад\t";
    fout3 << "Theta(t), рад\t" << endl;

    // Вычисление и запись значений аномалий в файл
    for (int t = 0; t <= T; t++) {
        fout3 << t << "\t";

        double M = n * t; // Средняя аномалия
        double E = bisection_method(M, e, epsilon); // Эксцентрическая аномалия
        double true_anomaly = atan(sqrt((1 + e) / (1 - e)) * tan(E / 2)) * 2; // Истинная аномалия

        if (true_anomaly < 0)
            true_anomaly += 2 * PI;

        fout3 << M << "\t";
        fout3 << E << "\t";
        fout3 << true_anomaly << endl;
    }

    fout3.close();
    cout << "данные были успешно внесены в файл task_three.txt" << endl;

    ofstream fout4;
    fout4.open("task_four.txt");

    if (!fout4) {
        cout << "ошибка, файл не открылся";
        return 0;
    }

    fout4 << "t, c\t";
    fout4 << "M(t), рад\t";
    fout4 << "E(t), рад\t";
    fout4 << "Theta(t), рад\t" << endl;

    // вычисление и запись значений в файл
    for (int t = 0; t <= T; t++) {
        fout4 << t << "\t";

        double M = n * t; // средняя аномалия
        double E = fixed_point_iteration(M, e, epsilon); // эксцентрическая аномалия
        double true_anomaly = atan(sqrt((1 + e) / (1 - e)) * tan(E / 2)) * 2; // истинная аномалия

        if (true_anomaly < 0)
            true_anomaly += 2 * PI;

        fout4 << M << "\t";
        fout4 << E << "\t";
        fout4 << true_anomaly << endl;
    }

    fout4.close();
    cout << "данные были успешно внесены в файл task_four.txt" << endl;

    return 0;
}