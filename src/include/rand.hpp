#pragma once

#include <random>


struct random_theta {
	std::mt19937 gen;
	//std::uniform_real_distribution<double> dis;
	std::normal_distribution<double> dis;

	random_theta() : gen(1), dis(0.0,0.5) {}//dis(-1.0,1.0) {}
	random_theta(int seed) : gen(seed), dis(0.0,0.5) {}//dis(-1.0,1.0) {}

	double operator()() {
		return dis(gen);
	}

}; // end of random_theta

struct random_uniform {
	//std::random_device rd{};
	std::mt19937 gen;
	std::uniform_real_distribution<double> dis;

	random_uniform() : gen(1), dis(0.0,1.0) {}
	random_uniform(int seed) : gen(seed), dis(0.0,1.0) {}

	double operator()() {
		return dis(gen);
	}

}; // end of random_uniform



