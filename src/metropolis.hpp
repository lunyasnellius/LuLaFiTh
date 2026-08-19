#pragma once

double acc_rate(double H_start, double H_end) {
	double tmp = H_end - H_start;
	if (tmp <= 0.0) {
		return 1.0;
	} else {
		return std::exp(-1.0 * tmp);
	}
}

bool acc_ensemble(double ac_rate, int seed = 1) {
	random_uniform random(seed);
	double comp = random();
	if (comp < ac_rate) {
		return true;
	} else {
		return false;
	}
}




