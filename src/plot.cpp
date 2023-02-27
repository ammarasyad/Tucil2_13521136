//
// Created by ammar on 27/02/2023.
//

#include <fstream>
#include "plot.h"

/**
 * Saves the given points to a file
 * @param filename
 * @param points
 * @param p1
 * @param p2
 */
void saveToFile(const string& filename, const vector<Point>& points, const Point& p1, const Point& p2) {
    ofstream file(filename);
    for (const Point& point : points) {
        for (auto& coord : point) {
            file << coord << " ";
        }
        if (point == p1 || point == p2) {
            file << 1;
        } else {
            file << 0;
        }
        file << endl;
    }
    file.close();
}

/**
 * Starts plotting the points in the given file
 * @param file
 */
void startPlot(const string& file = "points.txt") {
    cout << "Plotting..." << endl;
    FILE* pipe = popen("gnuplot -persist", "w");
    if (!pipe) {
        throw runtime_error("Could not open pipe to GNUPlot");
    }
    fprintf(pipe, "set title \"Nearest Points\"\n");
    fprintf(pipe, "splot \"%s\" using 1:2:3:($4==1 ? $3 : 1/0) with points pointtype 7, \"%s\" using 1:2:3:($4==0 ? $3 : 1/0) with points pointtype 5 \n", file.c_str(), file.c_str());
    pclose(pipe);
    cout << "Plotting done!" << endl;
}