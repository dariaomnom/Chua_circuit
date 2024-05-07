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
const double h = 0.0005;

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

    int num_points = 600;

    std::ifstream file("../start.txt"); // Откройте файл для чтения
    if (!file) {
        std::cout << "Unable to open file" << std::endl;
        return 1;
    }
    // Создаем двумерный статический массив
    double start_points[num_points][3];
    double original_points[num_points][3];
    double k[num_points][4][3];
    // Считываем координаты точек из файла
    int i = 0;
    std::string line;
    while (std::getline(file, line) && i < num_points) {
        std::istringstream iss(line);
        iss >> start_points[i][0] >> start_points[i][1] >> start_points[i][2];
        iss >> original_points[i][0] >> original_points[i][1] >> original_points[i][2];
//        std::cout << start_points[i][0] << " " << start_points[i][1] << std::endl;
        i++;
    }
    file.close();





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



    std::ofstream outputFile("../data3d.txt");


//    for (double t = 0; t < T; t += h) {
//        outputFile << std::fixed << std::setprecision(16) << X[0] << " " << X[1]  << " " << X[2] << std::endl;
//        RK4(X, X_tmp, k1, k2, k3, k4);
//    }
//    return 0;












        // Создание окна
        const unsigned int windowWidth = 800;
        const unsigned int windowHeight = 800;
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Attractor");

//        sf::RenderWindow window(sf::VideoMode(800, 600), "3D Animation");



        // Создаем точку
//        sf::CircleShape point(0.3f); // Радиус точки
//        point.setFillColor(sf::Color::Red); // Цвет точки



//        для много точек
//        std::vector<sf::Vector2f> points;
//        points.reserve(num_points);
//        for (int i = 0; i < num_points; ++i)
//        {
//            points.emplace_back(start_points[i][0], start_points[i][1]);
//        }

//        sf::VertexArray vertices(sf::Points, points.size());
//        for (std::size_t i = 0; i < points.size(); ++i)
//            vertices[i] = sf::Vertex(points[i], sf::Color::White);

//        для много точек


// было изначально
        // Предположим, что у вас есть вектор координат
//        std::vector<sf::Vector2f> coordinates = {
//                sf::Vector2f(X[0], X[1]),
////                sf::Vector2f(1.0f, 1.0f),
////                sf::Vector2f(2.0f, 2.0f),
//                // Добавьте больше координат по мере необходимости
//        };

//        sf::CircleShape points[1] = {point};
//        sf::CircleShape points[num_points];



        // Создание sf::VertexArray для хранения точек
//        sf::VertexArray points(sf::Points, coordinates.size()); // Предполагается, что у вас 10000 точек

        // Заполнение sf::VertexArray координатами
//        for (size_t i = 0; i < coordinates.size(); ++i) {
//            points[i].position = coordinates[i];
//        }




        // Настраиваем область отображения
