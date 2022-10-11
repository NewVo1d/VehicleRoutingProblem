#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <iostream>
using namespace std;

/* Mathematical constants */
const double PI = acos(-1);
const double eps = 1e-8;
const double inf = 1e30;

/* Basic constants */
const int MAXN = 510;	// maximum number of customers
const int MAXV = 22;	// maximum number of vehicles
const int MAXC = 22;	// maximum number of companies
const int MAXP = 200;	// maximum population size

struct Point {
	double x, y;
};

struct Route {
	int nv;
	double load;
	double length;
	double profit;
	int v[MAXN];
};

struct Solution {
	double fairness;
	double length;
	int tour[MAXN];
	Route r[MAXV];
};

/* Instance parameters */
int n;	                // number of customers
int V;	                // number of vehicles
int C;	                // capacity
int nc;	                // number of companies
int company[MAXV];		// company of a vehicle
int vc[MAXC];
double cap[MAXV + 1];	// capacity of vehicles
double c[MAXN][MAXN];	// distance (cost) matrix
double d[MAXN];			// demand of customer
double reward[MAXN];	// reward
Point p[MAXN];			// coordinate of customers

double alpha = 1;
double beta = 1;
double gmin_length;
double gmin_fairness;

/* Algorithm parameters */
int POP_SIZE = 200;			// Population size
double Pr = 1.0;			// Recombination probability
double Pm = 0.05;           // Mutation probability
double Pls = 0.2;			// Local search probability
int ls_iter = 3000;			// Local search iteration
double T = 600;				// Execution time (second)
double tau = 0.5;			// Tournament size

double dist(Point &p1, Point &p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double angleBetween(Point &p1, Point &p2, Point &p0)
{
    double sin = (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);  
    double cos = (p1.x - p0.x) * (p2.x - p0.x) + (p1.y - p0.y) * (p2.y - p0.y);
    double ret = atan2(sin, cos) * (180 / PI);
    return (ret >= 0) ? ret : (ret + 360);
}

bool is_dominate(Solution &s1, Solution &s2)
{
	if ((int)(s1.length / 100000) < (int)(s2.length / 100000)) return true;
	if ((int)(s1.length / 100000) > (int)(s2.length / 100000)) return false;

	if (s1.fairness > s2.fairness + eps || s1.length > s2.length + eps) return false;
	return (s1.fairness + eps < s2.fairness || s1.length + eps < s2.length);
}

bool is_Same(Solution &s1, Solution &s2)
{
	return (fabs(s1.fairness - s2.fairness) < eps && fabs(s1.length - s2.length) < eps);
}

void calculate_route_load(Route &r)
{
	r.load = 0;
	for (int i = 1; i < r.nv; i++) {
		r.load += d[r.v[i]];
	}
}

void calculate_route_length(Route &r)
{
	r.length = 0;
	for (int i = 0; i < r.nv - 1; i++) {
		r.length += c[r.v[i]][r.v[i + 1]];
	}
	r.length += c[r.v[r.nv - 1]][0];
}

void calculate_route_profit(Route &r)
{
	r.profit = -beta * r.length;
	for (int i = 1; i < r.nv; i++) {
		r.profit += alpha * reward[r.v[i]];
	}
}

void calculate_solution_length(Solution &s)
{
	s.length = 0;
	for (int i = 0; i < V; i++)
		s.length += s.r[i].length;
	s.length += s.r[V].length * 100000;
}

void calculate_solution_fairness(Solution &s)
{
	int i;
	double pf[MAXC];
	for (i = 0; i < nc; i++)
		pf[i] = 0;
	for (i = 0; i < V; i++)
		pf[company[i]] += s.r[i].profit / vc[company[i]];

	double maxp = -1e10;
	for (i = 0; i < nc; i++) {
		if (-pf[i] > maxp) maxp = -pf[i];
	}

	// double maxp = -inf;
	// for (i = 0; i < nc; i++) {
	// 	if (pf[i] > maxp) maxp = pf[i];
	// }

	s.fairness = maxp;
}

void make_giant_tour(Solution &s)
{
	int k = 0;
	s.tour[k++] = 0;
	for (int i = 0; i <= V; i++)
	for (int j = 1; j < s.r[i].nv; j++)
		s.tour[k++] = s.r[i].v[j];
	s.tour[k] = 0;
}

double random(double x, double y)
{
	return (double)rand() / RAND_MAX * (y - x) + x;
}

#endif