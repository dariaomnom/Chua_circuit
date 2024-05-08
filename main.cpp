#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
//#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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
const double h = 0.01;

class RenderWindow;

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

    int num_points = 700;

    std::ifstream file("../start.txt"); // Откройте файл для чтения
    if (!file) {
        std::cout << "Unable to open file" << std::endl;
        return 1;
    }

    double start_points[num_points][3];
    double original_points[num_points][3];
    double k[num_points][4][3];

    int i = 0;
    std::string line;
    while (std::getline(file, line) && i < num_points) {
        std::istringstream iss(line);
        iss >> start_points[i][0] >> start_points[i][1] >> start_points[i][2];
        for (int i = 0; i < num_points; i++) {
            for (int j = 0; j < 3; j++) {
                original_points[i][j] = start_points[i][j];
            }
        }

//        if (i <= 10) {
//            std::cout << start_points[i][0] << " " << start_points[i][1] << std::endl;
//            std::cout << original_points[i][0] << " " << original_points[i][1] << std::endl;
//        }
        i++;
    }
    file.close();


//          Для создания графика в gnuplot
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


//          Для создания графика в gnuplot
    std::ofstream outputFile("../data3d.txt");
    for (double t = 0; t < T; t += h) {
        outputFile << std::fixed << std::setprecision(16) << X[0] << " " << X[1]  << " " << X[2] << std::endl;
        RK4(X, X_tmp, k1, k2, k3, k4);
    }
//    return 0;



        const unsigned int windowWidth = 800;
        const unsigned int windowHeight = 800;
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Attractor");
        sf::View view(sf::FloatRect(-5.f, -5.f, 10.f, 10.f));
//        sf::View view(sf::FloatRect(-25.f, -25.f, 50.f, 50.f));
        view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
        window.setView(view);

        std::vector<sf::Vector2f> coordinates;
        for (int i = 0; i < num_points; ++i) {
            coordinates.push_back(sf::Vector2f(start_points[i][0], start_points[i][1]));
        }

        sf::Clock clock;
        const float desiredFrameTime = 5.0f; // 100 мс = 10 кадров в секунду


        double t = 0;
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            sf::Time elapsed = clock.restart();
            if (elapsed.asMilliseconds() < desiredFrameTime)
                sf::sleep(sf::milliseconds(desiredFrameTime - elapsed.asMilliseconds()));

            window.clear();

            if (t < T) {
                for (int i = 0; i < num_points; i++) {

//                    RK4(start_points[i], X_tmp, k[i][0], k[i][1], k[i][2], k[i][3]);

                    coordinates[i].x = start_points[i][0];
                    coordinates[i].y = start_points[i][1];

                    sf::CircleShape point_new(0.025f);
//                    sf::CircleShape point_new(0.20f);

                    point_new.setPosition(coordinates[i]);
                    if (original_points[i][0] < 0 && original_points[i][1] <= 0) {
                        point_new.setFillColor(sf::Color::Red);
                    } else if (original_points[i][0] < 0 && original_points[i][1] > 0) {
                        point_new.setFillColor(sf::Color::Green);
                    } else if (original_points[i][0] >= 0 && original_points[i][1] <= 0) {
                        point_new.setFillColor(sf::Color::Yellow);
                    } else if (original_points[i][0] >= 0 && original_points[i][1] > 0) {
                        point_new.setFillColor(sf::Color::Blue);
                    }
                    else {
                        point_new.setFillColor(sf::Color::Magenta);
                    }

                    window.draw(point_new);
//                    std::cout << point_new.getPosition().x << "   ";
//                    std::cout << point_new.getPosition().y << std::endl;
                    RK4(start_points[i], X_tmp, k[i][0], k[i][1], k[i][2], k[i][3]);
                }
                t += h;
            } else {
//                break;
                for (int j = 0; j < num_points; j++) {
                    start_points[j][0] = original_points[j][0];
                    start_points[j][1] = original_points[j][1];
                    t = 0;
                }
            }


            window.display();

        }

}
