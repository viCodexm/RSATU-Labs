
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    float s3(int x) {
        float res = 0, ch = 1, zn = 1, eps = 0.0001, sub = 1;
        int prev = 1, sign = 1;

        while (sub > eps) {
            ch *= x * x;
            prev += 2;
            zn *= prev * (prev - 1);
            sub = ch / zn;

            res += sign * sub;
            sign = -sign;
        }
        return res;
    }

    double calc(float x, int sign) {
        double t = x, s = x, eps = 0.000001;
        for (int n = 3; fabs(t) > eps; n += 2)
            s += t = -t * x * x / n / (n - 1);
        return s * sign;
    }

    double s1(double x) {
        int sign = (x < 0) ? -1 : 1;
        x = fmod(fabs(x), 2 * M_PI);
        if (x > M_PI) { x -= M_PI; sign = -sign; }
        if (x > M_PI / 2) x = M_PI - x;
        return calc(x, sign);
    }
    double s2(double x) {
        int sign = (x < 0) ? -1 : 1;
        return calc(x, sign);
    }

    
    double factorial(int n) {
        if (n < 2) return  1;
        return n * factorial(n - 1);
    }
    double taylor_sin(double x, int n) {
        double sum = 0;
        for (int i = 0; i <= n; ++i)
            sum += pow(-1, i) * pow(x, 2 * i + 1) / factorial(2 * i + 1);
        return sum;
    }
    double taylor_cos(double x, int n) {
        double sum = 0;
        for (int i = 0; i <= n; ++i)
            sum += pow(-1, i) * pow(x, 2 * i) / factorial(2 * i);
        return sum;
    }
    double taylor_log(double x) {
        if (x <= 0) {
            cerr << "Ошибка: x должно быть больше  0\n";
            return  0;
        }
        long double ratio = (x - 1) / (x + 1);
        long double acc = ratio, total = ratio;
        int power = 3;
        int n = 20;
        while (power < n) {
            acc *= ratio * ratio;
            total += (1 / (long double) power) * acc;
            power += 2;
        }
        return 2.0 * total;
    }
    double taylor_exp(double x, double eps) {
        double sum = 0, tmp = eps + 1;
        for (int i = 0; abs(tmp) > eps; ++i)
            sum += tmp = pow(x, i) / factorial(i);
        return sum;
    }


    void solve_problem1(double x) {
        cout << "\n\n----Задание 1:----\n";
        cout << "sin(x) Разложение в ряд: " << s1(x) << "\n";
        cout << "sin(x) Без переброса периода: " << s2(x) << "\n";
        cout << "sin(x) Отдельно числитель и знаменатель: " << taylor_sin(x, 10) << "\n";
        cout << "sin(x) Стандартная функция языка: " << sin(x) << "\n";
    }
    void solve_problem2(double x) {
        cout << "\n\n----Задание 2:----\n";
        int n = 10;
        double sin_x = taylor_sin(x, n), cos_x = taylor_cos(x, n);
        double sum_squares = sin_x * sin_x + cos_x * cos_x;
        cout << "sin^2(x) + cos^2(x) приближенно равно " << sum_squares << "\n";
    }
    void solve_problem3(double x) {
        cout << "\n\n----Задание 3:----\n";
        double a = 4;
        cout << "a = " << a << "\n";
        cout << "ln(a) Ряд Тейлора: " << taylor_log(a) << "\n";
        cout << "ln(a) Стандартная функция языка: " << log(a) << "\n";
        cout << "e^(x ln a) Ряд Тейлора: " << taylor_exp(x * log(a), 0.01) << "\n";
        cout << "e^(x ln a) Стандартная функция языка: " << exp(x * log(a)) << "\n";
        cout << "a^(x): " << pow(a, x) << "\n";
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    float x; cout << "Введите x: "; cin >> x; cout << x << "\n";
    Solution a;
    a.solve_problem1(x);
    a.solve_problem2(x);
    a.solve_problem3(x);
    
    
    return 0;
}