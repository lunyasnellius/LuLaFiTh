#pragma once 

#include "include/core.hpp"
#include "include/functions.hpp"
#include "u1-field.hpp"
// #include "p-field.hpp"
#include "u1-action.hpp"


/*
 * H = 1/2 * pi^2 + S_G
 */
double u1_hamilton(double beta, u1_field & gauge, u1_field & momenta) {
	double ham = 0.0;
	double tmp1(0.0);
	double tmp2(0.0);
	// calculate sum of all pi^2
	for (int x=0; x<8; ++x) {
		for (int t=0; t<8; ++t) {
			tmp1 = momenta(t,x,T_DIR).val * momenta(t,x,T_DIR).val;
			tmp2 = momenta(t,x,X_DIR).val * momenta(t,x,X_DIR).val;
			ham += tmp1 + tmp2;
		}
	}
	// factor 1/2 for kinetic part
	ham *= 0.5;
	// add gauge action
	ham += u1_action(beta, gauge);
	return ham;
}


