//
// Created by ammar on 2/26/23.
//

#ifndef TUCIL2_13521136_SORT_H
#define TUCIL2_13521136_SORT_H

#include <vector>
#include "point.h"

#define RUN 32

using namespace std;

inline double min(double a, double b) {
    return a < b ? a : b;
}

void swap(Point &a, Point &b) {
    Point temp = a;
    a = b;
    b = temp;
}

void insertionSort(vector<Point>& points, int left, int right, bool (*compare)(const Point&, const Point&)) {
    for (int i = left + 1; i <= right; i++) {
        const Point& temp = points[i];
        int j = i - 1;
        while (j >= left && compare(temp, points[j])) {
            points[j + 1] = points[j--];
        }
        points[j + 1] = temp;
    }
}

void merge(vector<Point>& points, int l, int m, int r, bool (*compare)(const Point&, const Point&)) {
    int left = m - l + 1;
    int right = r - m;
    vector<Point> L(left, Point(points[0].getDimension())), R(right, Point(points[0].getDimension()));
    for (int i = 0; i < left; i++) {
        L[i] = points.at(l + i);
    }
    for (int i = 0; i < right; i++) {
        R[i] = points[m + 1 + i];
    }
    int i = 0, j = 0, k = l;

    while (i < left && j < right) {
        if (L[i].getCoordinate(0) <= R[j].getCoordinate(0)) {
            points[k++] = L[i++];
        } else {
            points[k++] = R[j++];
        }
    }
    while (i < left) {
        points[k++] = L[i++];
    }
    while (j < right) {
        points[k++] = R[j++];
    }
}

// WHY DOES THIS NOT WORK IT WORKED ON MY PREVIOUS PROGRAMS
void timsort(vector<Point>& points, bool (*compare)(const Point&, const Point&)) {
    int n = points.size();
    for (int i = 0; i < n; i += RUN) {
        insertionSort(points, i, min((i + RUN - 1), (n - 1)), compare);
    }
    for (int size = RUN; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));
            if (mid < right) merge(points, left, mid, right, compare);
        }
    }
}

int partition(vector<Point>& points, int start, int end, bool (*compare)(const Point&, const Point&, bool)) {
    Point pivot = points[start];
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (compare(points[i], pivot, true)) {
            count++;
        }
    }

    int index = start + count;
    swap(points[start], points[index]);
    int i = start, j = end;

    while (i < index && j > index) {
        while (compare(points[i], pivot, true)) i++;
        while (compare(pivot, points[j], false)) j--;
        if (i < index && j > index) {
            swap(points[i++], points[j--]);
        }
    }
    return index;
}

void quickSort(vector<Point>& points, int start, int end, bool (*compare)(const Point&, const Point&, bool)) {
    if (start < end) {
        int p = partition(points, start, end, compare);
        quickSort(points, start, p - 1, compare);
        quickSort(points, p + 1, end, compare);
    }
}

#endif