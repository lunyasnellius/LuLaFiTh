#pragma once


double u1_loop(u1_field & gauge) {
	double sum = 0.0;
	for (int x=0; x<N_DIM; ++x) {
		for (int t=0; t<N_DIM; ++t) {
			sum += real(plaquette(t, x, gauge));
		}
	}
	return sum;
}