//        const float viewLeft = -3.f;
//        const float viewRight = 6.f;
//        const float viewBottom = -3.f * (static_cast<float>(windowHeight) / windowWidth);
//        const float viewTop = viewRight * (static_cast<float>(windowHeight) / windowWidth);
//        sf::View view(sf::FloatRect(viewLeft, viewBottom, viewRight - viewLeft, viewTop - viewBottom));
//        window.setView(view);



        sf::View view(sf::FloatRect(-6.f, -6.f, 12.f, 12.f));
        view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
        window.setView(view);

        std::vector<sf::Vector2f> coordinates;
        for (int i = 0; i < num_points; ++i) { // Adjust the size as needed
            coordinates.push_back(sf::Vector2f(start_points[i][0], start_points[i][1]));
        }




        // Создаем объект Clock для отслеживания времени
        sf::Clock clock;

        // Устанавливаем желаемый интервал между кадрами (в миллисекундах)
        const float desiredFrameTime = 50.0f; // 100 мс = 10 кадров в секунду



    // Главный цикл

        double t = 0;
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }


            // Отслеживаем время, прошедшее с последнего кадра
            sf::Time elapsed = clock.restart();

            // Если время, прошедшее с последнего кадра, меньше желаемого интервала, ждем
            if (elapsed.asMilliseconds() < desiredFrameTime)
                sf::sleep(sf::milliseconds(desiredFrameTime - elapsed.asMilliseconds()));


            // Очистка экрана
            window.clear();

            if (t < T) {
                for (int i = 0; i < num_points; i++) {


//                coordinates[i].x = start_points[i][0];
//                coordinates[i].y = start_points[i][1];
//                points[i].setPosition(coordinates[i]);

//                RK4(X, X_tmp, k1, k2, k3, k4);
                    RK4(start_points[i], X_tmp, k[i][0], k[i][1], k[i][2], k[i][3]);
//                    t += h;


                    coordinates[i].x = start_points[i][0];
                    coordinates[i].y = start_points[i][1];
//                points[i].setPosition(coordinates[i]);

                    sf::CircleShape point_new(0.020f);
//                    sf::CircleShape point_new(coordinates[i].x,
//                                              coordinates[i].y); // Create a new point shape for each coordinate
                    point_new.setPosition(coordinates[i]);
//                    if (original_points[i][0] < 0 && original_points[i][1] <= 0) {
//                        point_new.setFillColor(sf::Color::Red);
//                    } else if (original_points[i][0] <= 0 && original_points[i][1] > 0) {
//                        point_new.setFillColor(sf::Color::Green);
//                    } else if (original_points[i][0] <= 0 && original_points[i][1] <= 0) {
//                        point_new.setFillColor(sf::Color::Yellow);
//                    } else if (original_points[i][0] > 0 && original_points[i][1] > 0) {
//                        point_new.setFillColor(sf::Color::Blue);
//                    } else {
                        point_new.setFillColor(sf::Color::Magenta);
//                    }

                    window.draw(point_new);
//                    std::cout << point_new.getPosition().x << "   ";
//                    std::cout << point_new.getPosition().y << std::endl;
                }
                t += h;
            } else {
                break;
            }

            // Draw each point
//            for (const auto& coord : coordinates) {
//                sf::CircleShape point_new(coord.x, coord.y); // Create a new point shape for each coordinate
//                point_new.setFillColor(sf::Color::Red); // Set the color
//                window.draw(point_new);
//            }

            // Рендеринг точек
//            for (int i = 0; i < 1; i++) {
//                window.draw(points[i]);
//            }


            // Обновление окна
            window.display();


//            // Обновление координат точек
//            // Здесь должен быть ваш код для обновления координат точек
//            // Например:
////            for (int i = 0; i < points.getVertexCount(); ++i)
//            for (int i = 0; i < coordinates.size(); ++i)
//            {
//                for (double t = 0; t < T; t += h) {
//                    outputFile << std::fixed << std::setprecision(16) << X[0] << " " << X[1]  << " " << X[2] << std::endl;
////                    for (int c = 0; c < 3; c++) {
////                        coordinates[i][c] = X[c];
////                    }
//                    coordinates[i].x = X[0];
//                    coordinates[i].y = X[1];
////                    coordinates[i].z = X[2];
////                    points[i].position = coordinates[i];
//                    points[i].setPosition(coordinates[i]);
//
////                    points[i].position = sf::Vector3f(X[0], X[1], X[2]);
//                    RK4(X, X_tmp, k1, k2, k3, k4);
//                }
//                // Обновление координат вершины i
//                // points[i].position = newCoordinates; // Предполагается, что newCoordinates - это ваша новая координата
//            }
////            for (double t = 0; t < T; t += h) {
////                outputFile << std::fixed << std::setprecision(16) << X[0] << " " << X[1]  << " " << X[2] << std::endl;
////                points[0].position = sf::Vector3f(X[0], X[1], X[2]);
////                RK4(X, X_tmp, k1, k2, k3, k4);
////            }


////            std::cout << points[0].position.x << std::endl;
//            if (t < T) {
//                std::cout << points[0].getPosition().x << "   ";
//                std::cout << points[0].getPosition().y << std::endl;
//            }
//            // Рендеринг точек
////            window.draw(points);
//            for (int i = 0; i < 1; i++) {
//                window.draw(points[i]);
//            }
//
//            // Обновление окна
//            window.display();
//            std::cout << "_________" << std::endl;
        }

}
