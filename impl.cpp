#include <vector>
#include <cmath>
#include <limits>


struct Point {
    double x, y;
};

class Triangle {
public:
    Point p1, p2, p3;

    Triangle(Point a, Point b, Point c) : p1(a), p2(b), p3(c) {}

    [[nodiscard]] double perimeter() const {
        return distance(p1, p2) + distance(p2, p3) + distance(p3, p1);
    }

private:
    static double distance(const Point& a, const Point& b) {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
};

// Функция для поиска всех троек точек, лежащих на одной прямой
int countLines(Point* points, int size, int*** indices) {
    if (size < 3) {
        *indices = nullptr;
        return 0;
    }

    int count = 0;
    std::vector<std::vector<int>> lines;

    for (int i = 0; i < size - 2; ++i) {
        for (int j = i + 1; j < size - 1; ++j) {
            for (int k = j + 1; k < size; ++k) {
                double dx1 = points[j].x - points[i].x;
                double dy1 = points[j].y - points[i].y;
                double dx2 = points[k].x - points[i].x;
                double dy2 = points[k].y - points[i].y;

                if (dx1 * dy2 == dy1 * dx2) {
                    lines.push_back({i, j, k});
                    count++;
                }
            }
        }
    }

    *indices = new int*[count];
    for (int i = 0; i < count; ++i) {
        (*indices)[i] = new int[3];
        for (int j = 0; j < 3; ++j) {
            (*indices)[i][j] = lines[i][j];
        }
    }

    return count;
}

// Функция для нахождения точки, которая имеет минимальную сумму расстояний до всех остальных точек
Point getClosestPoint(Point* points, int size) {
    if (size == 0) {
        return {0, 0};  // Возвращаем фиктивную точку, если массив пуст
    }

    double minDistanceSum = std::numeric_limits<double>::max();
    Point closestPoint = points[0];

    for (int i = 0; i < size; ++i) {
        double distanceSum = 0;

        for (int j = 0; j < size; ++j) {
            if (i != j) {
                distanceSum += sqrt(pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2));
            }
        }

        if (distanceSum < minDistanceSum) {
            minDistanceSum = distanceSum;
            closestPoint = points[i];
        }
    }

    return closestPoint;
}

// Функция для нахождения треугольника с минимальным периметром
double getMinLengthTriangle(Point* points, int size, Triangle& triangle) {
    if (size < 3) {
        return 0;  // Если точек меньше 3, возвращаем 0 как периметр
    }

    double minPerimeter = std::numeric_limits<double>::max();

    for (int i = 0; i < size - 2; ++i) {
        for (int j = i + 1; j < size - 1; ++j) {
            for (int k = j + 1; k < size; ++k) {
                Triangle temp(points[i], points[j], points[k]);
                double perimeter = temp.perimeter();

                if (perimeter < minPerimeter) {
                    minPerimeter = perimeter;
                    triangle = temp;
                }
            }
        }
    }

    return minPerimeter;
}