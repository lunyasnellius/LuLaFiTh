#pragma once

#include "include/core.hpp"
#include "include/rand.hpp"


struct momentum {
	// theta values between -1 and 1
	double val;

	momentum() {
		val = 0.0;
	}
	momentum(double value) {
		val = constrain(value);
	}

	// when multiplying momentum with a theta (u1 link) object
	// add together the angles
	theta operator*(theta other) {
		val += other.val;
		return theta(val);
	}

	// when multiplying with another momentum, 
	// just multiply the values
	momentum operator*(momentum other) {
		val *= other.val;
		return momentum(val);
	}

}; // end of theta


struct p_field {
	// for an 8x8 lattice
	std::array<momentum,64> momentumt;
	std::array<momentum,64> momentumx;

	p_field() = default;
	p_field(double a_val, double b_val) : momentumt{a_val}, momentumx{b_val} {
		for (int i=0; i<64;++i) {
			momentumt[i].val = a_val;
			momentumx[i].val = b_val;
		}
	}

	void randomize(int seed) {
		random_var random(seed);
		for (int i=0; i<64;++i) {
			momentumt[i].val = random();
			momentumx[i].val = random();
		}
	}


	momentum operator()(int t, int x, int mu) {
		int idx = 8 * periodic(t) + periodic(x);
		if (mu == 0) {
			return momentumt[idx];
		} else {
			return momentumx[idx];
		}
	}

}; // end of p-field


