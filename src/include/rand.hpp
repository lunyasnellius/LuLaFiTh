#pragma once

#include <random>


struct random_var {
	std::mt19937 gen;
	std::uniform_real_distribution<double> dis;

	random_var() : gen(1), dis(-1.0,1.0) {}
	random_var(int seed) : gen(seed), dis(-1.0,1.0) {}

	double operator()() {
		return dis(gen);
	}

}; // end of rand



