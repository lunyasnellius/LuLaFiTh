#pragma once
#include <cmath>
#include <array>
#include <numbers>


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

struct theta {
	// theta values between -1 and 1
	double val;

	theta(double value) {
		val = constrain(value);
	}

	double operator*(theta other) {
		return constrain(val + other);
	}

}; // end of theta

int periodic(int index) {
	if (t < 0) {
		return 8 + index;
	} else if (t > 7) {
		return index - 8;
	} else {
		return index;
	}
}

double real(theta link) {
	return std::cos(std::numbers::pi_v<double> * link.val);
}

double imag(theta link) {
	return std::sin(std::numbers::pi_v<double> * link.val);
}

double dag(theta link) {
	return (-1.0 * link.val);
}

struct u1-field {
	// for an 8x8 lattice
	std::array<theta> thetat(64);
	std::array<theta> thetax(64);

	double operator()(int t, int x, int mu) {
		int idx = 8 * periodic(t) + periodic(x);
		if (mu == 0) {
			return thetat[idx];
		} else {
			return thetax[idx];
		}
	}

}; // end of u1-field

enum dir {
	T_DIR = 0,
	X_DIR = 1
}; 

double u1-action(double beta, u1-field & gauge) {
	double sum = 0.0;
	for (int x=0; x<8; ++x) 
	for (int t=0; t<8; ++t)
		sum -= real(gauge(t, x, T_DIR)    *     gauge(t+1, x, X_DIR) * 
			dag(gauge(t, x+1, T_DIR)) * dag(gauge(t, x, X_DIR)));

	return beta * sum / 2.0;
}

