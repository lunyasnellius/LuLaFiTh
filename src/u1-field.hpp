#pragma once
#include <cmath>
#include <array>
#include <numbers>

#include "include/core.hpp"
#include "include/rand.hpp"


struct theta {
	// theta values between -1 and 1
	double val;

	theta() {
		val = 0.0;
	}
	theta(double value) {
		val = constrain(value);
	}

	theta operator*(theta other) {
		val += other.val;
		return theta(val);
	}

}; // end of theta


struct u1_field {
	// for an 8x8 lattice
	std::array<theta,64> thetat;
	std::array<theta,64> thetax;

	u1_field() = default;
	u1_field(double a_val, double b_val) : thetat{a_val}, thetax{b_val} {
		for (int i=0; i<64;++i) {
			thetat[i].val = a_val;
			thetax[i].val = b_val;
		}
	}

	void randomize(int seed) {
		random_var random(seed);
		for (int i=0; i<64;++i) {
			thetat[i].val = random();
			thetax[i].val = random();
		}
	}


	theta operator()(int t, int x, int mu) {
		int idx = 8 * periodic(t) + periodic(x);
		if (mu == 0) {
			return thetat[idx];
		} else {
			return thetax[idx];
		}
	}

}; // end of u1-field


