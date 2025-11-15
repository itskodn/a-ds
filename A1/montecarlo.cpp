#include <iostream>
#include <fstream>
#include <random>
#include <cmath>
#include <vector>

using namespace std;
bool InIntersection(double x, double y, const vector<vector<double>>& circles) {
    for (const auto& c : circles) {
        double dx = x - c[0];
        double dy = y - c[1];
        if (dx * dx + dy * dy > c[2] * c[2]) {
            return false;
        }
    }
    return true;
}

double monteCarlo(int num_points, double xMin, double xMax, double yMin, double yMax, const vector<vector<double>>& circles) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> xDist(xMin, xMax);
    uniform_real_distribution<double> yDist(yMin, yMax);
    int points = 0;
    for (int i = 0; i < num_points; i++) {
        double x = xDist(gen);
        double y = yDist(gen);
        if (InIntersection(x, y, circles)) {
            points+=1;
        }
    }
    double area = (xMax - xMin) * (yMax - yMin);
    return (static_cast<double>(points) / num_points) * area;
}

int main() {
    vector<vector<double>> circles = {
        {1.0, 1.0, 1.0},
        {1.5, 2.0, sqrt(5.0) / 2.0},
        {2.0, 1.5, sqrt(5.0) / 2.0}
    };
    double exactArea = 0.25 * M_PI + 1.25 * asin(0.8) - 1;
    double wide_xmin = 1e9, wide_xmax = -1e9, wide_ymin = 1e9, wide_ymax = -1e9;
    double narrow_xmin = -1e9, narrow_xmax = 1e9, narrow_ymin = -1e9, narrow_ymax = 1e9;
    
    for (auto& c : circles) {
        wide_xmin = min(wide_xmin, c[0] - c[2]);
        wide_xmax = max(wide_xmax, c[0] + c[2]);
        wide_ymin = min(wide_ymin, c[1] - c[2]);
        wide_ymax = max(wide_ymax, c[1] + c[2]);
        narrow_xmin = max(narrow_xmin, c[0] - c[2]);
        narrow_xmax = min(narrow_xmax, c[0] + c[2]);
        narrow_ymin = max(narrow_ymin, c[1] - c[2]);
        narrow_ymax = min(narrow_ymax, c[1] + c[2]);
    }
    
    ofstream wideFile("wide.txt");
    ofstream narrowFile("narrow.txt");
    wideFile << "N Area RelativeError" << endl;
    narrowFile << "N Area RelativeError" << endl;
    for (int n = 100; n <= 100000; n += 500) {
        double wideArea = monteCarlo(n, wide_xmin, wide_xmax, wide_ymin, wide_ymax, circles);
        double wideError = abs(wideArea - exactArea) / exactArea;
        wideFile << n << " " << wideArea << " " << wideError << endl;
        
        double narrowArea = monteCarlo(n, narrow_xmin, narrow_xmax, narrow_ymin, narrow_ymax, circles);
        double narrowError = abs(narrowArea - exactArea) / exactArea;
        narrowFile << n << " " << narrowArea << " " << narrowError << endl;
    }
    
    wideFile.close();
    narrowFile.close();
    
    return 0;
}