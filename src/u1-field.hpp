#pragma once
#include <cmath>


struct u1-field {
	double thetat[64];
	double thetax[64];
	
	double operator()(int t, int x, int mu) {
		int idx = 8 * t + x;
		if (mu == 0) { return thetat[idx]; }
		else { return thetax[idx]; }
	}

}; // end of u1-field


double u1-action(double beta, u1-field & gauge) {
	double tmp = 0.0;
	for (int x=0; x<8; ++x) 
	for (int t=0; t<8; ++t)
		tmp += std::cos(gauge())


}

