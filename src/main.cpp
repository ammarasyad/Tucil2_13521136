#include <iostream>
#include <vector>
#include <chrono>
#include "point.h"
#include "rand.h"
#include "sort.h"
#include "plot.h"

using namespace std;

const int LEAF_SIZE = 64; // leaf size for divide and conquer, increase for more operations but slower, most optimal in my testing is 64

inline bool compareX(const Point& p1, const Point& p2, bool equals) {
    return equals ? p1.getCoordinate(0) <= p2.getCoordinate(0) : p1.getCoordinate(0) < p2.getCoordinate(0);
}

inline bool compareY(const Point& p1, const Point& p2, bool equals) {
    return equals ? p1.getCoordinate(1) <= p2.getCoordinate(1) : p1.getCoordinate(1) < p2.getCoordinate(1);
}

/**
 * @brief Brute force algorithm to find the closest pair of points
 * @param points
 * @return Closest pair of points
 */
Tuple<Point, Point> bruteForce(const vector<Point>& points) {
    double minDist = dist(points[0], points[1]);
    Point p1 = points[0];
    Point p2 = points[1];
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            double distIJ = dist(points[i], points[j]);
            if (distIJ < minDist) {
                minDist = distIJ;
                p1 = points[i];
                p2 = points[j];
            }
        }
    }
    return {p1, p2};
}

/**
 * @brief Helper function for DnC
 * @param points
 * @return Closest pair of points
 */
Tuple<Point, Point> divAndConHelper(vector<Point>& points) {
    if (points.size() <= LEAF_SIZE) {
        return bruteForce(points);
    }
    const int dim = points[0].getDimension();
    Point midPoint = points[points.size() / 2];
    vector<Point> pointsXL(points.begin(), points.begin() + points.size() / 2);
    vector<Point> pointsXR(points.begin() + points.size() / 2, points.end());

    auto [p1, p2] = divAndConHelper(pointsXL);
    auto [p3, p4] = divAndConHelper(pointsXR);

    double d1 = dist(p1, p2);
    double d2 = dist(p3, p4);
    double minDist;
    Point p5(dim), p6(dim);
    if (d1 < d2) {
        p5 = p1;
        p6 = p2;
        minDist = d1;
    } else {
        p5 = p3;
        p6 = p4;
        minDist = d2;
    }

    vector<Point> strip;
    for (const auto & point : points) {
        if (abs(point.getCoordinate(0) - midPoint.getCoordinate(0)) < minDist) {
            strip.push_back(point);
        }
    }

//    timsort(strip, compareY);
//    sort(strip.begin(), strip.end(), compareY);
    quickSort(strip, 0, strip.size() - 1, compareY);
    for (int i = 0; i < strip.size(); i++) {
        for (int j = i + 1; j < strip.size() && (strip[j].getCoordinate(1) - strip[i].getCoordinate(1)) < minDist; j++) {
            double distIJ = dist(strip[i], strip[j]);
            if (distIJ < minDist) {
                minDist = distIJ;
                p5 = strip[i];
                p6 = strip[j];
            }
        }
    }
    return {p5, p6};
}

/**
 * @brief Divide and conquer algorithm to find the closest pair of points
 * @param points
 * @return Closest pair of points
 */
Tuple<Point, Point> divideAndConquer(vector<Point>& points) {
    quickSort(points, 0, points.size() - 1, compareX);
//    timsort(points, compareX);
//    sort(points.begin(), points.end(), compareX);
    return divAndConHelper(points);
}

/**
 * @brief Driver function
 */
int main() {
    int n, dim;
    string input;
    cout << "Enter number of points (must be greater than or equal to 2): ";
    while (true) {
        getline(cin >> ws, input);
        if (strtol(input.c_str(), nullptr, 10) < 2) {
            cout << "Invalid input. Must be greater than or equal to 2: ";
            getline(cin >> ws, input);
        } else {
            break;
        }
    }
    n = stoi(input);

    cout << "Enter the dimension: ";
    while (true) {
        getline(cin >> ws, input);
        auto in = strtol(input.c_str(), nullptr, 10);
        if (in < 1 || in > 10) {
            cout << "Invalid input. Must be from 1 to 10 (inclusive): ";
            getline(cin >> ws, input);
        } else {
            break;
        }
    }
    dim = stoi(input);

    vector<Point> points(n, Point(dim));
    for (auto& p : points) {
        for (auto& c : p) {
            c = getRand();
        }
    }

    cout << "Dimension: " << points[0].getDimension() << endl;
    cout << "Number of points: " << points.size() << endl;

    cout << "--------------------------------------------" << endl;
    cout << "Brute force algorithm" << endl;
    cout << "--------------------------------------------" << endl;

    auto t1 = chrono::high_resolution_clock::now();
    auto [p1, p2] = bruteForce(points);
    auto t2 = chrono::high_resolution_clock::now();

    cout << "Number of operations: " << operations << endl;
    cout << "Closest pair of points: " << p1 << " and " << p2 << endl;
    cout << "Distance: " << dist(p1, p2) << endl;

    auto duration = chrono::duration<double, milli>(t2 - t1).count();
    cout << duration << " ms" << endl;

    cout << "--------------------------------------------" << endl;
    cout << "Divide and conquer algorithm" << endl;
    cout << "--------------------------------------------" << endl;

    operations = 0;

    t1 = chrono::high_resolution_clock::now();
    auto [p3, p4] = divideAndConquer(points);
    t2 = chrono::high_resolution_clock::now();

    cout << "Number of operations: " << operations << endl;
    cout << "Closest pair of points: " << p3 << " and " << p4 << endl;
    cout << "Distance: " << dist(p3, p4) << endl;

    duration = chrono::duration<double, milli>(t2 - t1).count();
    cout << duration << " ms" << endl;

    // Ask to save to file and plot
    if (dim == 3){
        cout << "Do you want to save the points to a file and plot them? (y/n): ";
        getline(cin >> ws, input);
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (input == "y" || input == "yes") {
            saveToFile("points.txt", points, p1, p2);
            startPlot("points.txt");
        } else if (input == "n" || input == "no") {
            cout << "Exiting..." << endl;
        } else {
            cout << "Invalid input. Exiting..." << endl;
        }
    }
    return 0;
}
