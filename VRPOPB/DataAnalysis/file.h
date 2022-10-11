#ifndef FILE_H
#define FILE_H

#include <vector>
#include <fstream>
using namespace std;

struct Point {
    double x, y;
};

double maxX, maxY;
vector<Point> points;
vector<Point> points1;
vector<Point> points2;
vector<Point> points3;
vector<Point> points4;

bool isHere(double x, double y) {
    for(Point point : points) {
        if(x == point.x && y == point.y) {
            return true;
        }
    }
    return false;
}

void readData(string filename) {

    int n;
    double x, y, t;
    maxX = -1;
    maxY = -1;
    points.clear();
    points1.clear();
    points2.clear();
    points3.clear();
    points4.clear();

    ifstream infile;
	infile.open("data\\mols\\" + filename, ios::in);
    infile >> t >> n;
    for(int i = 0;i < n;i ++) {
        infile >> x >> y;
        if(!isHere(x, y)) {
            Point point;
            point.x = x;
            point.y = y;
            points.push_back(point);
            points1.push_back(point);
        }
    }
    infile.close();

    infile.open("data\\dcd\\" + filename, ios::in);
    infile >> t >> n;
    for(int i = 0;i < n;i ++) {
        infile >> x >> y;
        if(!isHere(x, y)) {
            Point point;
            point.x = x;
            point.y = y;
            points.push_back(point);
            points2.push_back(point);
        }
    }
    infile.close();

    infile.open("data\\alns\\" + filename, ios::in);
    infile >> t >> n;
    for(int i = 0;i < n;i ++) {
        infile >> x >> y;
        if(!isHere(x, y)) {
            Point point;
            point.x = x;
            point.y = y;
            points.push_back(point);
            points3.push_back(point);
        }
    }
    infile.close();

    infile.open("data\\mols+\\" + filename, ios::in);
    infile >> t >> n;
    for(int i = 0;i < n;i ++) {
        infile >> x >> y;
        if(!isHere(x, y)) {
            Point point;
            point.x = x;
            point.y = y;
            points.push_back(point);
            points4.push_back(point);
        }
    }
    infile.close();

    for(Point point : points) {
        maxX = maxX<point.x?point.x:maxX;
        maxY = maxY<point.y?point.y:maxY;
    }

    // for(Point point : points) {
    //     cout << point.x << " " << point.y << endl;
    // }
}

#endif