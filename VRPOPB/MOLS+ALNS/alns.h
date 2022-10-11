#ifndef ALNS_H
#define ALNS_H

#include <algorithm>
#include "utility.h"

double randomProbability, worstProbability;

void randomDestory(Solution s, Solution &ss, int collect[], int &nc) {
	for (int i = 0; i <= V; i++) {
		ss.r[i].nv = 1;
		ss.r[i].v[0] = 0;
		for (int j = 1; j < s.r[i].nv; j++) {
			if (random(0,1) > 0.1) // greater than removal rate
				ss.r[i].v[ss.r[i].nv++] = s.r[i].v[j];
			else collect[nc++] = s.r[i].v[j];
		}
		ss.r[i].v[ss.r[i].nv] = 0;
		calculate_route_load(ss.r[i]);
		calculate_route_length(ss.r[i]);
		calculate_route_profit(ss.r[i]);
	}
}


void worstDestory(Solution s, Solution &ss, int collect[], int &nc) {
	for (int i = 0; i <= V; i++) {

		int index = -1;
		double worstReward = inf;
		for(int j = 1;j < s.r[i].nv;j ++) {
			if(reward[s.r[i].v[j]] < worstReward) {
				index = j;
				worstReward = reward[s.r[i].v[j]];
			}
		}

		ss.r[i].nv = 1;
		ss.r[i].v[0] = 0;
		for (int j = 1; j < s.r[i].nv; j++) {
			if(j == index) {
				collect[nc++] = s.r[i].v[j];
			}else {
				ss.r[i].v[ss.r[i].nv++] = s.r[i].v[j];		
			}
		}
		ss.r[i].v[ss.r[i].nv] = 0;
		calculate_route_load(ss.r[i]);
		calculate_route_length(ss.r[i]);
		calculate_route_profit(ss.r[i]);
	}
}

void repair(Solution &ss, int collect[], int &nc) {
	// repair process
	random_shuffle(collect, collect + nc);
	for (int i = 0; i < nc; i++) {
		double minr = 1e10;
		int jj, kk;
		for (int j = 0; j < V; j++)
		if (ss.r[j].load + d[collect[i]] <= C + 1e-5) {
			for (int k = 0; k < ss.r[j].nv; k++) {
				double regret = c[ss.r[j].v[k]][collect[i]] + c[collect[i]][ss.r[j].v[k + 1]]
					- c[ss.r[j].v[k]][ss.r[j].v[k + 1]];
				if (regret < minr) {
					minr = regret;
					jj = j;
					kk = k;
				}
			}
		}
		if (minr < 1e10) {
			for (int k = ss.r[jj].nv; k > kk; k--)
				ss.r[jj].v[k + 1] = ss.r[jj].v[k];
			ss.r[jj].v[kk + 1] = collect[i];
			ss.r[jj].nv++;
			calculate_route_load(ss.r[jj]);
			calculate_route_length(ss.r[jj]);
			calculate_route_profit(ss.r[jj]);
		} else {
			// cannot assign
			ss.r[V].v[ss.r[V].nv++] = collect[i];
			ss.r[V].v[ss.r[V].nv] = 0;
			calculate_route_load(ss.r[V]);
			calculate_route_length(ss.r[V]);
			calculate_route_profit(ss.r[V]);
		}
	}

	calculate_solution_length(ss);
	calculate_solution_fairness(ss);
}


void ALNS_operator(Solution &s) {

	int nc = 0;
	int collect[n];
	Solution ss;
	
	double probability = random(0,1);
	if(probability > (randomProbability / (randomProbability + worstProbability))) {
		randomDestory(s, ss, collect, nc);
	}else {
		worstDestory(s, ss, collect, nc);
	}

	repair(ss, collect, nc);
	
	if (is_dominate(ss, s)) {
		s = ss;
		make_giant_tour(s);

		if(probability > (randomProbability / (randomProbability + worstProbability))) {
			randomProbability ++;
		}else {
			worstProbability ++;
		}
	}
}

void ALNS(Solution &s)
{
	randomProbability = worstProbability = 1;
	for (int i = 0; i < 100; i++) {
		ALNS_operator(s);
	}
}

#endif