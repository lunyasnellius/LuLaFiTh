#pragma once


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
	for (int x=0; x<N_DIM; ++x) {
		for (int t=0; t<N_DIM; ++t) {
			sum += (1.0 - real(plaquette(t, x, gauge)));
		}
	}
	return beta * sum;
}

/*
 * function calculating the force from the u1-gauge action
 * at lattice point (t,x) on link in direction mu
 * as a function of beta and the u1 field gauge
 */
double u1_force(double beta, u1_field & gauge, int t, int x, int mu) {
	if (mu == T_DIR) {
		return beta * (imag(plaquette(t, x, gauge)) + imag(theta(-1.0*plaquette(t, x-1, gauge).val)));
	} else {
		return beta * (imag(plaquette(t, x, gauge)) + imag(theta(-1.0*plaquette(t-1, x, gauge).val)));
	}
}




