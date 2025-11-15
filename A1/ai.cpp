#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

int main() {
    std::vector<std::vector<double>> circles(3, std::vector<double>(3));
    for (int i = 0; i < 3; i++) {
        std::cin >> circles[i][0] >> circles[i][1] >> circles[i][2];
    }
    int n = 1000000;
    double xMin = -1e9, xMax = 1e9, yMin = -1e9, yMax = 1e9;
    for (auto& c : circles) {
        xMin = std::max(xMin, c[0] - c[2]);
        xMax = std::min(xMax, c[0] + c[2]);
        yMin = std::max(yMin, c[1] - c[2]);
        yMax = std::min(yMax, c[1] + c[2]);
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> xDist(xMin, xMax);
    std::uniform_real_distribution<double> yDist(yMin, yMax);
    
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        double x = xDist(gen);
        double y = yDist(gen);
        bool flag = true;
        for (auto& c : circles) {
            double dx = x - c[0];
            double dy = y - c[1];
            if (dx * dx + dy * dy > c[2] * c[2]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            cnt++;
        }
    }
    
    double s = (1.0 * cnt / n) * ((xMax - xMin) * (yMax - yMin));
    std::cout << std::fixed;
    std::cout.precision(20);
    std::cout << s;
    return 0;
}