//
// Created by ammar on 27/02/2023.
//

#ifndef TUCIL2_13521136_PLOT_H
#define TUCIL2_13521136_PLOT_H

#include <string>
#include <vector>
#include "point.h"

void saveToFile(const string& filename, const vector<Point>& points, const Point& p1, const Point& p2);
void startPlot(const string& file);

#endif
