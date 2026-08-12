#pragma once

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

	theta& operator=(theta other) {
		val = constrain(other.val);
		return *this;
	}

	theta& operator=(double other) {
		val = constrain(other);
		return *this;
	}


}; // end of theta


struct u1_field {
	// for an 8x8 lattice
	std::vector<theta> thetat;
	std::vector<theta> thetax;

	u1_field() : thetat(N_DIM*N_DIM,0.0), thetax(N_DIM*N_DIM,0.0) {}
	u1_field(double a_val, double b_val) : thetat(N_DIM*N_DIM,a_val), thetax(N_DIM*N_DIM,b_val) {}

	void randomize(int seed) {
		random_var random(seed);
		for (int i=0; i<(N_DIM*N_DIM); ++i) {
			thetat[i].val = random();
			thetax[i].val = random();
		}
	}


	theta & operator()(int t, int x, int mu) {
		int idx = N_DIM * periodic(t) + periodic(x);
		if (mu == 0) {
			return thetat[idx];
		} else {
			return thetax[idx];
		}
	}

	void print() {
		for (int i=0; i<N_DIM*N_DIM; ++i) {
			if (i%(N_DIM) == 0) std::cout << "\n";
			std::cout << "(" << thetat[i].val << "," << thetax[i].val << ")\t";
		}
		std::cout << "\n";
	}

}; // end of u1-field


