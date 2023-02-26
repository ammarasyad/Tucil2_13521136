#ifndef TUCIL2_13521136_POINT_H
#define TUCIL2_13521136_POINT_H

// 3D point

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

static long long operations;

// n-dimensional point
class Point {
public:
    explicit Point(int n) : dimension(n), coordinates(n, 0) {}
    Point(int n, const vector<double>& coordinates) : dimension(n), coordinates(coordinates) {}

    [[nodiscard]] int getDimension() const { return dimension; }
    [[nodiscard]] double getCoordinate(int i) const { return coordinates[i]; }
    [[nodiscard]] const vector<double>& getCoordinates() const { return coordinates; }

    Point operator+(const Point& p) const {
        vector<double> newCoordinates(dimension);
        for (int i = 0; i < dimension; i++) {
            newCoordinates[i] = coordinates[i] + p.coordinates[i];
        }
        return {dimension, newCoordinates};
    }

    Point operator-(const Point& p) const {
        vector<double> newCoordinates(dimension);
        for (int i = 0; i < dimension; i++) {
            newCoordinates[i] = coordinates[i] - p.coordinates[i];
        }
        return {dimension, newCoordinates};
    }

    explicit operator string() const {
        string result = "(";
        for (int i = 0; i < dimension; i++) {
            result += std::to_string(coordinates[i]);
            if (i < dimension - 1) {
                result += ", ";
            }
        }
        result += ")";
        return result;
    }

    friend ostream& operator<<(ostream& os, const Point& p) {
        os << (string) p;
        return os;
    }

    vector<double>::iterator begin() { return coordinates.begin(); }
    vector<double>::iterator end() { return coordinates.end(); }
    [[nodiscard]] vector<double>::const_iterator begin() const { return coordinates.begin(); }
    [[nodiscard]] vector<double>::const_iterator end() const { return coordinates.end(); }
private:
    int dimension;
    vector<double> coordinates;
};

// I want to use std::tuple, but I'm scared of breaking the rules :"
template <typename T1, typename T2>
class Tuple {
public:
    T1 first;
    T2 second;
};

inline double dist(const Point& p1, const Point& p2) {
    double result = 0;
    for (int i = 0; i < p1.getDimension(); i++) {
        result += pow(p1.getCoordinate(i) - p2.getCoordinate(i), 2);
    }
    operations++;
    return sqrt(result);
}

#endif
