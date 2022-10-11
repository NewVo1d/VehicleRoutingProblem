#ifndef IGD_H
#define IGD_H

#include <cmath>
#include "file.h"
using namespace std;

double caculatedis(double x1, double y1, double x2, double y2) {
    if(x1 == x2 && y1 == y2) {
        return 0x3f3f3f3f;
    }
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

void igd(string filename) 
{
    double igd1, igd2, igd3, igd4;
    igd1 = igd2 = igd3 = igd4 = 0.0;

    for(Point point1 : points1) {
        
        double mindis = 0x3f3f3f3f;
        for(Point point : points) {
            double dis = caculatedis(point.x, point.y, point1.x, point1.y);
            mindis = mindis>dis?dis:mindis;
        }

        igd1 += mindis;
    }
    igd1 /= points.size();

    for(Point point2 : points2) {
        
        double mindis = 0x3f3f3f3f;
        for(Point point : points) {
            double dis = caculatedis(point.x, point.y, point2.x, point2.y);
            mindis = mindis>dis?dis:mindis;
        }

        igd2 += mindis;
    }
    igd2 /= points.size();

    for(Point point3 : points3) {
        
        double mindis = 0x3f3f3f3f;
        for(Point point : points) {
            double dis = caculatedis(point.x, point.y, point3.x, point3.y);
            mindis = mindis>dis?dis:mindis;
        }

        igd3 += mindis;
    }
    igd3 /= points.size();

    for(Point point4 : points4) {
        
        double mindis = 0x3f3f3f3f;
        for(Point point : points) {
            double dis = caculatedis(point.x, point.y, point4.x, point4.y);
            mindis = mindis>dis?dis:mindis;
        }

        igd4 += mindis;
    }
    igd4 /= points.size();

    ofstream outfile;
	outfile.open("data\\analysis\\igd\\" + filename, ios::out);

    outfile << igd1 << endl;
    outfile << igd2 << endl;
    outfile << igd3 << endl;
    outfile << igd4 << endl;

    outfile.close();
}

#endif