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
		random_theta random(seed);
		for (int i=0; i<(N_DIM*N_DIM); ++i) {
			thetat[i] = random();
			thetax[i] = random();
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

	u1_field & operator=(u1_field & other) {
		for (int i=0; i<(N_DIM*N_DIM); ++i) {
			thetat[i] = other.thetat[i];
			thetax[i] = other.thetax[i];
		}
		return *this;
	}

	void print() {
		for (int i=0; i<N_DIM*N_DIM; ++i) {
			if (i%(N_DIM) == 0) std::cout << "\n";
			std::cout << "(" << thetat[i].val << "," << thetax[i].val << ")\t";
		}
		std::cout << "\n";
	}

	void print_file(std::string base_name, std::string metadata = "no metadata") {
		std::string pr_int = std::to_string(num_prints);
		if (num_prints < 10) pr_int = "0" + std::to_string(num_prints);

		// file name of the form "ensembles/NAME_#prints.csv"
		std::string name = "ensembles/" + base_name + "_" + pr_int + ".csv";

		// create folder, should it not exist yet
		if (!std::filesystem::exists("ensembles")) {
			std::filesystem::create_directory("ensembles");
		}

		int n=0;
		// modify filename to not overwrite already saved data
		while (std::filesystem::exists(name)) {
			name = "ensembles/" + base_name + "_" + pr_int + "_" +  std::to_string(n) + ".csv";
			++n;
		}

		std::fstream file(name, std::fstream::out | std::fstream::app);
		file << "# " << metadata << "\n";
		for (int i=0; i<N_DIM*N_DIM; ++i) {
			file << thetat[i].val << ", " << thetax[i].val;
			if (i%(N_DIM) != (N_DIM-1)) {
				file << ", ";
			} else {
				file << "\n";
			}
		}
		file.close();
		++num_prints;
	}

	private:
	static int num_prints;


}; // end of u1_field

int u1_field::num_prints = 0;


