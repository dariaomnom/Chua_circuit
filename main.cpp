#include <iostream>
#include <fstream>
#include <iomanip>

const double C1 = 1.0 / 9.0;
const double C2 = 1.0;
const double L = 1.0 / 7.0;
const double G = 0.7;
const double Ga = -0.8;
const double Gb = -0.5;

const double m0 = Ga / G;
const double m1 = Gb / G;
const double a = C2 / C1;
const double b = C2 / (G * G * L);

const double T = 100.0;
const double h = 0.001;

double H(double x) {
    return m1 * x + ((m0 - m1) / 2) * (fabs(x + 1) - fabs(x - 1));
}

void f_Chua(double* X, double* dX) {
    dX[0] = a * (X[1] - X[0] - H(X[0]));
    dX[1] = X[0] - X[1] + X[2];
    dX[2] = -b * X[1];
}

void RK4(double* X, double* X_tmp, double* k1, double* k2, double* k3, double* k4) {
    f_Chua(X, k1);
    for (int i = 0; i < 3; i++) {
        X_tmp[i] = X[i] + h * 0.5 * k1[i];
    }

    f_Chua(X_tmp, k2);
    for (int i = 0; i < 3; i++) {
        X_tmp[i] = X[i] + h * 0.5 * k2[i];
    }

    f_Chua(X_tmp, k3);
    for (int i = 0; i < 3; i++) {
        X_tmp[i] = X[i] + h * 1 * k3[i];
    }

    f_Chua(X_tmp, k4);
    for (int i = 0; i < 3; i++) {
        X[i] += h * (1.0 / 6.0 * k1[i] + 1.0 / 3.0 * k2[i] + 1.0 / 3.0 * k3[i] + 1.0 / 6.0 * k4[i]);
    }
}

int main() {
// Для стандарта C++11 и новее:
    double X[3] {-1.0, 1.0, 1.0};
    double X_tmp[3] {};
    double k1[3] {}, k2[3] {}, k3[3], k4[3] {};

// Если предыдущий вариант вызывает ошибки:
//    double X[3];
//    double X_tmp[3];
//    X[0] = -1.0;
//    X[1] = 1.0;
//    X[2] = 1.0;
//    double k1[3];
//    double k2[3];
//    double k3[3];
//    double k4[3];

    std::ofstream outputFile("data3d.txt");

    for (double t = 0; t < T; t += h) {
        outputFile << std::fixed << std::setprecision(16) << X[0] << " " << X[1]  << " " << X[2] << std::endl;
        RK4(X, X_tmp, k1, k2, k3, k4);
    }
}
