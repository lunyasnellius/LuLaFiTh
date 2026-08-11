#pragma once

#include "include/core.hpp"
#include "include/functions.hpp"
#include "u1-field.hpp"

/* 
 * 2-dim plaquette computation at location (t,x) for u1 field gauge
 */
theta plaquette(int t, int x, u1_field & gauge) {
	theta tmp(gauge(t, x, T_DIR).val + gauge(t+1, x, X_DIR).val - gauge(t, x+1, T_DIR).val - gauge(t, x, X_DIR).val);
	return tmp;
}

/*
 * function calculating the u1-gauge action 
 * for coupling strength beta and u1 field gauge
 */
double u1_action(double beta, u1_field & gauge) {
	double sum = 0.0;
	for (int x=0; x<8; ++x) {
		for (int t=0; t<8; ++t) {
			sum -= real( plaquette(t, x, gauge) );
		}
	}
	return beta * sum / 2.0;
}

