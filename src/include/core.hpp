#pragma once
#include <numbers>
#include <complex>
#include <random>
#include <cmath>
#include <array>
#include <vector>
#include <numbers>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

constexpr int N_DIM = 4;

double pi_val = std::numbers::pi_v<double>;

enum dir {
	T_DIR = 0,
	X_DIR = 1
};


double constrain(double angle) {
	double tmp = angle;
	if (angle >= 1.0) {
		while (tmp >= 1.0) tmp -= 2.0;
		return tmp;
	} else if (angle < -1.0) {
		while (tmp < -1.0) tmp += 2.0;
		return tmp;
	} else {
		return tmp;
	}
}

int periodic(int index) {
	if (index < 0) {
		return N_DIM + index;
	} else if (index > N_DIM - 1) {
		return index - N_DIM;
	} else {
		return index;
	}
}


