#include <cassert>
#include <iostream>
#include <vector>
#include "impl.cpp"

// Функция для ввода массива точек от пользователя
void inputPoints(std::vector<Point>& points) {
    int n;
    std::cout << "Введите количество точек: ";
    std::cin >> n;
    points.resize(n);

    for (int i = 0; i < n; ++i) {
        std::cout << "Введите координаты точки " << i + 1 << " - x,y: ";
        std::cin >> points[i].x >> points[i].y;
    }
}

// Консольное меню
void menu() {
    std::vector<Point> points;

    while (true) {
        std::cout << "\nВыберите операцию:\n";
        std::cout << "1. Ввести новые данные (точки)\n";
        std::cout << "2. Найти все тройки точек, лежащие на одной прямой\n";
        std::cout << "3. Найти точку с минимальной суммой расстояний до остальных точек\n";
        std::cout << "4. Найти треугольник с наименьшим периметром\n";
        std::cout << "0. Выйти\n";
        std::cout << "Ваш выбор: ";

        int choice;
        std::cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1:
                inputPoints(points);
                break;
            case 2: {
                if (points.empty()) {
                    std::cout << "Сначала введите точки (опция 1).\n";
                    break;
                }
                int** lineIndices;
                int lineCount = countLines(points.data(), points.size(), &lineIndices);
                std::cout << "Количество троек точек, лежащих на одной прямой: " << lineCount << std::endl;

                for (int i = 0; i < lineCount; ++i) {
                    std::cout << "Линия " << i + 1 << ": (" << lineIndices[i][0] << ", " << lineIndices[i][1] << ", " << lineIndices[i][2] << ")" << std::endl;
                    delete[] lineIndices[i];
                }
                delete[] lineIndices;
                break;
            }
            case 3: {
                if (points.empty()) {
                    std::cout << "Сначала введите точки (опция 1).\n";
                    break;
                }
                Point closestPoint = getClosestPoint(points.data(), points.size());
                std::cout << "Точка с минимальной суммой расстояний до остальных: (" << closestPoint.x << ", " << closestPoint.y << ")" << std::endl;
                break;
            }
            case 4: {
                if (points.empty()) {
                    std::cout << "Сначала введите точки (опция 1).\n";
                    break;
                }
                Triangle minTriangle({0, 0}, {0, 0}, {0, 0});
                double minPerimeter = getMinLengthTriangle(points.data(), points.size(), minTriangle);
                std::cout << "Треугольник с наименьшим периметром: ((" << minTriangle.p1.x << ", " << minTriangle.p1.y << "), ("
                          << minTriangle.p2.x << ", " << minTriangle.p2.y << "), ("
                          << minTriangle.p3.x << ", " << minTriangle.p3.y << ")) с периметром " << minPerimeter << std::endl;
                break;
            }
            default:
                std::cout << "Неверный выбор. Попробуйте еще раз.\n";
                break;
        }
    }
}

void testCountLines() {
    std::vector<Point> points = {{0, 0}, {1, 1}, {2, 2}, {0, 1}, {1, 2}, {2, 3}};
    int** indices = nullptr;
    int count = countLines(points.data(), points.size(), &indices);

    // Проверка количества троек точек, лежащих на одной прямой
    assert(count == 2);

    // Очистка выделенной памяти
    for (int i = 0; i < count; ++i) {
        delete[] indices[i];
    }
    delete[] indices;

    std::cout << "testCountLines passed.\n";
}

// Тесты для функции getClosestPoint
void testGetClosestPoint() {
    std::vector<Point> points = {{0, 0}, {1, 1}, {2, 2}, {0, 2}};
    Point closest = getClosestPoint(points.data(), points.size());

    // Ожидаемая точка с минимальной суммой расстояний до остальных
    assert(fabs(closest.x - 1) < 1e-6 && fabs(closest.y - 1) < 1e-6);

    std::cout << "testGetClosestPoint passed.\n";
}

// Тесты для функции getMinLengthTriangle
void testGetMinLengthTriangle() {
    std::vector<Point> points = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
    Triangle minTriangle({0, 0}, {0, 0}, {0, 0});
    double minPerimeter = getMinLengthTriangle(points.data(), points.size(), minTriangle);

    // Проверка периметра минимального треугольника
    assert(fabs(minPerimeter - (sqrt(2) + 2)) < 1e-6);

    std::cout << "testGetMinLengthTriangle passed.\n";
}

// Тесты для метода perimeter() класса Triangle
void testTrianglePerimeter() {
    Triangle triangle({0, 0}, {1, 0}, {0, 1});
    double perimeter = triangle.perimeter();

    // Ожидаемый периметр: sqrt(2) + 2
    assert(fabs(perimeter - (sqrt(2) + 2)) < 1e-6);

    std::cout << "testTrianglePerimeter passed.\n";
}

int runTests() {
    testCountLines();
    testGetClosestPoint();
    testGetMinLengthTriangle();
    testTrianglePerimeter();
    std::cout << "All tests passed.\n";
    return 0;
}


int main() {
    runTests();
    std::cout << "Запуск программы с консольным меню...\n";
    menu();

    return 0;
}
